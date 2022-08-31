/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

