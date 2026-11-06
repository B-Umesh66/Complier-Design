/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "yacc.y"

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

#line 101 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LETTER = 258,                  /* LETTER  */
    INTEGER = 259,                 /* INTEGER  */
    FLOAT = 260,                   /* FLOAT  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    WHILE = 263                    /* WHILE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define LETTER 258
#define INTEGER 259
#define FLOAT 260
#define IF 261
#define ELSE 262
#define WHILE 263

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 32 "yacc.y"

	char id[32];
	node *eval;

#line 175 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LETTER = 3,                     /* LETTER  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_FLOAT = 5,                      /* FLOAT  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_9_ = 9,                         /* '|'  */
  YYSYMBOL_10_ = 10,                       /* '&'  */
  YYSYMBOL_11_ = 11,                       /* '!'  */
  YYSYMBOL_12_ = 12,                       /* '<'  */
  YYSYMBOL_13_ = 13,                       /* '>'  */
  YYSYMBOL_14_ = 14,                       /* '+'  */
  YYSYMBOL_15_ = 15,                       /* '-'  */
  YYSYMBOL_16_ = 16,                       /* '*'  */
  YYSYMBOL_17_ = 17,                       /* '/'  */
  YYSYMBOL_18_ = 18,                       /* '('  */
  YYSYMBOL_19_ = 19,                       /* ')'  */
  YYSYMBOL_20_ = 20,                       /* '='  */
  YYSYMBOL_21_ = 21,                       /* ';'  */
  YYSYMBOL_22_ = 22,                       /* '{'  */
  YYSYMBOL_23_ = 23,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 24,                  /* $accept  */
  YYSYMBOL_PROGRAM = 25,                   /* PROGRAM  */
  YYSYMBOL_BODY = 26,                      /* BODY  */
  YYSYMBOL_IF_ELSE = 27,                   /* IF_ELSE  */
  YYSYMBOL_OPEN_STMT = 28,                 /* OPEN_STMT  */
  YYSYMBOL_CLOSED_STMT = 29,               /* CLOSED_STMT  */
  YYSYMBOL_STMTS = 30,                     /* STMTS  */
  YYSYMBOL_ASSIGN = 31,                    /* ASSIGN  */
  YYSYMBOL_LVALUE = 32,                    /* LVALUE  */
  YYSYMBOL_E = 33,                         /* E  */
  YYSYMBOL_COND = 34,                      /* COND  */
  YYSYMBOL_M = 35,                         /* M  */
  YYSYMBOL_IF_CONTROL = 36,                /* IF_CONTROL  */
  YYSYMBOL_WHILE_CONTROL = 37,             /* WHILE_CONTROL  */
  YYSYMBOL_N = 38                          /* N  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   87

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  35
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  68

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   263


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    11,     2,     2,     2,     2,    10,     2,
      18,    19,    16,    14,     2,    15,     2,    17,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    21,
      12,    20,    13,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,     9,    23,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    55,    55,    73,    74,    87,    88,    91,    92,    95,
      96,   104,   112,   116,   117,   120,   122,   125,   127,   129,
     137,   146,   155,   164,   165,   166,   169,   170,   171,   173,
     183,   193,   205,   207,   209,   211
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LETTER", "INTEGER",
  "FLOAT", "IF", "ELSE", "WHILE", "'|'", "'&'", "'!'", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'('", "')'", "'='", "';'", "'{'", "'}'", "$accept",
  "PROGRAM", "BODY", "IF_ELSE", "OPEN_STMT", "CLOSED_STMT", "STMTS",
  "ASSIGN", "LVALUE", "E", "COND", "M", "IF_CONTROL", "WHILE_CONTROL", "N", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-36)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      49,   -15,   -40,   -40,   -40,   -40,     7,    49,    28,   -40,
     -40,   -40,   -40,    29,    12,    30,    47,    -1,   -40,   -40,
      64,    26,   -40,    49,   -40,     7,     7,     7,     7,     7,
      27,    40,   -40,   -40,   -40,    70,    -8,    -8,   -40,   -40,
      27,    60,    -3,    27,   -40,     7,     7,   -40,   -40,   -40,
      17,    70,    70,    27,    27,    49,   -40,    50,   -40,   -40,
      58,    49,    59,   -40,   -40,    -4,   -40,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    23,    24,    25,    33,    34,     0,     0,     0,    14,
       3,     7,     8,    32,     0,     0,     6,     0,    32,    23,
       0,    32,     1,     0,     5,     0,     0,     0,     0,     0,
       0,     0,    18,    12,    13,    15,    19,    20,    21,    22,
       0,    31,     0,     0,    28,     0,     0,    32,    32,    32,
       0,    29,    30,     0,     0,     0,    32,    27,    26,     9,
       8,     0,     0,     4,    32,     0,    10,    11
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -20,   -40,     4,    -9,    63,   -40,   -40,    -6,
     -39,    -5,   -40,   -40,   -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      42,    23,    17,    18,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      20,    44,     4,    34,    50,   -17,    47,    48,    28,    29,
      19,     2,     3,    31,    57,    58,    49,    30,     7,    35,
      36,    37,    38,    39,    41,     6,    47,    48,    22,    -2,
      19,     2,     3,    24,    41,    59,    56,    41,    40,    51,
      52,    63,    53,    54,    55,     6,    60,    41,    41,    33,
      25,    61,     1,     2,     3,     4,    67,     5,    43,    65,
      48,    26,    27,    28,    29,   -35,    64,     6,   -16,    66,
      21,     7,    45,    46,    26,    27,    28,    29,    26,    27,
      28,    29,     0,    32,    26,    27,    28,    29
};

static const yytype_int8 yycheck[] =
{
       6,    40,     6,    23,    43,    20,     9,    10,    16,    17,
       3,     4,     5,    18,    53,    54,    19,    18,    22,    25,
      26,    27,    28,    29,    30,    18,     9,    10,     0,     0,
       3,     4,     5,    21,    40,    55,    19,    43,    11,    45,
      46,    61,    47,    48,    49,    18,    55,    53,    54,    23,
      20,    56,     3,     4,     5,     6,    65,     8,    18,    64,
      10,    14,    15,    16,    17,     7,     7,    18,    21,    65,
       7,    22,    12,    13,    14,    15,    16,    17,    14,    15,
      16,    17,    -1,    19,    14,    15,    16,    17
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,    18,    22,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    36,    37,     3,
      33,    30,     0,    35,    21,    20,    14,    15,    16,    17,
      18,    35,    19,    23,    26,    33,    33,    33,    33,    33,
      11,    33,    34,    18,    34,    12,    13,     9,    10,    19,
      34,    33,    33,    35,    35,    35,    19,    34,    34,    26,
      29,    35,    38,    26,     7,    35,    28,    29
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    24,    25,    26,    26,    26,    26,    27,    27,    28,
      28,    29,    29,    30,    30,    31,    31,    32,    33,    33,
      33,    33,    33,    33,    33,    33,    34,    34,    34,    34,
      34,    34,    35,    36,    37,    38
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     7,     2,     1,     1,     1,     6,
      10,    10,     3,     3,     1,     3,     1,     1,     3,     3,
       3,     3,     3,     1,     1,     1,     4,     4,     2,     3,
       3,     1,     0,     1,     1,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* PROGRAM: STMTS  */
