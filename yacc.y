%{
#include "node.h"
#include "constant_folding.h"
#include "constant_propagation.h"
#include "dead_code_elimination.h"
#include "common_subexpression_elimination.h"
#include "optimization_safety.h"
#include "pass_selector.h"
#include "optimization_report.h"
#include "optimization_effectiveness.h"
#include <cctype>
#include <errno.h>
#include <limits.h>
#define START_ADDRESS 100

int yylex(void);
extern FILE *yyin;
void yyerror(string str);
int nextquad = START_ADDRESS;
char code[100][50];
int var1;
int *var2;

int available_reg;
node *tree_pointer;

stack<string> reg_stack;
int memory_location_num = 0;
%}

%union
{
	char id[32];
	node *eval;
}

%token <id> LETTER INTEGER FLOAT
%token IF ELSE WHILE
%type <eval> PROGRAM BODY ASSIGN STMTS COND LVALUE E M N IF_ELSE OPEN_STMT CLOSED_STMT

%left '|'
%left '&'
%left '!'
%left '<' '>'
%left '+' '-'
%left '*' '/'
%left '(' ')'

%right '='

%start PROGRAM

%%

PROGRAM : STMTS	{ 
					int i;
					dce_finalize();
					optimization_effectiveness_finalize(START_ADDRESS, nextquad, code);
					pass_selector_report();
					optimization_report_print();
					optimization_effectiveness_print_stats();
					Backpatch($1->next,nextquad);
					dce_emit_surviving_register_code();
					printf("3 address code : \n");
					for(i=START_ADDRESS;i<nextquad;i++){
						if(!dead_code_elimination_is_enabled() || code[i-START_ADDRESS][0]!='\0')
							printf("\n%s",code[i-START_ADDRESS]);
					}
					printf("\n%d\n",nextquad);
				}
				;
				
BODY : IF_ELSE {}
	  | WHILE_CONTROL M '(' COND ')' M BODY {
				      $$=create_node();
				      Backpatch($7->next,$2->quad);
				      Backpatch($4->True,$6->quad);
				      $$->next=$4->False;
				      optimization_effectiveness_record_jump();
				      sprintf(code[nextquad-START_ADDRESS],"%d\tgoto %d",nextquad,$2->quad);
				      Gen();
				      clear_constant_bindings();
				      dce_exit_control();
				      cse_exit_control();
				      pass_selector_exit_control();
				      }
	  | ASSIGN ';'	{$$=create_node(); $$->next=(int*)malloc(sizeof(int)*15); $$->next[0]=0;}
	  | E {optimization_effectiveness_record_expression($1); pass_selector_analyze_expression($1); optimize_common_subexpressions($1); dce_mark_expression_used($1); emit_expression($1); $$=create_node(); $$->next=(int*)malloc(sizeof(int)*15); $$->next[0]=0;}
	  ;

IF_ELSE : OPEN_STMT	
	 	| CLOSED_STMT
	  	;
	  
OPEN_STMT : IF_CONTROL '(' COND ')' M BODY	{$$ = create_node(); Backpatch($3->True,$5->quad); $$->next=Merge($3->False,$6->next); clear_constant_bindings(); dce_exit_control(); cse_exit_control(); pass_selector_exit_control();}	
	  	  | IF_CONTROL '(' COND ')' M CLOSED_STMT N ELSE M OPEN_STMT	{				
											$$ = create_node();
											Backpatch($3->True,$5->quad);
											Backpatch($3->False,$9->quad);
											$$->next=Merge($6->next,$7->next);
											$$->next=Merge($$->next,$10->next); clear_constant_bindings(); dce_exit_control(); cse_exit_control(); pass_selector_exit_control();}
	 	  ;
	  
CLOSED_STMT : IF_CONTROL '(' COND ')' M CLOSED_STMT N ELSE M CLOSED_STMT	{			
											$$ = create_node();
											Backpatch($3->True,$5->quad);
											Backpatch($3->False,$9->quad);
											
											$$->next=Merge($6->next,$7->next);
											$$->next=Merge($$->next,$10->next); clear_constant_bindings(); dce_exit_control(); cse_exit_control(); pass_selector_exit_control();
											}
	    	| '{' STMTS '}'	{$$=create_node(); $$->next=$2->next;}
	    
	 		 ;  
	  
