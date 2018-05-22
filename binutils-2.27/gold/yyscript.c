/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 26 "yyscript.y" /* yacc.c:339  */


#include "config.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "script-c.h"


#line 79 "yyscript.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_YYSCRIPT_H_INCLUDED
# define YY_YY_YYSCRIPT_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PLUSEQ = 258,
    MINUSEQ = 259,
    MULTEQ = 260,
    DIVEQ = 261,
    LSHIFTEQ = 262,
    RSHIFTEQ = 263,
    ANDEQ = 264,
    OREQ = 265,
    OROR = 266,
    ANDAND = 267,
    EQ = 268,
    NE = 269,
    LE = 270,
    GE = 271,
    LSHIFT = 272,
    RSHIFT = 273,
    UNARY = 274,
    STRING = 275,
    QUOTED_STRING = 276,
    INTEGER = 277,
    ABSOLUTE = 278,
    ADDR = 279,
    ALIGN_K = 280,
    ALIGNOF = 281,
    ASSERT_K = 282,
    AS_NEEDED = 283,
    AT = 284,
    BIND = 285,
    BLOCK = 286,
    BYTE = 287,
    CONSTANT = 288,
    CONSTRUCTORS = 289,
    COPY = 290,
    CREATE_OBJECT_SYMBOLS = 291,
    DATA_SEGMENT_ALIGN = 292,
    DATA_SEGMENT_END = 293,
    DATA_SEGMENT_RELRO_END = 294,
    DEFINED = 295,
    DSECT = 296,
    ENTRY = 297,
    EXCLUDE_FILE = 298,
    EXTERN = 299,
    FILL = 300,
    FLOAT = 301,
    FORCE_COMMON_ALLOCATION = 302,
    GLOBAL = 303,
    GROUP = 304,
    HLL = 305,
    INCLUDE = 306,
    INHIBIT_COMMON_ALLOCATION = 307,
    INFO = 308,
    INPUT = 309,
    KEEP = 310,
    LEN = 311,
    LENGTH = 312,
    LOADADDR = 313,
    LOCAL = 314,
    LONG = 315,
    MAP = 316,
    MAX_K = 317,
    MEMORY = 318,
    MIN_K = 319,
    NEXT = 320,
    NOCROSSREFS = 321,
    NOFLOAT = 322,
    NOLOAD = 323,
    ONLY_IF_RO = 324,
    ONLY_IF_RW = 325,
    ORG = 326,
    ORIGIN = 327,
    OUTPUT = 328,
    OUTPUT_ARCH = 329,
    OUTPUT_FORMAT = 330,
    OVERLAY = 331,
    PHDRS = 332,
    PROVIDE = 333,
    PROVIDE_HIDDEN = 334,
    QUAD = 335,
    SEARCH_DIR = 336,
    SECTIONS = 337,
    SEGMENT_START = 338,
    SHORT = 339,
    SIZEOF = 340,
    SIZEOF_HEADERS = 341,
    SORT_BY_ALIGNMENT = 342,
    SORT_BY_INIT_PRIORITY = 343,
    SORT_BY_NAME = 344,
    SPECIAL = 345,
    SQUAD = 346,
    STARTUP = 347,
    SUBALIGN = 348,
    SYSLIB = 349,
    TARGET_K = 350,
    TRUNCATE = 351,
    VERSIONK = 352,
    OPTION = 353,
    PARSING_LINKER_SCRIPT = 354,
    PARSING_VERSION_SCRIPT = 355,
    PARSING_DEFSYM = 356,
    PARSING_DYNAMIC_LIST = 357,
    PARSING_SECTIONS_BLOCK = 358,
    PARSING_SECTION_COMMANDS = 359,
    PARSING_MEMORY_DEF = 360
  };
#endif
/* Tokens.  */
#define PLUSEQ 258
#define MINUSEQ 259
#define MULTEQ 260
#define DIVEQ 261
#define LSHIFTEQ 262
#define RSHIFTEQ 263
#define ANDEQ 264
#define OREQ 265
#define OROR 266
#define ANDAND 267
#define EQ 268
#define NE 269
#define LE 270
#define GE 271
#define LSHIFT 272
#define RSHIFT 273
#define UNARY 274
#define STRING 275
#define QUOTED_STRING 276
#define INTEGER 277
#define ABSOLUTE 278
#define ADDR 279
#define ALIGN_K 280
#define ALIGNOF 281
#define ASSERT_K 282
#define AS_NEEDED 283
#define AT 284
#define BIND 285
#define BLOCK 286
#define BYTE 287
#define CONSTANT 288
#define CONSTRUCTORS 289
#define COPY 290
#define CREATE_OBJECT_SYMBOLS 291
#define DATA_SEGMENT_ALIGN 292
#define DATA_SEGMENT_END 293
#define DATA_SEGMENT_RELRO_END 294
#define DEFINED 295
#define DSECT 296
#define ENTRY 297
#define EXCLUDE_FILE 298
#define EXTERN 299
#define FILL 300
#define FLOAT 301
#define FORCE_COMMON_ALLOCATION 302
#define GLOBAL 303
#define GROUP 304
#define HLL 305
#define INCLUDE 306
#define INHIBIT_COMMON_ALLOCATION 307
#define INFO 308
#define INPUT 309
#define KEEP 310
#define LEN 311
#define LENGTH 312
#define LOADADDR 313
#define LOCAL 314
#define LONG 315
#define MAP 316
#define MAX_K 317
#define MEMORY 318
#define MIN_K 319
#define NEXT 320
#define NOCROSSREFS 321
#define NOFLOAT 322
#define NOLOAD 323
#define ONLY_IF_RO 324
#define ONLY_IF_RW 325
#define ORG 326
#define ORIGIN 327
#define OUTPUT 328
#define OUTPUT_ARCH 329
#define OUTPUT_FORMAT 330
#define OVERLAY 331
#define PHDRS 332
#define PROVIDE 333
#define PROVIDE_HIDDEN 334
#define QUAD 335
#define SEARCH_DIR 336
#define SECTIONS 337
#define SEGMENT_START 338
#define SHORT 339
#define SIZEOF 340
#define SIZEOF_HEADERS 341
#define SORT_BY_ALIGNMENT 342
#define SORT_BY_INIT_PRIORITY 343
#define SORT_BY_NAME 344
#define SPECIAL 345
#define SQUAD 346
#define STARTUP 347
#define SUBALIGN 348
#define SYSLIB 349
#define TARGET_K 350
#define TRUNCATE 351
#define VERSIONK 352
#define OPTION 353
#define PARSING_LINKER_SCRIPT 354
#define PARSING_VERSION_SCRIPT 355
#define PARSING_DEFSYM 356
#define PARSING_DYNAMIC_LIST 357
#define PARSING_SECTIONS_BLOCK 358
#define PARSING_SECTION_COMMANDS 359
#define PARSING_MEMORY_DEF 360

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 53 "yyscript.y" /* yacc.c:355  */

  /* A string.  */
  struct Parser_string string;
  /* A number.  */
  uint64_t integer;
  /* An expression.  */
  Expression_ptr expr;
  /* An output section header.  */
  struct Parser_output_section_header output_section_header;
  /* An output section trailer.  */
  struct Parser_output_section_trailer output_section_trailer;
  /* A section constraint.  */
  enum Section_constraint constraint;
  /* A complete input section specification.  */
  struct Input_section_spec input_section_spec;
  /* A list of wildcard specifications, with exclusions.  */
  struct Wildcard_sections wildcard_sections;
  /* A single wildcard specification.  */
  struct Wildcard_section wildcard_section;
  /* A list of strings.  */
  String_list_ptr string_list;
  /* Information for a program header.  */
  struct Phdr_info phdr_info;
  /* Used for version scripts and within VERSION {}.  */
  struct Version_dependency_list* deplist;
  struct Version_expression_list* versyms;
  struct Version_tree* versnode;
  enum Script_section_type section_type;

#line 359 "yyscript.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void* closure);