#line 55 "yacc.y"
                { 
					int i;
					dce_finalize();
					optimization_effectiveness_finalize(START_ADDRESS, nextquad, code);
					pass_selector_report();
					optimization_report_print();
					optimization_effectiveness_print_stats();
					Backpatch((yyvsp[0].eval)->next,nextquad);
					dce_emit_surviving_register_code();
					printf("3 address code : \n");
					for(i=START_ADDRESS;i<nextquad;i++){
						if(!dead_code_elimination_is_enabled() || code[i-START_ADDRESS][0]!='\0')
							printf("\n%s",code[i-START_ADDRESS]);
					}
					printf("\n%d\n",nextquad);
				}
#line 1242 "y.tab.c"
    break;

  case 3: /* BODY: IF_ELSE  */
#line 73 "yacc.y"
               {}
#line 1248 "y.tab.c"
    break;

  case 4: /* BODY: WHILE_CONTROL M '(' COND ')' M BODY  */
#line 74 "yacc.y"
                                                {
				      (yyval.eval)=create_node();
				      Backpatch((yyvsp[0].eval)->next,(yyvsp[-5].eval)->quad);
				      Backpatch((yyvsp[-3].eval)->True,(yyvsp[-1].eval)->quad);
				      (yyval.eval)->next=(yyvsp[-3].eval)->False;
				      optimization_effectiveness_record_jump();
				      sprintf(code[nextquad-START_ADDRESS],"%d\tgoto %d",nextquad,(yyvsp[-5].eval)->quad);
				      Gen();
				      clear_constant_bindings();
				      dce_exit_control();
				      cse_exit_control();
				      pass_selector_exit_control();
				      }