STMTS : STMTS M BODY	{$$=create_node(); Backpatch($1->next,$2->quad); $$->next=$3->next;}
		   | BODY	{$$=create_node(); $$->next=$1->next;}
		   ;
		   
ASSIGN : LVALUE '=' E	{int first_quad=nextquad; optimization_effectiveness_record_expression($3); optimization_effectiveness_record_assignment(); pass_selector_analyze_assignment($1->place,$3); propagate_constants($3); pass_selector_analyze_folding($3); optimize_constant_expression($3); pass_selector_analyze_assignment($1->place,$3); optimize_common_subexpressions($3); dce_mark_expression_used($3); emit_expression($3); sprintf(code[nextquad-START_ADDRESS],"%d\t%s = %s",nextquad,$1->place,$3->place); Gen(); record_constant_assignment($1->place,$3); cse_invalidate_variable($1->place); dce_record_assignment($1->place,$3,first_quad,nextquad);
			  $3->isLeftChild =1;tree_pointer = $3;if(!dead_code_elimination_is_enabled()){printf("Labeling Algorithm (No. of registers required)\n");calc_registers(tree_pointer);printf("Gencode : \n");gencode(tree_pointer);printf("\n");}}
	   | E {optimization_effectiveness_record_expression($1); pass_selector_analyze_expression($1); optimize_common_subexpressions($1); dce_mark_expression_used($1); emit_expression($1);}	
	   ;

LVALUE : LETTER {$$=create_node(); strcpy($$->place,$1);};

E : '(' E ')' {$$ =create_node(); $$ = $2;}
  
    | E '+' E	{
				$$=create_node();
				strcpy($$->place,Newtemp()); 
				$1->isLeftChild = 1;
				$$->Operator = '+';
				$$->left = $1;
				$$->right = $3;
			}
  | E '-' E	{
				$$=create_node();
				strcpy($$->place,Newtemp());
				$1->isLeftChild = 1;
				$$->Operator = '-';
				$$->left = $1;
				$$->right = $3;
				
			}
  | E '*' E	{
				$$=create_node();
				strcpy($$->place,Newtemp());
				$1->isLeftChild = 1;
				$$->Operator = '*';
				$$->left = $1;
				$$->right = $3;
				
			}
  | E '/' E	{
				$$=create_node();
				strcpy($$->place,Newtemp());
				$1->isLeftChild = 1;
				$$->Operator = '/';
				$$->left = $1;
				$$->right = $3;
				
			}
  | LETTER		{$$ = create_node(); strcpy($$->place,$1);}
  | INTEGER		{$$=create_node(); strcpy($$->place,$1); { optimization_safety_result literal_safety; if(optimization_safety_parse_int32_literal($1,&$$->integer_value,&literal_safety)) $$->is_integer_constant=1; }}
  | FLOAT		{$$=create_node(); strcpy($$->place,$1);}
  ;