#endif /* !YY_YY_YYSCRIPT_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 373 "yyscript.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  26
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1464

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  129
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  240
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  549

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   360

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   125,     2,     2,     2,    31,    18,     2,
     119,   120,    29,    27,   123,    28,     2,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    13,   124,
      21,     7,    22,    12,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    17,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   127,     2,
       2,   126,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   121,    16,   122,   128,     2,     2,     2,
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
       5,     6,     8,     9,    10,    11,    14,    15,    19,    20,
      23,    24,    25,    26,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   235,   235,   236,   237,   238,   239,   240,   241,   246,
     247,   252,   253,   256,   255,   259,   261,   262,   263,   265,
     271,   278,   279,   282,   281,   285,   288,   287,   291,   293,
     294,   296,   299,   300,   308,   316,   316,   322,   324,   326,
     332,   333,   338,   340,   343,   342,   350,   351,   356,   358,
     359,   361,   365,   364,   373,   375,   373,   392,   397,   402,
     407,   412,   417,   426,   428,   433,   438,   443,   453,   454,
     461,   462,   469,   470,   477,   478,   480,   482,   488,   497,
     499,   504,   506,   511,   514,   520,   523,   528,   530,   536,
     537,   538,   540,   542,   544,   551,   552,   555,   561,   563,
     565,   567,   569,   576,   578,   584,   591,   600,   605,   614,
     619,   624,   629,   638,   643,   662,   681,   690,   692,   699,
     701,   706,   715,   716,   721,   724,   727,   732,   735,   738,
     742,   744,   746,   750,   752,   754,   759,   760,   765,   774,
     776,   783,   784,   792,   797,   808,   817,   819,   825,   831,
     837,   843,   849,   855,   861,   867,   869,   875,   875,   885,
     887,   889,   891,   893,   895,   897,   899,   901,   903,   905,
     907,   909,   911,   913,   915,   917,   919,   921,   923,   925,
     927,   929,   931,   933,   935,   937,   939,   941,   943,   945,
     947,   949,   951,   953,   955,   957,   959,   961,   963,   965,
     967,   972,   977,   979,   987,   993,  1003,  1006,  1007,  1011,
    1017,  1021,  1022,  1026,  1030,  1035,  1042,  1046,  1054,  1055,
    1057,  1059,  1061,  1070,  1075,  1080,  1085,  1092,  1091,  1102,
    1101,  1108,  1113,  1123,  1125,  1132,  1133,  1138,  1139,  1144,
    1145
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PLUSEQ", "MINUSEQ", "MULTEQ", "DIVEQ",
  "'='", "LSHIFTEQ", "RSHIFTEQ", "ANDEQ", "OREQ", "'?'", "':'", "OROR",
  "ANDAND", "'|'", "'^'", "'&'", "EQ", "NE", "'<'", "'>'", "LE", "GE",
  "LSHIFT", "RSHIFT", "'+'", "'-'", "'*'", "'/'", "'%'", "UNARY", "STRING",
  "QUOTED_STRING", "INTEGER", "ABSOLUTE", "ADDR", "ALIGN_K", "ALIGNOF",
  "ASSERT_K", "AS_NEEDED", "AT", "BIND", "BLOCK", "BYTE", "CONSTANT",
  "CONSTRUCTORS", "COPY", "CREATE_OBJECT_SYMBOLS", "DATA_SEGMENT_ALIGN",
  "DATA_SEGMENT_END", "DATA_SEGMENT_RELRO_END", "DEFINED", "DSECT",
  "ENTRY", "EXCLUDE_FILE", "EXTERN", "FILL", "FLOAT",
  "FORCE_COMMON_ALLOCATION", "GLOBAL", "GROUP", "HLL", "INCLUDE",
  "INHIBIT_COMMON_ALLOCATION", "INFO", "INPUT", "KEEP", "LEN", "LENGTH",
  "LOADADDR", "LOCAL", "LONG", "MAP", "MAX_K", "MEMORY", "MIN_K", "NEXT",
  "NOCROSSREFS", "NOFLOAT", "NOLOAD", "ONLY_IF_RO", "ONLY_IF_RW", "ORG",
  "ORIGIN", "OUTPUT", "OUTPUT_ARCH", "OUTPUT_FORMAT", "OVERLAY", "PHDRS",
  "PROVIDE", "PROVIDE_HIDDEN", "QUAD", "SEARCH_DIR", "SECTIONS",
  "SEGMENT_START", "SHORT", "SIZEOF", "SIZEOF_HEADERS",
  "SORT_BY_ALIGNMENT", "SORT_BY_INIT_PRIORITY", "SORT_BY_NAME", "SPECIAL",
  "SQUAD", "STARTUP", "SUBALIGN", "SYSLIB", "TARGET_K", "TRUNCATE",
  "VERSIONK", "OPTION", "PARSING_LINKER_SCRIPT", "PARSING_VERSION_SCRIPT",
  "PARSING_DEFSYM", "PARSING_DYNAMIC_LIST", "PARSING_SECTIONS_BLOCK",
  "PARSING_SECTION_COMMANDS", "PARSING_MEMORY_DEF", "'('", "')'", "'{'",
  "'}'", "','", "';'", "'!'", "'o'", "'l'", "'~'", "$accept", "top",
  "linker_script", "file_cmd", "$@1", "$@2", "$@3", "ignore_cmd",
  "extern_name_list", "$@4", "extern_name_list_body", "input_list",
  "input_list_element", "$@5", "sections_block", "section_block_cmd",
  "$@6", "section_header", "$@7", "$@8", "opt_address_and_section_type",
  "section_type", "opt_at", "opt_align", "opt_subalign", "opt_constraint",
  "section_trailer", "opt_memspec", "opt_at_memspec", "opt_phdr",
  "opt_fill", "section_cmds", "section_cmd", "data_length",
  "input_section_spec", "input_section_no_keep", "wildcard_file",
  "wildcard_sections", "wildcard_section", "exclude_names",
  "wildcard_name", "memory_defs", "memory_def", "memory_attr",
  "memory_origin", "memory_length", "phdrs_defs", "phdr_def", "phdr_type",
  "phdr_info", "assignment", "parse_exp", "$@9", "exp", "defsym_expr",
  "dynamic_list_expr", "dynamic_list_nodes", "dynamic_list_node",
  "version_script", "vers_nodes", "vers_node", "verdep", "vers_tag",
  "vers_defns", "$@10", "$@11", "string", "end", "opt_semicolon",
  "opt_comma", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,    61,   262,   263,
     264,   265,    63,    58,   266,   267,   124,    94,    38,   268,
     269,    60,    62,   270,   271,   272,   273,    43,    45,    42,
      47,    37,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,    40,
      41,   123,   125,    44,    59,    33,   111,   108,   126
};
# endif

#define YYPACT_NINF -417

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-417)))

