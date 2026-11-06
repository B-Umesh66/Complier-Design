#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<sstream>
#include<stack>
#include<stdint.h>

using namespace std;

typedef struct etype
{
	int* True;
	int* False;
	int* next;
	int quad;
	char place[32];
	
	char Operator;
	int registers;
	int isLeftChild;
	int is_integer_constant;
	int32_t integer_value;
	char cse_key[256];
	uint64_t cse_dependencies;
	
	struct etype* left;
	struct etype* right;
}node;

typedef struct register_stack
{
	string reg;
	struct register_stack *next;
}rstack;

char* Newtemp();
int* Makelist(int nquad);
int* Merge(int* list1,int* list2);
void Backpatch(int* list,int nquad);
void Gen();
node* create_node();
int calc_registers(node *);
void gencode(node *);
void Initialize_rstack();
void emit_expression(node *);
void optimize_constant_expression(node *);
void set_constant_folding(int enabled);
int constant_folding_is_enabled();
void set_constant_propagation(int enabled);
int constant_propagation_is_enabled();
void propagate_constants(node *);
void record_constant_assignment(const char *, node *);
void clear_constant_bindings();
void set_dead_code_elimination(int enabled);
int dead_code_elimination_is_enabled();
void dce_mark_expression_used(node *);
void dce_record_assignment(const char *, node *, int, int);
void dce_enter_control();
void dce_exit_control();
void dce_finalize();
void dce_emit_surviving_register_code();
void set_common_subexpression_elimination(int enabled);
int common_subexpression_elimination_is_enabled();
void optimize_common_subexpressions(node *);
void cse_invalidate_variable(const char *);
void cse_enter_control();
void cse_exit_control();


#endif