COND : COND '&' M COND	{$$=create_node(); Backpatch($1->True,$3->quad); $$->True=$4->True; $$->False=Merge($1->False,$4->False);}
	 | COND '|' M COND	{$$=create_node(); Backpatch($1->False,$3->quad); $$->True=Merge($1->True,$4->True); $$->False=$4->False;}
	 | '!' COND			{$$=create_node(); $$->True=$2->False; $$->False=$2->True;}
	 
	 | E '<' E	{
	 				$$=create_node();
	 					optimization_effectiveness_record_expression($1); optimization_effectiveness_record_expression($3); optimization_effectiveness_record_condition(); pass_selector_analyze_expression($1); propagate_constants($1); pass_selector_analyze_folding($1); optimize_constant_expression($1); optimize_common_subexpressions($1); dce_mark_expression_used($1); emit_expression($1); pass_selector_analyze_expression($3); propagate_constants($3); pass_selector_analyze_folding($3); optimize_constant_expression($3); optimize_common_subexpressions($3); dce_mark_expression_used($3); emit_expression($3);
					$$->True=Makelist(nextquad);
					$$->False=Makelist(nextquad+1);
					sprintf(code[nextquad-START_ADDRESS],"%d\tif %s < %s goto ",nextquad,$1->place,$3->place);
					Gen();
					sprintf(code[nextquad-START_ADDRESS],"%d\tgoto ",nextquad);
					Gen();
				}
	 | E '>' E	{
					$$=create_node();
					optimization_effectiveness_record_expression($1); optimization_effectiveness_record_expression($3); optimization_effectiveness_record_condition(); pass_selector_analyze_expression($1); propagate_constants($1); pass_selector_analyze_folding($1); optimize_constant_expression($1); optimize_common_subexpressions($1); dce_mark_expression_used($1); emit_expression($1); pass_selector_analyze_expression($3); propagate_constants($3); pass_selector_analyze_folding($3); optimize_constant_expression($3); optimize_common_subexpressions($3); dce_mark_expression_used($3); emit_expression($3);
					$$->True=Makelist(nextquad);
					$$->False=Makelist(nextquad+1);
					sprintf(code[nextquad-START_ADDRESS],"%d\tif %s > %s goto ",nextquad,$1->place,$3->place);
					Gen();
					sprintf(code[nextquad-START_ADDRESS],"%d\tgoto ",nextquad);
					Gen();
				}
	 | E		{
					$$=create_node();
					optimization_effectiveness_record_expression($1); optimization_effectiveness_record_condition(); pass_selector_analyze_expression($1); propagate_constants($1); pass_selector_analyze_folding($1); optimize_constant_expression($1); optimize_common_subexpressions($1); dce_mark_expression_used($1); emit_expression($1);
					$$->True=Makelist(nextquad);
					$$->False=Makelist(nextquad+1);
					sprintf(code[nextquad-START_ADDRESS],"%d\tif %s goto ",nextquad,$1->place);
					Gen();
					sprintf(code[nextquad-START_ADDRESS],"%d\tgoto ",nextquad);
					Gen();
				}
	 ;

M:	{$$=create_node(); $$->quad=nextquad;};

IF_CONTROL: IF {clear_constant_bindings(); dce_enter_control(); cse_enter_control(); pass_selector_enter_control();};

WHILE_CONTROL: WHILE {clear_constant_bindings(); dce_enter_control(); cse_enter_control(); pass_selector_enter_control();};

N:	{
		$$=create_node();
		optimization_effectiveness_record_jump();
		$$->next=Makelist(nextquad);
		sprintf(code[nextquad-START_ADDRESS],"%d\tgoto ",nextquad);
		Gen();
	};

%%

char* Newtemp()
{
	static int count=1;
	char* ch=(char*)malloc(sizeof(char)*5);
	sprintf(ch,"T%d",count++);
	return ch;
}

int* Makelist(int nquad)
{
	int* list=(int*)malloc(sizeof(int)*15);
	list[0]=nquad;
	list[1]=0;
	return list;
}

int* Merge(int* list1,int* list2)
{
	
	int* temp=list1,count1=0,count2=0,i=0;
	while(list1[count1]!=0) {count1++;}
	while(list2[count2]!=0)
	{
		list1[count1]=list2[count2];
		count1++;
		count2++;
	}
	return temp;
}

void Backpatch(int* list,int nquad)
{
	char addr[10];
	sprintf(addr,"%d",nquad);
	
	while(*list!=0)
	{
		int index = *list++ - START_ADDRESS;
		strcat(code[index],addr);
	}
}

void Gen()
{
	nextquad++;
}

void emit_expression(node *temp)
{
	if(temp==NULL || (temp->left==NULL && temp->right==NULL))
		return;
	emit_expression(temp->left);
	emit_expression(temp->right);
	sprintf(code[nextquad-START_ADDRESS],"%d\t%s = %s %c %s",nextquad,temp->place,temp->left->place,temp->Operator,temp->right->place);
	Gen();
}

void Initialize_rstack()
{
	int i=0;
	stringstream ss;
	string s;
	for(i=available_reg-1;i>=0;i--)
	{
	      ss<<i;
	      s = "R" + ss.str();
	      reg_stack.push(s);
	      ss.str("");
	}
}

string get_instruction(char op)
{
	string retval;
	switch(op)
	{
	    case '+' : 
		  retval = "ADD";
		  break;
	    case '-' : 
		  retval = "SUB";
		  break;
	    case '*' : 
		  retval = "MUL";
		  break;
	    case '/' : 
		  retval = "DIV";
		  break;
	}
	return retval;
}