#define YYTABLE_NINF -120

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     239,  -417,    24,   103,  -107,  -417,  -417,  -417,    27,   589,
    -417,  -417,   135,  -417,    24,  -417,   -62,  -417,    57,   175,
    -417,  -107,  -417,   179,   570,     8,  -417,   -45,   -36,   -32,
    -417,  -417,   103,  -417,     3,    -7,    10,    45,     6,    51,
      59,    71,    93,    97,   106,   114,  -417,  -417,  -417,  -105,
     314,  -417,  -417,   103,    91,   227,    26,   121,  -417,   135,
    -417,   126,  -417,   150,   161,   103,  -417,  -105,   314,  -417,
    -417,   166,  -417,  -417,   191,   103,   192,  -417,  -417,  -417,
     194,  -417,  -417,  -417,   196,  -417,  -417,   208,  -417,  -105,
      37,  -417,    46,  -417,   103,  -417,   213,  -417,   146,  -417,
     103,   103,  -417,   103,   103,   103,  -417,   103,  -417,   103,
    -417,  -417,  -417,  -417,  -417,  -417,  -417,  -417,  -417,  -417,
    -417,  -417,   158,   175,   175,   132,   189,   215,  -417,  1336,
      -5,  -417,   103,  -417,  -417,  -417,   332,  -417,  -417,  -417,
      42,   219,  -417,    99,  -417,   103,  -417,   225,   224,   228,
     229,   103,   146,   325,  -417,   -70,  -417,  -417,    29,   241,
       1,    32,   355,   356,   244,  -417,   253,    24,   254,  -417,
    -417,  -417,  -417,  -417,  -417,  -417,  -417,  -417,  -417,   251,
     255,  -417,  -417,  -417,   103,   -24,  1336,  1336,  -417,   258,
     261,   267,   270,   271,   272,   273,   275,   276,   280,   282,
     286,   287,   289,   299,   300,   301,   304,  -417,  1336,  1336,
    1336,  1205,  -417,   263,   303,   317,   318,  -417,  1240,   382,
    1227,   315,   320,   323,   324,   326,   327,   329,  -417,   330,
     334,   337,   339,   342,    75,  -417,  -417,  -417,   -10,   430,
     103,  -417,  -417,   -17,  -417,   119,  -417,   344,  -417,   146,
    -417,  -417,  -417,   103,  -417,  -417,   296,  -417,  -417,  -417,
     133,  -417,   343,  -417,   175,   187,   189,   345,  -417,    -8,
    -417,  -417,  -417,  1336,   103,  1336,   103,  1336,  1336,   103,
    1336,  1336,  1336,   103,   103,   103,  1336,  1336,   103,   103,
     103,   864,  -417,  -417,  1336,  1336,  1336,  1336,  1336,  1336,
    1336,  1336,  1336,  1336,  1336,  1336,  1336,  1336,  1336,  1336,
    1336,  1336,  1336,  -417,   103,  -417,  -417,  -417,  -417,  -417,
    -417,  -417,   433,   348,   350,   426,  -417,   137,   103,  -417,
      55,  -417,  -417,  -417,  -417,    55,   160,    55,   160,  -417,
     128,   103,   352,    -3,   353,   103,  -417,  -417,   146,  -417,
     347,  -417,    28,  -417,   354,   359,  -417,  -417,   351,   463,
    -417,  -417,  -417,   884,   362,   482,   363,   717,   904,   364,
     754,   937,   774,   365,   366,   367,   794,   827,   368,   370,
     369,  -417,   277,   734,   567,   842,   951,   807,   915,   915,
     385,   385,   385,   385,   405,   405,   311,   311,  -417,  -417,
    -417,   371,   113,  -417,   477,  1336,   376,   408,   502,   396,
     397,   145,  -417,   398,   399,   401,   403,  -417,   404,  -417,
    -417,  -417,  -417,   516,  -417,  -417,   153,   103,   406,    28,
     407,    44,  -417,  -417,   189,   410,   175,   175,  -417,  -417,
    -417,  1336,  -417,   103,  -417,  -417,  1336,  -417,  1336,  -417,
    -417,  -417,  1336,  1336,  -417,  1336,  -417,  1336,  -417,   506,
    -417,   971,  1336,   411,  -417,  -417,   520,  -417,  -417,    55,
    -417,  -417,  -417,    55,  -417,  -417,  -417,   414,  -417,  -417,
    -417,   500,  -417,  -417,   412,   351,   991,   417,  1011,  1044,
    1078,  1098,  1118,  1205,   103,  -417,   496,  -417,  1151,  1336,
     181,  -417,  -417,   155,   416,  -417,   422,   424,   189,   425,
    -417,  -417,  -417,  -417,  -417,  -417,  -417,  -417,   529,  -417,
    -417,  1185,  -417,  -417,  -417,  -417,  -417,    -1,    28,    28,
    -417,   103,    78,  -417,  -417,  -417,  -417,   545,  -417,  -417,
    -417,  -417,   103,   416,  -417,  -417,  -417,  -417,  -417
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,     0,     0,     0,    47,    87,   123,     0,     2,
     233,   234,   218,     3,   210,   211,     0,     4,     0,     0,
       5,   206,   207,     6,     7,   240,     1,     0,     0,     0,
      12,    13,     0,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    33,     9,    32,     0,
       0,   223,   224,   231,     0,     0,     0,     0,   212,   218,
     157,     0,   208,     0,     0,     0,    46,     0,    54,   121,
     120,     0,   102,    94,     0,     0,     0,   100,    98,   101,
       0,    99,    97,    88,     0,    90,   103,     0,   107,     0,
     105,   239,   126,   157,     0,    35,     0,    31,     0,   123,
       0,     0,   137,     0,     0,     0,    23,     0,    26,     0,
     236,   235,    29,   157,   157,   157,   157,   157,   157,   157,
     157,   157,     0,     0,     0,     0,   219,     0,   205,     0,
       0,   157,     0,    51,    49,    52,     0,   157,   157,    96,
       0,     0,   157,     0,    89,     0,   122,   129,     0,     0,
       0,     0,     0,     0,    44,   240,    40,    42,   240,     0,
       0,     0,     0,     0,     0,    47,     0,     0,     0,   147,
     148,   149,   150,   146,   151,   152,   153,   154,   227,     0,
       0,   213,   225,   226,   232,     0,     0,     0,   183,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   188,     0,     0,
       0,   158,   184,     0,     0,     0,     0,    57,     0,    68,
       0,     0,     0,     0,     0,   105,     0,     0,   119,     0,
       0,     0,     0,     0,   240,   110,   113,   125,     0,     0,
       0,    28,    11,    36,    37,   240,    43,     0,    16,     0,
      17,    34,    19,     0,    21,   136,     0,   157,   157,    22,
       0,    25,     0,    18,     0,   220,   221,     0,   214,     0,
     216,   163,   160,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   161,   162,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   209,     0,    48,    87,    65,    64,    66,
      63,    67,     0,     0,     0,    70,    59,     0,     0,    93,
       0,   104,    95,   108,    91,     0,     0,     0,     0,   106,
       0,     0,     0,     0,     0,     0,    38,    14,     0,    41,
       0,   140,   141,   139,     0,     0,    24,    27,   238,     0,
     229,   215,   217,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,     0,   181,   180,   179,   178,   177,   171,   172,
     175,   176,   173,   174,   169,   170,   167,   168,   164,   165,
     166,     0,     0,    58,     0,     0,     0,    72,     0,     0,
       0,   240,   118,     0,     0,     0,     0,   109,     0,   127,
     131,   130,   132,     0,    30,    39,   240,     0,     0,   141,
       0,   141,   155,   156,   237,     0,     0,     0,   196,   191,
     197,     0,   189,     0,   199,   195,     0,   202,     0,   187,
     194,   192,     0,     0,   193,     0,   190,     0,    50,    80,
      61,     0,     0,     0,    55,    60,     0,    92,   112,     0,
     115,   116,   114,     0,   128,   157,    45,     0,   157,   143,
     138,     0,   142,   228,     0,   238,     0,     0,     0,     0,
       0,     0,     0,   182,     0,    53,    82,    69,     0,     0,
      74,    62,   117,   240,   240,    20,     0,     0,   222,     0,
     198,   204,   200,   201,   185,   186,   203,    79,     0,    84,
      71,     0,    75,    76,    77,    56,   111,     0,   141,   141,
     230,     0,    86,    73,   134,   133,   135,     0,   145,   144,
      81,   157,     0,   240,   157,    85,    83,    78,   124
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -417,  -417,  -417,  -417,  -417,  -417,  -417,  -417,  -417,  -417,
    -417,  -146,   307,  -417,   388,  -417,  -417,  -417,  -417,  -417,
    -417,   230,  -417,  -417,  -417,  -417,  -417,  -417,  -417,  -417,
    -417,   242,  -417,  -417,  -417,   419,  -417,  -417,  -243,    87,
     -21,   462,  -417,  -417,  -417,  -417,  -417,  -417,  -417,  -416,
      -4,   -82,  -417,   268,  -417,  -417,  -417,   560,   434,  -417,
     586,  -417,   547,   -15,  -417,  -417,    -2,     5,   122,   -23
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    47,    96,   165,   167,    48,   150,   151,
     243,   155,   156,   247,    23,    66,   216,   135,   136,   500,
     219,   323,   325,   407,   464,   525,   495,   496,   519,   532,
     543,    24,    83,    84,    85,    86,    87,   234,   235,   411,
     236,    25,   146,   239,   423,   537,   161,   255,   352,   430,
      67,   128,   129,   291,    17,    20,    21,    22,    13,    14,
      15,   269,    56,    57,   264,   437,   212,   112,   435,   249
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,    18,    92,    88,    61,    49,   245,    50,    -8,    10,
      11,   148,    16,   479,    19,   482,    10,    11,   110,   111,
      89,    68,    90,    10,    11,    10,    11,    26,   182,   183,
      97,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   214,
     248,   122,   184,    91,    69,   221,   222,    10,    11,    59,
     229,    10,    11,   133,    60,    10,    11,    69,   534,   535,
     428,    70,   134,   139,    93,    10,    11,    10,    11,    10,
      11,   420,   421,    94,    70,   541,   428,    95,    10,    11,
     147,   542,   149,   413,   144,   415,   157,   417,   159,   160,
     268,   162,   163,   164,   123,   166,   345,   168,   179,   180,
     145,    69,   538,   539,    99,   341,   361,   213,   429,    88,
     227,   252,    98,   422,   253,    69,   536,   102,    70,   100,
     215,    91,    10,    11,   429,    92,    10,    11,   225,   228,
      69,   228,    70,   237,   223,    12,    10,    11,   125,   244,
     157,   250,    91,    71,   254,   230,  -119,    70,    72,   256,
      73,    10,    11,   481,   101,    16,    10,    11,    51,    52,
     103,    74,    69,    63,   153,   354,   355,    75,   104,    10,
      11,    76,   267,   270,   416,   317,    77,   154,    64,    70,
     105,   318,    53,    10,    11,   339,    54,    65,    91,   231,
     232,   233,   426,   319,    39,    40,    78,    55,    51,    52,
      79,   340,    10,    11,   106,    80,   107,    81,   320,    63,
     182,   183,   182,   183,    39,    40,   321,   108,   231,   232,
     233,    69,    53,   109,    64,   459,   342,    82,   344,   347,
     124,   346,    91,    65,   184,   126,   184,   157,    70,   358,
     130,   350,    10,    11,   353,   356,   181,   408,    68,   359,
     231,   232,   233,   522,   523,   468,   226,   362,    91,   131,
      39,    40,   364,   476,   366,   526,    91,   369,    91,   178,
     132,   373,   374,   375,   524,   137,   378,   379,   380,   294,
     457,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   227,
     138,   140,   401,   141,   412,   142,   414,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   410,   143,   228,    10,
      11,   351,   152,   228,   228,   228,   228,   185,   228,   418,
     310,   311,   312,   425,   238,   217,   157,   240,   241,   242,
     431,     1,     2,     3,     4,     5,     6,     7,   246,   186,
     187,   251,   257,   258,   259,    10,    11,   188,   189,   190,
     191,   192,   193,   261,   263,   265,   194,   273,   195,   266,
     274,    88,   196,   197,   198,   199,   275,   313,   469,   276,
     277,   278,   279,   504,   280,   281,   506,   211,    89,   282,
      90,   283,   200,   201,   220,   284,   285,   202,   286,   203,
     306,   307,   308,   309,   310,   311,   312,   204,   287,   288,
     289,   484,   485,   290,   324,   477,   314,   431,   205,   431,
     206,   207,   308,   309,   310,   311,   312,   315,   328,   316,
     329,   487,   330,   343,   331,  -119,   403,   332,   502,   333,
     334,   218,   412,   335,   271,   272,   336,   209,   337,   545,
     210,   338,   548,   348,   406,   357,   360,   228,   404,   405,
     427,   228,   419,   424,   432,   434,   436,   292,   293,   433,
     469,   527,   439,   442,   445,   449,   450,   451,   454,   456,
     460,   458,   517,   455,   294,   462,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   463,   465,   466,   467,   470,   471,
     547,   472,   473,   475,   474,   478,   431,   431,   494,   540,
     499,   480,   483,   501,   505,   507,   508,   511,   518,    91,
     546,   363,   528,   365,   529,   367,   368,   530,   370,   371,
     372,   531,   544,   260,   376,   377,   349,   409,   402,   224,
     503,   158,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     400,    62,    69,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,    70,
      58,   262,   440,    10,    11,   441,   127,   509,     0,     0,
      71,     0,     0,     0,     0,    72,     0,    73,     0,     0,
       0,     0,    10,    11,     0,     0,     0,     0,    74,    27,
       0,     0,     0,     0,    75,     0,     0,     0,    76,     0,
       0,     0,     0,    77,    28,     0,    29,     0,     0,    30,
       0,    31,     0,    32,    33,     0,    34,     0,     0,     0,
       0,    39,    40,    78,     0,    35,     0,    79,     0,     0,
       0,     0,    80,   461,    81,     0,    36,    37,     0,    38,
      39,    40,     0,    41,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,     0,    43,     0,    44,
      45,     0,     0,     0,     0,     0,     0,     0,     0,   486,
       0,     0,     0,    46,   488,     0,   489,     0,     0,     0,
     490,   491,     0,   492,     0,   493,     0,     0,     0,   294,
     498,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   294,   521,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   294,     0,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   294,     0,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   294,
     443,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,     0,     0,   294,   446,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   294,   448,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   294,   452,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,     0,     0,   294,
     453,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   294,   381,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   294,   438,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   294,   444,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   294,   447,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     294,   497,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     294,   510,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     294,   512,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   294,   513,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   294,   514,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   294,   515,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,     0,   516,   294,
     326,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,     0,
       0,     0,     0,     0,     0,     0,     0,   186,   187,     0,
       0,   520,     0,    10,    11,   188,   189,   190,   191,   192,
     193,     0,     0,     0,   194,     0,   195,     0,   317,     0,
     196,   197,   198,   199,   318,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   533,   319,     0,     0,     0,
     200,   201,     0,     0,     0,   202,     0,   203,     0,     0,
       0,   320,     0,     0,     0,   204,     0,     0,     0,   321,
       0,     0,     0,     0,     0,     0,   205,     0,   206,   207,
       0,     0,     0,     0,     0,     0,   327,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   208,
     322,     0,     0,   186,   187,   209,     0,     0,   210,    10,
      11,   188,   189,   190,   191,   192,   193,     0,     0,     0,
     194,     0,   195,     0,     0,     0,   196,   197,   198,   199,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   200,   201,     0,     0,
       0,   202,     0,   203,     0,     0,     0,     0,     0,     0,
       0,   204,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   205,     0,   206,   207,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   208,     0,     0,     0,     0,
       0,   209,     0,     0,   210
};

