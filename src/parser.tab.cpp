/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     WHILE = 260,
     BREAK = 261,
     CONTINUE = 262,
     RETURN = 263,
     INT = 264,
     VOID = 265,
     CONST = 266,
     EQ = 267,
     NE = 268,
     LE = 269,
     GE = 270,
     LT = 271,
     GT = 272,
     PLUS = 273,
     MINUS = 274,
     TIMES = 275,
     OVER = 276,
     MOD = 277,
     ASSIGN = 278,
     NOT = 279,
     AND = 280,
     OR = 281,
     LPAREN = 282,
     RPAREN = 283,
     LSQBRKET = 284,
     RSQBRKET = 285,
     LFLBRKET = 286,
     RFLBRKET = 287,
     SEMI = 288,
     COMMA = 289,
     NUM = 290,
     IDENT = 291
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define BREAK 261
#define CONTINUE 262
#define RETURN 263
#define INT 264
#define VOID 265
#define CONST 266
#define EQ 267
#define NE 268
#define LE 269
#define GE 270
#define LT 271
#define GT 272
#define PLUS 273
#define MINUS 274
#define TIMES 275
#define OVER 276
#define MOD 277
#define ASSIGN 278
#define NOT 279
#define AND 280
#define OR 281
#define LPAREN 282
#define RPAREN 283
#define LSQBRKET 284
#define RSQBRKET 285
#define LFLBRKET 286
#define RFLBRKET 287
#define SEMI 288
#define COMMA 289
#define NUM 290
#define IDENT 291




/* Copy the first part of user declarations.  */
#line 1 "parser.y"


#define YYPARSER

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
#include "variable.h"
#include "symtable.h"
#include "initializer.h"
#include "others.h"
#include "geneeyore.h"
#include "gentigger.h"
#include "genriscv.h"

using namespace std;

#define YYSTYPE void *

extern FILE * yyin;
extern FILE * yyout;
extern int yylineno;
extern int yylex();

vector<string> instructions;

Parser parser;
Initializer initializer;

vector<Variable *> del_var;

void yyerror(string msg) {
    cerr << "Error at line: " << yylineno << "\tMessage: " << msg << endl;
    exit(1);
}

void emit(string s) {
    instructions.push_back(s);
}