void swap_rstack()
{
	string s1, s2;
	s1 = reg_stack.top();
	reg_stack.pop();
	s2 = reg_stack.top();
	reg_stack.pop();
	reg_stack.push(s1);
	reg_stack.push(s2);
}

void gencode(node *temp)
{
	string reg_name;
	node *leftchild = temp->left;
	node *rightchild = temp->right;
	if((leftchild==NULL) && (rightchild==NULL))
	{
	      if(temp->isLeftChild==1)
	      {  
		  	cout << "MOV " + reg_stack.top() + ", " + temp->place << endl;
	      }
	}
	else if(rightchild->registers==0)
	{
	      gencode(leftchild);
	      cout << get_instruction(temp->Operator) << " " << reg_stack.top() << ", " << rightchild->place << endl; 
	}
	else if((leftchild->registers>=1) && (rightchild->registers>=1) && (rightchild->registers < available_reg))
	{
	      gencode(leftchild);
	      reg_name = reg_stack.top();
	      reg_stack.pop();
	      gencode(rightchild);
	      cout << get_instruction(temp->Operator) << " " << reg_name << ", " << reg_stack.top() << endl;
	      reg_stack.push(reg_name);
	}
	else if((leftchild->registers>=1) && (rightchild->registers>=1) && (leftchild->registers < available_reg))
	{
	      swap_rstack();
	      gencode(rightchild);
	      reg_name = reg_stack.top();
	      gencode(leftchild);
	      cout << get_instruction(temp->Operator) << " " << reg_stack.top() << ", " << reg_name << endl;
	      reg_stack.push(reg_name);
	      swap_rstack();
	}
	else if((leftchild->registers >= available_reg) && (rightchild->registers >= available_reg))
	{
	      gencode(rightchild);
	      cout << "SD " << reg_stack.top() << ", " << "MEM" << memory_location_num << endl;
	      memory_location_num++;		//can also push variable in stack
	      gencode(leftchild);
	      memory_location_num--;
	      cout << get_instruction(temp->Operator) << " " << reg_stack.top() << ", " << "MEM" << memory_location_num << endl;
	}
}

typedef struct menu_configuration
{
	int constant_folding;
	int constant_propagation;
	int dead_code_elimination;
	int common_subexpression_elimination;
	int adaptive_optimization;
	int statistics;
	int report;
	int registers;
	string input_file;
} menu_configuration;

static int apply_compiler_option(const char *option)
{
	if(strcmp(option,"--auto-opt")==0)
		pass_selector_set_auto(1);
	else if(strcmp(option,"--report")==0)
	{
		optimization_report_set_enabled(1);
		optimization_effectiveness_set_enabled(1);
	}
	else if(strcmp(option,"--report-json")==0)
	{
		optimization_report_set_json(1);
		optimization_effectiveness_set_enabled(1);
	}
	else if(strcmp(option,"--stats")==0)
	{
		if(!optimization_effectiveness_is_enabled())
			optimization_effectiveness_set_enabled(1);
		optimization_effectiveness_set_stats_output(1);
	}
	else if(strcmp(option,"--const-fold")==0)
	{
		set_constant_folding(1);
		pass_selector_note_manual_option(PASS_CONSTANT_FOLDING,1);
	}
	else if(strcmp(option,"--no-const-fold")==0)
	{
		set_constant_folding(0);
		pass_selector_note_manual_option(PASS_CONSTANT_FOLDING,0);
	}
	else if(strcmp(option,"--const-propagation")==0)
	{
		set_constant_propagation(1);
		pass_selector_note_manual_option(PASS_CONSTANT_PROPAGATION,1);
	}
	else if(strcmp(option,"--no-const-propagation")==0)
	{
		set_constant_propagation(0);
		pass_selector_note_manual_option(PASS_CONSTANT_PROPAGATION,0);
	}
	else if(strcmp(option,"--dead-code")==0)
	{
		set_dead_code_elimination(1);
		pass_selector_note_manual_option(PASS_DEAD_CODE_ELIMINATION,1);
	}
	else if(strcmp(option,"--no-dead-code")==0)
	{
		set_dead_code_elimination(0);
		pass_selector_note_manual_option(PASS_DEAD_CODE_ELIMINATION,0);
	}
	else if(strcmp(option,"--cse")==0)
	{
		set_common_subexpression_elimination(1);
		pass_selector_note_manual_option(PASS_COMMON_SUBEXPRESSION_ELIMINATION,1);
	}
	else if(strcmp(option,"--no-cse")==0)
	{
		set_common_subexpression_elimination(0);
		pass_selector_note_manual_option(PASS_COMMON_SUBEXPRESSION_ELIMINATION,0);
	}
	else
		return 0;
	return 1;
}