static const yytype_int16 yycheck[] =
{
       2,     3,    25,    24,    19,     9,   152,     9,     0,    33,
      34,    93,    14,   429,   121,   431,    33,    34,   123,   124,
      24,    23,    24,    33,    34,    33,    34,     0,    33,    34,
      32,   113,   114,   115,   116,   117,   118,   119,   120,   121,
       3,     4,     5,     6,     7,     8,     9,    10,    11,   131,
     120,    53,    57,   123,    12,   137,   138,    33,    34,   121,
     142,    33,    34,    65,     7,    33,    34,    12,    69,    70,
      42,    29,    67,    75,   119,    33,    34,    33,    34,    33,
      34,    84,    85,   119,    29,     7,    42,   119,    33,    34,
      92,    13,    94,   336,    89,   338,    98,   340,   100,   101,
     124,   103,   104,   105,    13,   107,   123,   109,   123,   124,
      64,    12,   528,   529,   121,   125,   124,   122,    90,   140,
     141,   120,   119,   126,   123,    12,   127,   121,    29,   119,
     132,   123,    33,    34,    90,   158,    33,    34,   140,   141,
      12,   143,    29,   145,   102,   121,    33,    34,   122,   151,
     152,   122,   123,    40,   122,    56,   119,    29,    45,   161,
      47,    33,    34,   119,   119,   167,    33,    34,    33,    34,
     119,    58,    12,    40,    28,   257,   258,    64,   119,    33,
      34,    68,   184,   185,    56,    48,    73,    41,    55,    29,
     119,    54,    57,    33,    34,   120,    61,    64,   123,   100,
     101,   102,   348,    66,    91,    92,    93,    72,    33,    34,
      97,   234,    33,    34,   121,   102,   119,   104,    81,    40,
      33,    34,    33,    34,    91,    92,    89,   121,   100,   101,
     102,    12,    57,   119,    55,   122,   238,   124,   240,   120,
      13,   243,   123,    64,    57,   124,    57,   249,    29,   264,
     124,   253,    33,    34,   256,   122,   124,   120,   260,    72,
     100,   101,   102,    82,    83,   120,    47,   269,   123,   119,
      91,    92,   274,   120,   276,   120,   123,   279,   123,   121,
     119,   283,   284,   285,   103,   119,   288,   289,   290,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,   330,
     119,   119,   314,   119,   335,   119,   337,     3,     4,     5,
       6,     7,     8,     9,    10,    11,   328,   119,   330,    33,
      34,    35,   119,   335,   336,   337,   338,   122,   340,   341,
      29,    30,    31,   345,   119,    13,   348,   123,   120,   120,
     352,   112,   113,   114,   115,   116,   117,   118,    33,    27,
      28,   120,     7,     7,   120,    33,    34,    35,    36,    37,
      38,    39,    40,   120,   120,   124,    44,   119,    46,   124,
     119,   402,    50,    51,    52,    53,   119,   124,   411,   119,
     119,   119,   119,   475,   119,   119,   478,   129,   402,   119,
     402,   119,    70,    71,   136,   119,   119,    75,   119,    77,
      25,    26,    27,    28,    29,    30,    31,    85,   119,   119,
     119,   436,   437,   119,    42,   427,   123,   429,    96,   431,
      98,    99,    27,    28,    29,    30,    31,   120,   123,   121,
     120,   443,   119,    13,   120,   119,    13,   120,   469,   120,
     120,   119,   473,   119,   186,   187,   119,   125,   119,   541,
     128,   119,   544,   119,    38,   122,   121,   469,   120,   119,
     123,   473,   120,   120,   120,   124,    13,   209,   210,   120,
     503,   504,   120,   120,   120,   120,   120,   120,   120,   120,
      13,   120,   494,   123,    12,   119,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   106,    13,   120,   120,   120,   120,
     543,   120,   119,     7,   120,   119,   528,   529,    22,   531,
     119,   124,   122,    13,   120,    35,   124,   120,    42,   123,
     542,   273,   120,   275,   120,   277,   278,   122,   280,   281,
     282,    22,     7,   165,   286,   287,   249,   327,   316,   140,
     473,    99,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,    21,    12,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    29,
      14,   167,   120,    33,    34,   123,    59,   485,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    58,    40,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    68,    -1,
      -1,    -1,    -1,    73,    55,    -1,    57,    -1,    -1,    60,
      -1,    62,    -1,    64,    65,    -1,    67,    -1,    -1,    -1,
      -1,    91,    92,    93,    -1,    76,    -1,    97,    -1,    -1,
      -1,    -1,   102,   405,   104,    -1,    87,    88,    -1,    90,
      91,    92,    -1,    94,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,    -1,    -1,   108,    -1,   110,
     111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   441,
      -1,    -1,    -1,   124,   446,    -1,   448,    -1,    -1,    -1,
     452,   453,    -1,   455,    -1,   457,    -1,    -1,    -1,    12,
     462,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    12,   499,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    12,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    12,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    12,
     123,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    12,   123,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    12,   123,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    12,   123,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    12,
     123,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    12,   120,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    12,   120,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    12,   120,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,   120,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,   120,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      12,   120,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      12,   120,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    12,   120,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,   120,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    12,   120,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,   120,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,
      -1,   120,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    44,    -1,    46,    -1,    48,    -1,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,    66,    -1,    -1,    -1,
      70,    71,    -1,    -1,    -1,    75,    -1,    77,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,
     120,    -1,    -1,    27,    28,   125,    -1,    -1,   128,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      44,    -1,    46,    -1,    -1,    -1,    50,    51,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    -1,    -1,
      -1,    75,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    98,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,    -1,
      -1,   125,    -1,    -1,   128
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   112,   113,   114,   115,   116,   117,   118,   130,   131,
      33,    34,   121,   187,   188,   189,   195,   183,   195,   121,
     184,   185,   186,   143,   160,   170,     0,    40,    55,    57,
      60,    62,    64,    65,    67,    76,    87,    88,    90,    91,
      92,    94,    95,   108,   110,   111,   124,   132,   136,   179,
     195,    33,    34,    57,    61,    72,   191,   192,   189,   121,
       7,   192,   186,    40,    55,    64,   144,   179,   195,    12,
      29,    40,    45,    47,    58,    64,    68,    73,    93,    97,
     102,   104,   124,   161,   162,   163,   164,   165,   169,   179,
     195,   123,   198,   119,   119,   119,   133,   195,   119,   121,
     119,   119,   121,   119,   119,   119,   121,   119,   121,   119,
     123,   124,   196,     3,     4,     5,     6,     7,     8,     9,
      10,    11,   195,    13,    13,   122,   124,   191,   180,   181,
     124,   119,   119,   195,   196,   146,   147,   119,   119,   195,
     119,   119,   119,   119,   196,    64,   171,   195,   180,   195,
     137,   138,   119,    28,    41,   140,   141,   195,   170,   195,
     195,   175,   195,   195,   195,   134,   195,   135,   195,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   121,   192,
     192,   124,    33,    34,    57,   122,    27,    28,    35,    36,
      37,    38,    39,    40,    44,    46,    50,    51,    52,    53,
      70,    71,    75,    77,    85,    96,    98,    99,   119,   125,
     128,   182,   195,   122,   180,   195,   145,    13,   119,   149,
     182,   180,   180,   102,   164,   195,    47,   169,   195,   180,
      56,   100,   101,   102,   166,   167,   169,   195,   119,   172,
     123,   120,   120,   139,   195,   140,    33,   142,   120,   198,
     122,   120,   120,   123,   122,   176,   195,     7,     7,   120,
     143,   120,   187,   120,   193,   124,   124,   195,   124,   190,
     195,   182,   182,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   182,   182,   182,    12,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,   124,   123,   120,   121,    48,    54,    66,
      81,    89,   120,   150,    42,   151,    13,   119,   123,   120,
     119,   120,   120,   120,   120,   119,   119,   119,   119,   120,
     198,   125,   195,    13,   195,   123,   195,   120,   119,   141,
     195,    35,   177,   195,   180,   180,   122,   122,   192,    72,
     121,   124,   195,   182,   195,   182,   195,   182,   182,   195,
     182,   182,   182,   195,   195,   195,   182,   182,   195,   195,
     195,   120,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   195,   160,    13,   120,   119,    38,   152,   120,   150,
     195,   168,   169,   167,   169,   167,    56,   167,   195,   120,
      84,    85,   126,   173,   120,   195,   140,   123,    42,    90,
     178,   195,   120,   120,   124,   197,    13,   194,   120,   120,
     120,   123,   120,   123,   120,   120,   123,   120,   123,   120,
     120,   120,   123,   123,   120,   123,   120,    13,   120,   122,
      13,   182,   119,   106,   153,    13,   120,   120,   120,   198,
     120,   120,   120,   119,   120,     7,   120,   195,   119,   178,
     124,   119,   178,   122,   192,   192,   182,   195,   182,   182,
     182,   182,   182,   182,    22,   155,   156,   120,   182,   119,
     148,    13,   169,   168,   180,   120,   180,    35,   124,   197,
     120,   120,   120,   120,   120,   120,   120,   195,    42,   157,
     120,   182,    82,    83,   103,   154,   120,   198,   120,   120,
     122,    22,   158,   120,    69,    70,   127,   174,   178,   178,
     195,     7,    13,   159,     7,   180,   195,   198,   180
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   129,   130,   130,   130,   130,   130,   130,   130,   131,
     131,   132,   132,   133,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   134,   132,   132,   135,   132,   132,   132,
     132,   132,   132,   132,   136,   138,   137,   139,   139,   139,
     140,   140,   141,   141,   142,   141,   143,   143,   144,   144,
     144,   144,   145,   144,   147,   148,   146,   149,   149,   149,
     149,   149,   149,   150,   150,   150,   150,   150,   151,   151,
     152,   152,   153,   153,   154,   154,   154,   154,   155,   156,
     156,   157,   157,   158,   158,   159,   159,   160,   160,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   162,   162,
     162,   162,   162,   163,   163,   164,   164,   165,   165,   166,
     166,   166,   166,   167,   167,   167,   167,   168,   168,   169,
     169,   169,   170,   170,   171,   171,   171,   172,   172,   172,
     173,   173,   173,   174,   174,   174,   175,   175,   176,   177,
     177,   178,   178,   178,   178,   178,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   181,   180,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   183,   184,   185,   185,   186,
     187,   188,   188,   189,   189,   189,   190,   190,   191,   191,
     191,   191,   191,   192,   192,   192,   192,   193,   192,   194,
     192,   192,   192,   195,   195,   196,   196,   197,   197,   198,
     198
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       0,     4,     1,     0,     5,     1,     4,     4,     4,     4,
       8,     4,     4,     0,     5,     4,     0,     5,     4,     2,
       6,     2,     1,     1,     4,     0,     2,     1,     2,     3,
       1,     3,     1,     2,     0,     5,     2,     0,     4,     2,
       6,     2,     0,     7,     0,     0,     7,     1,     3,     2,
       4,     4,     5,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     1,     1,     1,     5,     2,
       0,     3,     0,     3,     0,     2,     0,     0,     2,     2,
       1,     4,     6,     4,     1,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     4,     1,     4,     3,
       1,     6,     4,     1,     4,     4,     4,     3,     1,     1,
       1,     1,     3,     0,    10,     2,     0,     3,     4,     0,
       1,     1,     1,     1,     1,     1,     2,     0,     4,     1,
       1,     0,     2,     2,     5,     5,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     6,     6,     0,     2,     3,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     5,     1,     1,     6,     6,     4,     1,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     6,     4,
       6,     6,     4,     6,     6,     3,     1,     1,     2,     5,
       1,     1,     2,     4,     5,     6,     1,     2,     0,     2,
       4,     4,     8,     1,     1,     3,     3,     0,     7,     0,
       9,     1,     3,     1,     1,     1,     1,     1,     0,     1,
       0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (closure, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, closure); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void* closure)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (closure);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void* closure)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, closure);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, void* closure)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , closure);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, closure); \
} while (0)

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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void* closure)
{
  YYUSE (yyvaluep);
  YYUSE (closure);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void* closure)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, closure);
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 12:
#line 254 "yyscript.y" /* yacc.c:1646  */
    { script_set_common_allocation(closure, 1); }