#line 1266 "y.tab.c"
    break;

  case 5: /* BODY: ASSIGN ';'  */
#line 87 "yacc.y"
                        {(yyval.eval)=create_node(); (yyval.eval)->next=(int*)malloc(sizeof(int)*15); (yyval.eval)->next[0]=0;}
#line 1272 "y.tab.c"
    break;

  case 6: /* BODY: E  */
#line 88 "yacc.y"
              {optimization_effectiveness_record_expression((yyvsp[0].eval)); pass_selector_analyze_expression((yyvsp[0].eval)); optimize_common_subexpressions((yyvsp[0].eval)); dce_mark_expression_used((yyvsp[0].eval)); emit_expression((yyvsp[0].eval)); (yyval.eval)=create_node(); (yyval.eval)->next=(int*)malloc(sizeof(int)*15); (yyval.eval)->next[0]=0;}
#line 1278 "y.tab.c"
    break;

  case 9: /* OPEN_STMT: IF_CONTROL '(' COND ')' M BODY  */
#line 95 "yacc.y"
                                                {(yyval.eval) = create_node(); Backpatch((yyvsp[-3].eval)->True,(yyvsp[-1].eval)->quad); (yyval.eval)->next=Merge((yyvsp[-3].eval)->False,(yyvsp[0].eval)->next); clear_constant_bindings(); dce_exit_control(); cse_exit_control(); pass_selector_exit_control();}
#line 1284 "y.tab.c"
    break;

  case 10: /* OPEN_STMT: IF_CONTROL '(' COND ')' M CLOSED_STMT N ELSE M OPEN_STMT  */
#line 96 "yacc.y"
                                                                                {				
											(yyval.eval) = create_node();
											Backpatch((yyvsp[-7].eval)->True,(yyvsp[-5].eval)->quad);
											Backpatch((yyvsp[-7].eval)->False,(yyvsp[-1].eval)->quad);
											(yyval.eval)->next=Merge((yyvsp[-4].eval)->next,(yyvsp[-3].eval)->next);
											(yyval.eval)->next=Merge((yyval.eval)->next,(yyvsp[0].eval)->next); clear_constant_bindings(); dce_exit_control(); cse_exit_control(); pass_selector_exit_control();}
#line 1295 "y.tab.c"
    break;

  case 11: /* CLOSED_STMT: IF_CONTROL '(' COND ')' M CLOSED_STMT N ELSE M CLOSED_STMT  */
#line 104 "yacc.y"
                                                                                {			
											(yyval.eval) = create_node();
											Backpatch((yyvsp[-7].eval)->True,(yyvsp[-5].eval)->quad);
											Backpatch((yyvsp[-7].eval)->False,(yyvsp[-1].eval)->quad);
											
											(yyval.eval)->next=Merge((yyvsp[-4].eval)->next,(yyvsp[-3].eval)->next);
											(yyval.eval)->next=Merge((yyval.eval)->next,(yyvsp[0].eval)->next); clear_constant_bindings(); dce_exit_control(); cse_exit_control(); pass_selector_exit_control();
											}
#line 1308 "y.tab.c"
    break;

  case 12: /* CLOSED_STMT: '{' STMTS '}'  */
#line 112 "yacc.y"
                                {(yyval.eval)=create_node(); (yyval.eval)->next=(yyvsp[-1].eval)->next;}
#line 1314 "y.tab.c"
    break;

  case 13: /* STMTS: STMTS M BODY  */