static int read_menu_line(const char *prompt, string *value)
{
	cout << prompt;
	return getline(cin, *value) ? 1 : 0;
}

static int read_yes_no(const char *prompt)
{
	string answer;
	for(;;)
	{
		if(!read_menu_line(prompt, &answer))
			return 0;
		if(answer.size() == 1 && (answer[0] == 'y' || answer[0] == 'Y'))
			return 1;
		if(answer.size() == 1 && (answer[0] == 'n' || answer[0] == 'N'))
			return 0;
		cout << "Please enter Y or N." << endl;
	}
}

static void enable_all_optimizations(menu_configuration *configuration)
{
	configuration->constant_folding = 1;
	configuration->constant_propagation = 1;
	configuration->dead_code_elimination = 1;
	configuration->common_subexpression_elimination = 1;
}

static void print_menu_configuration(const menu_configuration *configuration)
{
	cout << "\nSelected configuration:\n"
		<< "  Input file: " << configuration->input_file << "\n"
		<< "  Registers: " << configuration->registers << "\n"
		<< "  Constant Folding: " << (configuration->constant_folding ? "enabled" : "disabled") << "\n"
		<< "  Constant Propagation: " << (configuration->constant_propagation ? "enabled" : "disabled") << "\n"
		<< "  Dead Code Elimination: " << (configuration->dead_code_elimination ? "enabled" : "disabled") << "\n"
		<< "  Common Subexpression Elimination: " << (configuration->common_subexpression_elimination ? "enabled" : "disabled") << "\n"
		<< "  Adaptive Optimization: " << (configuration->adaptive_optimization ? "enabled" : "disabled") << "\n"
		<< "  TAC Statistics: " << (configuration->statistics ? "enabled" : "disabled") << "\n"
		<< "  Explainable Report: " << (configuration->report ? "enabled" : "disabled") << "\n" << endl;
}

static void apply_menu_configuration(const menu_configuration *configuration)
{
	if(configuration->constant_folding)
		apply_compiler_option("--const-fold");
	if(configuration->constant_propagation)
		apply_compiler_option("--const-propagation");
	if(configuration->dead_code_elimination)
		apply_compiler_option("--dead-code");
	if(configuration->common_subexpression_elimination)
		apply_compiler_option("--cse");
	if(configuration->adaptive_optimization)
		apply_compiler_option("--auto-opt");
	if(configuration->statistics)
		apply_compiler_option("--stats");
	if(configuration->report)
		apply_compiler_option("--report");
}