void loop_init_to_zero(string name, int start, int end) {
    if (start >= end)
        return;
    if (parser.is_global())
        emit("//inserttomain");
    Variable * temp = new Variable(false);
    emit(temp->get_name() + " = " + to_string(start * 4));
    int label = parser.alloc_label();
    emit("l" + to_string(label) + ":");
    emit(name + "[" + temp->get_name() + "] = 0");
    emit(temp->get_name() + " = " + temp->get_name() + " + 4");
    emit("if " + temp->get_name() + " < " + to_string(end * 4) + " goto " + "l" + to_string(label));
    temp->rel_seqno();
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 237 "parser.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   223

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNRULES -- Number of states.  */
#define YYNSTATES  202

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    13,    15,    17,    22,
      24,    28,    29,    34,    35,    41,    45,    50,    52,    53,
      57,    58,    63,    65,    69,    73,    75,    79,    81,    82,
      87,    90,    91,    97,    99,   100,   104,   105,   110,   112,
     116,   117,   124,   125,   126,   135,   136,   143,   144,   145,
     154,   157,   162,   168,   173,   180,   188,   191,   192,   193,
     199,   201,   204,   206,   208,   213,   215,   218,   220,   221,
     222,   231,   232,   233,   241,   244,   247,   250,   254,   257,
     258,   260,   262,   264,   267,   271,   276,   280,   282,   284,
     286,   290,   295,   298,   301,   304,   306,   310,   312,   316,
     320,   324,   326,   330,   334,   336,   340,   344,   348,   352,
     354,   358,   362,   364,   368,   370,   374
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      38,     0,    -1,    39,    -1,    59,    -1,    38,    39,    -1,
      38,    59,    -1,    40,    -1,    50,    -1,    11,     9,    41,
      33,    -1,    42,    -1,    41,    34,    42,    -1,    -1,    36,
      43,    23,    46,    -1,    -1,    36,    45,    44,    23,    46,
      -1,    29,    91,    30,    -1,    45,    29,    91,    30,    -1,
      91,    -1,    -1,    31,    47,    32,    -1,    -1,    31,    48,
      49,    32,    -1,    46,    -1,    49,    34,    46,    -1,     9,
      51,    33,    -1,    52,    -1,    51,    34,    52,    -1,    36,
      -1,    -1,    36,    53,    23,    55,    -1,    36,    45,    -1,
      -1,    36,    45,    54,    23,    55,    -1,    78,    -1,    -1,
      31,    56,    32,    -1,    -1,    31,    57,    58,    32,    -1,
      55,    -1,    58,    34,    55,    -1,    -1,    10,    36,    27,
      28,    60,    67,    -1,    -1,    -1,    10,    36,    27,    61,
      66,    28,    62,    67,    -1,    -1,     9,    36,    27,    28,
      63,    67,    -1,    -1,    -1,     9,    36,    27,    64,    66,
      28,    65,    67,    -1,     9,    36,    -1,     9,    36,    29,
      30,    -1,     9,    36,    29,    30,    45,    -1,    66,    34,
       9,    36,    -1,    66,    34,     9,    36,    29,    30,    -1,
      66,    34,     9,    36,    29,    30,    45,    -1,    31,    32,
      -1,    -1,    -1,    31,    68,    70,    69,    32,    -1,    71,
      -1,    70,    71,    -1,    39,    -1,    72,    -1,    80,    23,
      78,    33,    -1,    33,    -1,    78,    33,    -1,    67,    -1,
      -1,    -1,     3,    27,    79,    28,    73,    72,    74,    77,
      -1,    -1,    -1,     5,    75,    27,    79,    28,    76,    72,
      -1,     6,    33,    -1,     7,    33,    -1,     8,    33,    -1,
       8,    78,    33,    -1,     4,    72,    -1,    -1,    86,    -1,
      90,    -1,    36,    -1,    36,    81,    -1,    29,    78,    30,
      -1,    81,    29,    78,    30,    -1,    27,    78,    28,    -1,
      80,    -1,    35,    -1,    82,    -1,    36,    27,    28,    -1,
      36,    27,    84,    28,    -1,    18,    83,    -1,    19,    83,
      -1,    24,    83,    -1,    78,    -1,    84,    34,    78,    -1,
      83,    -1,    85,    20,    83,    -1,    85,    21,    83,    -1,
      85,    22,    83,    -1,    85,    -1,    86,    18,    85,    -1,
      86,    19,    85,    -1,    86,    -1,    87,    16,    86,    -1,
      87,    17,    86,    -1,    87,    14,    86,    -1,    87,    15,
      86,    -1,    87,    -1,    88,    12,    87,    -1,    88,    13,
      87,    -1,    88,    -1,    89,    25,    88,    -1,    89,    -1,
      90,    26,    89,    -1,    86,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    70,    70,    71,    72,    73,    76,    77,    80,    83,
      84,    87,    87,    93,    93,   101,   105,   111,   123,   123,
     135,   135,   147,   148,   151,   154,   155,   158,   164,   164,
     170,   178,   178,   186,   196,   196,   208,   208,   220,   221,
     224,   224,   234,   237,   234,   248,   248,   258,   261,   258,
     274,   281,   290,   300,   306,   314,   325,   326,   329,   326,
     335,   336,   339,   340,   343,   349,   350,   351,   352,   357,
     352,   365,   370,   365,   379,   383,   387,   390,   396,   397,
     400,   405,   410,   414,   467,   471,   477,   480,   489,   494,
     497,   517,   534,   537,   546,   561,   565,   571,   574,   584,
     594,   606,   609,   619,   631,   634,   644,   654,   664,   676,
     679,   689,   701,   707,   714,   720,   727
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "BREAK",
  "CONTINUE", "RETURN", "INT", "VOID", "CONST", "EQ", "NE", "LE", "GE",
  "LT", "GT", "PLUS", "MINUS", "TIMES", "OVER", "MOD", "ASSIGN", "NOT",
  "AND", "OR", "LPAREN", "RPAREN", "LSQBRKET", "RSQBRKET", "LFLBRKET",
  "RFLBRKET", "SEMI", "COMMA", "NUM", "IDENT", "$accept", "CompUnit",
  "Decl", "ConstDecl", "ConstDefCommaArray", "ConstDef", "@1", "@2",
  "ConstExpSqArray", "ConstInitVal", "@3", "@4", "ConstInitValArray",
  "VarDecl", "VarDefCommaArray", "VarDef", "@5", "@6", "InitVal", "@7",
  "@8", "InitValArray", "FuncDef", "@9", "@10", "@11", "@12", "@13", "@14",
  "FuncFParams", "Block", "@15", "@16", "BlockItemArray", "BlockItem",
  "Stmt", "@17", "@18", "@19", "@20", "OptionalElse", "Exp", "Cond",
  "LVal", "ExpSqArray", "PrimaryExp", "UnaryExp", "FuncRParams", "MulExp",
  "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", "ConstExp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    38,    38,    38,    39,    39,    40,    41,
      41,    43,    42,    44,    42,    45,    45,    46,    47,    46,
      48,    46,    49,    49,    50,    51,    51,    52,    53,    52,
      52,    54,    52,    55,    56,    55,    57,    55,    58,    58,
      60,    59,    61,    62,    59,    63,    59,    64,    65,    59,
      66,    66,    66,    66,    66,    66,    67,    68,    69,    67,
      70,    70,    71,    71,    72,    72,    72,    72,    73,    74,
      72,    75,    76,    72,    72,    72,    72,    72,    77,    77,
      78,    79,    80,    80,    81,    81,    82,    82,    82,    83,
      83,    83,    83,    83,    83,    84,    84,    85,    85,    85,
      85,    86,    86,    86,    87,    87,    87,    87,    87,    88,
      88,    88,    89,    89,    90,    90,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     4,     1,
       3,     0,     4,     0,     5,     3,     4,     1,     0,     3,
       0,     4,     1,     3,     3,     1,     3,     1,     0,     4,
       2,     0,     5,     1,     0,     3,     0,     4,     1,     3,
       0,     6,     0,     0,     8,     0,     6,     0,     0,     8,
       2,     4,     5,     4,     6,     7,     2,     0,     0,     5,
       1,     2,     1,     1,     4,     1,     2,     1,     0,     0,
       8,     0,     0,     7,     2,     2,     2,     3,     2,     0,
       1,     1,     1,     2,     3,     4,     3,     1,     1,     1,
       3,     4,     2,     2,     2,     1,     3,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     2,     6,     7,     3,    27,
       0,    25,     0,     0,     1,     4,     5,    47,     0,    30,
       0,    24,     0,    42,    11,     0,     9,    45,     0,     0,
       0,     0,     0,    88,    82,    87,    89,    97,   101,   116,
       0,     0,     0,     0,    27,    26,    40,     0,     0,    13,
       8,     0,     0,     0,     0,    92,    93,    94,     0,    80,
       0,     0,    83,     0,     0,     0,     0,     0,    15,     0,
       0,    36,    29,    33,     0,     0,     0,     0,    10,    57,
      46,    50,    48,     0,    86,    90,    95,     0,     0,     0,
      98,    99,   100,   102,   103,    16,    32,     0,     0,    41,
      43,    20,    12,    17,     0,    56,     0,     0,     0,     0,
      91,     0,    84,     0,    35,    38,     0,     0,     0,     0,
      14,     0,    71,     0,     0,     0,     0,    65,    62,    67,
      58,    60,    63,     0,    87,    51,    49,    53,    96,    85,
      37,     0,    44,    19,    22,     0,     0,     0,    74,    75,
      76,     0,     0,    61,    66,     0,    52,     0,    39,    21,
       0,     0,   104,   109,   112,   114,    81,     0,    77,    59,
       0,    54,    23,    68,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,    55,     0,   107,   108,   105,   106,
     110,   111,   113,   115,    72,    69,     0,    79,    73,     0,
      70,    78
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,   128,     6,    25,    26,    48,    77,    19,   102,
     118,   119,   145,     7,    10,    11,    20,    42,    72,    97,
      98,   116,     8,    74,    47,   117,    52,    28,   108,    54,
     129,   106,   152,   130,   131,   132,   185,   197,   147,   196,
     200,   133,   161,    35,    62,    36,    37,    87,    38,    59,
     163,   164,   165,   166,   103
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -175
static const yytype_int16 yypact[] =
{
      74,   -12,    -7,     5,    26,  -175,  -175,  -175,  -175,   -11,
      80,  -175,     7,     9,  -175,  -175,  -175,    22,   170,    23,
      37,  -175,    17,    46,    40,    82,  -175,  -175,    91,   170,
     170,   170,   170,  -175,   -10,  -175,  -175,  -175,    77,   101,
      61,   170,    86,    20,    41,  -175,  -175,    91,   104,    95,
    -175,     9,    72,    93,   -13,  -175,  -175,  -175,   103,   101,
     149,   170,   111,   170,   170,   170,   170,   170,  -175,   113,
      20,   112,  -175,  -175,    72,    39,   168,   110,  -175,   114,
    -175,   116,  -175,   132,  -175,  -175,  -175,    44,   117,   170,
    -175,  -175,  -175,    77,    77,  -175,  -175,   119,    20,  -175,
    -175,   137,  -175,  -175,   168,  -175,    99,   134,    72,   136,
    -175,   170,  -175,   140,  -175,  -175,    45,    72,   143,   168,
    -175,   152,  -175,   148,   157,    30,    17,  -175,  -175,  -175,
      99,  -175,  -175,   158,   173,    40,  -175,   164,  -175,  -175,
    -175,    20,  -175,  -175,  -175,    60,   170,   171,  -175,  -175,
    -175,   167,   169,  -175,  -175,   170,    95,   172,  -175,  -175,
     168,   179,   101,    73,   109,   183,   184,   170,  -175,  -175,
     176,    40,  -175,  -175,   170,   170,   170,   170,   170,   170,
     170,   170,   185,  -175,    95,   147,   101,   101,   101,   101,
      73,    73,   109,   183,  -175,  -175,   147,   207,  -175,   147,
    -175,  -175
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -175,  -175,    76,  -175,  -175,   161,  -175,  -175,   -23,   -99,
    -175,  -175,  -175,  -175,  -175,   192,  -175,  -175,   -66,  -175,
    -175,  -175,   211,  -175,  -175,  -175,  -175,  -175,  -175,   174,
     -46,  -175,  -175,  -175,    87,  -174,  -175,  -175,  -175,  -175,
    -175,   -30,    49,  -103,  -175,  -175,   -22,  -175,    70,   -18,
     -40,    38,    42,  -175,    -8
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -35
static const yytype_int16 yytable[] =
{
      39,    49,    58,   134,    96,   120,    80,    55,    56,    57,
      40,   195,   -28,    73,    13,    82,    17,    60,    18,    61,
     144,    83,   198,    39,     9,   201,    14,   134,    99,    12,
      86,    88,   115,    69,    23,     1,     2,     3,    29,    30,
      73,    90,    91,    92,    31,    24,   -31,    32,    29,    30,
      27,    71,    41,    44,    31,    33,    34,    32,    39,   113,
      43,   172,   136,   150,   -28,    33,    34,   100,    73,    18,
      18,   142,   110,    83,    46,   158,     5,   140,   111,   141,
      15,   138,   134,     1,     2,     3,    39,   174,   175,   176,
     177,    68,   159,   134,   160,   151,   134,    63,    64,    65,
      53,    39,   121,    79,   122,   123,   124,   125,   126,    70,
       3,    73,   156,    21,    22,    50,    51,    29,    30,    66,
      67,   178,   179,    31,    41,   170,    32,    76,   162,    81,
      79,    84,   127,   104,    33,    34,    93,    94,   190,   191,
      89,   109,    39,    95,   -34,   107,   105,   112,   184,   162,
     121,   114,   122,   123,   124,   125,   186,   187,   188,   189,
     162,   162,   162,   162,   135,    29,    30,    29,    30,   -18,
     139,    31,   137,    31,    32,   143,    32,    85,    79,   146,
     127,   148,    33,    34,    33,    34,    29,    30,    29,    30,
     149,   154,    31,   157,    31,    32,   155,    32,   167,   101,
     168,   169,   171,    33,    34,    33,    34,   173,   180,   183,
     181,   199,    78,   194,    45,    16,   182,   153,   192,     0,
       0,    75,     0,   193
};

static const yytype_int16 yycheck[] =
{
      18,    24,    32,   106,    70,   104,    52,    29,    30,    31,
      18,   185,    23,    43,     9,    28,    27,    27,    29,    29,
     119,    34,   196,    41,    36,   199,     0,   130,    74,    36,
      60,    61,    98,    41,    27,     9,    10,    11,    18,    19,
      70,    63,    64,    65,    24,    36,    23,    27,    18,    19,
      28,    31,    29,    36,    24,    35,    36,    27,    76,    89,
      23,   160,   108,    33,    23,    35,    36,    28,    98,    29,
      29,   117,    28,    34,    28,   141,     0,    32,    34,    34,
       4,   111,   185,     9,    10,    11,   104,    14,    15,    16,
      17,    30,    32,   196,    34,   125,   199,    20,    21,    22,
       9,   119,     3,    31,     5,     6,     7,     8,     9,    23,
      11,   141,   135,    33,    34,    33,    34,    18,    19,    18,
      19,    12,    13,    24,    29,   155,    27,    23,   146,    36,
      31,    28,    33,    23,    35,    36,    66,    67,   178,   179,
      29,     9,   160,    30,    32,    29,    32,    30,   171,   167,
       3,    32,     5,     6,     7,     8,   174,   175,   176,   177,
     178,   179,   180,   181,    30,    18,    19,    18,    19,    32,
      30,    24,    36,    24,    27,    32,    27,    28,    31,    27,
      33,    33,    35,    36,    35,    36,    18,    19,    18,    19,
      33,    33,    24,    29,    24,    27,    23,    27,    27,    31,
      33,    32,    30,    35,    36,    35,    36,    28,    25,    33,
      26,     4,    51,    28,    22,     4,   167,   130,   180,    -1,
      -1,    47,    -1,   181
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    11,    38,    39,    40,    50,    59,    36,
      51,    52,    36,     9,     0,    39,    59,    27,    29,    45,
      53,    33,    34,    27,    36,    41,    42,    28,    64,    18,
      19,    24,    27,    35,    36,    80,    82,    83,    85,    86,
      91,    29,    54,    23,    36,    52,    28,    61,    43,    45,
      33,    34,    63,     9,    66,    83,    83,    83,    78,    86,
      27,    29,    81,    20,    21,    22,    18,    19,    30,    91,
      23,    31,    55,    78,    60,    66,    23,    44,    42,    31,
      67,    36,    28,    34,    28,    28,    78,    84,    78,    29,
      83,    83,    83,    85,    85,    30,    55,    56,    57,    67,
      28,    31,    46,    91,    23,    32,    68,    29,    65,     9,
      28,    34,    30,    78,    32,    55,    58,    62,    47,    48,
      46,     3,     5,     6,     7,     8,     9,    33,    39,    67,
      70,    71,    72,    78,    80,    30,    67,    36,    78,    30,
      32,    34,    67,    32,    46,    49,    27,    75,    33,    33,
      33,    78,    69,    71,    33,    23,    45,    29,    55,    32,
      34,    79,    86,    87,    88,    89,    90,    27,    33,    32,
      78,    30,    46,    28,    14,    15,    16,    17,    12,    13,
      25,    26,    79,    33,    45,    73,    86,    86,    86,    86,
      87,    87,    88,    89,    28,    72,    76,    74,    72,     4,
      77,    72
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 11:
#line 87 "parser.y"
    {
                            (yyval) = new Variable(true, true);
                            parser.top->insert_var(*((string *)(yyvsp[(1) - (1)])), (Variable *)(yyval));
                            initializer.set_target((Variable *)(yyval), false);
                        ;}
    break;

  case 13:
#line 93 "parser.y"
    {
                            (yyval) = new Variable(true, (vector<int> *)(yyvsp[(2) - (2)]));
                            parser.top->insert_var(*((string *)(yyvsp[(1) - (2)])), (Variable *)(yyval));
                            initializer.set_target((Variable *)(yyval), true);
                        ;}
    break;

  case 15:
#line 101 "parser.y"
    {
                            (yyval) = new vector<int>;
                            ((vector<int> *)(yyval))->push_back(((Variable *)(yyvsp[(2) - (3)]))->init_val);
                        ;}
    break;

  case 16:
#line 105 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (4)]);
                            ((vector<int> *)(yyval))->push_back(((Variable *)(yyvsp[(3) - (4)]))->init_val);
                        ;}
    break;

  case 17:
#line 111 "parser.y"
    {
                            int val = ((Variable *)(yyvsp[(1) - (1)]))->init_val;
                            if (!initializer.is_array) {
                                initializer.target->init_val = val;
                                emit(initializer.target->get_name() + " = " + to_string(val));
                            }
                            else {
                                int pos = initializer.init_next_val(val);
                                emit(initializer.target->get_name() + "[" + to_string(pos * 4) + "] = " + to_string(val));
                            }
                            ((Variable *)(yyvsp[(1) - (1)]))->rel_seqno();
                        ;}
    break;

  case 18:
#line 123 "parser.y"
    {
                            pair<int, int> p = initializer.increase_dim();
                            string name = initializer.target->get_name();
                            loop_init_to_zero(name, p.first, p.second);
                            int pos = initializer.init_next_val(0);
                            emit(name + "[" + to_string(pos * 4) + "] = 0");
                        ;}
    break;

  case 19:
#line 130 "parser.y"
    {
                            pair<int, int> p = initializer.decrease_dim();
                            string name = initializer.target->get_name();
                            loop_init_to_zero(name, p.first, p.second);
                        ;}
    break;

  case 20:
#line 135 "parser.y"
    {
                            pair<int, int> p = initializer.increase_dim();
                            string name = initializer.target->get_name();
                            loop_init_to_zero(name, p.first, p.second);
                        ;}
    break;

  case 21:
#line 140 "parser.y"
    {
                            pair<int, int> p = initializer.decrease_dim();
                            string name = initializer.target->get_name();
                            loop_init_to_zero(name, p.first, p.second);
                        ;}
    break;

  case 27:
#line 158 "parser.y"
    {
                            (yyval) = new Variable(false, true);
                            parser.top->insert_var(*((string *)(yyvsp[(1) - (1)])), (Variable *)(yyval));
                            if (parser.is_global())
                                emit(((Variable *)(yyval))->get_name() + " = 0");
                        ;}
    break;

  case 28:
#line 164 "parser.y"
    {
                            (yyval) = new Variable(false, true);
                            parser.top->insert_var(*((string *)(yyvsp[(1) - (1)])), (Variable *)(yyval));
                            initializer.set_target((Variable *)(yyval), false);
                        ;}
    break;

  case 30:
#line 170 "parser.y"
    {
                            (yyval) = new Variable(false, (vector<int> *)(yyvsp[(2) - (2)]));
                            parser.top->insert_var(*((string *)(yyvsp[(1) - (2)])), (Variable *)(yyval));
                            if (parser.is_global()) {
                                string name = ((Variable *)(yyval))->get_name();
                                loop_init_to_zero(name, 0, ((Variable *)(yyval))->size);
                            }
                        ;}
    break;

  case 31:
#line 178 "parser.y"
    {
                            (yyval) = new Variable(false, (vector<int> *)(yyvsp[(2) - (2)]));
                            parser.top->insert_var(*((string *)(yyvsp[(1) - (2)])), (Variable *)(yyval));
                            initializer.set_target((Variable *)(yyval), true);
                        ;}
    break;

  case 33:
#line 186 "parser.y"
    {
                            string name = ((Variable *)(yyvsp[(1) - (1)]))->get_name();
                            if (!initializer.is_array)
                                emit(initializer.target->get_name() + " = " + name);
                            else {
                                int pos = initializer.init_next_val(0);
                                emit(initializer.target->get_name() + "[" + to_string(pos * 4) + "] = " + name);
                            }
                            ((Variable *)(yyvsp[(1) - (1)]))->rel_seqno();
                        ;}
    break;

  case 34:
#line 196 "parser.y"
    {
                            pair<int, int> p = initializer.increase_dim();
                            string name = initializer.target->get_name();
                            loop_init_to_zero(name, p.first, p.second);
                            int pos = initializer.init_next_val(0);
                            emit(name + "[" + to_string(pos * 4) + "] = 0");
                        ;}
    break;

  case 35:
#line 203 "parser.y"
    {
                            pair<int, int> p = initializer.decrease_dim();
                            string name = initializer.target->get_name();
                            loop_init_to_zero(name, p.first, p.second);
                        ;}
    break;

  case 36:
#line 208 "parser.y"
    {
                            pair<int, int> p = initializer.increase_dim();
                            string name = initializer.target->get_name();
                            loop_init_to_zero(name, p.first, p.second);
                        ;}
    break;

  case 37:
#line 213 "parser.y"
    {
                            pair<int, int> p = initializer.decrease_dim();
                            string name = initializer.target->get_name();
                            loop_init_to_zero(name, p.first, p.second);
                        ;}
    break;

  case 40:
#line 224 "parser.y"
    {
                            emit("f_" + *((string *)(yyvsp[(2) - (4)])) + " [0]");
                            Function * func = new Function(false, 0);
                            parser.add_func(*((string *)(yyvsp[(2) - (4)])), func);
                        ;}
    break;

  case 41:
#line 229 "parser.y"
    {
                            if (instructions.back().substr(0, 6) != "return")
                                emit("return");
                            emit("end f_" + *((string *)(yyvsp[(2) - (6)])));
                        ;}
    break;

  case 42:
#line 234 "parser.y"
    {
                            parser.new_symtab();
                        ;}
    break;

  case 43:
#line 237 "parser.y"
    {
                            emit("f_" + *((string *)(yyvsp[(2) - (6)])) + " [" + to_string(*((int *)(yyvsp[(5) - (6)]))) + "]");
                            Function * func = new Function(false, *((int *)(yyvsp[(5) - (6)])));
                            parser.add_func(*((string *)(yyvsp[(2) - (6)])), func);
                        ;}
    break;

  case 44:
#line 242 "parser.y"
    {
                            if (instructions.back().substr(0, 6) != "return")
                                emit("return");
                            emit("end f_" + *((string *)(yyvsp[(2) - (8)])));
                            parser.del_symtab();
                        ;}
    break;

  case 45:
#line 248 "parser.y"
    {
                            emit("f_" + *((string *)(yyvsp[(2) - (4)])) + " [0]");
                            Function * func = new Function(true, 0);
                            parser.add_func(*((string *)(yyvsp[(2) - (4)])), func);
                        ;}
    break;

  case 46:
#line 253 "parser.y"
    {
                            if (instructions.back().substr(0, 6) != "return")
                                emit("return 0");
                            emit("end f_" + *((string *)(yyvsp[(2) - (6)])));
                        ;}
    break;

  case 47:
#line 258 "parser.y"
    {
                            parser.new_symtab();
                        ;}
    break;

  case 48:
#line 261 "parser.y"
    {
                            emit("f_" + *((string *)(yyvsp[(2) - (6)])) + " [" + to_string(*((int *)(yyvsp[(5) - (6)]))) + "]");
                            Function * func = new Function(true, *((int *)(yyvsp[(5) - (6)])));
                            parser.add_func(*((string *)(yyvsp[(2) - (6)])), func);
                        ;}
    break;

  case 49:
#line 266 "parser.y"
    {
                            if (instructions.back().substr(0, 6) != "return")
                                emit("return 0");
                            emit("end f_" + *((string *)(yyvsp[(2) - (8)])));
                            parser.del_symtab();
                        ;}
    break;

  case 50:
#line 274 "parser.y"
    {
                            (yyval) = new int;
                            *((int *)(yyval)) = 0;
                            Variable * param = new Variable(true, *((int *)(yyval)));
                            (*((int *)(yyval)))++;
                            parser.top->insert_var(*((string *)(yyvsp[(2) - (2)])), param);
                        ;}
    break;

  case 51:
#line 281 "parser.y"
    {
                            (yyval) = new int;
                            *((int *)(yyval)) = 0;
                            vector<int> * shape = new vector<int>;
                            shape->push_back(0);
                            Variable * param = new Variable(*((int *)(yyval)), shape);
                            (*((int *)(yyval)))++;
                            parser.top->insert_var(*((string *)(yyvsp[(2) - (4)])), param);
                        ;}
    break;

  case 52:
#line 290 "parser.y"
    {
                            (yyval) = new int;
                            *((int *)(yyval)) = 0;
                            vector<int> * shape = new vector<int>;
                            shape->push_back(0);
                            shape->insert(shape->end(), ((vector<int> *)(yyvsp[(5) - (5)]))->begin(), ((vector<int> *)(yyvsp[(5) - (5)]))->end());
                            Variable * param = new Variable(*((int *)(yyval)), shape);
                            (*((int *)(yyval)))++;
                            parser.top->insert_var(*((string *)(yyvsp[(2) - (5)])), param);
                        ;}
    break;

  case 53:
#line 300 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (4)]);
                            Variable * param = new Variable(true, *((int *)(yyval)));
                            (*((int *)(yyval)))++;
                            parser.top->insert_var(*((string *)(yyvsp[(4) - (4)])), param);
                        ;}
    break;

  case 54:
#line 306 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (6)]);
                            vector<int> * shape = new vector<int>;
                            shape->push_back(0);
                            Variable * param = new Variable(*((int *)(yyval)), shape);
                            (*((int *)(yyval)))++;
                            parser.top->insert_var(*((string *)(yyvsp[(4) - (6)])), param);
                        ;}
    break;

  case 55:
#line 314 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (7)]);
                            vector<int> * shape = new vector<int>;
                            shape->push_back(0);
                            shape->insert(shape->end(), ((vector<int> *)(yyvsp[(7) - (7)]))->begin(), ((vector<int> *)(yyvsp[(7) - (7)]))->end());
                            Variable * param = new Variable(*((int *)(yyval)), shape);
                            (*((int *)(yyval)))++;
                            parser.top->insert_var(*((string *)(yyvsp[(4) - (7)])), param);
                        ;}
    break;

  case 57:
#line 326 "parser.y"
    {
                            parser.new_symtab();
                        ;}
    break;

  case 58:
#line 329 "parser.y"
    {
                            parser.del_symtab();
                        ;}
    break;

  case 64:
#line 343 "parser.y"
    {
                            emit(((Variable *)(yyvsp[(1) - (4)]))->get_name() + " = " + ((Variable *)(yyvsp[(3) - (4)]))->get_name());
                            if (((Variable *)(yyvsp[(1) - (4)]))->is_access())
                                ((Variable *)(yyvsp[(1) - (4)]))->offset->rel_seqno();
                            ((Variable *)(yyvsp[(3) - (4)]))->rel_seqno();
                        ;}
    break;

  case 68:
#line 352 "parser.y"
    {
                            (yyvsp[(1) - (4)]) = new IfStmt(*((int *)(yyvsp[(3) - (4)])), parser.alloc_label(), parser.alloc_label());
                            emit("goto l" + to_string(((IfStmt *)(yyvsp[(1) - (4)]))->false_label));
                            emit("l" + to_string(((IfStmt *)(yyvsp[(1) - (4)]))->true_label) + ":");
                        ;}
    break;

  case 69:
#line 357 "parser.y"
    {
                            emit("goto l" + to_string(((IfStmt *)(yyvsp[(1) - (6)]))->next_label));
                            emit("l" + to_string(((IfStmt *)(yyvsp[(1) - (6)]))->false_label) + ":");
                        ;}
    break;

  case 70:
#line 361 "parser.y"
    {
                            emit("l" + to_string(((IfStmt *)(yyvsp[(1) - (8)]))->next_label) + ":");
                            delete (IfStmt *)(yyvsp[(1) - (8)]);
                        ;}
    break;

  case 71:
#line 365 "parser.y"
    {
                            (yyvsp[(1) - (1)]) = new WhileLoop(parser.alloc_label(), parser.alloc_label());
                            parser.add_while((WhileLoop *)(yyvsp[(1) - (1)]));
                            emit("l" + to_string(((WhileLoop *)(yyvsp[(1) - (1)]))->begin_label) + ":");
                        ;}
    break;

  case 72:
#line 370 "parser.y"
    {
                            emit("goto l" + to_string(((WhileLoop *)(yyvsp[(1) - (5)]))->next_label));
                            emit("l" + to_string(*((int *)(yyvsp[(4) - (5)]))) + ":");
                        ;}
    break;

  case 73:
#line 374 "parser.y"
    {
                            emit("goto l" + to_string(((WhileLoop *)(yyvsp[(1) - (7)]))->begin_label));
                            emit("l" + to_string(((WhileLoop *)(yyvsp[(1) - (7)]))->next_label) + ":");
                            parser.pop_while();
                        ;}
    break;

  case 74:
#line 379 "parser.y"
    {
                            WhileLoop * current = parser.get_curr_while();
                            emit("goto l" + to_string(current->next_label));
                        ;}
    break;

  case 75:
#line 383 "parser.y"
    {
                            WhileLoop * current = parser.get_curr_while();
                            emit("goto l" + to_string(current->begin_label));
                        ;}
    break;

  case 76:
#line 387 "parser.y"
    {
                            emit("return");
                        ;}
    break;

  case 77:
#line 390 "parser.y"
    {
                            emit("return " + ((Variable *)(yyvsp[(2) - (3)]))->get_name());
                            ((Variable *)(yyvsp[(2) - (3)]))->rel_seqno();
                        ;}
    break;

  case 80:
#line 400 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 81:
#line 405 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 82:
#line 410 "parser.y"
    {
                            string name = *((string *)(yyvsp[(1) - (1)]));
                            (yyval) = parser.top->find_var(name);
                        ;}
    break;

  case 83:
#line 414 "parser.y"
    {
                            string name = *((string *)(yyvsp[(1) - (2)]));
                            Variable * var = parser.top->find_var(name);
                            vector<Variable *> & pos = *((vector<Variable *> *)(yyvsp[(2) - (2)]));
                            const vector<int> & mul_shape = var->get_mul_shape();
                            bool all_have_init_val = true;
                            int len = pos.size();
                            int sum_offset = 0;
                            for (int i = 0; i < len; i++) {
                                if (!pos[i]->have_init_val())
                                    all_have_init_val = false;
                                else
                                    sum_offset += pos[i]->init_val * mul_shape[i];
                            }
                            if (all_have_init_val) {
                                if (pos.size() == mul_shape.size()) {
                                    if (var->have_init_val())
                                        (yyval) = new Variable(var->array_value[sum_offset / 4]);
                                    else {
                                        Variable * var_offset = new Variable(sum_offset);
                                        (yyval) = new Variable(var, var_offset);
                                    }
                                }
                                else {
                                    (yyval) = new Variable(false);
                                    emit(((Variable *)(yyval))->get_name() + " = " + var->get_name() + " + " + to_string(sum_offset));
                                    var->rel_seqno();
                                }
                            }
                            else {
                                Variable * var_offset = new Variable(false);
                                emit(var_offset->get_name() + " = " + to_string(sum_offset));
                                Variable * temp = new Variable(false);
                                for (int i = 0; i < len; i++) {
                                    if (!pos[i]->have_init_val()) {
                                        emit(temp->get_name() + " = " + pos[i]->get_name() + " * " + to_string(mul_shape[i]));
                                        pos[i]->rel_seqno();
                                        emit(var_offset->get_name() + " = " + var_offset->get_name() + " + " + temp->get_name());
                                    }
                                }
                                temp->rel_seqno();
                                if (pos.size() == mul_shape.size())
                                    (yyval) = new Variable(var, var_offset);
                                else {
                                    (yyval) = new Variable(false);
                                    emit(((Variable *)(yyval))->get_name() + " = " + var->get_name() + " + " + var_offset->get_name());
                                    var->rel_seqno();
                                    var_offset->rel_seqno();
                                }
                            }
                        ;}
    break;

  case 84:
#line 467 "parser.y"
    {
                            (yyval) = new vector<Variable *>;
                            ((vector<Variable *> *)(yyval))->push_back((Variable *)(yyvsp[(2) - (3)]));
                        ;}
    break;

  case 85:
#line 471 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (4)]);
                            ((vector<Variable *> *)(yyval))->push_back((Variable *)(yyvsp[(3) - (4)]));
                        ;}
    break;

  case 86:
#line 477 "parser.y"
    {
                            (yyval) = (yyvsp[(2) - (3)]);
                        ;}
    break;

  case 87:
#line 480 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (1)]))->is_access()) {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (1)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (1)]))->offset->rel_seqno();
                            }
                            else
                                (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 88:
#line 489 "parser.y"
    {
                            (yyval) = new Variable(*((int *)(yyvsp[(1) - (1)])));
                        ;}
    break;

  case 89:
#line 494 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 90:
#line 497 "parser.y"
    {
                            string name = *((string *)(yyvsp[(1) - (3)]));
                            if (name == "starttime") {
                                emit("param "+ to_string(yylineno));
                                emit("call f__sysy_starttime");
                            }
                            else if (name == "stoptime") {
                                emit("param "+ to_string(yylineno));
                                emit("call f__sysy_stoptime");
                            }
                            else {
                                Function * func = parser.get_func(name);
                                if (func->ret_int) {
                                    (yyval) = new Variable(false);
                                    emit(((Variable *)(yyval))->get_name() + " = call f_" + name);
                                }
                                else
                                    emit("call f_" + name);
                            }
                        ;}
    break;

  case 91:
#line 517 "parser.y"
    {
                            string name = *((string *)(yyvsp[(1) - (4)]));
                            Function * func = parser.get_func(name);
                            vector<Variable *> & params = *((vector<Variable *> *)(yyvsp[(3) - (4)]));
                            if (params.size() != func->param_count)
                                yyerror("function get wrong parameters");
                            for (vector<Variable *>::iterator it = params.begin(); it != params.end(); it++) {
                                emit("param " + (*it)->get_name());
                                (*it)->rel_seqno();
                            }
                            if (func->ret_int) {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = call f_" + name);
                            }
                            else
                                emit("call f_" + name);
                        ;}
    break;

  case 92:
#line 534 "parser.y"
    {
                            (yyval) = (yyvsp[(2) - (2)]);
                        ;}
    break;

  case 93:
#line 537 "parser.y"
    {
                            if (((Variable *)(yyvsp[(2) - (2)]))->have_init_val())
                                (yyval) = new Variable(-1 * ((Variable *)(yyvsp[(2) - (2)]))->init_val);
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = - " + ((Variable *)(yyvsp[(2) - (2)]))->get_name());
                                ((Variable *)(yyvsp[(2) - (2)]))->rel_seqno();
                            }
                        ;}
    break;

  case 94:
#line 546 "parser.y"
    {
                            if (((Variable *)(yyvsp[(2) - (2)]))->have_init_val()) {
                                if ((((Variable *)(yyvsp[(2) - (2)]))->init_val) == 0)
                                    (yyval) = new Variable(1);
                                else
                                    (yyval) = new Variable(0);
                            }
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = ! " + ((Variable *)(yyvsp[(2) - (2)]))->get_name());
                                ((Variable *)(yyvsp[(2) - (2)]))->rel_seqno();
                            }
                        ;}
    break;

  case 95:
#line 561 "parser.y"
    {
                            (yyval) = new vector<Variable *>;
                            ((vector<Variable *> *)(yyval))->push_back((Variable *)(yyvsp[(1) - (1)]));
                        ;}
    break;

  case 96:
#line 565 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (3)]);
                            ((vector<Variable *> *)(yyval))->push_back((Variable *)(yyvsp[(3) - (3)]));
                        ;}
    break;

  case 97:
#line 571 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 98:
#line 574 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable(((Variable *)(yyvsp[(1) - (3)]))->init_val * ((Variable *)(yyvsp[(3) - (3)]))->init_val);
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " * " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 99:
#line 584 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable(((Variable *)(yyvsp[(1) - (3)]))->init_val / ((Variable *)(yyvsp[(3) - (3)]))->init_val);
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " / " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 100:
#line 594 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable(((Variable *)(yyvsp[(1) - (3)]))->init_val % ((Variable *)(yyvsp[(3) - (3)]))->init_val);
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " % " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 101:
#line 606 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 102:
#line 609 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable(((Variable *)(yyvsp[(1) - (3)]))->init_val + ((Variable *)(yyvsp[(3) - (3)]))->init_val);
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " + " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 103:
#line 619 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable(((Variable *)(yyvsp[(1) - (3)]))->init_val - ((Variable *)(yyvsp[(3) - (3)]))->init_val);
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " - " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 104:
#line 631 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 105:
#line 634 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable((int)(((Variable *)(yyvsp[(1) - (3)]))->init_val < ((Variable *)(yyvsp[(3) - (3)]))->init_val));
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " < " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 106:
#line 644 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable((int)(((Variable *)(yyvsp[(1) - (3)]))->init_val > ((Variable *)(yyvsp[(3) - (3)]))->init_val));
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " > " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 107:
#line 654 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable((int)(((Variable *)(yyvsp[(1) - (3)]))->init_val <= ((Variable *)(yyvsp[(3) - (3)]))->init_val));
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " <= " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 108:
#line 664 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable((int)(((Variable *)(yyvsp[(1) - (3)]))->init_val >= ((Variable *)(yyvsp[(3) - (3)]))->init_val));
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " >= " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 109:
#line 676 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;

  case 110:
#line 679 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable((int)(((Variable *)(yyvsp[(1) - (3)]))->init_val == ((Variable *)(yyvsp[(3) - (3)]))->init_val));
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " == " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 111:
#line 689 "parser.y"
    {
                            if (((Variable *)(yyvsp[(1) - (3)]))->have_init_val() && ((Variable *)(yyvsp[(3) - (3)]))->have_init_val())
                                (yyval) = new Variable((int)(((Variable *)(yyvsp[(1) - (3)]))->init_val != ((Variable *)(yyvsp[(3) - (3)]))->init_val));
                            else {
                                (yyval) = new Variable(false);
                                emit(((Variable *)(yyval))->get_name() + " = " + ((Variable *)(yyvsp[(1) - (3)]))->get_name() + " != " + ((Variable *)(yyvsp[(3) - (3)]))->get_name());
                                ((Variable *)(yyvsp[(1) - (3)]))->rel_seqno();
                                ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                            }
                        ;}
    break;

  case 112:
#line 701 "parser.y"
    {
                            (yyval) = new int;
                            *((int *)(yyval)) = parser.alloc_label();
                            emit("if " + ((Variable *)(yyvsp[(1) - (1)]))->get_name() + " == 0 goto l" + to_string(*((int *)(yyval))));
                            ((Variable *)(yyvsp[(1) - (1)]))->rel_seqno();
                        ;}
    break;

  case 113:
#line 707 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (3)]);
                            emit("if " + ((Variable *)(yyvsp[(3) - (3)]))->get_name() + " == 0 goto l" + to_string(*((int *)(yyval))));
                            ((Variable *)(yyvsp[(3) - (3)]))->rel_seqno();
                        ;}
    break;

  case 114:
#line 714 "parser.y"
    {
                            (yyval) = new int;
                            *((int *)(yyval)) = parser.alloc_label();
                            emit("goto l" + to_string(*((int *)(yyval))));
                            emit("l" + to_string(*((int *)(yyvsp[(1) - (1)]))) + ":");
                        ;}
    break;

  case 115:
#line 720 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (3)]);
                            emit("goto l" + to_string(*((int *)(yyval))));
                            emit("l" + to_string(*((int *)(yyvsp[(3) - (3)]))) + ":");
                        ;}
    break;

  case 116:
#line 727 "parser.y"
    {
                            (yyval) = (yyvsp[(1) - (1)]);
                        ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2528 "parser.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 732 "parser.y"


void add_sys_calls() {
    parser.add_func("getint", new Function(true, 0));
    parser.add_func("getch", new Function(true, 0));
    parser.add_func("getarray", new Function(true, 1));
    parser.add_func("putint", new Function(false, 1));
    parser.add_func("putch", new Function(false, 1));
    parser.add_func("putarray", new Function(false, 2));
}

void del_temp_var() {
    for (vector<Variable *>::iterator it = del_var.begin(); it != del_var.end(); it++)
        delete *it;
}

int main(int argc, char ** argv) {
    bool to_eeyore = false;
    bool to_tigger = false;
    bool to_riscv = false;
    if (argc == 5) {
        if ((yyin = fopen(argv[2], "r")) == NULL) {
            cerr << "can't open " << argv[3] << endl;
            exit(1);
        }
        if (freopen(argv[4], "w", stdout) == NULL) {
            cerr << "can't open " << argv[5] << endl;
            exit(1);
        }
        to_riscv = true;
    }
    else if (argc == 6) {
        if ((yyin = fopen(argv[3], "r")) == NULL) {
            cerr << "can't open " << argv[3] << endl;
            exit(1);
        }
        if (freopen(argv[5], "w", stdout) == NULL) {
            cerr << "can't open " << argv[5] << endl;
            exit(1);
        }
        if (argv[2][1] == 't')
            to_tigger = true;
        else if (argv[2][1] == 'e')
            to_eeyore = true;
        else {
            cerr << "wrong parameter " << argv[2] << endl;
            exit(1);
        }
    }
    else {
        cerr << "wrong parameter" << endl;
        exit(1);
    }
    add_sys_calls();
    yyparse();
    del_temp_var();
    EeyoreGenerator eeyoregenerator(instructions);
    if (to_eeyore) {
        for (vector<string>::iterator it = eeyoregenerator.eeyore.begin(); it != eeyoregenerator.eeyore.end(); it++)
            cout << *it << endl;
        return 0;
    }
    TiggerGenerator tiggergenerator(eeyoregenerator.eeyore);
    if (to_tigger) {
        for (vector<string>::iterator it = tiggergenerator.tigger.begin(); it != tiggergenerator.tigger.end(); it++)
            cout << *it << endl;
        return 0;
    }
    RiscvGenerator riscvgenerator(tiggergenerator.tigger);
    if (to_riscv) {
        for (vector<string>::iterator it = riscvgenerator.riscv.begin(); it != riscvgenerator.riscv.end(); it++)
            cout << *it << endl;
    }
    return 0;
}