#line 116 "yacc.y"
                        {(yyval.eval)=create_node(); Backpatch((yyvsp[-2].eval)->next,(yyvsp[-1].eval)->quad); (yyval.eval)->next=(yyvsp[0].eval)->next;}
#line 1320 "y.tab.c"
    break;

  case 14: /* STMTS: BODY  */
#line 117 "yacc.y"
                                {(yyval.eval)=create_node(); (yyval.eval)->next=(yyvsp[0].eval)->next;}
#line 1326 "y.tab.c"
    break;

  case 15: /* ASSIGN: LVALUE '=' E  */
#line 120 "yacc.y"
                        {int first_quad=nextquad; optimization_effectiveness_record_expression((yyvsp[0].eval)); optimization_effectiveness_record_assignment(); pass_selector_analyze_assignment((yyvsp[-2].eval)->place,(yyvsp[0].eval)); propagate_constants((yyvsp[0].eval)); pass_selector_analyze_folding((yyvsp[0].eval)); optimize_constant_expression((yyvsp[0].eval)); pass_selector_analyze_assignment((yyvsp[-2].eval)->place,(yyvsp[0].eval)); optimize_common_subexpressions((yyvsp[0].eval)); dce_mark_expression_used((yyvsp[0].eval)); emit_expression((yyvsp[0].eval)); sprintf(code[nextquad-START_ADDRESS],"%d\t%s = %s",nextquad,(yyvsp[-2].eval)->place,(yyvsp[0].eval)->place); Gen(); record_constant_assignment((yyvsp[-2].eval)->place,(yyvsp[0].eval)); cse_invalidate_variable((yyvsp[-2].eval)->place); dce_record_assignment((yyvsp[-2].eval)->place,(yyvsp[0].eval),first_quad,nextquad);
			  (yyvsp[0].eval)->isLeftChild =1;tree_pointer = (yyvsp[0].eval);if(!dead_code_elimination_is_enabled()){printf("Labeling Algorithm (No. of registers required)\n");calc_registers(tree_pointer);printf("Gencode : \n");gencode(tree_pointer);printf("\n");}}
#line 1333 "y.tab.c"
    break;

  case 16: /* ASSIGN: E  */
#line 122 "yacc.y"
               {optimization_effectiveness_record_expression((yyvsp[0].eval)); pass_selector_analyze_expression((yyvsp[0].eval)); optimize_common_subexpressions((yyvsp[0].eval)); dce_mark_expression_used((yyvsp[0].eval)); emit_expression((yyvsp[0].eval));}
#line 1339 "y.tab.c"
    break;

  case 17: /* LVALUE: LETTER  */
#line 125 "yacc.y"
                {(yyval.eval)=create_node(); strcpy((yyval.eval)->place,(yyvsp[0].id));}
#line 1345 "y.tab.c"
    break;

  case 18: /* E: '(' E ')'  */
#line 127 "yacc.y"
              {(yyval.eval) =create_node(); (yyval.eval) = (yyvsp[-1].eval);}
#line 1351 "y.tab.c"
    break;

  case 19: /* E: E '+' E  */
#line 129 "yacc.y"
                {
				(yyval.eval)=create_node();
				strcpy((yyval.eval)->place,Newtemp()); 
				(yyvsp[-2].eval)->isLeftChild = 1;
				(yyval.eval)->Operator = '+';
				(yyval.eval)->left = (yyvsp[-2].eval);
				(yyval.eval)->right = (yyvsp[0].eval);
			}
#line 1364 "y.tab.c"
    break;

  case 20: /* E: E '-' E  */
#line 137 "yacc.y"
                {
				(yyval.eval)=create_node();
				strcpy((yyval.eval)->place,Newtemp());
				(yyvsp[-2].eval)->isLeftChild = 1;
				(yyval.eval)->Operator = '-';
				(yyval.eval)->left = (yyvsp[-2].eval);
				(yyval.eval)->right = (yyvsp[0].eval);
				
			}
#line 1378 "y.tab.c"
    break;

  case 21: /* E: E '*' E  */