static int run_interactive_menu(void)
{
	string input;
	string register_text;
	int choice;

	for(;;)
	{
		menu_configuration configuration = {0, 0, 0, 0, 0, 0, 0, 3, "input.txt"};
		cout << "\n=== Explainable C Compiler Optimization Menu ===\n"
			<< " 1. Run Without Optimization\n"
			<< " 2. Constant Folding\n"
			<< " 3. Constant Propagation\n"
			<< " 4. Dead Code Elimination\n"
			<< " 5. Common Subexpression Elimination\n"
			<< " 6. Adaptive Optimization\n"
			<< " 7. Enable All Optimizations\n"
			<< " 8. Custom Optimization Selection\n"
			<< " 9. Optimization Statistics\n"
			<< "10. Explainable Optimization Report\n"
			<< "11. Complete Analysis\n"
			<< "12. Exit\n";
		if(!read_menu_line("Select an option [1-12]: ", &input))
			return 0;
		stringstream choice_stream(input);
		char extra;
		if(!(choice_stream >> choice) || (choice_stream >> extra) || choice < 1 || choice > 12)
		{
			cout << "Invalid choice. Please select a number from 1 to 12." << endl;
			continue;
		}
		if(choice == 12)
		{
			cout << "Exiting compiler menu." << endl;
			return 0;
		}
		switch(choice)
		{
			case 2: configuration.constant_folding = 1; break;
			case 3: configuration.constant_propagation = 1; break;
			case 4: configuration.dead_code_elimination = 1; break;
			case 5: configuration.common_subexpression_elimination = 1; break;
			case 6: configuration.adaptive_optimization = 1; break;
			case 7: enable_all_optimizations(&configuration); break;
			case 8:
				configuration.constant_folding = read_yes_no("Enable Constant Folding? [Y/N]: ");
				configuration.constant_propagation = read_yes_no("Enable Constant Propagation? [Y/N]: ");
				configuration.dead_code_elimination = read_yes_no("Enable Dead Code Elimination? [Y/N]: ");
				configuration.common_subexpression_elimination = read_yes_no("Enable Common Subexpression Elimination? [Y/N]: ");
				break;
			case 9: enable_all_optimizations(&configuration); configuration.statistics = 1; break;
			case 10: enable_all_optimizations(&configuration); configuration.report = 1; break;
			case 11: enable_all_optimizations(&configuration); configuration.statistics = 1; configuration.report = 1; break;
			default: break;
		}
		if(!read_menu_line("Input file [input.txt]: ", &input))
			return 0;
		if(!input.empty())
			configuration.input_file = input;
		FILE *input_file = fopen(configuration.input_file.c_str(), "r");
		if(input_file == NULL)
		{
			cout << "Unable to open input file: " << configuration.input_file << endl;
			continue;
		}
		if(!read_menu_line("Available registers [3]: ", &register_text))
		{
			fclose(input_file);
			return 0;
		}
		if(!register_text.empty())
		{
			stringstream register_stream(register_text);
			char register_extra;
			if(!(register_stream >> configuration.registers) || (register_stream >> register_extra) || configuration.registers <= 0)
			{
				cout << "Invalid register count; using 3." << endl;
				configuration.registers = 3;
			}
		}
		print_menu_configuration(&configuration);
		yyin = input_file;
		available_reg = configuration.registers;
		apply_menu_configuration(&configuration);
		return 1;
	}
}

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		if(!run_interactive_menu())
			return 0;
	}
	else
	{
		available_reg = atoi(argv[1]);
		for(int option_index=2; option_index<argc; option_index++)
		{
			if(!apply_compiler_option(argv[option_index]))
			{
				cout << "Unknown option: " << argv[option_index] << endl;
				return 1;
			}
		}
	}
	Initialize_rstack();
	yyparse();

	cout << ".........................." << endl;
	return 0;
}

int calc_registers(node *temp)
{
    int retval,reg_for_left, reg_for_right;
    if((temp->left==NULL) && (temp->right==NULL))
    {
		if(temp->isLeftChild==1)
		{
			  retval = 1;
		}
		else
		{
			  retval = 0;
		}
    }
    else
    {	
	//left_child=1;
	reg_for_left = calc_registers(temp->left);
	//left_child=0;
 	reg_for_right = calc_registers(temp->right);
 	if(reg_for_left > reg_for_right)
 	{
	    retval = max(reg_for_left, reg_for_right+1);
	}
	else
	{
	    retval = max(reg_for_right, reg_for_left+1);
	}
    }
    printf("%s\t :\t %d\n",temp->place, retval);
    temp->registers = retval;
    return retval;
}
//use ? :
int max(int x, int y)
{
	int retval;
	if(x>y)
	{
	      retval = x;
	}
	else
	{
	      retval = y;
	}
	return retval;
}

node* create_node()
{
	node *n=(node *) malloc(sizeof(node));
	n->left = NULL;
	n->right = NULL;
	n->registers = 0;
	n->isLeftChild = 0;
	n->is_integer_constant = 0;
	n->integer_value = 0;
	n->cse_key[0] = '\0';
	n->cse_dependencies = 0;
	n->Operator = '\0';
	n->place[0] = '\0';
	return n;
}

void yyerror(string str)
{
	cout << endl;
	cout << str;
}