#line 2041 "yyscript.c" /* yacc.c:1646  */
    break;

  case 13:
#line 256 "yyscript.y" /* yacc.c:1646  */
    { script_start_group(closure); }
#line 2047 "yyscript.c" /* yacc.c:1646  */
    break;

  case 14:
#line 258 "yyscript.y" /* yacc.c:1646  */
    { script_end_group(closure); }
#line 2053 "yyscript.c" /* yacc.c:1646  */
    break;

  case 15:
#line 260 "yyscript.y" /* yacc.c:1646  */
    { script_set_common_allocation(closure, 0); }
#line 2059 "yyscript.c" /* yacc.c:1646  */
    break;

  case 18:
#line 264 "yyscript.y" /* yacc.c:1646  */
    { script_parse_option(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 2065 "yyscript.c" /* yacc.c:1646  */
    break;

  case 19:
#line 266 "yyscript.y" /* yacc.c:1646  */
    {
	      if (!script_check_output_format(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length,
					      NULL, 0, NULL, 0))
		YYABORT;
	    }
#line 2075 "yyscript.c" /* yacc.c:1646  */
    break;

  case 20:
#line 272 "yyscript.y" /* yacc.c:1646  */
    {
	      if (!script_check_output_format(closure, (yyvsp[-5].string).value, (yyvsp[-5].string).length,
					      (yyvsp[-3].string).value, (yyvsp[-3].string).length,
					      (yyvsp[-1].string).value, (yyvsp[-1].string).length))
		YYABORT;
	    }
#line 2086 "yyscript.c" /* yacc.c:1646  */
    break;

  case 22:
#line 280 "yyscript.y" /* yacc.c:1646  */
    { script_add_search_dir(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 2092 "yyscript.c" /* yacc.c:1646  */
    break;

  case 23:
#line 282 "yyscript.y" /* yacc.c:1646  */
    { script_start_sections(closure); }
#line 2098 "yyscript.c" /* yacc.c:1646  */
    break;

  case 24:
#line 284 "yyscript.y" /* yacc.c:1646  */
    { script_finish_sections(closure); }
#line 2104 "yyscript.c" /* yacc.c:1646  */
    break;

  case 25:
#line 286 "yyscript.y" /* yacc.c:1646  */
    { script_set_target(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 2110 "yyscript.c" /* yacc.c:1646  */
    break;

  case 26:
#line 288 "yyscript.y" /* yacc.c:1646  */
    { script_push_lex_into_version_mode(closure); }
#line 2116 "yyscript.c" /* yacc.c:1646  */
    break;

  case 27:
#line 290 "yyscript.y" /* yacc.c:1646  */
    { script_pop_lex_mode(closure); }
#line 2122 "yyscript.c" /* yacc.c:1646  */
    break;

  case 28:
#line 292 "yyscript.y" /* yacc.c:1646  */
    { script_set_entry(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 2128 "yyscript.c" /* yacc.c:1646  */
    break;

  case 30:
#line 295 "yyscript.y" /* yacc.c:1646  */
    { script_add_assertion(closure, (yyvsp[-3].expr), (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 2134 "yyscript.c" /* yacc.c:1646  */
    break;

  case 31:
#line 297 "yyscript.y" /* yacc.c:1646  */
    { script_include_directive(PARSING_LINKER_SCRIPT, closure,
				       (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2141 "yyscript.c" /* yacc.c:1646  */
    break;

  case 35:
#line 316 "yyscript.y" /* yacc.c:1646  */
    { script_push_lex_into_expression_mode(closure); }
#line 2147 "yyscript.c" /* yacc.c:1646  */
    break;

  case 36:
#line 318 "yyscript.y" /* yacc.c:1646  */
    { script_pop_lex_mode(closure); }
#line 2153 "yyscript.c" /* yacc.c:1646  */
    break;

  case 37:
#line 323 "yyscript.y" /* yacc.c:1646  */
    { script_add_extern(closure, (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2159 "yyscript.c" /* yacc.c:1646  */
    break;

  case 38:
#line 325 "yyscript.y" /* yacc.c:1646  */
    { script_add_extern(closure, (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2165 "yyscript.c" /* yacc.c:1646  */
    break;

  case 39:
#line 327 "yyscript.y" /* yacc.c:1646  */
    { script_add_extern(closure, (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2171 "yyscript.c" /* yacc.c:1646  */
    break;

  case 42:
#line 339 "yyscript.y" /* yacc.c:1646  */
    { script_add_file(closure, (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2177 "yyscript.c" /* yacc.c:1646  */
    break;

  case 43:
#line 341 "yyscript.y" /* yacc.c:1646  */
    { script_add_library(closure, (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2183 "yyscript.c" /* yacc.c:1646  */
    break;

  case 44:
#line 343 "yyscript.y" /* yacc.c:1646  */
    { script_start_as_needed(closure); }
#line 2189 "yyscript.c" /* yacc.c:1646  */
    break;

  case 45:
#line 345 "yyscript.y" /* yacc.c:1646  */
    { script_end_as_needed(closure); }
#line 2195 "yyscript.c" /* yacc.c:1646  */
    break;

  case 48:
#line 357 "yyscript.y" /* yacc.c:1646  */
    { script_set_entry(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 2201 "yyscript.c" /* yacc.c:1646  */
    break;

  case 50:
#line 360 "yyscript.y" /* yacc.c:1646  */
    { script_add_assertion(closure, (yyvsp[-3].expr), (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 2207 "yyscript.c" /* yacc.c:1646  */
    break;

  case 51:
#line 362 "yyscript.y" /* yacc.c:1646  */
    { script_include_directive(PARSING_SECTIONS_BLOCK, closure,
				       (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2214 "yyscript.c" /* yacc.c:1646  */
    break;

  case 52:
#line 365 "yyscript.y" /* yacc.c:1646  */
    { script_start_output_section(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length, &(yyvsp[0].output_section_header)); }
#line 2220 "yyscript.c" /* yacc.c:1646  */
    break;

  case 53:
#line 367 "yyscript.y" /* yacc.c:1646  */
    { script_finish_output_section(closure, &(yyvsp[0].output_section_trailer)); }
#line 2226 "yyscript.c" /* yacc.c:1646  */
    break;

  case 54:
#line 373 "yyscript.y" /* yacc.c:1646  */
    { script_push_lex_into_expression_mode(closure); }
#line 2232 "yyscript.c" /* yacc.c:1646  */
    break;

  case 55:
#line 375 "yyscript.y" /* yacc.c:1646  */
    { script_pop_lex_mode(closure); }
#line 2238 "yyscript.c" /* yacc.c:1646  */
    break;

  case 56:
#line 377 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.output_section_header).address = (yyvsp[-5].output_section_header).address;
	      (yyval.output_section_header).section_type = (yyvsp[-5].output_section_header).section_type;
	      (yyval.output_section_header).load_address = (yyvsp[-4].expr);
	      (yyval.output_section_header).align = (yyvsp[-3].expr);
	      (yyval.output_section_header).subalign = (yyvsp[-2].expr);
	      (yyval.output_section_header).constraint = (yyvsp[0].constraint);
	    }
#line 2251 "yyscript.c" /* yacc.c:1646  */
    break;

  case 57:
#line 393 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.output_section_header).address = NULL;
	      (yyval.output_section_header).section_type = SCRIPT_SECTION_TYPE_NONE;
	    }
#line 2260 "yyscript.c" /* yacc.c:1646  */
    break;

  case 58:
#line 398 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.output_section_header).address = NULL;
	      (yyval.output_section_header).section_type = SCRIPT_SECTION_TYPE_NONE;
	    }
#line 2269 "yyscript.c" /* yacc.c:1646  */
    break;

  case 59:
#line 403 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.output_section_header).address = (yyvsp[-1].expr);
	      (yyval.output_section_header).section_type = SCRIPT_SECTION_TYPE_NONE;
	    }
#line 2278 "yyscript.c" /* yacc.c:1646  */
    break;

  case 60:
#line 408 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.output_section_header).address = (yyvsp[-3].expr);
	      (yyval.output_section_header).section_type = SCRIPT_SECTION_TYPE_NONE;
	    }
#line 2287 "yyscript.c" /* yacc.c:1646  */
    break;

  case 61:
#line 413 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.output_section_header).address = NULL;
	      (yyval.output_section_header).section_type = (yyvsp[-2].section_type);
	    }
#line 2296 "yyscript.c" /* yacc.c:1646  */
    break;

  case 62:
#line 418 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.output_section_header).address = (yyvsp[-4].expr);
	      (yyval.output_section_header).section_type = (yyvsp[-2].section_type);
	    }
#line 2305 "yyscript.c" /* yacc.c:1646  */
    break;

  case 63:
#line 427 "yyscript.y" /* yacc.c:1646  */
    { (yyval.section_type) = SCRIPT_SECTION_TYPE_NOLOAD; }
#line 2311 "yyscript.c" /* yacc.c:1646  */
    break;

  case 64:
#line 429 "yyscript.y" /* yacc.c:1646  */
    {
	      yyerror(closure, "DSECT section type is unsupported");
	      (yyval.section_type) = SCRIPT_SECTION_TYPE_DSECT;
	    }
#line 2320 "yyscript.c" /* yacc.c:1646  */
    break;

  case 65:
#line 434 "yyscript.y" /* yacc.c:1646  */
    {
	      yyerror(closure, "COPY section type is unsupported");
	      (yyval.section_type) = SCRIPT_SECTION_TYPE_COPY;
	    }
#line 2329 "yyscript.c" /* yacc.c:1646  */
    break;

  case 66:
#line 439 "yyscript.y" /* yacc.c:1646  */
    {
	      yyerror(closure, "INFO section type is unsupported");
	      (yyval.section_type) = SCRIPT_SECTION_TYPE_INFO;
	    }
#line 2338 "yyscript.c" /* yacc.c:1646  */
    break;

  case 67:
#line 444 "yyscript.y" /* yacc.c:1646  */
    {
	      yyerror(closure, "OVERLAY section type is unsupported");
	      (yyval.section_type) = SCRIPT_SECTION_TYPE_OVERLAY;
	    }
#line 2347 "yyscript.c" /* yacc.c:1646  */
    break;

  case 68:
#line 453 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2353 "yyscript.c" /* yacc.c:1646  */
    break;

  case 69:
#line 455 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2359 "yyscript.c" /* yacc.c:1646  */
    break;

  case 70:
#line 461 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2365 "yyscript.c" /* yacc.c:1646  */
    break;

  case 71:
#line 463 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2371 "yyscript.c" /* yacc.c:1646  */
    break;

  case 72:
#line 469 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2377 "yyscript.c" /* yacc.c:1646  */
    break;

  case 73:
#line 471 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2383 "yyscript.c" /* yacc.c:1646  */
    break;

  case 74:
#line 477 "yyscript.y" /* yacc.c:1646  */
    { (yyval.constraint) = CONSTRAINT_NONE; }
#line 2389 "yyscript.c" /* yacc.c:1646  */
    break;

  case 75:
#line 479 "yyscript.y" /* yacc.c:1646  */
    { (yyval.constraint) = CONSTRAINT_ONLY_IF_RO; }
#line 2395 "yyscript.c" /* yacc.c:1646  */
    break;

  case 76:
#line 481 "yyscript.y" /* yacc.c:1646  */
    { (yyval.constraint) = CONSTRAINT_ONLY_IF_RW; }
#line 2401 "yyscript.c" /* yacc.c:1646  */
    break;

  case 77:
#line 483 "yyscript.y" /* yacc.c:1646  */
    { (yyval.constraint) = CONSTRAINT_SPECIAL; }
#line 2407 "yyscript.c" /* yacc.c:1646  */
    break;

  case 78:
#line 489 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.output_section_trailer).fill = (yyvsp[-1].expr);
	      (yyval.output_section_trailer).phdrs = (yyvsp[-2].string_list);
	    }
#line 2416 "yyscript.c" /* yacc.c:1646  */
    break;

  case 79:
#line 498 "yyscript.y" /* yacc.c:1646  */
    { script_set_section_region(closure, (yyvsp[0].string).value, (yyvsp[0].string).length, 1); }
#line 2422 "yyscript.c" /* yacc.c:1646  */
    break;

  case 81:
#line 505 "yyscript.y" /* yacc.c:1646  */
    { script_set_section_region(closure, (yyvsp[0].string).value, (yyvsp[0].string).length, 0); }
#line 2428 "yyscript.c" /* yacc.c:1646  */
    break;

  case 83:
#line 512 "yyscript.y" /* yacc.c:1646  */
    { (yyval.string_list) = script_string_list_push_back((yyvsp[-2].string_list), (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2434 "yyscript.c" /* yacc.c:1646  */
    break;

  case 84:
#line 514 "yyscript.y" /* yacc.c:1646  */
    { (yyval.string_list) = NULL; }
#line 2440 "yyscript.c" /* yacc.c:1646  */
    break;

  case 85:
#line 521 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2446 "yyscript.c" /* yacc.c:1646  */
    break;

  case 86:
#line 523 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2452 "yyscript.c" /* yacc.c:1646  */
    break;

  case 91:
#line 539 "yyscript.y" /* yacc.c:1646  */
    { script_add_data(closure, (yyvsp[-3].integer), (yyvsp[-1].expr)); }
#line 2458 "yyscript.c" /* yacc.c:1646  */
    break;

  case 92:
#line 541 "yyscript.y" /* yacc.c:1646  */
    { script_add_assertion(closure, (yyvsp[-3].expr), (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 2464 "yyscript.c" /* yacc.c:1646  */
    break;

  case 93:
#line 543 "yyscript.y" /* yacc.c:1646  */
    { script_add_fill(closure, (yyvsp[-1].expr)); }
#line 2470 "yyscript.c" /* yacc.c:1646  */
    break;

  case 94:
#line 545 "yyscript.y" /* yacc.c:1646  */
    {
	      /* The GNU linker uses CONSTRUCTORS for the a.out object
		 file format.  It does nothing when using ELF.  Since
		 some ELF linker scripts use it although it does
		 nothing, we accept it and ignore it.  */
	    }
#line 2481 "yyscript.c" /* yacc.c:1646  */
    break;

  case 96:
#line 553 "yyscript.y" /* yacc.c:1646  */
    { script_include_directive(PARSING_SECTION_COMMANDS, closure,
				       (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2488 "yyscript.c" /* yacc.c:1646  */
    break;

  case 98:
#line 562 "yyscript.y" /* yacc.c:1646  */
    { (yyval.integer) = QUAD; }
#line 2494 "yyscript.c" /* yacc.c:1646  */
    break;

  case 99:
#line 564 "yyscript.y" /* yacc.c:1646  */
    { (yyval.integer) = SQUAD; }
#line 2500 "yyscript.c" /* yacc.c:1646  */
    break;

  case 100:
#line 566 "yyscript.y" /* yacc.c:1646  */
    { (yyval.integer) = LONG; }
#line 2506 "yyscript.c" /* yacc.c:1646  */
    break;

  case 101:
#line 568 "yyscript.y" /* yacc.c:1646  */
    { (yyval.integer) = SHORT; }
#line 2512 "yyscript.c" /* yacc.c:1646  */
    break;

  case 102:
#line 570 "yyscript.y" /* yacc.c:1646  */
    { (yyval.integer) = BYTE; }
#line 2518 "yyscript.c" /* yacc.c:1646  */
    break;

  case 103:
#line 577 "yyscript.y" /* yacc.c:1646  */
    { script_add_input_section(closure, &(yyvsp[0].input_section_spec), 0); }
#line 2524 "yyscript.c" /* yacc.c:1646  */
    break;

  case 104:
#line 579 "yyscript.y" /* yacc.c:1646  */
    { script_add_input_section(closure, &(yyvsp[-1].input_section_spec), 1); }
#line 2530 "yyscript.c" /* yacc.c:1646  */
    break;

  case 105:
#line 585 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.input_section_spec).file.name = (yyvsp[0].string);
	      (yyval.input_section_spec).file.sort = SORT_WILDCARD_NONE;
	      (yyval.input_section_spec).input_sections.sections = NULL;
	      (yyval.input_section_spec).input_sections.exclude = NULL;
	    }
#line 2541 "yyscript.c" /* yacc.c:1646  */
    break;

  case 106:
#line 592 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.input_section_spec).file = (yyvsp[-3].wildcard_section);
	      (yyval.input_section_spec).input_sections = (yyvsp[-1].wildcard_sections);
	    }
#line 2550 "yyscript.c" /* yacc.c:1646  */
    break;

  case 107:
#line 601 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.wildcard_section).name = (yyvsp[0].string);
	      (yyval.wildcard_section).sort = SORT_WILDCARD_NONE;
	    }
#line 2559 "yyscript.c" /* yacc.c:1646  */
    break;

  case 108:
#line 606 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.wildcard_section).name = (yyvsp[-1].string);
	      (yyval.wildcard_section).sort = SORT_WILDCARD_BY_NAME;
	    }
#line 2568 "yyscript.c" /* yacc.c:1646  */
    break;

  case 109:
#line 615 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.wildcard_sections).sections = script_string_sort_list_add((yyvsp[-2].wildcard_sections).sections, &(yyvsp[0].wildcard_section));
	      (yyval.wildcard_sections).exclude = (yyvsp[-2].wildcard_sections).exclude;
	    }
#line 2577 "yyscript.c" /* yacc.c:1646  */
    break;

  case 110:
#line 620 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.wildcard_sections).sections = script_new_string_sort_list(&(yyvsp[0].wildcard_section));
	      (yyval.wildcard_sections).exclude = NULL;
	    }
#line 2586 "yyscript.c" /* yacc.c:1646  */
    break;

  case 111:
#line 625 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.wildcard_sections).sections = (yyvsp[-5].wildcard_sections).sections;
	      (yyval.wildcard_sections).exclude = script_string_list_append((yyvsp[-5].wildcard_sections).exclude, (yyvsp[-1].string_list));
	    }
#line 2595 "yyscript.c" /* yacc.c:1646  */
    break;

  case 112:
#line 630 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.wildcard_sections).sections = NULL;
	      (yyval.wildcard_sections).exclude = (yyvsp[-1].string_list);
	    }
#line 2604 "yyscript.c" /* yacc.c:1646  */
    break;

  case 113:
#line 639 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.wildcard_section).name = (yyvsp[0].string);
	      (yyval.wildcard_section).sort = SORT_WILDCARD_NONE;
	    }
#line 2613 "yyscript.c" /* yacc.c:1646  */
    break;

  case 114:
#line 644 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.wildcard_section).name = (yyvsp[-1].wildcard_section).name;
	      switch ((yyvsp[-1].wildcard_section).sort)
		{
		case SORT_WILDCARD_NONE:
		  (yyval.wildcard_section).sort = SORT_WILDCARD_BY_NAME;
		  break;
		case SORT_WILDCARD_BY_NAME:
		case SORT_WILDCARD_BY_NAME_BY_ALIGNMENT:
		  break;
		case SORT_WILDCARD_BY_ALIGNMENT:
		case SORT_WILDCARD_BY_ALIGNMENT_BY_NAME:
		  (yyval.wildcard_section).sort = SORT_WILDCARD_BY_NAME_BY_ALIGNMENT;
		  break;
		default:
		  abort();
		}
	    }
#line 2636 "yyscript.c" /* yacc.c:1646  */
    break;

  case 115:
#line 663 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.wildcard_section).name = (yyvsp[-1].wildcard_section).name;
	      switch ((yyvsp[-1].wildcard_section).sort)
		{
		case SORT_WILDCARD_NONE:
		  (yyval.wildcard_section).sort = SORT_WILDCARD_BY_ALIGNMENT;
		  break;
		case SORT_WILDCARD_BY_ALIGNMENT:
		case SORT_WILDCARD_BY_ALIGNMENT_BY_NAME:
		  break;
		case SORT_WILDCARD_BY_NAME:
		case SORT_WILDCARD_BY_NAME_BY_ALIGNMENT:
		  (yyval.wildcard_section).sort = SORT_WILDCARD_BY_ALIGNMENT_BY_NAME;
		  break;
		default:
		  abort();
		}
	    }
#line 2659 "yyscript.c" /* yacc.c:1646  */
    break;

  case 116:
#line 682 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.wildcard_section).name = (yyvsp[-1].string);
	      (yyval.wildcard_section).sort = SORT_WILDCARD_BY_INIT_PRIORITY;
	    }
#line 2668 "yyscript.c" /* yacc.c:1646  */
    break;

  case 117:
#line 691 "yyscript.y" /* yacc.c:1646  */
    { (yyval.string_list) = script_string_list_push_back((yyvsp[-2].string_list), (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2674 "yyscript.c" /* yacc.c:1646  */
    break;

  case 118:
#line 693 "yyscript.y" /* yacc.c:1646  */
    { (yyval.string_list) = script_new_string_list((yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2680 "yyscript.c" /* yacc.c:1646  */
    break;

  case 119:
#line 700 "yyscript.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 2686 "yyscript.c" /* yacc.c:1646  */
    break;

  case 120:
#line 702 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.string).value = "*";
	      (yyval.string).length = 1;
	    }
#line 2695 "yyscript.c" /* yacc.c:1646  */
    break;

  case 121:
#line 707 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.string).value = "?";
	      (yyval.string).length = 1;
	    }
#line 2704 "yyscript.c" /* yacc.c:1646  */
    break;

  case 124:
#line 722 "yyscript.y" /* yacc.c:1646  */
    { script_add_memory(closure, (yyvsp[-9].string).value, (yyvsp[-9].string).length, (yyvsp[-8].integer), (yyvsp[-4].expr), (yyvsp[0].expr)); }
#line 2710 "yyscript.c" /* yacc.c:1646  */
    break;

  case 125:
#line 725 "yyscript.y" /* yacc.c:1646  */
    { script_include_directive(PARSING_MEMORY_DEF, closure,
				     (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2717 "yyscript.c" /* yacc.c:1646  */
    break;

  case 127:
#line 733 "yyscript.y" /* yacc.c:1646  */
    { (yyval.integer) = script_parse_memory_attr(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length, 0); }
#line 2723 "yyscript.c" /* yacc.c:1646  */
    break;

  case 128:
#line 736 "yyscript.y" /* yacc.c:1646  */
    { (yyval.integer) = script_parse_memory_attr(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length, 1); }
#line 2729 "yyscript.c" /* yacc.c:1646  */
    break;

  case 129:
#line 738 "yyscript.y" /* yacc.c:1646  */
    { (yyval.integer) = 0; }
#line 2735 "yyscript.c" /* yacc.c:1646  */
    break;

  case 138:
#line 766 "yyscript.y" /* yacc.c:1646  */
    { script_add_phdr(closure, (yyvsp[-3].string).value, (yyvsp[-3].string).length, (yyvsp[-2].integer), &(yyvsp[-1].phdr_info)); }
#line 2741 "yyscript.c" /* yacc.c:1646  */
    break;

  case 139:
#line 775 "yyscript.y" /* yacc.c:1646  */
    { (yyval.integer) = script_phdr_string_to_type(closure, (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 2747 "yyscript.c" /* yacc.c:1646  */
    break;

  case 140:
#line 777 "yyscript.y" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].integer); }
#line 2753 "yyscript.c" /* yacc.c:1646  */
    break;

  case 141:
#line 783 "yyscript.y" /* yacc.c:1646  */
    { memset(&(yyval.phdr_info), 0, sizeof(struct Phdr_info)); }
#line 2759 "yyscript.c" /* yacc.c:1646  */
    break;

  case 142:
#line 785 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.phdr_info) = (yyvsp[0].phdr_info);
	      if ((yyvsp[-1].string).length == 7 && strncmp((yyvsp[-1].string).value, "FILEHDR", 7) == 0)
		(yyval.phdr_info).includes_filehdr = 1;
	      else
		yyerror(closure, "PHDRS syntax error");
	    }
#line 2771 "yyscript.c" /* yacc.c:1646  */
    break;

  case 143:
#line 793 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.phdr_info) = (yyvsp[0].phdr_info);
	      (yyval.phdr_info).includes_phdrs = 1;
	    }
#line 2780 "yyscript.c" /* yacc.c:1646  */
    break;

  case 144:
#line 798 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.phdr_info) = (yyvsp[0].phdr_info);
	      if ((yyvsp[-4].string).length == 5 && strncmp((yyvsp[-4].string).value, "FLAGS", 5) == 0)
		{
		  (yyval.phdr_info).is_flags_valid = 1;
		  (yyval.phdr_info).flags = (yyvsp[-2].integer);
		}
	      else
		yyerror(closure, "PHDRS syntax error");
	    }
#line 2795 "yyscript.c" /* yacc.c:1646  */
    break;

  case 145:
#line 809 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.phdr_info) = (yyvsp[0].phdr_info);
	      (yyval.phdr_info).load_address = (yyvsp[-2].expr);
	    }
#line 2804 "yyscript.c" /* yacc.c:1646  */
    break;

  case 146:
#line 818 "yyscript.y" /* yacc.c:1646  */
    { script_set_symbol(closure, (yyvsp[-2].string).value, (yyvsp[-2].string).length, (yyvsp[0].expr), 0, 0); }
#line 2810 "yyscript.c" /* yacc.c:1646  */
    break;

  case 147:
#line 820 "yyscript.y" /* yacc.c:1646  */
    {
	      Expression_ptr s = script_exp_string((yyvsp[-2].string).value, (yyvsp[-2].string).length);
	      Expression_ptr e = script_exp_binary_add(s, (yyvsp[0].expr));
	      script_set_symbol(closure, (yyvsp[-2].string).value, (yyvsp[-2].string).length, e, 0, 0);
	    }
#line 2820 "yyscript.c" /* yacc.c:1646  */
    break;

  case 148:
#line 826 "yyscript.y" /* yacc.c:1646  */
    {
	      Expression_ptr s = script_exp_string((yyvsp[-2].string).value, (yyvsp[-2].string).length);
	      Expression_ptr e = script_exp_binary_sub(s, (yyvsp[0].expr));
	      script_set_symbol(closure, (yyvsp[-2].string).value, (yyvsp[-2].string).length, e, 0, 0);
	    }
#line 2830 "yyscript.c" /* yacc.c:1646  */
    break;

  case 149:
#line 832 "yyscript.y" /* yacc.c:1646  */
    {
	      Expression_ptr s = script_exp_string((yyvsp[-2].string).value, (yyvsp[-2].string).length);
	      Expression_ptr e = script_exp_binary_mult(s, (yyvsp[0].expr));
	      script_set_symbol(closure, (yyvsp[-2].string).value, (yyvsp[-2].string).length, e, 0, 0);
	    }
#line 2840 "yyscript.c" /* yacc.c:1646  */
    break;

  case 150:
#line 838 "yyscript.y" /* yacc.c:1646  */
    {
	      Expression_ptr s = script_exp_string((yyvsp[-2].string).value, (yyvsp[-2].string).length);
	      Expression_ptr e = script_exp_binary_div(s, (yyvsp[0].expr));
	      script_set_symbol(closure, (yyvsp[-2].string).value, (yyvsp[-2].string).length, e, 0, 0);
	    }
#line 2850 "yyscript.c" /* yacc.c:1646  */
    break;

  case 151:
#line 844 "yyscript.y" /* yacc.c:1646  */
    {
	      Expression_ptr s = script_exp_string((yyvsp[-2].string).value, (yyvsp[-2].string).length);
	      Expression_ptr e = script_exp_binary_lshift(s, (yyvsp[0].expr));
	      script_set_symbol(closure, (yyvsp[-2].string).value, (yyvsp[-2].string).length, e, 0, 0);
	    }
#line 2860 "yyscript.c" /* yacc.c:1646  */
    break;

  case 152:
#line 850 "yyscript.y" /* yacc.c:1646  */
    {
	      Expression_ptr s = script_exp_string((yyvsp[-2].string).value, (yyvsp[-2].string).length);
	      Expression_ptr e = script_exp_binary_rshift(s, (yyvsp[0].expr));
	      script_set_symbol(closure, (yyvsp[-2].string).value, (yyvsp[-2].string).length, e, 0, 0);
	    }
#line 2870 "yyscript.c" /* yacc.c:1646  */
    break;

  case 153:
#line 856 "yyscript.y" /* yacc.c:1646  */
    {
	      Expression_ptr s = script_exp_string((yyvsp[-2].string).value, (yyvsp[-2].string).length);
	      Expression_ptr e = script_exp_binary_bitwise_and(s, (yyvsp[0].expr));
	      script_set_symbol(closure, (yyvsp[-2].string).value, (yyvsp[-2].string).length, e, 0, 0);
	    }
#line 2880 "yyscript.c" /* yacc.c:1646  */
    break;

  case 154:
#line 862 "yyscript.y" /* yacc.c:1646  */
    {
	      Expression_ptr s = script_exp_string((yyvsp[-2].string).value, (yyvsp[-2].string).length);
	      Expression_ptr e = script_exp_binary_bitwise_or(s, (yyvsp[0].expr));
	      script_set_symbol(closure, (yyvsp[-2].string).value, (yyvsp[-2].string).length, e, 0, 0);
	    }
#line 2890 "yyscript.c" /* yacc.c:1646  */
    break;

  case 155:
#line 868 "yyscript.y" /* yacc.c:1646  */
    { script_set_symbol(closure, (yyvsp[-3].string).value, (yyvsp[-3].string).length, (yyvsp[-1].expr), 1, 0); }
#line 2896 "yyscript.c" /* yacc.c:1646  */
    break;

  case 156:
#line 870 "yyscript.y" /* yacc.c:1646  */
    { script_set_symbol(closure, (yyvsp[-3].string).value, (yyvsp[-3].string).length, (yyvsp[-1].expr), 1, 1); }
#line 2902 "yyscript.c" /* yacc.c:1646  */
    break;

  case 157:
#line 875 "yyscript.y" /* yacc.c:1646  */
    { script_push_lex_into_expression_mode(closure); }
#line 2908 "yyscript.c" /* yacc.c:1646  */
    break;

  case 158:
#line 877 "yyscript.y" /* yacc.c:1646  */
    {
	      script_pop_lex_mode(closure);
	      (yyval.expr) = (yyvsp[0].expr);
	    }
#line 2917 "yyscript.c" /* yacc.c:1646  */
    break;

  case 159:
#line 886 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2923 "yyscript.c" /* yacc.c:1646  */
    break;

  case 160:
#line 888 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_unary_minus((yyvsp[0].expr)); }
#line 2929 "yyscript.c" /* yacc.c:1646  */
    break;

  case 161:
#line 890 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_unary_logical_not((yyvsp[0].expr)); }
#line 2935 "yyscript.c" /* yacc.c:1646  */
    break;

  case 162:
#line 892 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_unary_bitwise_not((yyvsp[0].expr)); }
#line 2941 "yyscript.c" /* yacc.c:1646  */
    break;

  case 163:
#line 894 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2947 "yyscript.c" /* yacc.c:1646  */
    break;

  case 164:
#line 896 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_mult((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2953 "yyscript.c" /* yacc.c:1646  */
    break;

  case 165:
#line 898 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_div((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2959 "yyscript.c" /* yacc.c:1646  */
    break;

  case 166:
#line 900 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_mod((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2965 "yyscript.c" /* yacc.c:1646  */
    break;

  case 167:
#line 902 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_add((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2971 "yyscript.c" /* yacc.c:1646  */
    break;

  case 168:
#line 904 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_sub((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2977 "yyscript.c" /* yacc.c:1646  */
    break;

  case 169:
#line 906 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_lshift((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2983 "yyscript.c" /* yacc.c:1646  */
    break;

  case 170:
#line 908 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_rshift((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2989 "yyscript.c" /* yacc.c:1646  */
    break;

  case 171:
#line 910 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_eq((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2995 "yyscript.c" /* yacc.c:1646  */
    break;

  case 172:
#line 912 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_ne((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3001 "yyscript.c" /* yacc.c:1646  */
    break;

  case 173:
#line 914 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_le((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3007 "yyscript.c" /* yacc.c:1646  */
    break;

  case 174:
#line 916 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_ge((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3013 "yyscript.c" /* yacc.c:1646  */
    break;

  case 175:
#line 918 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_lt((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3019 "yyscript.c" /* yacc.c:1646  */
    break;

  case 176:
#line 920 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_gt((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3025 "yyscript.c" /* yacc.c:1646  */
    break;

  case 177:
#line 922 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_bitwise_and((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3031 "yyscript.c" /* yacc.c:1646  */
    break;

  case 178:
#line 924 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_bitwise_xor((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3037 "yyscript.c" /* yacc.c:1646  */
    break;

  case 179:
#line 926 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_bitwise_or((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3043 "yyscript.c" /* yacc.c:1646  */
    break;

  case 180:
#line 928 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_logical_and((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3049 "yyscript.c" /* yacc.c:1646  */
    break;

  case 181:
#line 930 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_binary_logical_or((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3055 "yyscript.c" /* yacc.c:1646  */
    break;

  case 182:
#line 932 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_trinary_cond((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3061 "yyscript.c" /* yacc.c:1646  */
    break;

  case 183:
#line 934 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_integer((yyvsp[0].integer)); }
#line 3067 "yyscript.c" /* yacc.c:1646  */
    break;

  case 184:
#line 936 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_symbol(closure, (yyvsp[0].string).value, (yyvsp[0].string).length); }
#line 3073 "yyscript.c" /* yacc.c:1646  */
    break;

  case 185:
#line 938 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_max((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 3079 "yyscript.c" /* yacc.c:1646  */
    break;

  case 186:
#line 940 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_min((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 3085 "yyscript.c" /* yacc.c:1646  */
    break;

  case 187:
#line 942 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_defined((yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3091 "yyscript.c" /* yacc.c:1646  */
    break;

  case 188:
#line 944 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_sizeof_headers(); }
#line 3097 "yyscript.c" /* yacc.c:1646  */
    break;

  case 189:
#line 946 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_alignof((yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3103 "yyscript.c" /* yacc.c:1646  */
    break;

  case 190:
#line 948 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_sizeof((yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3109 "yyscript.c" /* yacc.c:1646  */
    break;

  case 191:
#line 950 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_addr((yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3115 "yyscript.c" /* yacc.c:1646  */
    break;

  case 192:
#line 952 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_loadaddr((yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3121 "yyscript.c" /* yacc.c:1646  */
    break;

  case 193:
#line 954 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_origin(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3127 "yyscript.c" /* yacc.c:1646  */
    break;

  case 194:
#line 956 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_length(closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3133 "yyscript.c" /* yacc.c:1646  */
    break;

  case 195:
#line 958 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_constant((yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3139 "yyscript.c" /* yacc.c:1646  */
    break;

  case 196:
#line 960 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_absolute((yyvsp[-1].expr)); }
#line 3145 "yyscript.c" /* yacc.c:1646  */
    break;

  case 197:
#line 962 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_align(script_exp_string(".", 1), (yyvsp[-1].expr)); }
#line 3151 "yyscript.c" /* yacc.c:1646  */
    break;

  case 198:
#line 964 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_align((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 3157 "yyscript.c" /* yacc.c:1646  */
    break;

  case 199:
#line 966 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_align(script_exp_string(".", 1), (yyvsp[-1].expr)); }
#line 3163 "yyscript.c" /* yacc.c:1646  */
    break;

  case 200:
#line 968 "yyscript.y" /* yacc.c:1646  */
    {
	      script_data_segment_align(closure);
	      (yyval.expr) = script_exp_function_data_segment_align((yyvsp[-3].expr), (yyvsp[-1].expr));
	    }
#line 3172 "yyscript.c" /* yacc.c:1646  */
    break;

  case 201:
#line 973 "yyscript.y" /* yacc.c:1646  */
    {
	      script_data_segment_relro_end(closure);
	      (yyval.expr) = script_exp_function_data_segment_relro_end((yyvsp[-3].expr), (yyvsp[-1].expr));
	    }
#line 3181 "yyscript.c" /* yacc.c:1646  */
    break;

  case 202:
#line 978 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_data_segment_end((yyvsp[-1].expr)); }
#line 3187 "yyscript.c" /* yacc.c:1646  */
    break;

  case 203:
#line 980 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.expr) = script_exp_function_segment_start((yyvsp[-3].string).value, (yyvsp[-3].string).length, (yyvsp[-1].expr));
	      /* We need to take note of any SEGMENT_START expressions
		 because they change the behaviour of -Ttext, -Tdata and
		 -Tbss options.  */
	      script_saw_segment_start_expression(closure);
	    }
#line 3199 "yyscript.c" /* yacc.c:1646  */
    break;

  case 204:
#line 988 "yyscript.y" /* yacc.c:1646  */
    { (yyval.expr) = script_exp_function_assert((yyvsp[-3].expr), (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3205 "yyscript.c" /* yacc.c:1646  */
    break;

  case 205:
#line 994 "yyscript.y" /* yacc.c:1646  */
    { script_set_symbol(closure, (yyvsp[-2].string).value, (yyvsp[-2].string).length, (yyvsp[0].expr), 0, 0); }
#line 3211 "yyscript.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1012 "yyscript.y" /* yacc.c:1646  */
    { script_new_vers_node (closure, NULL, (yyvsp[-3].versyms)); }
#line 3217 "yyscript.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1027 "yyscript.y" /* yacc.c:1646  */
    {
	      script_register_vers_node (closure, NULL, 0, (yyvsp[-2].versnode), NULL);
	    }
#line 3225 "yyscript.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1031 "yyscript.y" /* yacc.c:1646  */
    {
	      script_register_vers_node (closure, (yyvsp[-4].string).value, (yyvsp[-4].string).length, (yyvsp[-2].versnode),
					 NULL);
	    }
#line 3234 "yyscript.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1036 "yyscript.y" /* yacc.c:1646  */
    {
	      script_register_vers_node (closure, (yyvsp[-5].string).value, (yyvsp[-5].string).length, (yyvsp[-3].versnode), (yyvsp[-1].deplist));
	    }
#line 3242 "yyscript.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1043 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.deplist) = script_add_vers_depend (closure, NULL, (yyvsp[0].string).value, (yyvsp[0].string).length);
	    }
#line 3250 "yyscript.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1047 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.deplist) = script_add_vers_depend (closure, (yyvsp[-1].deplist), (yyvsp[0].string).value, (yyvsp[0].string).length);
	    }
#line 3258 "yyscript.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1054 "yyscript.y" /* yacc.c:1646  */
    { (yyval.versnode) = script_new_vers_node (closure, NULL, NULL); }
#line 3264 "yyscript.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1056 "yyscript.y" /* yacc.c:1646  */
    { (yyval.versnode) = script_new_vers_node (closure, (yyvsp[-1].versyms), NULL); }
#line 3270 "yyscript.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1058 "yyscript.y" /* yacc.c:1646  */
    { (yyval.versnode) = script_new_vers_node (closure, (yyvsp[-1].versyms), NULL); }
#line 3276 "yyscript.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1060 "yyscript.y" /* yacc.c:1646  */
    { (yyval.versnode) = script_new_vers_node (closure, NULL, (yyvsp[-1].versyms)); }
#line 3282 "yyscript.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1062 "yyscript.y" /* yacc.c:1646  */
    { (yyval.versnode) = script_new_vers_node (closure, (yyvsp[-5].versyms), (yyvsp[-1].versyms)); }
#line 3288 "yyscript.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1071 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.versyms) = script_new_vers_pattern (closure, NULL, (yyvsp[0].string).value,
					    (yyvsp[0].string).length, 0);
	    }
#line 3297 "yyscript.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1076 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.versyms) = script_new_vers_pattern (closure, NULL, (yyvsp[0].string).value,
					    (yyvsp[0].string).length, 1);
	    }
#line 3306 "yyscript.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1081 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.versyms) = script_new_vers_pattern (closure, (yyvsp[-2].versyms), (yyvsp[0].string).value,
                                            (yyvsp[0].string).length, 0);
	    }
#line 3315 "yyscript.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1086 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.versyms) = script_new_vers_pattern (closure, (yyvsp[-2].versyms), (yyvsp[0].string).value,
                                            (yyvsp[0].string).length, 1);
	    }
#line 3324 "yyscript.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1092 "yyscript.y" /* yacc.c:1646  */
    { version_script_push_lang (closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3330 "yyscript.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1094 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.versyms) = (yyvsp[-2].versyms);
	      version_script_pop_lang(closure);
	    }
#line 3339 "yyscript.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1102 "yyscript.y" /* yacc.c:1646  */
    { version_script_push_lang (closure, (yyvsp[-1].string).value, (yyvsp[-1].string).length); }
#line 3345 "yyscript.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1104 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.versyms) = script_merge_expressions ((yyvsp[-8].versyms), (yyvsp[-2].versyms));
	      version_script_pop_lang(closure);
	    }
#line 3354 "yyscript.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1109 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.versyms) = script_new_vers_pattern (closure, NULL, "extern",
					    sizeof("extern") - 1, 1);
	    }
#line 3363 "yyscript.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1114 "yyscript.y" /* yacc.c:1646  */
    {
	      (yyval.versyms) = script_new_vers_pattern (closure, (yyvsp[-2].versyms), "extern",
					    sizeof("extern") - 1, 1);
	    }
#line 3372 "yyscript.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1124 "yyscript.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 3378 "yyscript.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1126 "yyscript.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 3384 "yyscript.c" /* yacc.c:1646  */
    break;


#line 3388 "yyscript.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (closure, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (closure, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, closure);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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
                  yystos[yystate], yyvsp, closure);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (closure, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, closure);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, closure);
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
  return yyresult;
}
#line 1148 "yyscript.y" /* yacc.c:1906  */