#line 146 "yacc.y"
                {
				(yyval.eval)=create_node();
				strcpy((yyval.eval)->place,Newtemp());
				(yyvsp[-2].eval)->isLeftChild = 1;
				(yyval.eval)->Operator = '*';
				(yyval.eval)->left = (yyvsp[-2].eval);
				(yyval.eval)->right = (yyvsp[0].eval);
				
			}
#line 1392 "y.tab.c"
    break;

  case 22: /* E: E '/' E  */
#line 155 "yacc.y"
                {
				(yyval.eval)=create_node();
				strcpy((yyval.eval)->place,Newtemp());
				(yyvsp[-2].eval)->isLeftChild = 1;
				(yyval.eval)->Operator = '/';
				(yyval.eval)->left = (yyvsp[-2].eval);
				(yyval.eval)->right = (yyvsp[0].eval);
				
			}
#line 1406 "y.tab.c"
    break;

  case 23: /* E: LETTER  */
#line 164 "yacc.y"
                        {(yyval.eval) = create_node(); strcpy((yyval.eval)->place,(yyvsp[0].id));}
#line 1412 "y.tab.c"
    break;

  case 24: /* E: INTEGER  */
#line 165 "yacc.y"
                        {(yyval.eval)=create_node(); strcpy((yyval.eval)->place,(yyvsp[0].id)); { optimization_safety_result literal_safety; if(optimization_safety_parse_int32_literal((yyvsp[0].id),&(yyval.eval)->integer_value,&literal_safety)) (yyval.eval)->is_integer_constant=1; }}
#line 1418 "y.tab.c"
    break;

  case 25: /* E: FLOAT  */
#line 166 "yacc.y"
                        {(yyval.eval)=create_node(); strcpy((yyval.eval)->place,(yyvsp[0].id));}
#line 1424 "y.tab.c"
    break;

  case 26: /* COND: COND '&' M COND  */
#line 169 "yacc.y"
                        {(yyval.eval)=create_node(); Backpatch((yyvsp[-3].eval)->True,(yyvsp[-1].eval)->quad); (yyval.eval)->True=(yyvsp[0].eval)->True; (yyval.eval)->False=Merge((yyvsp[-3].eval)->False,(yyvsp[0].eval)->False);}
#line 1430 "y.tab.c"
    break;

  case 27: /* COND: COND '|' M COND  */
#line 170 "yacc.y"
                                {(yyval.eval)=create_node(); Backpatch((yyvsp[-3].eval)->False,(yyvsp[-1].eval)->quad); (yyval.eval)->True=Merge((yyvsp[-3].eval)->True,(yyvsp[0].eval)->True); (yyval.eval)->False=(yyvsp[0].eval)->False;}
#line 1436 "y.tab.c"
    break;

  case 28: /* COND: '!' COND  */
#line 171 "yacc.y"
                                        {(yyval.eval)=create_node(); (yyval.eval)->True=(yyvsp[0].eval)->False; (yyval.eval)->False=(yyvsp[0].eval)->True;}
#line 1442 "y.tab.c"
    break;

  case 29: /* COND: E '<' E  */
#line 173 "yacc.y"
                        {
	 				(yyval.eval)=create_node();
	 					optimization_effectiveness_record_expression((yyvsp[-2].eval)); optimization_effectiveness_record_expression((yyvsp[0].eval)); optimization_effectiveness_record_condition(); pass_selector_analyze_expression((yyvsp[-2].eval)); propagate_constants((yyvsp[-2].eval)); pass_selector_analyze_folding((yyvsp[-2].eval)); optimize_constant_expression((yyvsp[-2].eval)); optimize_common_subexpressions((yyvsp[-2].eval)); dce_mark_expression_used((yyvsp[-2].eval)); emit_expression((yyvsp[-2].eval)); pass_selector_analyze_expression((yyvsp[0].eval)); propagate_constants((yyvsp[0].eval)); pass_selector_analyze_folding((yyvsp[0].eval)); optimize_constant_expression((yyvsp[0].eval)); optimize_common_subexpressions((yyvsp[0].eval)); dce_mark_expression_used((yyvsp[0].eval)); emit_expression((yyvsp[0].eval));
					(yyval.eval)->True=Makelist(nextquad);
					(yyval.eval)->False=Makelist(nextquad+1);
					sprintf(code[nextquad-START_ADDRESS],"%d\tif %s < %s goto ",nextquad,(yyvsp[-2].eval)->place,(yyvsp[0].eval)->place);
					Gen();
					sprintf(code[nextquad-START_ADDRESS],"%d\tgoto ",nextquad);
					Gen();
				}
#line 1457 "y.tab.c"
    break;

  case 30: /* COND: E '>' E  */
#line 183 "yacc.y"
                        {
					(yyval.eval)=create_node();
					optimization_effectiveness_record_expression((yyvsp[-2].eval)); optimization_effectiveness_record_expression((yyvsp[0].eval)); optimization_effectiveness_record_condition(); pass_selector_analyze_expression((yyvsp[-2].eval)); propagate_constants((yyvsp[-2].eval)); pass_selector_analyze_folding((yyvsp[-2].eval)); optimize_constant_expression((yyvsp[-2].eval)); optimize_common_subexpressions((yyvsp[-2].eval)); dce_mark_expression_used((yyvsp[-2].eval)); emit_expression((yyvsp[-2].eval)); pass_selector_analyze_expression((yyvsp[0].eval)); propagate_constants((yyvsp[0].eval)); pass_selector_analyze_folding((yyvsp[0].eval)); optimize_constant_expression((yyvsp[0].eval)); optimize_common_subexpressions((yyvsp[0].eval)); dce_mark_expression_used((yyvsp[0].eval)); emit_expression((yyvsp[0].eval));
					(yyval.eval)->True=Makelist(nextquad);
					(yyval.eval)->False=Makelist(nextquad+1);
					sprintf(code[nextquad-START_ADDRESS],"%d\tif %s > %s goto ",nextquad,(yyvsp[-2].eval)->place,(yyvsp[0].eval)->place);
					Gen();
					sprintf(code[nextquad-START_ADDRESS],"%d\tgoto ",nextquad);
					Gen();
				}
#line 1472 "y.tab.c"
    break;

  case 31: /* COND: E  */
#line 193 "yacc.y"
                        {
					(yyval.eval)=create_node();
					optimization_effectiveness_record_expression((yyvsp[0].eval)); optimization_effectiveness_record_condition(); pass_selector_analyze_expression((yyvsp[0].eval)); propagate_constants((yyvsp[0].eval)); pass_selector_analyze_folding((yyvsp[0].eval)); optimize_constant_expression((yyvsp[0].eval)); optimize_common_subexpressions((yyvsp[0].eval)); dce_mark_expression_used((yyvsp[0].eval)); emit_expression((yyvsp[0].eval));
					(yyval.eval)->True=Makelist(nextquad);
					(yyval.eval)->False=Makelist(nextquad+1);
					sprintf(code[nextquad-START_ADDRESS],"%d\tif %s goto ",nextquad,(yyvsp[0].eval)->place);
					Gen();
					sprintf(code[nextquad-START_ADDRESS],"%d\tgoto ",nextquad);
					Gen();
				}
#line 1487 "y.tab.c"
    break;

  case 32: /* M: %empty  */
#line 205 "yacc.y"
        {(yyval.eval)=create_node(); (yyval.eval)->quad=nextquad;}
#line 1493 "y.tab.c"
    break;

  case 33: /* IF_CONTROL: IF  */
#line 207 "yacc.y"
               {clear_constant_bindings(); dce_enter_control(); cse_enter_control(); pass_selector_enter_control();}
#line 1499 "y.tab.c"
    break;

  case 34: /* WHILE_CONTROL: WHILE  */
#line 209 "yacc.y"
                     {clear_constant_bindings(); dce_enter_control(); cse_enter_control(); pass_selector_enter_control();}
#line 1505 "y.tab.c"
    break;

  case 35: /* N: %empty  */
#line 211 "yacc.y"
        {
		(yyval.eval)=create_node();
		optimization_effectiveness_record_jump();
		(yyval.eval)->next=Makelist(nextquad);
		sprintf(code[nextquad-START_ADDRESS],"%d\tgoto ",nextquad);
		Gen();
	}
#line 1517 "y.tab.c"
    break;


#line 1521 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 219 "yacc.y"


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
