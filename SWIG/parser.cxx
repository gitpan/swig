
/*  A Bison parser, made from parser.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	ID	258
#define	HBLOCK	259
#define	WRAPPER	260
#define	POUND	261
#define	STRING	262
#define	NUM_INT	263
#define	NUM_FLOAT	264
#define	CHARCONST	265
#define	NUM_UNSIGNED	266
#define	NUM_LONG	267
#define	NUM_ULONG	268
#define	TYPEDEF	269
#define	TYPE_INT	270
#define	TYPE_UNSIGNED	271
#define	TYPE_SHORT	272
#define	TYPE_LONG	273
#define	TYPE_FLOAT	274
#define	TYPE_DOUBLE	275
#define	TYPE_CHAR	276
#define	TYPE_VOID	277
#define	TYPE_SIGNED	278
#define	TYPE_BOOL	279
#define	TYPE_TYPEDEF	280
#define	LPAREN	281
#define	RPAREN	282
#define	COMMA	283
#define	SEMI	284
#define	EXTERN	285
#define	INIT	286
#define	LBRACE	287
#define	RBRACE	288
#define	DEFINE	289
#define	PERIOD	290
#define	CONST	291
#define	STRUCT	292
#define	UNION	293
#define	EQUAL	294
#define	SIZEOF	295
#define	MODULE	296
#define	LBRACKET	297
#define	RBRACKET	298
#define	WEXTERN	299
#define	ILLEGAL	300
#define	READONLY	301
#define	READWRITE	302
#define	NAME	303
#define	RENAME	304
#define	INCLUDE	305
#define	CHECKOUT	306
#define	ADDMETHODS	307
#define	PRAGMA	308
#define	CVALUE	309
#define	COUT	310
#define	ENUM	311
#define	ENDDEF	312
#define	MACRO	313
#define	CLASS	314
#define	PRIVATE	315
#define	PUBLIC	316
#define	PROTECTED	317
#define	COLON	318
#define	STATIC	319
#define	VIRTUAL	320
#define	FRIEND	321
#define	OPERATOR	322
#define	THROW	323
#define	TEMPLATE	324
#define	NATIVE	325
#define	INLINE	326
#define	IFDEF	327
#define	IFNDEF	328
#define	ENDIF	329
#define	ELSE	330
#define	UNDEF	331
#define	IF	332
#define	DEFINED	333
#define	ELIF	334
#define	RAW_MODE	335
#define	ALPHA_MODE	336
#define	TEXT	337
#define	DOC_DISABLE	338
#define	DOC_ENABLE	339
#define	STYLE	340
#define	LOCALSTYLE	341
#define	TYPEMAP	342
#define	EXCEPT	343
#define	IMPORT	344
#define	ECHO	345
#define	NEW	346
#define	APPLY	347
#define	CLEAR	348
#define	DOCONLY	349
#define	TITLE	350
#define	SECTION	351
#define	SUBSECTION	352
#define	SUBSUBSECTION	353
#define	LESSTHAN	354
#define	GREATERTHAN	355
#define	USERDIRECTIVE	356
#define	OC_INTERFACE	357
#define	OC_END	358
#define	OC_PUBLIC	359
#define	OC_PRIVATE	360
#define	OC_PROTECTED	361
#define	OC_CLASS	362
#define	OC_IMPLEMENT	363
#define	OC_PROTOCOL	364
#define	OR	365
#define	XOR	366
#define	AND	367
#define	LSHIFT	368
#define	RSHIFT	369
#define	PLUS	370
#define	MINUS	371
#define	STAR	372
#define	SLASH	373
#define	UMINUS	374
#define	NOT	375
#define	LNOT	376
#define	DCOLON	377

#line 1 "parser.y"


/*******************************************************************************
 * Simplified Wrapper and Interface Generator  (SWIG)
 * 
 * Dave Beazley
 * 
 * Department of Computer Science        Theoretical Division (T-11)
 * University of Utah                    Los Alamos National Laboratory
 * Salt Lake City, Utah  84112           Los Alamos, New Mexico  87545
 * beazley@cs.utah.edu                   beazley@lanl.gov
 *
 * Copyright (c) 1995-1997
 * The University of Utah and the Regents of the University of California
 * All Rights Reserved
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that 
 * (1) The above copyright notice and the following two paragraphs
 * appear in all copies of the source code and (2) redistributions
 * including binaries reproduces these notices in the supporting
 * documentation.   Substantial modifications to this software may be
 * copyrighted by their authors and need not follow the licensing terms
 * described here, provided that the new terms are clearly indicated in
 * all files where they apply.
 * 
 * IN NO EVENT SHALL THE AUTHOR, THE UNIVERSITY OF CALIFORNIA, THE 
 * UNIVERSITY OF UTAH OR DISTRIBUTORS OF THIS SOFTWARE BE LIABLE TO ANY
 * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF THE AUTHORS OR ANY OF THE ABOVE PARTIES HAVE BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR, THE UNIVERSITY OF CALIFORNIA, AND THE UNIVERSITY OF UTAH
 * SPECIFICALLY DISCLAIM ANY WARRANTIES,INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND 
 * THE AUTHORS AND DISTRIBUTORS HAVE NO OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 *******************************************************************************/
/***********************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.2/SWIG/RCS/parser.y,v 1.78 1997/07/27 20:30:28 beazley Exp $
 *
 * parser.y
 *
 * YACC parser for parsing function declarations.
 *
 * *** DISCLAIMER ***
 *
 * This is the most ugly, incredibly henious, and completely unintelligible
 * file in SWIG.  While it started out simple, it has grown into a
 * monster that is almost unmaintainable.   A complete parser rewrite is
 * currently in progress that should make this file about 1/4 the size
 * that it is now.   Needless to say, don't modify this file or even look
 * at it for that matter!
 *
 * -- Revision History (at end)
 ***********************************************************************/

#define yylex yylex

extern "C" int yylex();
void   yyerror (char *s);       
    
extern int  line_number;
extern int  start_line;
extern void skip_brace(void);
extern void skip_define(void);
extern void skip_decl(void);
extern int  skip_cond(int);
extern void skip_to_end(void);
extern void skip_template(void);
extern void scanner_check_typedef(void);
extern void scanner_ignore_typedef(void);
extern void scanner_clear_start(void);
extern void start_inline(char *, int);
extern void format_string(char *);
extern void swig_pragma(char *, char *);

#include "internal.h"

#ifdef NEED_ALLOC
void *alloca(unsigned n) {
  return((void *) malloc(n));
}
#else
// This redefinition is apparently needed on a number of machines,
// particularly HPUX
#undef  alloca
#define alloca  malloc
#endif

// Initialization flags.   These indicate whether or not certain
// features have been initialized.  These were added to allow
// interface files without the block (required in previous
// versions).

static int     module_init = 0;    /* Indicates whether the %module name was given */
static int     title_init = 0;     /* Indicates whether %title directive has been given */
static int     doc_init = 0;    

static int     lang_init = 0;      /* Indicates if the language has been initialized */

static int            i;
       int            Error = 0;
static char           temp_name[128];
static DataType      *temp_typeptr, temp_type;
static char           yy_rename[256];
static int            Rename_true = 0;
static DataType      *Active_type = 0;         // Used to support variable lists
static int            Active_extern = 0;       // Whether or not list is external
static int            Active_static = 0;
static DataType       *Active_typedef = 0;     // Used for typedef lists
static int            InArray = 0;             // Used when an array declaration is found 
static int            in_then = 0;
static int            in_else = 0;       
static int            allow = 1;               // Used during conditional compilation
static int            doc_scope = 0;           // Documentation scoping
static String         ArrayString;             // Array type attached to parameter names
static String         ArrayBackup;             // Array backup string
static char           *DefArg = 0;             // Default argument hack
static char           *ConstChar = 0;          // Used to store raw character constants
static ParmList       *tm_parm = 0;            // Parameter list used to hold typemap parameters
static Hash            name_hash;              // Hash table containing renamings
       char           *objc_construct = "new"; // Objective-C constructor
       char           *objc_destruct = "free"; // Objective-C destructor

/* Some macros for building constants */

#define E_BINARY(TARGET, SRC1, SRC2, OP)  \
        TARGET = new char[strlen(SRC1) + strlen(SRC2) +strlen(OP)+1];\
	sprintf(TARGET,"%s%s%s",SRC1,OP,SRC2);

/* C++ modes */

#define  CPLUS_PUBLIC    1
#define  CPLUS_PRIVATE   2
#define  CPLUS_PROTECTED 3

int     cplus_mode;

// Declarations of some functions for handling C++ 

extern void cplus_open_class(char *name, char *rname, char *ctype);
extern void cplus_member_func(char *, char *, DataType *, ParmList *, int);
extern void cplus_constructor(char *, char *, ParmList *);
extern void cplus_destructor(char *, char *);
extern void cplus_variable(char *, char *, DataType *);
extern void cplus_static_func(char *, char *, DataType *, ParmList *);
extern void cplus_declare_const(char *, char *, DataType *, char *);
extern void cplus_class_close(char *);
extern void cplus_inherit(int, char **);
extern void cplus_cleanup(void);
extern void cplus_static_var(char *, char *, DataType *);
extern void cplus_register_type(char *);
extern void cplus_register_scope(Hash *);
extern void cplus_inherit_scope(int, char **);
extern DocEntry *cplus_set_class(char *);
extern void cplus_unset_class();
extern void cplus_abort();
  
// ----------------------------------------------------------------------
// static init_language()
//
// Initialize the target language.
// Does nothing if this function has already been called.
// ----------------------------------------------------------------------

static void init_language() {
  if (!lang_init) {
    lang->initialize();
    
    // Initialize the documentation system

    if (!doctitle) {
      doctitle = new DocTitle(title,0);
    }
    if (!doc_init)
      doctitle->usage = title;

    doc_stack[0] = doctitle;
    doc_stack_top = 0;
    
    int oldignore = IgnoreDoc;
    IgnoreDoc = 1;
    if (ConfigFile) {
      include_file(ConfigFile);
    }
    IgnoreDoc = oldignore;
  }
  lang_init = 1;
  title_init = 1;
}

// ----------------------------------------------------------------------
// int promote(int t1, int t2)
//
// Promote types (for constant expressions)
// ----------------------------------------------------------------------

int promote(int t1, int t2) {

  if ((t1 == T_ERROR) || (t2 == T_ERROR)) return T_ERROR;
  if ((t1 == T_DOUBLE) || (t2 == T_DOUBLE)) return T_DOUBLE;
  if ((t1 == T_FLOAT) || (t2 == T_FLOAT)) return T_FLOAT;
  if ((t1 == T_ULONG) || (t2 == T_ULONG)) return T_ULONG;
  if ((t1 == T_LONG) || (t2 == T_LONG)) return T_LONG;
  if ((t1 == T_UINT) || (t2 == T_UINT)) return T_UINT;
  if ((t1 == T_INT) || (t2 == T_INT)) return T_INT;
  if ((t1 == T_USHORT) || (t2 == T_USHORT)) return T_SHORT;
  if ((t1 == T_SHORT) || (t2 == T_SHORT)) return T_SHORT;
  if ((t1 == T_UCHAR) || (t2 == T_UCHAR)) return T_UCHAR;
  if (t1 != t2) {
    fprintf(stderr,"%s : Line %d. Type mismatch in constant expression\n",
	    input_file, line_number);
    FatalError();
  }
  return t1;
}

/* Generate the scripting name of an object.  Takes %name directive into 
   account among other things */

static char *make_name(char *name) {
  // Check to see if the name is in the hash
  char *nn = (char *) name_hash.lookup(name);
  if (nn) return nn;        // Yep, return it.

  if (Rename_true) {
    Rename_true = 0;
    return yy_rename;
  } else {
    // Now check to see if the name contains a $
    if (strchr(name,'$')) {
      static String temp;
      temp = "";
      temp << name;
      temp.replace("$","_S_");
      return temp;
    } else {
      return name;
    }
  }
}

/* Return the parent of a documentation entry.   If wrapping externally, this is 0 */

static DocEntry *doc_parent() {
  if (!WrapExtern) 
    return doc_stack[doc_stack_top];
  else
    return 0;
}

// ----------------------------------------------------------------------
// create_function(int ext, char *name, DataType *t, ParmList *l)
//
// Creates a function and manages documentation creation.  Really
// only used internally to the parser.
// ----------------------------------------------------------------------

void create_function(int ext, char *name, DataType *t, ParmList *l) {
  if (Active_static) return;     // Static declaration. Ignore

  init_language();
  char *iname = make_name(name);

  // Check if symbol already exists

  if (add_symbol(iname, t, (char *) 0)) {
    fprintf(stderr,"%s : Line %d. Function %s multiply defined (2nd definition ignored).\n",
	    input_file, line_number, iname);
  } else {
    if (WrapExtern) return;        // External wrapper file. Ignore
    Stat_func++;
    if (Verbose) {
      fprintf(stderr,"Wrapping function : ");
      emit_extern_func(name, t, l, 0, stderr);
    }

    // If extern, make an extern declaration in the SWIG wrapper file

    if (ext) 
      emit_extern_func(name, t, l, ext, f_header);
    else if (ForceExtern) {
      emit_extern_func(name, t, l, 1, f_header);
    }

    // If this function has been declared inline, produce a function

    doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
    lang->create_function(name, iname, t, l);
    l->check_defined();
    t->check_defined();
  }
  scanner_clear_start();
}

// -------------------------------------------------------------------
// create_variable(int ext, char *name, DataType *t)
//
// Create a link to a global variable.
// -------------------------------------------------------------------

void create_variable(int ext, char *name, DataType *t) {

  int oldstatus = Status;

  if (Active_static) return;  // If static ignore
				   
  init_language();

  char *iname = make_name(name);
  if (add_symbol(iname, t, (char *) 0)) {
    fprintf(stderr,"%s : Line %d. Variable %s multiply defined (2nd definition ignored).\n",
	    input_file, line_number, iname);
  } else {
    if (WrapExtern)    return;  // If %extern mode, ignore
    Stat_var++;
    if (Verbose) {
      fprintf(stderr,"Wrapping variable : ");
      emit_extern_var(name, t, 0, stderr);
    }

    // If externed, output an external declaration

    if (ext) 
      emit_extern_var(name, t, ext, f_header);
    else if (ForceExtern) {
      emit_extern_var(name, t, 1, f_header);
    }

    // If variable datatype is read-only, we'll force it to be readonly
    if (t->status & STAT_READONLY) Status = Status | STAT_READONLY;

    // Now dump it out
    doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
    lang->link_variable(name, iname, t);
    t->check_defined();
    Status = oldstatus;
  }
  scanner_clear_start();
}

// ------------------------------------------------------------------
// create_constant(char *name, DataType *type, char *value)
//
// Creates a new constant.
// -------------------------------------------------------------------

void create_constant(char *name, DataType *type, char *value) {

  if (Active_static) return;

  init_language();

  if (Rename_true) {
    fprintf(stderr,"%s : Line %d. %%name directive ignored with #define\n",
	    input_file, line_number);
    Rename_true = 0;
  }

  if ((type->type == T_CHAR) && (!type->is_pointer))
    type->is_pointer++;
  
  if (!value) value = copy_string(name);
  sprintf(temp_name,"const:%s", name);
  if (add_symbol(temp_name, type, value)) {
    fprintf(stderr,"%s : Line %d. Constant %s multiply defined. (2nd definition ignored)\n",
	    input_file, line_number, name);
  } else {
    // Update symbols value if already defined.
    update_symbol(name, type, value);

    if (!WrapExtern) {    // Only wrap the constant if not in %extern mode
      Stat_const++;
      if (Verbose) 
	fprintf(stderr,"Creating constant %s = %s\n", name, value);

      doc_entry = new DocDecl(name,doc_stack[doc_stack_top]);	   
      lang->declare_const(name, name, type, value);
      type->check_defined();
    }
  }
  scanner_clear_start();
}


/* Print out array brackets */
void print_array() {
  int i;
  for (i = 0; i < InArray; i++)
    fprintf(stderr,"[]");
}

/* manipulate small stack for managing if-then-else */

static int then_data[100];
static int else_data[100];
static int allow_data[100];
static int te_index = 0;
static int prev_allow = 1;

void if_push() {
  then_data[te_index] = in_then;
  else_data[te_index] = in_else;
  allow_data[te_index] = allow;
  prev_allow = allow;
  te_index++;
  if (te_index >= 100) {
    fprintf(stderr,"SWIG.  Internal parser error. if-then-else stack overflow.\n");
    SWIG_exit(1);
  }
}

void if_pop() {
  if (te_index > 0) {
    te_index--;
    in_then = then_data[te_index];
    in_else = else_data[te_index];
    allow = allow_data[te_index];
    if (te_index > 0) {
      prev_allow = allow_data[te_index-1];
    } else {
      prev_allow = 1;
    }
  }
}

// Structures for handling code fragments built for nested classes

struct Nested {
  String   code;         // Associated code fragment
  int      line;         // line number where it starts
  char     *name;        // Name associated with this nested class
  DataType *type;        // Datatype associated with the name
  Nested   *next;        // Next code fragment in list
};

// Some internal variables for saving nested class information

static Nested      *nested_list = 0;

// Add a function to the nested list

static void add_nested(Nested *n) {
  Nested *n1;
  if (!nested_list) nested_list = n;
  else {
    n1 = nested_list;
    while (n1->next) n1 = n1->next;
    n1->next = n;
  }
}

// Dump all of the nested class declarations to the inline processor
// However.  We need to do a few name replacements and other munging
// first.  This function must be called before closing a class!

static void dump_nested(char *parent) {
  Nested *n,*n1;
  n = nested_list;
  int oldstatus = Status;

  Status = STAT_READONLY;
  while (n) {
    // Token replace the name of the parent class
    n->code.replace("$classname",parent);

    // Fix up the name of the datatype (for building typedefs and other stuff)
    sprintf(n->type->name,"%s_%s",parent,n->name);
    
    // Add the appropriate declaration to the C++ processor
    doc_entry = new DocDecl(n->name,doc_stack[doc_stack_top]);
    cplus_variable(n->name,(char *) 0, n->type);

    // Dump the code to the scanner
    if (Verbose)
      fprintf(stderr,"Splitting from %s : (line %d) \n%s\n", parent,n->line, n->code.get());

    fprintf(f_header,"\n%s\n", n->code.get());
    start_inline(n->code.get(),n->line);

    n1 = n->next;
    delete n;
    n = n1;
  }
  nested_list = 0;
  Status = oldstatus;
}    


#line 502 "parser.y"
typedef union {         
  char        *id;
  struct Declaration {
    char *id;
    int   is_pointer;
    int   is_reference;
  } decl;
  struct InitList {
    char **names;
    int    count;
  } ilist;
  struct DocList {
    char **names;
    char **values;
    int  count;
  } dlist;
  struct Define {
    char *id;
    int   type;
  } dtype;
  DataType     *type;
  Parm         *p;
  TMParm       *tmparm;
  ParmList     *pl;
  int           ivalue;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		895
#define	YYFLAG		-32768
#define	YYNTBASE	123

#define YYTRANSLATE(x) ((unsigned)(x) <= 377 ? yytranslate[x] : 256)

static const char yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
   106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
   116,   117,   118,   119,   120,   121,   122
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     7,     9,    12,    15,    18,    21,    23,
    24,    32,    37,    38,    46,    51,    52,    62,    70,    71,
    80,    88,    96,    97,   107,   109,   111,   116,   121,   122,
   126,   127,   133,   141,   153,   157,   161,   165,   169,   171,
   173,   175,   177,   180,   182,   184,   187,   190,   193,   196,
   199,   201,   205,   209,   213,   216,   219,   220,   229,   230,
   231,   242,   251,   258,   267,   274,   285,   294,   300,   304,
   310,   313,   319,   322,   324,   326,   328,   330,   336,   338,
   340,   343,   346,   348,   349,   355,   366,   378,   379,   386,
   390,   394,   396,   399,   402,   404,   406,   409,   412,   417,
   420,   423,   431,   435,   442,   444,   445,   452,   453,   462,
   465,   467,   470,   472,   474,   477,   480,   483,   485,   489,
   491,   493,   496,   499,   503,   507,   516,   520,   523,   526,
   528,   530,   533,   537,   540,   542,   544,   546,   549,   551,
   553,   556,   559,   562,   565,   569,   574,   576,   578,   580,
   583,   586,   588,   590,   592,   594,   596,   599,   602,   605,
   608,   611,   614,   618,   621,   624,   626,   629,   632,   634,
   636,   638,   640,   642,   645,   648,   651,   654,   657,   659,
   661,   664,   667,   669,   671,   673,   676,   679,   681,   683,
   685,   686,   689,   691,   693,   697,   699,   701,   703,   707,
   709,   711,   712,   717,   720,   722,   724,   726,   728,   730,
   732,   734,   736,   741,   746,   748,   752,   756,   760,   764,
   768,   772,   776,   780,   784,   788,   791,   794,   798,   800,
   802,   803,   812,   813,   814,   826,   827,   828,   838,   843,
   853,   860,   866,   868,   869,   876,   879,   882,   884,   887,
   888,   889,   897,   898,   902,   904,   911,   919,   925,   932,
   939,   940,   946,   951,   952,   958,   966,   969,   972,   975,
   980,   981,   985,   986,   994,   996,   998,  1000,  1004,  1006,
  1008,  1010,  1011,  1018,  1019,  1025,  1029,  1033,  1037,  1041,
  1043,  1045,  1047,  1049,  1051,  1053,  1055,  1056,  1062,  1063,
  1070,  1073,  1076,  1079,  1084,  1087,  1091,  1093,  1095,  1099,
  1105,  1113,  1116,  1118,  1121,  1123,  1125,  1129,  1131,  1134,
  1138,  1141,  1145,  1147,  1149,  1151,  1153,  1155,  1157,  1159,
  1164,  1166,  1170,  1174,  1177,  1179,  1181,  1185,  1190,  1194,
  1196,  1200,  1201,  1211,  1212,  1222,  1224,  1226,  1231,  1235,
  1238,  1240,  1242,  1245,  1246,  1250,  1251,  1255,  1256,  1260,
  1261,  1265,  1267,  1271,  1274,  1278,  1279,  1286,  1290,  1295,
  1297,  1300,  1301,  1307,  1308,  1315,  1316,  1320,  1322,  1328,
  1334,  1336,  1338,  1342,  1347,  1349,  1353,  1355,  1360,  1362,
  1364,  1367,  1371,  1376,  1378,  1381,  1384,  1386,  1388,  1390,
  1393,  1397,  1399,  1402,  1406,  1410,  1419,  1422,  1423,  1428,
  1429,  1433,  1435,  1439,  1441,  1443,  1445,  1451,  1454,  1457,
  1460,  1463
};

static const short yyrhs[] = {    -1,
   124,   125,     0,   125,   126,     0,   255,     0,    50,   252,
     0,    44,   252,     0,    89,   252,     0,    51,   252,     0,
     6,     0,     0,   148,   162,   158,   161,   155,   127,   144,
     0,   148,   163,    26,   117,     0,     0,    64,   162,   158,
   161,   155,   128,   144,     0,    64,   163,    26,   117,     0,
     0,   148,   162,   158,    26,   150,    27,   211,   129,   144,
     0,   148,   162,   158,    26,   150,    27,   149,     0,     0,
   148,   158,    26,   150,    27,   211,   130,   144,     0,    64,
   162,   158,    26,   150,    27,   149,     0,    71,   162,   158,
    26,   150,    27,   149,     0,     0,    64,   162,   158,    26,
   150,    27,   211,   131,   144,     0,    46,     0,    47,     0,
    48,    26,     3,    27,     0,    49,     3,     3,    29,     0,
     0,    91,   132,   126,     0,     0,    48,    26,    27,   133,
   176,     0,    70,    26,     3,    27,   148,     3,    29,     0,
    70,    26,     3,    27,   148,   162,   158,    26,   150,    27,
    29,     0,    95,     7,   242,     0,    96,     7,   242,     0,
    97,     7,   242,     0,    98,     7,   242,     0,    81,     0,
    80,     0,    83,     0,    84,     0,    82,     4,     0,   137,
     0,     4,     0,     5,     4,     0,    31,     4,     0,    71,
     4,     0,    90,     4,     0,    90,     7,     0,    94,     0,
    31,     3,   169,     0,    41,     3,   169,     0,    34,     3,
   147,     0,    34,    58,     0,    76,     3,     0,     0,   148,
    56,   170,    32,   134,   171,    33,    29,     0,     0,     0,
    14,    56,   170,    32,   135,   171,    33,     3,   136,   140,
     0,    87,    26,     3,    28,   244,    27,   245,    32,     0,
    87,    26,   244,    27,   245,    32,     0,    87,    26,     3,
    28,   244,    27,   245,    29,     0,    87,    26,   244,    27,
   245,    29,     0,    87,    26,     3,    28,   244,    27,   245,
    39,   247,    29,     0,    87,    26,   244,    27,   245,    39,
   247,    29,     0,    92,   247,    32,   245,    33,     0,    93,
   245,    29,     0,    88,    26,     3,    27,    32,     0,    88,
    32,     0,    88,    26,     3,    27,    29,     0,    88,    29,
     0,    29,     0,   176,     0,   217,     0,     1,     0,    30,
     7,    32,   125,    33,     0,   141,     0,   143,     0,    85,
   241,     0,    86,   241,     0,   253,     0,     0,    14,   162,
   158,   138,   140,     0,    14,   162,    26,   117,   154,    27,
    26,   150,    27,    29,     0,    14,   162,   159,    26,   117,
   154,    27,    26,   150,    27,    29,     0,     0,    14,   162,
   158,   160,   139,   140,     0,    28,   158,   140,     0,    28,
   158,   160,     0,   255,     0,    72,     3,     0,    73,     3,
     0,    75,     0,    74,     0,    77,   142,     0,    79,   142,
     0,    78,    26,     3,    27,     0,    78,     3,     0,   121,
   142,     0,    53,    26,     3,    28,     3,   243,    27,     0,
    53,     3,   243,     0,    53,    26,     3,    27,     3,   243,
     0,    29,     0,     0,    28,   158,   161,   155,   145,   144,
     0,     0,    28,   158,    26,   150,    27,   211,   146,   144,
     0,   167,    57,     0,    57,     0,     1,    57,     0,    30,
     0,   255,     0,    30,     7,     0,   211,    32,     0,   152,
   151,     0,   255,     0,    28,   152,   151,     0,   255,     0,
   153,     0,   157,   153,     0,   162,   154,     0,   162,   159,
   154,     0,   162,   112,   154,     0,   162,    26,   159,   154,
    27,    26,   150,    27,     0,    35,    35,    35,     0,     3,
   155,     0,     3,   160,     0,   160,     0,   255,     0,    39,
   167,     0,    39,   112,     3,     0,    39,    32,     0,   255,
     0,    54,     0,    55,     0,   157,   156,     0,   156,     0,
     3,     0,   159,     3,     0,   112,     3,     0,   117,   255,
     0,   117,   159,     0,    42,    43,   161,     0,    42,   175,
    43,   161,     0,   160,     0,   255,     0,    15,     0,    17,
   166,     0,    18,   166,     0,    21,     0,    24,     0,    19,
     0,    20,     0,    22,     0,    23,   164,     0,    16,   165,
     0,    25,   221,     0,     3,   221,     0,    36,   162,     0,
   210,     3,     0,     3,   122,     3,     0,   122,     3,     0,
    56,     3,     0,    15,     0,    17,   166,     0,    18,   166,
     0,    21,     0,    24,     0,    19,     0,    20,     0,    22,
     0,    23,   164,     0,    16,   165,     0,    25,   221,     0,
    36,   162,     0,   210,     3,     0,   255,     0,    15,     0,
    17,   166,     0,    18,   166,     0,    21,     0,   255,     0,
    15,     0,    17,   166,     0,    18,   166,     0,    21,     0,
    15,     0,   255,     0,     0,   168,   175,     0,     7,     0,
    10,     0,   169,    28,     3,     0,   255,     0,     3,     0,
   255,     0,   171,    28,   172,     0,   172,     0,     3,     0,
     0,     3,    39,   173,   174,     0,   141,   172,     0,   255,
     0,   175,     0,    10,     0,     8,     0,     9,     0,    11,
     0,    12,     0,    13,     0,    40,    26,   162,    27,     0,
    26,   163,    27,   175,     0,     3,     0,     3,   122,     3,
     0,   175,   115,   175,     0,   175,   116,   175,     0,   175,
   117,   175,     0,   175,   118,   175,     0,   175,   112,   175,
     0,   175,   110,   175,     0,   175,   111,   175,     0,   175,
   113,   175,     0,   175,   114,   175,     0,   116,   175,     0,
   120,   175,     0,    26,   175,    27,     0,   177,     0,   183,
     0,     0,   148,   210,     3,   206,    32,   178,   186,    33,
     0,     0,     0,    14,   210,     3,   206,    32,   179,   186,
    33,   158,   180,   140,     0,     0,     0,    14,   210,    32,
   181,   186,    33,   158,   182,   140,     0,   148,   210,     3,
    29,     0,   148,   162,   158,   122,     3,    26,   150,    27,
    29,     0,   148,   162,   158,   122,     3,    29,     0,   148,
   162,   158,   122,    67,     0,    69,     0,     0,    52,     3,
    32,   184,   185,    33,     0,   190,   186,     0,   235,   231,
     0,   255,     0,   190,   186,     0,     0,     0,    52,    32,
   187,   186,    33,   188,   186,     0,     0,     1,   189,   186,
     0,   255,     0,   162,   158,    26,   150,    27,   202,     0,
    65,   162,   158,    26,   150,    27,   203,     0,     3,    26,
   150,    27,   212,     0,   120,     3,    26,   150,    27,   202,
     0,    65,   120,     3,    26,    27,   202,     0,     0,   162,
   158,   155,   191,   199,     0,   162,   158,   160,   155,     0,
     0,    64,   162,   158,   192,   199,     0,    64,   162,   158,
    26,   150,    27,   202,     0,    61,    63,     0,    60,    63,
     0,    62,    63,     0,    48,    26,     3,    27,     0,     0,
    91,   193,   190,     0,     0,    56,   170,    32,   194,   204,
    33,    29,     0,    46,     0,    47,     0,    66,     0,   162,
   198,    67,     0,   141,     0,   137,     0,   143,     0,     0,
   210,     3,    32,   195,   197,    29,     0,     0,   210,    32,
   196,   158,    29,     0,   210,     3,    29,     0,   162,   159,
    26,     0,   163,    26,   117,     0,     3,    26,   117,     0,
    29,     0,   158,     0,   255,     0,   159,     0,   112,     0,
   255,     0,    29,     0,     0,    28,   158,   155,   200,   199,
     0,     0,    28,   158,   160,   155,   201,   199,     0,   211,
    29,     0,   211,    32,     0,   211,    29,     0,   211,    39,
   167,    29,     0,   211,    32,     0,   204,    28,   205,     0,
   205,     0,     3,     0,     3,    39,   174,     0,    48,    26,
     3,    27,     3,     0,    48,    26,     3,    27,     3,    39,
   174,     0,   141,   205,     0,   255,     0,    63,   207,     0,
   255,     0,   208,     0,   207,    28,   208,     0,     3,     0,
    65,     3,     0,    65,   209,     3,     0,   209,     3,     0,
   209,    65,     3,     0,    61,     0,    60,     0,    62,     0,
    59,     0,    37,     0,    38,     0,    36,     0,    68,    26,
   150,    27,     0,   255,     0,   211,   213,    29,     0,   211,
   213,    32,     0,    63,   214,     0,   255,     0,   215,     0,
   214,    28,   215,     0,     3,    26,   216,    27,     0,     3,
    26,    27,     0,   175,     0,   216,    28,   175,     0,     0,
   102,     3,   220,   218,    32,   222,    33,   231,   103,     0,
     0,   102,     3,    26,     3,    27,   221,   219,   231,   103,
     0,   108,     0,   109,     0,   107,     3,   169,    29,     0,
    63,     3,   221,     0,   221,   255,     0,    99,     0,   255,
     0,   227,   222,     0,     0,   104,   223,   222,     0,     0,
   105,   224,   222,     0,     0,   106,   225,   222,     0,     0,
     1,   226,   222,     0,   255,     0,   228,   230,    29,     0,
   162,   158,     0,   162,   158,   160,     0,     0,    48,    26,
     3,    27,   229,   228,     0,    28,   158,   230,     0,    28,
   158,   160,   230,     0,   255,     0,   235,   231,     0,     0,
    52,    32,   232,   231,    33,     0,     0,    48,    26,     3,
    27,   233,   231,     0,     0,     1,   234,   231,     0,   255,
     0,   116,   237,     3,   239,   236,     0,   115,   237,     3,
   239,   236,     0,    29,     0,    32,     0,    26,   162,    27,
     0,    26,   162,   159,    27,     0,   255,     0,    26,   152,
    27,     0,   255,     0,   239,   240,   238,     3,     0,   255,
     0,    63,     0,     3,    63,     0,     3,   243,   242,     0,
   242,    28,     3,   243,     0,   255,     0,    39,     8,     0,
    39,     7,     0,   255,     0,     3,     0,    36,     0,   247,
   246,     0,    28,   247,   246,     0,   255,     0,   162,   248,
     0,   162,   159,   248,     0,   162,   112,   248,     0,   162,
    26,   159,   248,    27,    26,   150,    27,     0,     3,   251,
     0,     0,     3,   160,   249,   251,     0,     0,   160,   250,
   251,     0,   251,     0,    26,   150,    27,     0,   255,     0,
     3,     0,     7,     0,   101,    26,   150,    27,   254,     0,
   101,   254,     0,     3,    29,     0,     7,    29,     0,    32,
    33,     0,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   586,   595,   607,   611,   615,   626,   643,   661,   671,   682,
   709,   713,   721,   727,   733,   742,   754,   758,   771,   780,
   784,   799,   822,   831,   837,   844,   850,   858,   867,   869,
   875,   881,   887,   899,   920,   968,   998,  1034,  1071,  1079,
  1088,  1102,  1118,  1127,  1131,  1142,  1152,  1161,  1171,  1177,
  1184,  1190,  1212,  1228,  1247,  1254,  1260,  1260,  1275,  1275,
  1285,  1295,  1308,  1327,  1339,  1357,  1372,  1393,  1404,  1421,
  1428,  1435,  1440,  1446,  1447,  1448,  1449,  1467,  1468,  1472,
  1476,  1492,  1505,  1513,  1525,  1529,  1551,  1575,  1591,  1604,
  1616,  1627,  1647,  1673,  1696,  1715,  1725,  1751,  1780,  1789,
  1796,  1802,  1810,  1814,  1822,  1823,  1849,  1850,  1860,  1863,
  1866,  1869,  1877,  1878,  1879,  1891,  1900,  1906,  1909,  1914,
  1917,  1922,  1937,  1963,  1982,  1994,  2005,  2015,  2024,  2029,
  2035,  2042,  2043,  2049,  2053,  2056,  2057,  2060,  2063,  2070,
  2074,  2079,  2089,  2090,  2094,  2098,  2105,  2108,  2116,  2119,
  2122,  2125,  2128,  2131,  2134,  2137,  2140,  2144,  2148,  2159,
  2174,  2179,  2184,  2193,  2199,  2209,  2212,  2215,  2218,  2221,
  2224,  2227,  2230,  2233,  2237,  2241,  2245,  2250,  2259,  2262,
  2268,  2274,  2280,  2290,  2293,  2299,  2305,  2311,  2319,  2320,
  2323,  2323,  2329,  2336,  2348,  2354,  2364,  2365,  2371,  2372,
  2376,  2381,  2381,  2388,  2389,  2392,  2404,  2415,  2419,  2423,
  2427,  2431,  2435,  2440,  2445,  2457,  2464,  2470,  2476,  2483,
  2490,  2501,  2513,  2525,  2537,  2549,  2556,  2566,  2577,  2578,
  2581,  2615,  2652,  2686,  2749,  2753,  2776,  2812,  2815,  2828,
  2849,  2869,  2877,  2885,  2895,  2903,  2904,  2905,  2908,  2909,
  2911,  2913,  2914,  2924,  2925,  2928,  2952,  2975,  2996,  3016,
  3036,  3087,  3089,  3120,  3139,  3143,  3163,  3174,  3185,  3196,
  3204,  3206,  3211,  3211,  3229,  3234,  3240,  3248,  3254,  3259,
  3263,  3282,  3283,  3308,  3309,  3333,  3340,  3345,  3350,  3355,
  3358,  3359,  3362,  3363,  3364,  3367,  3368,  3392,  3393,  3418,
  3421,  3424,  3427,  3428,  3429,  3432,  3433,  3436,  3451,  3467,
  3482,  3498,  3499,  3502,  3505,  3511,  3524,  3533,  3538,  3543,
  3552,  3561,  3572,  3573,  3574,  3578,  3579,  3580,  3583,  3584,
  3585,  3590,  3593,  3596,  3597,  3600,  3601,  3604,  3605,  3608,
  3609,  3617,  3633,  3650,  3661,  3666,  3667,  3668,  3683,  3684,
  3688,  3694,  3699,  3700,  3702,  3703,  3705,  3706,  3708,  3709,
  3722,  3723,  3726,  3733,  3755,  3777,  3780,  3782,  3802,  3824,
  3827,  3828,  3830,  3833,  3836,  3837,  3850,  3851,  3854,  3874,
  3895,  3896,  3899,  3902,  3906,  3914,  3918,  3926,  3932,  3937,
  3938,  3949,  3959,  3966,  3973,  3976,  3979,  3989,  3992,  3997,
  4003,  4007,  4010,  4023,  4037,  4050,  4065,  4069,  4072,  4078,
  4081,  4088,  4094,  4097,  4102,  4103,  4109,  4110,  4113,  4114,
  4115,  4147
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ID","HBLOCK",
"WRAPPER","POUND","STRING","NUM_INT","NUM_FLOAT","CHARCONST","NUM_UNSIGNED",
"NUM_LONG","NUM_ULONG","TYPEDEF","TYPE_INT","TYPE_UNSIGNED","TYPE_SHORT","TYPE_LONG",
"TYPE_FLOAT","TYPE_DOUBLE","TYPE_CHAR","TYPE_VOID","TYPE_SIGNED","TYPE_BOOL",
"TYPE_TYPEDEF","LPAREN","RPAREN","COMMA","SEMI","EXTERN","INIT","LBRACE","RBRACE",
"DEFINE","PERIOD","CONST","STRUCT","UNION","EQUAL","SIZEOF","MODULE","LBRACKET",
"RBRACKET","WEXTERN","ILLEGAL","READONLY","READWRITE","NAME","RENAME","INCLUDE",
"CHECKOUT","ADDMETHODS","PRAGMA","CVALUE","COUT","ENUM","ENDDEF","MACRO","CLASS",
"PRIVATE","PUBLIC","PROTECTED","COLON","STATIC","VIRTUAL","FRIEND","OPERATOR",
"THROW","TEMPLATE","NATIVE","INLINE","IFDEF","IFNDEF","ENDIF","ELSE","UNDEF",
"IF","DEFINED","ELIF","RAW_MODE","ALPHA_MODE","TEXT","DOC_DISABLE","DOC_ENABLE",
"STYLE","LOCALSTYLE","TYPEMAP","EXCEPT","IMPORT","ECHO","NEW","APPLY","CLEAR",
"DOCONLY","TITLE","SECTION","SUBSECTION","SUBSUBSECTION","LESSTHAN","GREATERTHAN",
"USERDIRECTIVE","OC_INTERFACE","OC_END","OC_PUBLIC","OC_PRIVATE","OC_PROTECTED",
"OC_CLASS","OC_IMPLEMENT","OC_PROTOCOL","OR","XOR","AND","LSHIFT","RSHIFT","PLUS",
"MINUS","STAR","SLASH","UMINUS","NOT","LNOT","DCOLON","program","@1","command",
"statement","@2","@3","@4","@5","@6","@7","@8","@9","@10","@11","typedef_decl",
"@12","@13","typedeflist","cond_compile","cpp_const_expr","pragma","stail","@14",
"@15","definetail","extern","func_end","parms","ptail","parm","parm_type","pname",
"def_args","parm_specifier","parm_specifier_list","declaration","stars","array",
"array2","type","strict_type","opt_signed","opt_unsigned","opt_int","definetype",
"@16","initlist","ename","enumlist","edecl","@17","etype","expr","cpp","cpp_class",
"@18","@19","@20","@21","@22","cpp_other","@23","added_members","cpp_members",
"@24","@25","@26","cpp_member","@27","@28","@29","@30","@31","@32","nested_decl",
"type_extra","cpp_tail","@33","@34","cpp_end","cpp_vend","cpp_enumlist","cpp_edecl",
"inherit","base_list","base_specifier","access_specifier","cpptype","cpp_const",
"ctor_end","ctor_initializer","mem_initializer_list","mem_initializer","expr_list",
"objective_c","@35","@36","objc_inherit","objc_protolist","objc_data","@37",
"@38","@39","@40","objc_vars","objc_var","@41","objc_vartail","objc_methods",
"@42","@43","@44","objc_method","objc_end","objc_ret_type","objc_arg_type","objc_args",
"objc_separator","stylelist","styletail","stylearg","tm_method","tm_list","tm_tail",
"typemap_parm","typemap_name","@45","@46","typemap_args","idstring","user_directive",
"uservalue","empty", NULL
};
#endif

static const short yyr1[] = {     0,
   124,   123,   125,   125,   126,   126,   126,   126,   126,   127,
   126,   126,   128,   126,   126,   129,   126,   126,   130,   126,
   126,   126,   131,   126,   126,   126,   126,   126,   132,   126,
   133,   126,   126,   126,   126,   126,   126,   126,   126,   126,
   126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
   126,   126,   126,   126,   126,   126,   134,   126,   135,   136,
   126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
   126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
   126,   126,   126,   138,   137,   137,   137,   139,   137,   140,
   140,   140,   141,   141,   141,   141,   141,   141,   142,   142,
   142,   143,   143,   143,   144,   145,   144,   146,   144,   147,
   147,   147,   148,   148,   148,   149,   150,   150,   151,   151,
   152,   152,   153,   153,   153,   153,   153,   154,   154,   154,
   154,   155,   155,   155,   155,   156,   156,   157,   157,   158,
   158,   158,   159,   159,   160,   160,   161,   161,   162,   162,
   162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
   162,   162,   162,   162,   162,   163,   163,   163,   163,   163,
   163,   163,   163,   163,   163,   163,   163,   163,   164,   164,
   164,   164,   164,   165,   165,   165,   165,   165,   166,   166,
   168,   167,   167,   167,   169,   169,   170,   170,   171,   171,
   172,   173,   172,   172,   172,   174,   174,   175,   175,   175,
   175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
   175,   175,   175,   175,   175,   175,   175,   175,   176,   176,
   178,   177,   179,   180,   177,   181,   182,   177,   183,   183,
   183,   183,   183,   184,   183,   185,   185,   185,   186,   187,
   188,   186,   189,   186,   186,   190,   190,   190,   190,   190,
   191,   190,   190,   192,   190,   190,   190,   190,   190,   190,
   193,   190,   194,   190,   190,   190,   190,   190,   190,   190,
   190,   195,   190,   196,   190,   190,   190,   190,   190,   190,
   197,   197,   198,   198,   198,   199,   200,   199,   201,   199,
   202,   202,   203,   203,   203,   204,   204,   205,   205,   205,
   205,   205,   205,   206,   206,   207,   207,   208,   208,   208,
   208,   208,   209,   209,   209,   210,   210,   210,   211,   211,
   211,   212,   212,   213,   213,   214,   214,   215,   215,   216,
   216,   218,   217,   219,   217,   217,   217,   217,   220,   220,
   221,   221,   222,   223,   222,   224,   222,   225,   222,   226,
   222,   222,   227,   228,   228,   229,   228,   230,   230,   230,
   231,   232,   231,   233,   231,   234,   231,   231,   235,   235,
   236,   236,   237,   237,   237,   238,   238,   239,   239,   240,
   240,   241,   242,   242,   243,   243,   243,   244,   244,   245,
   246,   246,   247,   247,   247,   247,   248,   249,   248,   250,
   248,   248,   251,   251,   252,   252,   253,   253,   254,   254,
   254,   255
};

static const short yyr2[] = {     0,
     0,     2,     2,     1,     2,     2,     2,     2,     1,     0,
     7,     4,     0,     7,     4,     0,     9,     7,     0,     8,
     7,     7,     0,     9,     1,     1,     4,     4,     0,     3,
     0,     5,     7,    11,     3,     3,     3,     3,     1,     1,
     1,     1,     2,     1,     1,     2,     2,     2,     2,     2,
     1,     3,     3,     3,     2,     2,     0,     8,     0,     0,
    10,     8,     6,     8,     6,    10,     8,     5,     3,     5,
     2,     5,     2,     1,     1,     1,     1,     5,     1,     1,
     2,     2,     1,     0,     5,    10,    11,     0,     6,     3,
     3,     1,     2,     2,     1,     1,     2,     2,     4,     2,
     2,     7,     3,     6,     1,     0,     6,     0,     8,     2,
     1,     2,     1,     1,     2,     2,     2,     1,     3,     1,
     1,     2,     2,     3,     3,     8,     3,     2,     2,     1,
     1,     2,     3,     2,     1,     1,     1,     2,     1,     1,
     2,     2,     2,     2,     3,     4,     1,     1,     1,     2,
     2,     1,     1,     1,     1,     1,     2,     2,     2,     2,
     2,     2,     3,     2,     2,     1,     2,     2,     1,     1,
     1,     1,     1,     2,     2,     2,     2,     2,     1,     1,
     2,     2,     1,     1,     1,     2,     2,     1,     1,     1,
     0,     2,     1,     1,     3,     1,     1,     1,     3,     1,
     1,     0,     4,     2,     1,     1,     1,     1,     1,     1,
     1,     1,     4,     4,     1,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     2,     2,     3,     1,     1,
     0,     8,     0,     0,    11,     0,     0,     9,     4,     9,
     6,     5,     1,     0,     6,     2,     2,     1,     2,     0,
     0,     7,     0,     3,     1,     6,     7,     5,     6,     6,
     0,     5,     4,     0,     5,     7,     2,     2,     2,     4,
     0,     3,     0,     7,     1,     1,     1,     3,     1,     1,
     1,     0,     6,     0,     5,     3,     3,     3,     3,     1,
     1,     1,     1,     1,     1,     1,     0,     5,     0,     6,
     2,     2,     2,     4,     2,     3,     1,     1,     3,     5,
     7,     2,     1,     2,     1,     1,     3,     1,     2,     3,
     2,     3,     1,     1,     1,     1,     1,     1,     1,     4,
     1,     3,     3,     2,     1,     1,     3,     4,     3,     1,
     3,     0,     9,     0,     9,     1,     1,     4,     3,     2,
     1,     1,     2,     0,     3,     0,     3,     0,     3,     0,
     3,     1,     3,     2,     3,     0,     6,     3,     4,     1,
     2,     0,     5,     0,     6,     0,     3,     1,     5,     5,
     1,     1,     3,     4,     1,     3,     1,     4,     1,     1,
     2,     3,     4,     1,     2,     2,     1,     1,     1,     2,
     3,     1,     2,     3,     3,     8,     2,     0,     4,     0,
     3,     1,     3,     1,     1,     1,     5,     2,     2,     2,
     2,     0
};

static const short yydefact[] = {     1,
   422,     0,     4,    77,    45,     0,     9,     0,    74,   113,
     0,     0,     0,     0,    25,    26,     0,     0,     0,     0,
     0,     0,     0,   243,     0,     0,     0,     0,    96,    95,
     0,     0,     0,    40,    39,     0,    41,    42,     0,     0,
     0,     0,     0,     0,    29,     0,     0,    51,     0,     0,
     0,     0,     0,     0,     0,   346,   347,     3,    44,    79,
    80,     0,    75,   229,   230,    76,    83,   114,    46,   422,
   149,   422,   422,   422,   154,   155,   152,   156,   422,   153,
   422,     0,   327,   328,   422,   326,     0,     0,     0,   115,
   422,    47,     0,    55,   422,   415,   416,     6,     0,     0,
     5,     8,     0,   422,     0,   149,   422,   422,   422,   154,
   155,   152,   156,   422,   153,   422,     0,     0,     0,     0,
     0,     0,    48,     0,     0,    93,    94,    56,     0,     0,
    97,    98,    43,   422,    81,    82,     0,     0,    73,    71,
     7,    49,    50,     0,   422,     0,     0,   422,   422,   422,
   422,   422,     0,     0,   422,     0,   418,   422,   422,   422,
   422,     0,   422,     0,     0,     0,     0,     0,   351,     0,
   160,   352,   185,   422,   422,   188,   158,   184,   189,   150,
   190,   151,   180,   422,   422,   183,   157,   179,   159,   161,
   165,     0,   198,   164,   140,     0,    84,     0,   162,   236,
   422,    52,   196,     0,   193,   194,   111,    54,     0,     0,
    53,     0,    31,     0,   244,     0,   103,   397,     0,   158,
   150,   151,   157,   159,   161,   165,   422,     0,   162,     0,
     0,   162,   100,     0,   101,   422,   398,   399,     0,     0,
    30,   422,   422,     0,   422,   422,   410,   403,   412,   414,
     0,    69,     0,   400,   402,    35,   394,    36,    37,    38,
   419,   420,     0,   136,   137,     0,   422,   121,   139,     0,
   422,   118,   421,     0,     0,   342,   422,     0,     0,   142,
   144,   143,   422,   141,   422,     0,   162,   163,   186,   187,
   181,   182,    59,   422,   422,    88,     0,     0,     0,   315,
     0,     0,     0,   112,   110,   215,   208,   209,   210,   211,
   212,     0,     0,     0,     0,   192,    27,   422,    28,   422,
   396,   395,     0,     0,   422,   147,   422,   148,    15,   422,
   422,     0,   392,     0,     0,     0,   422,   408,   407,     0,
   422,   422,     0,   405,   404,   422,     0,   422,     0,     0,
     0,     0,   117,   120,   122,   138,   422,     0,   422,   123,
   422,   130,   131,     0,   422,     0,   350,   348,    57,     0,
   422,     0,   422,    12,   239,     0,   422,     0,     0,    85,
    92,   422,   422,   318,   324,   323,   325,     0,   314,   316,
     0,   233,   253,   422,     0,   290,   275,   276,     0,     0,
   422,     0,     0,     0,     0,     0,   277,   271,     0,   280,
   279,   281,   422,     0,     0,     0,     0,   255,    78,   195,
     0,   166,   422,   422,   422,   171,   172,   169,   173,   422,
   170,   422,     0,     0,     0,     0,     0,   226,   227,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   113,
     0,    32,   422,   422,     0,     0,     0,   248,   422,   422,
     0,   191,    13,   135,     0,     0,    99,   398,     0,     0,
    72,    70,   422,   413,     0,   145,   422,   411,    68,   401,
   422,   127,   417,   422,   128,   129,   422,   125,   124,   422,
   349,     0,   422,   422,     0,     0,   242,    10,   231,   201,
   422,     0,   200,   205,     0,   422,    89,     0,   319,     0,
     0,   321,     0,     0,     0,   422,     0,   250,     0,   268,
   267,   269,     0,     0,     0,     0,     0,   294,   422,   293,
     0,   295,     0,     0,   249,   162,   284,   216,   175,   167,
   168,   174,   176,   177,     0,   228,   178,     0,   222,   223,
   221,   224,   225,   217,   218,   219,   220,     0,   115,     0,
     0,     0,     0,   385,     0,   245,   246,   376,     0,     0,
   247,     0,   378,   104,     0,   422,   134,     0,   132,     0,
   422,     0,   422,     0,    65,    63,     0,   409,     0,   146,
   393,   119,     0,   344,   360,     0,   354,   356,   358,     0,
     0,     0,   422,   362,     0,   329,     0,    19,   331,   422,
   422,   241,     0,     0,   202,   204,   422,     0,   422,    90,
    91,     0,   320,   317,   322,     0,   254,   289,     0,     0,
     0,   273,   264,     0,     0,   272,   422,   422,   261,   422,
   287,   278,   288,   237,   286,   282,     0,   214,   213,   422,
     0,   162,     0,   422,   422,     0,     0,   372,   371,   102,
    21,    23,   133,     0,   105,    14,    33,     0,    22,     0,
     0,     0,   422,     0,     0,     0,     0,     0,     0,     0,
   364,     0,   353,     0,     0,   370,     0,   422,     0,    18,
    16,     0,    11,     0,     0,   199,    60,     0,   422,     0,
   422,   270,     0,   422,   422,     0,     0,   422,     0,     0,
     0,   263,   422,   422,     0,   383,     0,     0,   389,     0,
   377,     0,     0,   116,     0,   422,   422,    64,    62,     0,
    67,     0,   422,     0,   361,     0,   355,   357,   359,   365,
     0,   422,   363,    58,     0,    20,     0,     0,   232,   207,
   203,   206,   422,     0,     0,   234,   422,   258,   251,   308,
     0,   422,     0,   307,   313,     0,     0,   296,   265,   422,
     0,   422,   422,   262,   238,   291,     0,   292,   285,   384,
     0,   381,   382,   390,   380,   422,   379,   374,     0,    24,
   422,   422,     0,     0,   406,     0,   345,   366,   343,   422,
   368,   330,    17,   240,    61,    86,     0,   422,     0,     0,
   335,     0,     0,     0,   312,   422,     0,   422,   422,   260,
     0,   422,   259,   256,   283,   391,     0,     0,   387,     0,
   373,     0,   106,     0,    66,   126,     0,   369,    87,   235,
     0,   334,   336,   332,   333,   252,   309,     0,   306,   274,
   266,   297,   422,   301,   302,   257,     0,     0,   388,   375,
   422,     0,    34,   367,     0,     0,     0,     0,   299,   303,
   305,   191,   386,   108,   107,   339,   340,     0,   337,   310,
   298,     0,     0,     0,   338,     0,     0,   300,   304,   109,
   341,   311,     0,     0,     0
};

static const short yydefgoto[] = {   893,
     1,     2,    58,   613,   580,   747,   689,   725,   144,   318,
   493,   377,   753,   410,   295,   382,   380,   411,   131,   412,
   666,   862,   884,   208,    62,   661,   340,   353,   267,   268,
   360,   463,   269,   270,   164,   165,   362,   327,   271,   414,
   187,   177,   180,   209,   210,   202,   192,   502,   503,   695,
   751,   752,    63,    64,   614,   514,   808,   301,   713,    65,
   320,   455,   415,   631,   812,   515,   416,   711,   706,   526,
   704,   714,   647,   777,   531,   769,   868,   882,   820,   856,
   763,   764,   299,   389,   390,   391,   125,   821,   758,   810,
   842,   843,   878,    66,   366,   675,   276,   171,   601,   678,
   679,   680,   676,   602,   603,   837,   685,   571,   723,   830,
   656,   572,   785,   563,   828,   718,   786,   135,   256,   217,
   239,   147,   254,   148,   248,   473,   346,   249,    98,    67,
   157,   272
};

static const short yypact[] = {-32768,
-32768,  1140,-32768,-32768,-32768,    58,-32768,  1789,-32768,    80,
   424,    52,   158,    93,-32768,-32768,   144,   272,    93,    93,
   282,   184,  1813,-32768,   290,  1673,   315,   368,-32768,-32768,
   375,   -35,   -35,-32768,-32768,   394,-32768,-32768,   381,   381,
   393,   251,    93,   373,-32768,  1837,  1837,-32768,   427,   466,
   481,   495,   400,   403,   513,-32768,-32768,-32768,-32768,-32768,
-32768,  1008,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   269,
-32768,   508,   503,   503,-32768,-32768,-32768,-32768,   590,-32768,
   425,  1837,-32768,-32768,   528,-32768,   569,    73,   227,   542,
-32768,-32768,   633,-32768,-32768,-32768,-32768,-32768,   319,   578,
-32768,-32768,   556,   544,   594,   577,   508,   503,   503,   580,
   584,   588,   603,   590,   605,   425,  1837,   619,    95,   609,
   634,   635,-32768,    95,   644,-32768,-32768,-32768,   382,   -35,
-32768,-32768,-32768,   544,-32768,-32768,   177,   645,-32768,-32768,
-32768,-32768,-32768,  1360,   150,   585,   623,   628,-32768,-32768,
-32768,-32768,   631,   632,   821,   624,-32768,   175,-32768,    15,
   528,   667,   555,   650,   679,    95,   657,   681,-32768,   682,
-32768,-32768,-32768,   503,   503,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,   503,   503,-32768,-32768,-32768,-32768,-32768,
   655,   656,-32768,-32768,-32768,   572,   649,   399,    12,-32768,
-32768,   665,-32768,   637,-32768,-32768,-32768,-32768,   638,   693,
   665,   670,-32768,   678,-32768,   539,-32768,-32768,   530,   673,
   683,   684,   685,   688,   690,-32768,   311,   600,   692,   694,
   697,-32768,-32768,   705,-32768,-32768,   706,-32768,   708,   709,
-32768,   415,  1078,    48,   288,   288,-32768,-32768,-32768,-32768,
  1837,-32768,  1837,-32768,-32768,   710,-32768,   710,   710,   710,
-32768,-32768,   702,-32768,-32768,   712,   714,-32768,-32768,   821,
   237,-32768,-32768,   717,   737,-32768,-32768,   523,   711,-32768,
-32768,-32768,   821,-32768,   185,   629,   202,-32768,-32768,-32768,
-32768,-32768,-32768,   124,   719,-32768,   640,   389,   716,-32768,
   880,  1250,   747,-32768,-32768,   636,-32768,-32768,-32768,-32768,
-32768,  1925,   725,   693,   693,  1522,-32768,   259,-32768,  1470,
-32768,-32768,   751,   752,   821,-32768,   720,-32768,-32768,   730,
   821,   736,   710,   179,  1837,   465,   821,-32768,-32768,   738,
   288,   649,  1626,-32768,-32768,   740,   731,   628,   764,   733,
   236,   821,-32768,-32768,-32768,-32768,   423,   555,   124,-32768,
   124,-32768,-32768,   743,   425,   744,-32768,-32768,-32768,   748,
   821,    45,   720,-32768,-32768,   745,   322,   753,    95,-32768,
-32768,   719,   124,-32768,-32768,-32768,-32768,   349,   750,-32768,
    37,-32768,-32768,    23,  1837,-32768,-32768,-32768,   755,   754,
   528,   721,   724,   727,  1837,  1697,-32768,-32768,   776,-32768,
-32768,-32768,   102,   757,   759,   880,   300,-32768,-32768,-32768,
   785,-32768,   508,   503,   503,-32768,-32768,-32768,-32768,   590,
-32768,   425,  1837,   767,   937,   792,  1837,-32768,-32768,   693,
   693,   693,   693,   693,   693,   693,   693,   693,   380,   789,
  1837,-32768,   771,   771,   768,   880,   484,-32768,   544,   544,
   773,    60,-32768,-32768,  1861,   775,-32768,-32768,   777,   498,
-32768,-32768,   740,-32768,   779,-32768,   649,-32768,-32768,-32768,
   544,-32768,-32768,   714,-32768,-32768,   124,-32768,-32768,   425,
-32768,   957,   322,   201,   783,   469,-32768,-32768,-32768,   780,
   322,   405,-32768,-32768,   788,   176,-32768,   793,-32768,   800,
   389,-32768,   813,   880,   880,  1628,   819,-32768,   791,-32768,
-32768,-32768,    95,   822,    95,  1551,   802,   667,   445,   410,
   763,-32768,   715,    95,-32768,   586,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   693,-32768,-32768,   799,   450,   551,
   614,   478,   478,   460,   460,-32768,-32768,   312,-32768,    95,
   830,  1837,   831,-32768,   832,-32768,-32768,-32768,   823,   815,
-32768,   254,-32768,-32768,   824,   201,-32768,   845,-32768,   591,
     2,    95,   201,  1837,-32768,-32768,  1837,-32768,   827,-32768,
-32768,-32768,   828,-32768,-32768,   835,-32768,-32768,-32768,    95,
   817,   957,   826,-32768,   433,-32768,   836,-32768,-32768,   201,
   821,-32768,   591,   880,-32768,-32768,   322,   860,   821,-32768,
-32768,   838,-32768,-32768,-32768,   833,-32768,-32768,   840,   842,
   880,-32768,   844,   846,   847,-32768,   821,   821,-32768,   720,
-32768,-32768,-32768,-32768,-32768,-32768,    95,-32768,-32768,   808,
   762,   292,     6,-32768,-32768,   254,   871,-32768,-32768,-32768,
-32768,   853,-32768,    95,-32768,-32768,-32768,   861,-32768,   853,
   509,   857,   821,   862,    78,   957,   887,   957,   957,   957,
   649,    78,-32768,    95,   863,-32768,   864,   821,   591,-32768,
   853,   881,-32768,   858,   434,-32768,-32768,   884,   821,    95,
   201,-32768,   874,   512,   821,   596,   885,   821,   888,   892,
   596,-32768,   719,    95,   891,-32768,   894,   229,-32768,   229,
-32768,   895,   484,-32768,   591,   437,   821,-32768,-32768,  1837,
-32768,   896,   821,   811,-32768,   898,-32768,-32768,-32768,-32768,
   834,   331,-32768,-32768,   903,-32768,   591,   902,-32768,-32768,
-32768,  1522,   719,   905,   908,-32768,   886,-32768,-32768,   909,
   921,   512,   436,-32768,-32768,   923,    95,-32768,-32768,   201,
   924,   201,   201,-32768,-32768,-32768,   927,-32768,-32768,-32768,
   899,-32768,-32768,-32768,-32768,   935,-32768,-32768,   930,-32768,
   821,   720,   939,   938,-32768,   941,-32768,-32768,-32768,   826,
-32768,-32768,-32768,-32768,-32768,-32768,   940,   719,   967,   474,
-32768,   880,   434,   980,-32768,   512,   955,   201,   423,-32768,
   524,   201,-32768,-32768,-32768,-32768,   821,   982,-32768,   254,
-32768,   959,-32768,   960,-32768,-32768,  1743,-32768,-32768,-32768,
   965,   964,-32768,-32768,-32768,-32768,-32768,   969,-32768,-32768,
-32768,-32768,   720,-32768,-32768,-32768,   510,   970,-32768,-32768,
   201,   591,-32768,-32768,    26,   967,   995,   596,-32768,-32768,
-32768,   500,-32768,-32768,-32768,-32768,  1522,   599,-32768,   962,
-32768,   596,   974,   591,-32768,   693,   434,-32768,-32768,-32768,
  1522,-32768,  1004,  1006,-32768
};

static const short yypgoto[] = {-32768,
-32768,   806,   865,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,     8,-32768,-32768,  -378,    11,    -5,    21,
  -550,-32768,-32768,-32768,    56,  -245,  -129,   526,  -349,   742,
  -264,  -352,   749,-32768,    98,   -80,    63,  -278,   473,    -8,
  -103,   -87,    97,  -456,-32768,   -27,  -144,   515,  -477,-32768,
  -731,  -194,   696,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,  -398,-32768,-32768,-32768,  -301,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,  -679,-32768,-32768,  -594,-32768,
-32768,  -685,  -273,-32768,   504,   630,    19,  -472,-32768,-32768,
-32768,   151,-32768,-32768,-32768,-32768,-32768,   -69,  -381,-32768,
-32768,-32768,-32768,-32768,   183,-32768,  -633,  -487,-32768,-32768,
-32768,   701,   302,   582,-32768,   379,-32768,   997,   -16,   -98,
   704,  -242,   691,   -44,  -200,-32768,-32768,  -217,   347,-32768,
   689,    -1
};


#define	YYLAST		2045


static const short yytable[] = {     3,
    68,   146,   484,   507,   485,   579,   373,   198,   347,    59,
   223,   189,    60,   376,   120,   316,   279,   535,   456,   220,
   498,   608,    61,   616,   339,   266,    89,   132,   306,   378,
   667,   774,   716,   307,   308,   236,   309,   310,   311,   512,
  -140,   121,   129,  -422,   344,   345,   224,   496,   516,   343,
   306,   312,   876,   167,    93,   307,   308,   567,   309,   310,
   311,    69,   693,   476,   246,   313,   205,   211,   172,   206,
   178,   181,   181,   312,   298,   195,   815,   188,   568,   172,
   168,   847,   281,   193,   659,   130,    90,   313,   277,   203,
   342,   577,   470,   203,   488,    96,   489,   195,   196,    97,
   169,   513,   218,   662,   195,   178,   181,   181,   801,    94,
   670,   497,   188,   169,   172,   626,   627,   435,   508,   438,
   439,   169,   163,   170,   235,   569,   357,   620,   478,   570,
   849,   278,   218,   258,   259,   260,   170,   691,   746,   696,
   475,   314,    68,   250,   170,   315,   255,   257,   257,   257,
   257,    59,   242,   370,    60,   892,   172,   203,   172,   193,
    95,   282,   341,   314,    61,   244,   838,   315,   721,    99,
   182,   578,   181,   181,   790,   243,   639,   823,   824,   237,
  -422,   468,   181,   181,   162,   197,   104,   734,   881,   163,
   361,   244,   453,   454,   741,   461,   803,   300,   590,     3,
   274,   466,   888,   379,   221,   222,   162,   247,   348,   105,
   371,   163,   238,   528,   238,   694,   227,   244,   163,   333,
   683,   231,   593,   851,   636,   328,   244,  -178,   757,   199,
   375,   781,   703,  -422,   257,   789,   606,   275,   153,   357,
   250,   495,   154,   250,   250,   549,   550,   551,   552,   553,
   554,   555,   556,   557,   568,   588,   519,   782,   200,   296,
   783,   245,   358,   285,   298,   354,   163,   156,   607,   363,
   289,   290,   449,   169,   100,   367,   138,   487,   244,   139,
   291,   292,   140,   328,   103,   300,  -422,   712,   450,   326,
   242,   784,   363,   381,   735,   491,   737,   738,   739,   418,
    68,   569,   536,   434,   338,   570,   372,   247,   247,    59,
    21,   875,    60,   337,   650,   122,    68,   126,   458,   417,
   375,   212,    61,  -422,   500,   464,   542,    24,    68,   244,
   436,   537,   530,   890,   775,   539,   325,   669,   417,   250,
   328,   671,   860,   200,   250,   213,   255,   326,   359,   857,
   648,   509,   244,   163,   298,   464,  -422,   363,   684,   363,
   574,   575,   543,   172,   690,   101,   102,   169,   453,   454,
   127,   464,   244,   451,   805,   504,   142,   128,   376,   143,
   381,   363,   591,   134,   233,   465,   629,   501,   874,   141,
   170,   384,   172,    27,    28,    29,    30,   133,    32,   193,
    33,   284,   153,   247,   326,   158,   154,   234,   385,   386,
   387,   532,   284,   846,   418,   883,    83,    84,   137,   486,
   594,   178,   181,   181,   297,   155,    91,    92,   188,   840,
   172,   156,   617,   149,   417,   641,   306,   618,    86,   833,
   337,   307,   308,   750,   309,   310,   311,   792,   385,   386,
   387,   564,   564,   388,   418,   573,   244,   218,   218,   312,
   617,   462,   791,   816,   244,   687,   852,   558,   817,   561,
   638,   250,   150,   313,   417,   328,   506,   858,   244,   218,
    88,   692,   354,   462,   568,   363,   244,   151,   172,   698,
   604,   504,   609,   471,   611,   119,   472,   612,   124,   504,
   869,   152,   844,   501,   381,   845,   205,   709,   710,   206,
   529,   501,   418,   418,   760,   159,  -422,   179,   145,   145,
   540,   541,   173,   169,   174,   175,   585,   464,   176,   586,
   191,   569,   417,   417,   166,   570,   587,   728,   870,   326,
   729,   871,   672,   732,   417,   321,   322,   730,   872,   314,
   303,   368,   854,   315,   190,   855,   323,   324,   745,   761,
   441,   442,   443,   444,   445,   446,   447,   448,   621,   755,
   573,   194,   717,   201,   609,   766,   447,   448,   771,   172,
   214,   609,   216,    27,    28,    29,    30,   215,    32,   225,
    33,   640,   445,   446,   447,   448,   219,   793,   453,   454,
   604,   686,  -166,   796,   183,  -171,   184,   185,   609,  -172,
   186,  -178,   418,  -169,   645,   504,   251,   646,   664,   665,
   633,   226,   635,   767,   768,   885,   886,   501,  -173,   418,
  -170,   644,   417,   204,   228,  -191,   229,   230,   464,   205,
  -191,  -191,   206,  -191,  -191,  -191,   232,   240,   300,   417,
   300,   252,   719,   719,   573,   253,   273,   651,  -191,   261,
   262,   832,   442,   443,   444,   445,   446,   447,   448,   280,
   877,   163,  -191,   573,   604,   283,   604,   604,   604,   668,
   573,   284,   286,   287,   288,   794,  -197,   293,   294,   207,
   244,   891,   303,   304,   305,   306,   317,   681,  -175,   609,
   307,   308,   765,   309,   310,   311,   319,   332,  -167,  -168,
  -174,   381,   778,  -176,   762,  -177,   329,  -178,   312,   364,
   330,   573,   331,   145,   328,   145,   443,   444,   445,   446,
   447,   448,   313,   334,   335,   336,   350,   349,   351,   365,
   686,   352,   369,   740,   715,   374,   379,   392,  -191,   420,
   437,   381,  -191,   459,   460,   811,   383,   421,   462,   450,
   765,   726,   467,   479,   474,   337,   481,   482,   609,   490,
   609,   609,   762,   413,   494,   492,   499,   511,   527,   505,
   517,   742,   533,   520,   829,   518,   521,   538,   326,   522,
   464,   534,   413,   545,   547,   559,   562,   756,   686,   576,
   566,   583,   623,   584,   800,   589,   381,   145,   314,   610,
   418,   776,   315,   619,   765,   625,   609,   464,   615,   622,
   609,   630,   632,    70,   634,   649,   762,   637,   573,   642,
   417,   643,   652,   654,   655,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,   658,   663,   657,   682,
   660,   464,   673,   684,   674,   263,    82,    83,    84,   609,
   677,   688,   697,   699,   819,   700,   701,    88,   702,   705,
   298,   707,   708,   722,   264,   265,   118,   523,   525,    86,
   393,   853,   394,   372,   724,   731,   727,   733,   413,   736,
   749,   743,   744,   395,   106,   107,   108,   109,   110,   111,
   112,   113,   114,   115,   116,   544,   759,   748,   396,   548,
   754,   770,  -422,   797,   772,   117,    83,    84,   773,   779,
   780,   788,   795,   560,   798,   397,   398,   399,   413,   802,
   804,   400,    22,   806,   807,   401,   799,   582,    86,   402,
   403,   404,    87,   405,   406,   407,   814,   813,   809,   818,
   822,    27,    28,    29,    30,   825,    32,   595,    33,    70,
   827,   826,   831,   546,   600,   834,   835,   836,   839,   841,
   408,    71,    72,    73,    74,    75,    76,    77,    78,    79,
    80,    81,   848,   850,   859,   861,   413,   413,   863,  -422,
   865,   866,    82,    83,    84,   867,   873,   880,   413,   409,
   887,    87,   889,   894,   596,   895,   302,   605,   241,   592,
   160,   355,   118,   452,   624,    86,   879,   510,   356,   864,
   457,   787,   106,   107,   108,   109,   110,   111,   112,   113,
   114,   115,   116,   720,   653,   565,   136,   469,   480,   483,
     0,     0,     0,   117,    83,    84,   440,   441,   442,   443,
   444,   445,   446,   447,   448,     0,   145,     0,     0,   145,
   597,   598,   599,   161,     0,     0,    86,     0,     0,     0,
     0,     0,     0,     0,   600,     0,     0,     0,    87,     0,
    70,     0,     0,     0,     0,     0,   413,     0,     0,     0,
     0,     0,    71,    72,    73,    74,    75,    76,    77,    78,
    79,    80,    81,   413,     0,     0,     0,     0,     0,     0,
     0,     0,   263,    82,    83,    84,     0,     0,     0,   162,
     0,     0,     0,     0,   163,     0,     0,     0,     0,    87,
     0,   264,   265,   118,     0,     0,    86,     0,     0,    -2,
     4,     0,  -422,     5,     6,     7,     0,     0,   600,     0,
   600,   600,   600,     8,  -422,  -422,  -422,  -422,  -422,  -422,
  -422,  -422,  -422,  -422,  -422,     0,     0,     0,     9,    10,
    11,     0,     0,    12,     0,  -422,  -422,  -422,     0,     0,
    13,     0,     0,    14,     0,    15,    16,    17,    18,    19,
    20,    21,    22,     0,   163,  -422,     0,     0,  -422,    87,
     0,     0,   145,    23,     0,     0,     0,     0,    24,    25,
    26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,     0,     0,
    53,    54,     0,     0,     0,     0,    55,    56,    57,     0,
     4,  -422,  -422,     5,     6,     7,  -422,     0,     0,     0,
     0,  -422,     0,     8,  -422,  -422,  -422,  -422,  -422,  -422,
  -422,  -422,  -422,  -422,  -422,     0,     0,     0,     9,    10,
    11,     0,   419,    12,   413,  -422,  -422,  -422,     0,     0,
    13,     0,     0,    14,     0,    15,    16,    17,    18,    19,
    20,    21,    22,     0,     0,  -422,     0,     0,  -422,   600,
     0,     0,     0,    23,     0,     0,     0,     0,    24,    25,
    26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,     0,     0,
    53,    54,     0,     0,     0,     0,    55,    56,    57,     0,
     4,  -422,  -422,     5,     6,     7,  -422,     0,     0,     0,
     0,  -422,     0,     8,  -422,  -422,  -422,  -422,  -422,  -422,
  -422,  -422,  -422,  -422,  -422,     0,     0,     0,     9,    10,
    11,     0,     0,    12,     0,  -422,  -422,  -422,     0,     0,
    13,     0,     0,    14,     0,    15,    16,    17,    18,    19,
    20,    21,    22,     0,     0,  -422,     0,     0,  -422,     0,
     0,     0,     0,    23,     0,     0,     0,     0,    24,    25,
    26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,     0,     0,
    53,    54,     0,     0,     0,     0,    55,    56,    57,     0,
     0,  -422,   394,     0,     0,     0,  -422,     0,     0,     0,
     0,  -422,     0,   395,   106,   107,   108,   109,   110,   111,
   112,   113,   114,   115,   116,     0,     0,     0,   396,     0,
     0,     0,     0,     0,     0,   117,    83,    84,     0,     0,
     0,     0,     0,     0,     0,   397,   398,   399,     0,     0,
     0,     0,    22,     0,     0,   401,     0,     0,    86,   402,
   403,   404,     0,   405,   406,   407,     0,     0,     0,     0,
     0,    27,    28,    29,    30,     0,    32,     0,    33,     0,
     0,     0,     0,   394,     0,     0,     0,     0,     0,     0,
   408,     0,     0,     0,   395,   106,   107,   108,   109,   110,
   111,   112,   113,   114,   115,   116,     0,     0,     0,   396,
     0,     0,     0,     0,   453,   454,   117,    83,    84,   409,
     0,    87,     0,     0,     0,     0,   397,   398,   399,     0,
     0,     0,     0,    22,     0,     0,   401,     0,     0,    86,
   402,   403,   404,     0,   405,   406,   407,     0,     0,     0,
     0,     0,    27,    28,    29,    30,     0,    32,     0,    33,
    70,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     0,   408,    71,    72,    73,    74,    75,    76,    77,    78,
    79,    80,    81,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   263,    82,    83,    84,     0,     0,   477,     0,
   409,     0,    87,     0,     0,    70,   123,     0,     0,     0,
     0,   264,   265,   118,     0,     0,    86,    71,    72,    73,
    74,    75,    76,    77,    78,    79,    80,    81,     0,    70,
     0,     0,     0,     0,     0,     0,     0,     0,    82,    83,
    84,    71,    72,    73,    74,    75,    76,    77,    78,    79,
    80,    81,     0,     0,     0,     0,     0,     0,   118,     0,
     0,    86,    82,    83,    84,   440,   441,   442,   443,   444,
   445,   446,   447,   448,   628,    70,     0,     0,     0,    87,
     0,     0,   118,     0,     0,    86,     0,    71,    72,    73,
    74,    75,    76,    77,    78,    79,    80,    81,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    82,    83,
    84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   596,    70,     0,     0,    87,     0,     0,     0,   118,     0,
     0,    86,     0,    71,    72,    73,    74,    75,    76,    77,
    78,    79,    80,    81,     0,    70,   524,     0,    87,     0,
     0,     0,     0,     0,    82,    83,    84,   106,   107,   108,
   109,   110,   111,   112,   113,   114,   115,   116,     0,    70,
     0,     0,     0,     0,    85,     0,     0,    86,   117,    83,
    84,    71,    72,    73,    74,    75,    76,    77,    78,    79,
    80,    81,     0,   581,    87,     0,     0,     0,   118,     0,
     0,    86,    82,    83,    84,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,     0,     0,     0,     0,
     0,     0,   118,     0,     0,    86,    82,    83,    84,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    87,     0,     0,     0,     0,     0,   118,     0,     0,    86,
     0,     0,     0,     0,     0,     0,     0,   306,     0,     0,
     0,     0,   307,   308,    87,   309,   310,   311,     0,   422,
   423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
   312,     0,     0,     0,     0,     0,     0,     0,    87,     0,
   433,    83,    84,     0,   313,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    87,    86,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   314,     0,     0,     0,   315
};

static const short yycheck[] = {     1,
     2,    46,   352,   382,   357,   462,   285,    88,   251,     2,
   114,    81,     2,   287,    23,   210,   161,   416,   320,   107,
   373,   494,     2,   501,   242,   155,     8,    33,     3,   294,
    29,   711,    27,     8,     9,   134,    11,    12,    13,     3,
    26,    23,    78,    32,   245,   246,   116,     3,    26,   244,
     3,    26,    27,    62,     3,     8,     9,   456,    11,    12,
    13,     4,   613,   342,   145,    40,     7,    95,    70,    10,
    72,    73,    74,    26,    63,     3,   762,    79,     1,    81,
    62,   813,   163,    85,   572,   121,     7,    40,   158,    91,
    43,    32,   335,    95,   359,     3,   361,     3,    26,     7,
    99,    65,   104,   576,     3,   107,   108,   109,   742,    58,
   583,    67,   114,    99,   116,   514,   515,   312,   383,   314,
   315,    99,   117,   122,   130,    48,     3,   506,   346,    52,
   816,   159,   134,   150,   151,   152,   122,   610,   689,   617,
   341,   116,   144,   145,   122,   120,   148,   149,   150,   151,
   152,   144,     3,   283,   144,   887,   158,   159,   160,   161,
     3,   163,   243,   116,   144,    42,   800,   120,   656,    26,
    74,   112,   174,   175,   725,    26,   529,   772,   773,     3,
   103,     3,   184,   185,   112,    88,     3,   675,   868,   117,
   271,    42,   115,   116,   682,   325,   747,   199,   477,   201,
    26,   331,   882,    28,   108,   109,   112,   145,   253,    26,
    26,   117,    36,   112,    36,   614,   119,    42,   117,   236,
   602,   124,   487,   818,   526,   227,    42,    26,   701,     3,
    29,     3,   631,    32,   236,   723,    36,    63,     3,     3,
   242,   371,     7,   245,   246,   440,   441,   442,   443,   444,
   445,   446,   447,   448,     1,   473,   401,    29,    32,   197,
    32,   112,    26,   166,    63,   267,   117,    32,    68,   271,
   174,   175,    14,    99,     3,   277,    26,   358,    42,    29,
   184,   185,    32,   285,     3,   287,    33,   640,    30,   227,
     3,    63,   294,   295,   676,   365,   678,   679,   680,   301,
   302,    48,     3,   312,   242,    52,   122,   245,   246,   302,
    52,   862,   302,    26,     3,    26,   318,     3,   320,   301,
    29,     3,   302,    32,     3,   327,   430,    69,   330,    42,
   312,    32,   413,   884,   713,   423,    26,   583,   320,   341,
   342,   584,   830,    32,   346,    27,   348,   285,   112,   822,
   545,     3,    42,   117,    63,   357,   103,   359,    28,   361,
   459,   460,   432,   365,   610,    19,    20,    99,   115,   116,
     3,   373,    42,   318,   753,   377,     4,     3,   652,     7,
   382,   383,   481,     3,     3,   330,   516,   377,   861,    43,
   122,     3,   394,    72,    73,    74,    75,     4,    77,   401,
    79,     3,     3,   341,   342,     3,     7,    26,    60,    61,
    62,   413,     3,   812,   416,   872,    37,    38,    26,   357,
   490,   423,   424,   425,    26,    26,     3,     4,   430,   808,
   432,    32,    28,     7,   416,    26,     3,    33,    59,   792,
    26,     8,     9,    10,    11,    12,    13,   726,    60,    61,
    62,   453,   454,    65,   456,   457,    42,   459,   460,    26,
    28,    39,    26,    28,    42,    33,   819,   449,    33,   451,
    26,   473,     7,    40,   456,   477,   379,   827,    42,   481,
     8,   611,   484,    39,     1,   487,    42,     7,   490,   619,
   492,   493,   494,    29,    26,    23,    32,    29,    26,   501,
   853,     7,    29,   493,   506,    32,     7,   637,   638,    10,
   413,   501,   514,   515,     3,     3,    33,    15,    46,    47,
   424,   425,    15,    99,    17,    18,    29,   529,    21,    32,
     3,    48,   514,   515,    62,    52,    39,    29,    29,   477,
    32,    32,   587,   673,   526,     7,     8,    39,    39,   116,
    28,    29,    29,   120,    82,    32,    27,    28,   688,    48,
   111,   112,   113,   114,   115,   116,   117,   118,   506,   699,
   572,     3,   653,    32,   576,   705,   117,   118,   708,   581,
     3,   583,    39,    72,    73,    74,    75,    32,    77,   117,
    79,   529,   115,   116,   117,   118,     3,   727,   115,   116,
   602,   603,    26,   733,    15,    26,    17,    18,   610,    26,
    21,    26,   614,    26,    29,   617,    32,    32,    28,    29,
   523,     3,   525,    28,    29,    27,    28,   617,    26,   631,
    26,   534,   614,     1,    26,     3,     3,     3,   640,     7,
     8,     9,    10,    11,    12,    13,     3,     3,   650,   631,
   652,    29,   654,   655,   656,    28,    33,   560,    26,    29,
    29,   791,   112,   113,   114,   115,   116,   117,   118,     3,
   865,   117,    40,   675,   676,    26,   678,   679,   680,   582,
   682,     3,    26,     3,     3,   730,    32,    32,   117,    57,
    42,   886,    28,    57,    57,     3,    27,   600,    26,   701,
     8,     9,   704,    11,    12,    13,    29,     3,    26,    26,
    26,   713,   714,    26,   704,    26,   117,    26,    26,     3,
    27,   723,    26,   251,   726,   253,   113,   114,   115,   116,
   117,   118,    40,    28,    27,    27,    35,    28,    27,     3,
   742,    28,    32,   681,   647,   117,    28,    32,   116,     3,
    26,   753,   120,     3,     3,   757,   117,   122,    39,    30,
   762,   664,    27,    33,    27,    26,     3,    35,   770,    27,
   772,   773,   762,   301,    27,    32,    32,    28,     3,    27,
    26,   684,    26,    63,   786,    32,    63,     3,   726,    63,
   792,    33,   320,    27,     3,     7,    26,   700,   800,    27,
    33,    27,     3,    27,   742,    27,   808,   335,   116,    27,
   812,   714,   120,    26,   816,     3,   818,   819,    39,    27,
   822,     3,    32,     3,     3,    27,   816,    26,   830,    67,
   812,   117,     3,     3,     3,    15,    16,    17,    18,    19,
    20,    21,    22,    23,    24,    25,    32,     3,    26,    33,
    27,   853,    26,    28,    27,    35,    36,    37,    38,   861,
    26,    26,     3,    26,   767,    33,    27,   395,    27,    26,
    63,    26,    26,     3,    54,    55,    56,   405,   406,    59,
     1,   819,     3,   122,    32,    29,    26,    26,   416,     3,
    33,    29,    29,    14,    15,    16,    17,    18,    19,    20,
    21,    22,    23,    24,    25,   433,    33,    27,    29,   437,
    27,    27,    33,   103,    27,    36,    37,    38,    27,    29,
    27,    27,    27,   451,    27,    46,    47,    48,   456,    27,
    29,    52,    53,    29,    27,    56,   103,   465,    59,    60,
    61,    62,   122,    64,    65,    66,    26,    39,    63,    27,
    27,    72,    73,    74,    75,    29,    77,     1,    79,     3,
    26,    63,    33,    27,   492,    27,    29,    27,    29,     3,
    91,    15,    16,    17,    18,    19,    20,    21,    22,    23,
    24,    25,     3,    29,     3,    27,   514,   515,    29,    33,
    26,    28,    36,    37,    38,    27,    27,     3,   526,   120,
    39,   122,    29,     0,    48,     0,   201,   493,   144,   484,
     3,   270,    56,   318,   511,    59,   866,   388,   270,   837,
   320,   720,    15,    16,    17,    18,    19,    20,    21,    22,
    23,    24,    25,   655,   562,   454,    40,   334,   348,   351,
    -1,    -1,    -1,    36,    37,    38,   110,   111,   112,   113,
   114,   115,   116,   117,   118,    -1,   584,    -1,    -1,   587,
   104,   105,   106,    56,    -1,    -1,    59,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   602,    -1,    -1,    -1,   122,    -1,
     3,    -1,    -1,    -1,    -1,    -1,   614,    -1,    -1,    -1,
    -1,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
    23,    24,    25,   631,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,   112,
    -1,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,   122,
    -1,    54,    55,    56,    -1,    -1,    59,    -1,    -1,     0,
     1,    -1,     3,     4,     5,     6,    -1,    -1,   676,    -1,
   678,   679,   680,    14,    15,    16,    17,    18,    19,    20,
    21,    22,    23,    24,    25,    -1,    -1,    -1,    29,    30,
    31,    -1,    -1,    34,    -1,    36,    37,    38,    -1,    -1,
    41,    -1,    -1,    44,    -1,    46,    47,    48,    49,    50,
    51,    52,    53,    -1,   117,    56,    -1,    -1,    59,   122,
    -1,    -1,   730,    64,    -1,    -1,    -1,    -1,    69,    70,
    71,    72,    73,    74,    75,    76,    77,    -1,    79,    80,
    81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    95,    96,    97,    98,    -1,    -1,
   101,   102,    -1,    -1,    -1,    -1,   107,   108,   109,    -1,
     1,   112,     3,     4,     5,     6,   117,    -1,    -1,    -1,
    -1,   122,    -1,    14,    15,    16,    17,    18,    19,    20,
    21,    22,    23,    24,    25,    -1,    -1,    -1,    29,    30,
    31,    -1,    33,    34,   812,    36,    37,    38,    -1,    -1,
    41,    -1,    -1,    44,    -1,    46,    47,    48,    49,    50,
    51,    52,    53,    -1,    -1,    56,    -1,    -1,    59,   837,
    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    69,    70,
    71,    72,    73,    74,    75,    76,    77,    -1,    79,    80,
    81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    95,    96,    97,    98,    -1,    -1,
   101,   102,    -1,    -1,    -1,    -1,   107,   108,   109,    -1,
     1,   112,     3,     4,     5,     6,   117,    -1,    -1,    -1,
    -1,   122,    -1,    14,    15,    16,    17,    18,    19,    20,
    21,    22,    23,    24,    25,    -1,    -1,    -1,    29,    30,
    31,    -1,    -1,    34,    -1,    36,    37,    38,    -1,    -1,
    41,    -1,    -1,    44,    -1,    46,    47,    48,    49,    50,
    51,    52,    53,    -1,    -1,    56,    -1,    -1,    59,    -1,
    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    69,    70,
    71,    72,    73,    74,    75,    76,    77,    -1,    79,    80,
    81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    95,    96,    97,    98,    -1,    -1,
   101,   102,    -1,    -1,    -1,    -1,   107,   108,   109,    -1,
    -1,   112,     3,    -1,    -1,    -1,   117,    -1,    -1,    -1,
    -1,   122,    -1,    14,    15,    16,    17,    18,    19,    20,
    21,    22,    23,    24,    25,    -1,    -1,    -1,    29,    -1,
    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    -1,    -1,
    -1,    -1,    53,    -1,    -1,    56,    -1,    -1,    59,    60,
    61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
    -1,    72,    73,    74,    75,    -1,    77,    -1,    79,    -1,
    -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,
    91,    -1,    -1,    -1,    14,    15,    16,    17,    18,    19,
    20,    21,    22,    23,    24,    25,    -1,    -1,    -1,    29,
    -1,    -1,    -1,    -1,   115,   116,    36,    37,    38,   120,
    -1,   122,    -1,    -1,    -1,    -1,    46,    47,    48,    -1,
    -1,    -1,    -1,    53,    -1,    -1,    56,    -1,    -1,    59,
    60,    61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,
    -1,    -1,    72,    73,    74,    75,    -1,    77,    -1,    79,
     3,   110,   111,   112,   113,   114,   115,   116,   117,   118,
    -1,    91,    15,    16,    17,    18,    19,    20,    21,    22,
    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    35,    36,    37,    38,    -1,    -1,    43,    -1,
   120,    -1,   122,    -1,    -1,     3,     4,    -1,    -1,    -1,
    -1,    54,    55,    56,    -1,    -1,    59,    15,    16,    17,
    18,    19,    20,    21,    22,    23,    24,    25,    -1,     3,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
    38,    15,    16,    17,    18,    19,    20,    21,    22,    23,
    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
    -1,    59,    36,    37,    38,   110,   111,   112,   113,   114,
   115,   116,   117,   118,   117,     3,    -1,    -1,    -1,   122,
    -1,    -1,    56,    -1,    -1,    59,    -1,    15,    16,    17,
    18,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    48,     3,    -1,    -1,   122,    -1,    -1,    -1,    56,    -1,
    -1,    59,    -1,    15,    16,    17,    18,    19,    20,    21,
    22,    23,    24,    25,    -1,     3,   120,    -1,   122,    -1,
    -1,    -1,    -1,    -1,    36,    37,    38,    15,    16,    17,
    18,    19,    20,    21,    22,    23,    24,    25,    -1,     3,
    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,    36,    37,
    38,    15,    16,    17,    18,    19,    20,    21,    22,    23,
    24,    25,    -1,     3,   122,    -1,    -1,    -1,    56,    -1,
    -1,    59,    36,    37,    38,    15,    16,    17,    18,    19,
    20,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
    -1,    -1,    56,    -1,    -1,    59,    36,    37,    38,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   122,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
    -1,    -1,     8,     9,   122,    11,    12,    13,    -1,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,
    36,    37,    38,    -1,    40,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   122,    59,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   116,    -1,    -1,    -1,   120
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/lib/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "/usr/lib/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 586 "parser.y"
{ 
                    {
		      int ii;
		      for (ii = 0; ii < 256; ii++) {
			handler_stack[ii] = 0;
		      }
		      handler_stack[0] = comment_handler;
		    }
                    doc_stack[0] = doctitle;
                 ;
    break;}
case 2:
#line 595 "parser.y"
{
		   CommentHandler::cleanup();
                   cplus_cleanup();
		   doc_entry = doctitle;
		   lang->close();
		   if (te_index) {
		     fprintf(stderr,"%s : EOF.  Missing #endif detected.\n", input_file);
		     FatalError();
		   }
               ;
    break;}
case 3:
#line 607 "parser.y"
{ 
		     scanner_clear_start();
                     Error = 0;
                ;
    break;}
case 4:
#line 611 "parser.y"
{
	       ;
    break;}
case 5:
#line 615 "parser.y"
{
                  if (allow) {
//		    init_language();
		    doc_entry = 0;
		    // comment_handler->clear();
		    include_file(yyvsp[0].id);
		  }
                ;
    break;}
case 6:
#line 626 "parser.y"
{
		 if (allow) {
		   int oldextern = WrapExtern;
//		   init_language();
		   doc_entry = 0;
		   // comment_handler->clear();
		   WrapExtern = 1;
		   if (include_file(yyvsp[0].id) >= 0) {
		     add_symbol("SWIGEXTERN",0,0);
		   } else {
		     WrapExtern = oldextern;
		   }
		 }
	       ;
    break;}
case 7:
#line 643 "parser.y"
{
		  if (allow) {
		    int oldextern = WrapExtern;
		    init_language();
		    doc_entry = 0;
		    WrapExtern = 1;
		    if (include_file(yyvsp[0].id) >= 0) {
		      add_symbol("SWIGEXTERN",0,0);
		      lang->import(yyvsp[0].id);
		    } else {
		      WrapExtern = oldextern;
		    }
		  }
                ;
    break;}
case 8:
#line 661 "parser.y"
{
                  if (allow) {
                     if ((checkout_file(yyvsp[0].id,yyvsp[0].id)) == 0) {
                       fprintf(stderr,"%s checked out from the SWIG library.\n",yyvsp[0].id);
                      }
                  }
                ;
    break;}
case 9:
#line 671 "parser.y"
{
		 if (allow) {
                  doc_entry = 0;
		  if (Verbose) {
		    fprintf(stderr,"%s : Line %d.  CPP %s ignored.\n", input_file, line_number,yyvsp[0].id);
		  }
		 }
		;
    break;}
case 10:
#line 682 "parser.y"
{
		  if (allow) {
		    init_language();
		    if (Active_type) delete Active_type;
		    Active_type = new DataType(yyvsp[-3].type);
		    Active_extern = yyvsp[-4].ivalue;
		    yyvsp[-3].type->is_pointer += yyvsp[-2].decl.is_pointer;
		    if (yyvsp[-1].ivalue > 0) {
		      yyvsp[-3].type->is_pointer++;
		      yyvsp[-3].type->status = STAT_READONLY;
                      yyvsp[-3].type->arraystr = copy_string(ArrayString);
		    }
		    if (yyvsp[-2].decl.is_reference) {
		      fprintf(stderr,"%s : Line %d. Error. Linkage to C++ reference not allowed.\n", input_file, line_number);
		      FatalError();
		    } else {
		      if (yyvsp[-3].type->qualifier) {
			if (strcmp(yyvsp[-3].type->qualifier,"const") == 0) {
			  if (yyvsp[0].dtype.type != T_ERROR)
			    create_constant(yyvsp[-2].decl.id, yyvsp[-3].type, yyvsp[0].dtype.id);
			} else 
			  create_variable(yyvsp[-4].ivalue,yyvsp[-2].decl.id,yyvsp[-3].type);
		      } else
			create_variable(yyvsp[-4].ivalue,yyvsp[-2].decl.id,yyvsp[-3].type);
		    }
		  }
		  delete yyvsp[-3].type;
                ;
    break;}
case 11:
#line 709 "parser.y"
{ ;
    break;}
case 12:
#line 713 "parser.y"
{ 
                   skip_decl();
		   fprintf(stderr,"%s : Line %d. Function pointers not currently supported.\n",
			   input_file, line_number);
		;
    break;}
case 13:
#line 721 "parser.y"
{
		  if (Verbose) {
		    fprintf(stderr,"static variable %s ignored.\n",yyvsp[-2].decl.id);
		  }
		  Active_static = 1;
		  delete yyvsp[-3].type;
		;
    break;}
case 14:
#line 727 "parser.y"
{
		  Active_static = 0;
		;
    break;}
case 15:
#line 733 "parser.y"
{ 
                   skip_decl();
		   fprintf(stderr,"%s : Line %d. Function pointers not currently supported.\n",
			   input_file, line_number);
		;
    break;}
case 16:
#line 742 "parser.y"
{
		  if (allow) {
		    init_language();
		    if (Active_type) delete Active_type;
		    Active_type = new DataType(yyvsp[-5].type);
		    Active_extern = yyvsp[-6].ivalue;
		    yyvsp[-5].type->is_pointer += yyvsp[-4].decl.is_pointer;
		    yyvsp[-5].type->is_reference = yyvsp[-4].decl.is_reference;
		    create_function(yyvsp[-6].ivalue, yyvsp[-4].decl.id, yyvsp[-5].type, yyvsp[-2].pl);
		  }
		  delete yyvsp[-5].type;
		  delete yyvsp[-2].pl;
		;
    break;}
case 17:
#line 754 "parser.y"
{ ;
    break;}
case 18:
#line 758 "parser.y"
{
		  if (allow) {
		    init_language();
		    yyvsp[-5].type->is_pointer += yyvsp[-4].decl.is_pointer;
		    yyvsp[-5].type->is_reference = yyvsp[-4].decl.is_reference;
		    create_function(yyvsp[-6].ivalue, yyvsp[-4].decl.id, yyvsp[-5].type, yyvsp[-2].pl);
		  }
		  delete yyvsp[-5].type;
		  delete yyvsp[-2].pl;
		;
    break;}
case 19:
#line 771 "parser.y"
{ 
		  if (allow) {
                    init_language();
		    DataType *t = new DataType(T_INT);
                    t->is_pointer += yyvsp[-4].decl.is_pointer;
		    t->is_reference = yyvsp[-4].decl.is_reference;
		    create_function(yyvsp[-5].ivalue,yyvsp[-4].decl.id,t,yyvsp[-2].pl);
		    delete t;
		  }
                ;
    break;}
case 20:
#line 780 "parser.y"
{ ;
    break;}
case 21:
#line 784 "parser.y"
{
		  if ((allow) && (Inline)) {
		    if (strlen(CCode.get())) {
		      init_language();
		      yyvsp[-5].type->is_pointer += yyvsp[-4].decl.is_pointer;
		      yyvsp[-5].type->is_reference = yyvsp[-4].decl.is_reference;
		      create_function(0, yyvsp[-4].decl.id, yyvsp[-5].type, yyvsp[-2].pl);
		    }
		  }
		  delete yyvsp[-5].type;
		  delete yyvsp[-2].pl;
		;
    break;}
case 22:
#line 799 "parser.y"
{
		  if (allow) {
		    init_language();
		    yyvsp[-5].type->is_pointer += yyvsp[-4].decl.is_pointer;
		    yyvsp[-5].type->is_reference = yyvsp[-4].decl.is_reference;
		    if (Inline) {
		      fprintf(stderr,"%s : Line %d. Repeated %%inline directive.\n",input_file,line_number);
		      FatalError();
		    } else {
		      if (strlen(CCode.get())) {
			fprintf(f_header,"static ");
			emit_extern_func(yyvsp[-4].decl.id,yyvsp[-5].type,yyvsp[-2].pl,3,f_header);
			fprintf(f_header,"%s\n",CCode.get());
		      }
		      create_function(0, yyvsp[-4].decl.id, yyvsp[-5].type, yyvsp[-2].pl);
		    }
		  }
		  delete yyvsp[-5].type;
		  delete yyvsp[-2].pl;
		;
    break;}
case 23:
#line 822 "parser.y"
{
		  if (allow) {
		    if (Verbose) {
		      fprintf(stderr,"static function %s ignored.\n", yyvsp[-4].decl.id);
		    }
		  }
		  Active_static = 1;
		  delete yyvsp[-5].type;
		  delete yyvsp[-2].pl;
		;
    break;}
case 24:
#line 831 "parser.y"
{
		  Active_static = 0;
		 ;
    break;}
case 25:
#line 837 "parser.y"
{
		  if (allow)
		    Status = Status | STAT_READONLY;
	       ;
    break;}
case 26:
#line 844 "parser.y"
{
		 if (allow)
		   Status = Status & ~STAT_READONLY;
	       ;
    break;}
case 27:
#line 850 "parser.y"
{
		 if (allow) {
                     strcpy(yy_rename,yyvsp[-1].id);
                     Rename_true = 1;
		 }
               ;
    break;}
case 28:
#line 858 "parser.y"
{ 
		 if (name_hash.lookup(yyvsp[-2].id)) {
		   name_hash.remove(yyvsp[-2].id);
		 }
		 name_hash.add(yyvsp[-2].id,copy_string(yyvsp[-1].id));
	       ;
    break;}
case 29:
#line 867 "parser.y"
{
                     NewObject = 1;
                ;
    break;}
case 30:
#line 869 "parser.y"
{
                     NewObject = 0;
               ;
    break;}
case 31:
#line 875 "parser.y"
{
		 if (allow) {
		   fprintf(stderr,"%s : Lind %d. Empty %%name() is no longer supported.\n",
			   input_file, line_number);
		   FatalError();
		 }
	       ;
    break;}
case 32:
#line 881 "parser.y"
{
		 Rename_true = 0;
	       ;
    break;}
case 33:
#line 887 "parser.y"
{
		 if (allow && (!WrapExtern)) {
		   init_language();
		   if (add_symbol(yyvsp[-4].id,(DataType *) 0, (char *) 0)) {
		     fprintf(stderr,"%s : Line %d. Name of native function %s conflicts with previous declaration (ignored)\n",
			     input_file, line_number, yyvsp[-4].id);
		   } else {
		     doc_entry = new DocDecl(yyvsp[-4].id,doc_stack[doc_stack_top]);
		     lang->add_native(yyvsp[-4].id,yyvsp[-1].id);
		   }
		 }
	       ;
    break;}
case 34:
#line 899 "parser.y"
{
		 if (allow && (!WrapExtern)) {
		   init_language();
		   yyvsp[-5].type->is_pointer += yyvsp[-4].decl.is_pointer;
		   if (add_symbol(yyvsp[-8].id,(DataType *) 0, (char *) 0)) {
		     fprintf(stderr,"%s : Line %d. Name of native function %s conflicts with previous declaration (ignored)\n",
			     input_file, line_number, yyvsp[-8].id);
		   } else {
		     if (yyvsp[-6].ivalue) {
		       emit_extern_func(yyvsp[-4].decl.id, yyvsp[-5].type, yyvsp[-2].pl, yyvsp[-6].ivalue, f_header);
		     }
		     doc_entry = new DocDecl(yyvsp[-8].id,doc_stack[doc_stack_top]);
		     lang->add_native(yyvsp[-8].id,yyvsp[-4].decl.id);
		   }
		 }
		 delete yyvsp[-5].type;
		 delete yyvsp[-2].pl;
	       ;
    break;}
case 35:
#line 920 "parser.y"
{
		 if (allow && (!WrapExtern)) {
		   if (!title_init) {
		     title_init = 1;
		     doc_init = 1;
		     if (!comment_handler) {
		       comment_handler = new CommentHandler();
		     }
		     { 
		       int ii;
		       for (ii = 0; ii < yyvsp[0].dlist.count; ii++) {
			 comment_handler->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		       }
		     }
		     // Create a new title for documentation 
		     {
		       int temp = line_number;
		       line_number = yyvsp[-2].ivalue;
		       if (!doctitle)
			 doctitle = new DocTitle(yyvsp[-1].id,0);
		       else {
			 doctitle->name = copy_string(title);
			 doctitle->line_number = yyvsp[-2].ivalue;
			 doctitle->end_line = yyvsp[-2].ivalue;
		       }
		       line_number = temp;
		     }
		     doctitle->usage = yyvsp[-1].id;
		     doc_entry = doctitle;
		     doc_stack[0] = doc_entry;
		     doc_stack_top = 0;
		     handler_stack[0] = comment_handler;
		     { 
		       int ii;
		       for (ii = 0; ii < yyvsp[0].dlist.count; ii++) {
			 doc_stack[doc_stack_top]->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		       }
		     }

		   } else {
		     // Ignore it
		   }
		 }
	       ;
    break;}
case 36:
#line 968 "parser.y"
{
		 if (allow && (!WrapExtern) && (!IgnoreDoc)) {
		   // Copy old comment handler
		   // if (handler_stack[1]) delete handler_stack[1];
		   handler_stack[1] = new CommentHandler(handler_stack[0]);  
		   comment_handler = handler_stack[1];
		   { 
		     int ii;
		     for (ii = 0; ii < yyvsp[0].dlist.count; ii++) {
		       comment_handler->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		     }
		   }
		   {
		     int temp = line_number;
		     line_number = yyvsp[-2].ivalue;
		     doc_entry = new DocSection(yyvsp[-1].id,doc_stack[0]);
		     line_number = temp;
		   }
		   doc_stack_top = 1;
		   doc_stack[1] = doc_entry;
		   { 
		     int ii;
		     for (ii = 0; ii < yyvsp[0].dlist.count; ii++) {
		       doc_stack[doc_stack_top]->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		     }
		   }
		 }
	       ;
    break;}
case 37:
#line 998 "parser.y"
{
		 if (allow && (!WrapExtern) && (!IgnoreDoc)) {
		   if (doc_stack_top < 1) {
		     fprintf(stderr,"%s : Line %d. Can't apply %%subsection here.\n", input_file,line_number);
		     FatalError();
		   } else {

		     // Copy old comment handler
		     // if (handler_stack[2]) delete handler_stack[2];
		     handler_stack[2] = new CommentHandler(handler_stack[1]);
		     comment_handler = handler_stack[2];
		     { 
		       int ii;
		       for (ii = 0; ii < yyvsp[0].dlist.count; ii++) {
			 comment_handler->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		       }
		     }
		     {
		       int temp = line_number;
		       line_number = yyvsp[-2].ivalue;
		       doc_entry = new DocSection(yyvsp[-1].id,doc_stack[1]);
		       line_number = temp;
		     }
		     doc_stack_top = 2;
		     doc_stack[2] = doc_entry;
		     { 
		       int ii;
		       for (ii = 0; ii < yyvsp[0].dlist.count; ii++) {
			 doc_stack[doc_stack_top]->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		       }
		     }
		   }
		 }
	       ;
    break;}
case 38:
#line 1034 "parser.y"
{
		 if (allow && (!WrapExtern) && (!IgnoreDoc)) {
		   if (doc_stack_top < 2) {
		     fprintf(stderr,"%s : Line %d. Can't apply %%subsubsection here.\n", input_file,line_number);
		     FatalError();
		   } else {

		     // Copy old comment handler

		     // if (handler_stack[3]) delete handler_stack[3];
		     handler_stack[3] = new CommentHandler(handler_stack[2]);
		     comment_handler = handler_stack[3];
		     { 
		       int ii;
		       for (ii = 0; ii < yyvsp[0].dlist.count; ii++) {
			 comment_handler->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		       }
		     }
		     {
		       int temp = line_number;
		       line_number = yyvsp[-2].ivalue;
		       doc_entry = new DocSection(yyvsp[-1].id,doc_stack[2]);
		       line_number = temp;
		     }
		     doc_stack_top = 3;
		     doc_stack[3] = doc_entry;
		     { 
		       int ii;
		       for (ii = 0; ii < yyvsp[0].dlist.count; ii++) {
			 doc_stack[doc_stack_top]->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		       }
		     }
		   }
		 }
	       ;
    break;}
case 39:
#line 1071 "parser.y"
{
		 if (allow && (!WrapExtern)) {
		   fprintf(stderr,"%%alpha directive is obsolete.  Use '%%style sort' instead.\n");
		   handler_stack[0]->style("sort",0);
		   doc_stack[0]->style("sort",0);
		 }
	       ;
    break;}
case 40:
#line 1079 "parser.y"
{
		 if (allow && (!WrapExtern)) {
		   fprintf(stderr,"%%raw directive is obsolete. Use '%%style nosort' instead.\n");
		   handler_stack[0]->style("nosort",0);
		   doc_stack[0]->style("nosort",0);
		 }
	       ;
    break;}
case 41:
#line 1088 "parser.y"
{
		 if (allow) {
		   if (IgnoreDoc) {
		     /* Already in a disabled documentation */
		     doc_scope++;
		   } else {
		     if (Verbose)
		       fprintf(stderr,"%s : Line %d. Documentation disabled.\n", input_file, line_number);
		     IgnoreDoc = 1;
		     doc_scope = 1;
		   }
		 }
	       ;
    break;}
case 42:
#line 1102 "parser.y"
{
		 if (allow) {
		   if (IgnoreDoc) {
		     if (doc_scope > 1) {
		       doc_scope--;
		     } else {
		       if (Verbose)
			 fprintf(stderr,"%s : Line %d. Documentation enabled.\n", input_file, line_number);
		       IgnoreDoc = 0;
		       doc_scope = 0;
		     }
		   }
		 }
	       ;
    break;}
case 43:
#line 1118 "parser.y"
{
		 if (allow && (!WrapExtern)) {
		   yyvsp[0].id[strlen(yyvsp[0].id) - 1] = 0;
		   doc_entry = new DocText(yyvsp[0].id,doc_stack[doc_stack_top]);
		   doc_entry = 0;
		 }
	       ;
    break;}
case 44:
#line 1127 "parser.y"
{ ;
    break;}
case 45:
#line 1131 "parser.y"
{
		 if (allow && (!WrapExtern)) {
		   init_language();
		   yyvsp[0].id[strlen(yyvsp[0].id) - 1] = 0;
//		   fprintf(f_header,"#line %d \"%s\"\n", start_line, input_file);
		   fprintf(f_header, "%s\n", yyvsp[0].id);
		 }
	       ;
    break;}
case 46:
#line 1142 "parser.y"
{
                 if (allow && (!WrapExtern)) {
		   init_language();
		   yyvsp[0].id[strlen(yyvsp[0].id) - 1] = 0;
		   fprintf(f_wrappers,"%s\n",yyvsp[0].id);
		 }
	       ;
    break;}
case 47:
#line 1152 "parser.y"
{
		 if (allow && (!WrapExtern)) {
		   init_language();
		   yyvsp[0].id[strlen(yyvsp[0].id) -1] = 0;
		   fprintf(f_init,"%s\n", yyvsp[0].id);
		 }
	       ;
    break;}
case 48:
#line 1161 "parser.y"
{
		 if (allow && (!WrapExtern)) {
		   init_language();
		   yyvsp[0].id[strlen(yyvsp[0].id) - 1] = 0;
		   fprintf(f_header, "%s\n", yyvsp[0].id);
		   start_inline(yyvsp[0].id,start_line);
		 }
	       ;
    break;}
case 49:
#line 1171 "parser.y"
{
		 if (allow && (!WrapExtern)) {
		   fprintf(stderr,"%s\n", yyvsp[0].id);
		 }
	       ;
    break;}
case 50:
#line 1177 "parser.y"
{
                 if (allow && (!WrapExtern)) {
                   fprintf(stderr,"%s\n", yyvsp[0].id);
                 }
               ;
    break;}
case 51:
#line 1184 "parser.y"
{
                   DocOnly = 1;
               ;
    break;}
case 52:
#line 1190 "parser.y"
{
		 if (allow) {
		   if (!module_init) {
		     lang->set_init(yyvsp[-1].id);
		     module_init = 1;
		     init_language();
		   } else {
		     if (Verbose)
		       fprintf(stderr,"%s : Line %d. %%init %s ignored.\n",
			       input_file, line_number, yyvsp[-1].id);
		   }
		   if (yyvsp[0].ilist.count > 0) {
		     fprintf(stderr,"%s : Line %d. Warning. Init list no longer supported.\n",
			     input_file,line_number);
		   }
		 }
		 for (i = 0; i < yyvsp[0].ilist.count; i++)
		   if (yyvsp[0].ilist.names[i]) delete [] yyvsp[0].ilist.names[i];
		 delete [] yyvsp[0].ilist.names;
	       ;
    break;}
case 53:
#line 1212 "parser.y"
{
		 if (allow) {
		   if (yyvsp[0].ilist.count)
		     lang->set_module(yyvsp[-1].id,yyvsp[0].ilist.names);
		   else
		     lang->set_module(yyvsp[-1].id,0);
		   module_init = 1;
		   init_language();
		 }
		 for (i = 0; i < yyvsp[0].ilist.count; i++)
		   if (yyvsp[0].ilist.names[i]) delete [] yyvsp[0].ilist.names[i];
		 delete [] yyvsp[0].ilist.names;
	       ;
    break;}
case 54:
#line 1228 "parser.y"
{
		 if (allow) {
		   if ((yyvsp[0].dtype.type != T_ERROR) && (yyvsp[0].dtype.type != T_SYMBOL)) {
		     init_language();
		     temp_typeptr = new DataType(yyvsp[0].dtype.type);
		     create_constant(yyvsp[-1].id, temp_typeptr, yyvsp[0].dtype.id);
		     delete temp_typeptr;
		   } else if (yyvsp[0].dtype.type == T_SYMBOL) {
		     // Add a symbol to the SWIG symbol table
		     if (add_symbol(yyvsp[-1].id,(DataType *) 0, (char *) 0)) {
		       fprintf(stderr,"%s : Line %d. Warning. Symbol %s already defined.\n", 
			       input_file,line_number, yyvsp[-1].id);
		     }
		   }
		 }
	       ;
    break;}
case 55:
#line 1247 "parser.y"
{
		 if (Verbose) {
		   fprintf(stderr,"%s : Line %d.  CPP Macro ignored.\n", input_file, line_number);
		 }
	       ;
    break;}
case 56:
#line 1254 "parser.y"
{
		 remove_symbol(yyvsp[0].id);
	       ;
    break;}
case 57:
#line 1260 "parser.y"
{ scanner_clear_start(); ;
    break;}
case 58:
#line 1260 "parser.y"
{ 
		 if (allow) {
		   init_language();
		   if (yyvsp[-5].id) {
		     temp_type.type = T_INT;
		     temp_type.is_pointer = 0;
		     temp_type.implicit_ptr = 0;
		     sprintf(temp_type.name,"int");
		     temp_type.typedef_add(yyvsp[-5].id,1);
		   }
		 }
	       ;
    break;}
case 59:
#line 1275 "parser.y"
{ scanner_clear_start(); ;
    break;}
case 60:
#line 1275 "parser.y"
{
		 if (allow) {
		   init_language();
		   temp_type.type = T_INT;
		   temp_type.is_pointer = 0;
		   temp_type.implicit_ptr = 0;
		   sprintf(temp_type.name,"int");
		   Active_typedef = new DataType(&temp_type);
		   temp_type.typedef_add(yyvsp[0].id,1);
		 }
	       ;
    break;}
case 61:
#line 1285 "parser.y"
{ ;
    break;}
case 62:
#line 1295 "parser.y"
{
		   TMParm *p;
                   skip_brace();
		   p = yyvsp[-1].tmparm;
		   while (p) {
		     typemap_register(yyvsp[-3].id,yyvsp[-5].id,p->p->t,p->p->name,CCode,p->args);
		     p = p->next;
                   }
		   delete yyvsp[-5].id;
		   delete yyvsp[-3].id;
	       ;
    break;}
case 63:
#line 1308 "parser.y"
{
		 if (!typemap_lang) {
		   fprintf(stderr,"SWIG internal error. No typemap_lang specified.\n");
		   fprintf(stderr,"typemap on %s : Line %d. will be ignored.\n",input_file,line_number);
		   FatalError();
		 } else {
		   TMParm *p;
		   skip_brace();
		   p = yyvsp[-1].tmparm;
		   while (p) {
		     typemap_register(yyvsp[-3].id,typemap_lang,p->p->t,p->p->name,CCode,p->args);
		     p = p->next;
		   }
		 }
		 delete yyvsp[-3].id;
	       ;
    break;}
case 64:
#line 1327 "parser.y"
{
		 TMParm *p;
		 p = yyvsp[-1].tmparm;
		 while (p) {
                   typemap_clear(yyvsp[-3].id,yyvsp[-5].id,p->p->t,p->p->name);
		   p = p->next;
		 }
		 delete yyvsp[-5].id;
		 delete yyvsp[-3].id;
	       ;
    break;}
case 65:
#line 1339 "parser.y"
{
		 if (!typemap_lang) {
		   fprintf(stderr,"SWIG internal error. No typemap_lang specified.\n");
		   fprintf(stderr,"typemap on %s : Line %d. will be ignored.\n",input_file,line_number);
		   FatalError();
		 } else {
		   TMParm *p;
		   p = yyvsp[-1].tmparm;
		   while (p) {
		     typemap_clear(yyvsp[-3].id,typemap_lang,p->p->t,p->p->name);
		     p = p->next;
		   }
		 }
		 delete yyvsp[-3].id;
	       ;
    break;}
case 66:
#line 1357 "parser.y"
{
                   TMParm *p;
		   p = yyvsp[-3].tmparm;
		   while (p) {
		     typemap_copy(yyvsp[-5].id,yyvsp[-7].id,yyvsp[-1].tmparm->p->t,yyvsp[-1].tmparm->p->name,p->p->t,p->p->name);
		     p = p->next;
		   }
		   delete yyvsp[-7].id;
		   delete yyvsp[-5].id;
		   delete yyvsp[-1].tmparm->p;
		   delete yyvsp[-1].tmparm;
	       ;
    break;}
case 67:
#line 1372 "parser.y"
{
		 if (!typemap_lang) {
		   fprintf(stderr,"SWIG internal error. No typemap_lang specified.\n");
		   fprintf(stderr,"typemap on %s : Line %d. will be ignored.\n",input_file,line_number);
		   FatalError();
		 } else {
                   TMParm *p;
		   p = yyvsp[-3].tmparm;
		   while (p) {
		     typemap_copy(yyvsp[-5].id,typemap_lang,yyvsp[-1].tmparm->p->t,yyvsp[-1].tmparm->p->name,p->p->t,p->p->name);
		     p = p->next;
		   }
		 }
		 delete yyvsp[-5].id;
		 delete yyvsp[-1].tmparm->p;
		 delete yyvsp[-1].tmparm;
	       ;
    break;}
case 68:
#line 1393 "parser.y"
{
		 TMParm *p;
		 p = yyvsp[-1].tmparm;
		 while(p) {
		   typemap_apply(yyvsp[-3].tmparm->p->t,yyvsp[-3].tmparm->p->name,p->p->t,p->p->name);
		   p = p->next;
		 }
		 delete yyvsp[-1].tmparm;
		 delete yyvsp[-3].tmparm->args;
		 delete yyvsp[-3].tmparm;
               ;
    break;}
case 69:
#line 1404 "parser.y"
{
		 TMParm *p;
		 p = yyvsp[-1].tmparm;
		 while (p) {
		   typemap_clear_apply(p->p->t, p->p->name);
		   p = p->next;
		 }
               ;
    break;}
case 70:
#line 1421 "parser.y"
{
                    skip_brace();
                    fragment_register("except",yyvsp[-2].id, CCode);
		    delete yyvsp[-2].id;
	       ;
    break;}
case 71:
#line 1428 "parser.y"
{
                    skip_brace();
                    fragment_register("except",typemap_lang, CCode);
               ;
    break;}
case 72:
#line 1435 "parser.y"
{
                     fragment_clear("except",yyvsp[-2].id);
               ;
    break;}
case 73:
#line 1440 "parser.y"
{
                     fragment_clear("except",typemap_lang);
	       ;
    break;}
case 74:
#line 1446 "parser.y"
{ ;
    break;}
case 75:
#line 1447 "parser.y"
{ ;
    break;}
case 76:
#line 1448 "parser.y"
{ ;
    break;}
case 77:
#line 1449 "parser.y"
{
		 if (!Error) {
		   {
		     static int last_error_line = -1;
		     if (last_error_line != line_number) {
		       fprintf(stderr,"%s : Line %d. Syntax error in input.\n", input_file, line_number);
		       FatalError();
		       last_error_line = line_number;
                       // Try to make some kind of recovery.
		       skip_decl();
		     }
		     Error = 1;
		   }
		 }
	       ;
    break;}
case 78:
#line 1467 "parser.y"
{ ;
    break;}
case 79:
#line 1468 "parser.y"
{ ;
    break;}
case 80:
#line 1472 "parser.y"
{ ;
    break;}
case 81:
#line 1476 "parser.y"
{
		 { 
		   int ii,jj;
		   for (ii = 0; ii < yyvsp[0].dlist.count; ii++) {
		     comment_handler->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		     for (jj = 0; jj < doc_stack_top; jj++) 
		       doc_stack[jj]->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		     if (doctitle)
		       doctitle->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		     doc->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		   }
		 }
	       ;
    break;}
case 82:
#line 1492 "parser.y"
{
		 { 
		   int ii;
		   for (ii = 0; ii < yyvsp[0].dlist.count; ii++) {
		     comment_handler = new CommentHandler(comment_handler);
		     handler_stack[doc_stack_top] = comment_handler;
		     comment_handler->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		     doc_stack[doc_stack_top]->style(yyvsp[0].dlist.names[ii],yyvsp[0].dlist.values[ii]);
		   }
		 }
	       ;
    break;}
case 83:
#line 1505 "parser.y"
{ ;
    break;}
case 84:
#line 1513 "parser.y"
{
		 if (allow) {
		   init_language();
		   /* Add a new typedef */
		   Active_typedef = new DataType(yyvsp[-1].type);
		   yyvsp[-1].type->is_pointer += yyvsp[0].decl.is_pointer;
		   yyvsp[-1].type->typedef_add(yyvsp[0].decl.id);
		   /* If this is %typedef, add it to the header */
		   if (yyvsp[-2].ivalue) 
		     fprintf(f_header,"typedef %s %s;\n", yyvsp[-1].type->print_full(), yyvsp[0].decl.id);
		   cplus_register_type(yyvsp[0].decl.id);
		 }
	       ;
    break;}
case 85:
#line 1525 "parser.y"
{ ;
    break;}
case 86:
#line 1529 "parser.y"
{
		 if (allow) {
		   init_language();
		   /* Typedef'd pointer */
		   if (yyvsp[-9].ivalue) {
		     sprintf(temp_name,"(*%s)",yyvsp[-5].id);
		     fprintf(f_header,"typedef ");
		     emit_extern_func(temp_name, yyvsp[-8].type,yyvsp[-2].pl,0,f_header);
		   }
		   strcpy(yyvsp[-8].type->name,"<function ptr>");
		   yyvsp[-8].type->type = T_USER;
		   yyvsp[-8].type->is_pointer = 1;
		   yyvsp[-8].type->typedef_add(yyvsp[-5].id,1);
		   cplus_register_type(yyvsp[-5].id);
		 }
		 delete yyvsp[-8].type;
		 delete yyvsp[-5].id;
		 delete yyvsp[-2].pl;
	       ;
    break;}
case 87:
#line 1551 "parser.y"
{
		 if (allow) {
		   init_language();
		   if (yyvsp[-10].ivalue) {
		     yyvsp[-9].type->is_pointer += yyvsp[-8].ivalue;
		     sprintf(temp_name,"(*%s)",yyvsp[-5].id);
		     fprintf(f_header,"typedef ");
		     emit_extern_func(temp_name, yyvsp[-9].type,yyvsp[-2].pl,0,f_header);
		   }

		   /* Typedef'd pointer */
		   strcpy(yyvsp[-9].type->name,"<function ptr>");
		   yyvsp[-9].type->type = T_USER;
		   yyvsp[-9].type->is_pointer = 1;
		   yyvsp[-9].type->typedef_add(yyvsp[-5].id,1);
		   cplus_register_type(yyvsp[-5].id);
		 }
		 delete yyvsp[-9].type;
		 delete yyvsp[-5].id;
		 delete yyvsp[-2].pl;
	       ;
    break;}
case 88:
#line 1575 "parser.y"
{
		 if (allow) {
		   init_language();
		   Active_typedef = new DataType(yyvsp[-2].type);
		   // This datatype is going to be readonly
			
		   yyvsp[-2].type->status = STAT_READONLY | STAT_REPLACETYPE;
		   yyvsp[-2].type->is_pointer += yyvsp[-1].decl.is_pointer;
		   // Turn this into a "pointer" corresponding to the array
		   yyvsp[-2].type->is_pointer++;
		   yyvsp[-2].type->arraystr = copy_string(ArrayString);
		   yyvsp[-2].type->typedef_add(yyvsp[-1].decl.id);
		   fprintf(stderr,"%s : Line %d. Warning. Array type %s will be read-only without a typemap\n",input_file,line_number, yyvsp[-1].decl.id);
		   cplus_register_type(yyvsp[-1].decl.id);

		 }
	       ;
    break;}
case 89:
#line 1591 "parser.y"
{ ;
    break;}
case 90:
#line 1604 "parser.y"
{
                if (allow) {
		  if (Active_typedef) {
		    DataType *t;
		    t = new DataType(Active_typedef);
		    t->is_pointer += yyvsp[-1].decl.is_pointer;
		    t->typedef_add(yyvsp[-1].decl.id);
		    cplus_register_type(yyvsp[-1].decl.id);
		    delete t;
		  }
		}
              ;
    break;}
case 91:
#line 1616 "parser.y"
{
		    DataType *t;
		    t = new DataType(Active_typedef);
		    t->status = STAT_READONLY | STAT_REPLACETYPE;
		    t->is_pointer += yyvsp[-1].decl.is_pointer + 1;
		    t->arraystr = copy_string(ArrayString);
		    t->typedef_add(yyvsp[-1].decl.id);
		    cplus_register_type(yyvsp[-1].decl.id);
		    delete t;
    		    fprintf(stderr,"%s : Line %d. Warning. Array type %s will be read-only without a typemap.\n",input_file,line_number, yyvsp[-1].decl.id);
	      ;
    break;}
case 92:
#line 1627 "parser.y"
{ ;
    break;}
case 93:
#line 1647 "parser.y"
{
		 /* Push old if-then-else status */
		 if_push();
		 /* Look a symbol up in the symbol table */
		 if (lookup_symbol(yyvsp[0].id)) {
		   in_then = 1;
		   in_else = 0;
		   allow = 1 & prev_allow;
		 } else {
		   /* Condition is false.   Skip over whatever is in this block */
		   in_else = skip_cond(1);
		   if (in_else == -1) {
		     /* Unrecoverable error */
		     SWIG_exit(1);
		   }
		   if (!in_else) {
		     if_pop();        // Pop out. Reached end of block
		   } else {
		     allow = prev_allow;
		     in_then = 0;
		   }
		 }
                ;
    break;}
case 94:
#line 1673 "parser.y"
{
		 if_push();
		 if (lookup_symbol(yyvsp[0].id)) {
		   /* Condition is false.   Skip over whatever is in this block */
		   in_else = skip_cond(1);
		   if (in_else == -1) {
		     /* Unrecoverable error */
		     SWIG_exit(1);
		   }
		   if (!in_else) {
		     if_pop();        // Pop out. Reached end of block
		   } else {
		     allow = prev_allow;
		     in_then = 0;
		   }
		 } else {
		   in_then = 1;
		   in_else = 0;		   
		   allow = 1 & prev_allow;
		 }
	       ;
    break;}
case 95:
#line 1696 "parser.y"
{
		 if ((!in_then) || (in_else)) {
		   fprintf(stderr,"%s : Line %d. Misplaced else\n", input_file, line_number);
		   FatalError();
		 } else {
		   in_then = 0;
		   in_else = 1;
		   if (allow) {
		     allow = 0;
		     /* Skip over rest of the conditional */
		     skip_cond(0);
		     if_pop();
		   } else {
		     allow = 1;
		   }
		   allow = allow & prev_allow;
		 }
	       ;
    break;}
case 96:
#line 1715 "parser.y"
{
		 if ((!in_then) && (!in_else)) {
		   fprintf(stderr,"%s : Line %d. Misplaced endif\n", input_file, line_number);
		   FatalError();
		 } else {
		   if_pop();
		 }
	       ;
    break;}
case 97:
#line 1725 "parser.y"
{
		 /* Push old if-then-else status */
		 if_push();
		 if (yyvsp[0].ivalue) {
		   in_then = 1;
		   in_else = 0;
		   allow = 1 & prev_allow;
		 } else {
		   /* Condition is false.   Skip over whatever is in this block */
		   in_else = skip_cond(1);
		   if (in_else == -1) {
		     /* Unrecoverable error */
		     SWIG_exit(1);
		   }
		   if (!in_else) {
		     if_pop();        // Pop out. Reached end of block
		   } else {
		     allow = prev_allow;
		     in_then = 0;
		   }
		 }
	       ;
    break;}
case 98:
#line 1751 "parser.y"
{
		 /* have to pop old if clause off */
		 if_pop();

		 /* Push old if-then-else status */
		 if_push();
		 if (yyvsp[0].ivalue) {
		   in_then = 1;
		   in_else = 0;
		   allow = 1 & prev_allow;
		 } else {
		   /* Condition is false.   Skip over whatever is in this block */
		   in_else = skip_cond(1);
		   if (in_else == -1) {
		     /* Unrecoverable error */
		     SWIG_exit(1);
		   }
		   if (!in_else) {
		     if_pop();        // Pop out. Reached end of block
		   } else {
		     allow = prev_allow;
		     in_then = 0;
		   }
		 }
	       ;
    break;}
case 99:
#line 1780 "parser.y"
{

                 /* Look ID up in the symbol table */
                    if (lookup_symbol(yyvsp[-1].id)) {
		      yyval.ivalue = 1;
		    } else {
		      yyval.ivalue = 0;
		    }
               ;
    break;}
case 100:
#line 1789 "parser.y"
{
		 if (lookup_symbol(yyvsp[0].id)) {
		   yyval.ivalue = 1;
		 } else {
		   yyval.ivalue = 0;
		 }
	       ;
    break;}
case 101:
#line 1796 "parser.y"
{
                      if (yyvsp[0].ivalue) yyval.ivalue = 0;
		      else yyval.ivalue = 1;
	       ;
    break;}
case 102:
#line 1802 "parser.y"
{
		 if (allow && (!WrapExtern))
		   lang->pragma(yyvsp[-4].id,yyvsp[-2].id,yyvsp[-1].id);
		   fprintf(stderr,"%s : Line %d. Warning. '%%pragma(lang,opt=value)' syntax is obsolete.\n",
			   input_file,line_number);
		   fprintf(stderr,"        Use '%%pragma(lang) opt=value' instead.\n");
	       ;
    break;}
case 103:
#line 1810 "parser.y"
{
                 if (allow && (!WrapExtern)) 
		   swig_pragma(yyvsp[-1].id,yyvsp[0].id);
    	       ;
    break;}
case 104:
#line 1814 "parser.y"
{
		 if (allow && (!WrapExtern))
		   lang->pragma(yyvsp[-3].id,yyvsp[-1].id,yyvsp[0].id);
	       ;
    break;}
case 105:
#line 1822 "parser.y"
{ ;
    break;}
case 106:
#line 1823 "parser.y"
{
		 if (allow) {
		   init_language();
		   temp_typeptr = new DataType(Active_type);
		   temp_typeptr->is_pointer += yyvsp[-2].decl.is_pointer;
		   if (yyvsp[-1].ivalue > 0) {
		     temp_typeptr->is_pointer++;
		     temp_typeptr->status = STAT_READONLY;
		     temp_typeptr->arraystr = copy_string(ArrayString);
		   }
		   if (yyvsp[-2].decl.is_reference) {
		     fprintf(stderr,"%s : Line %d. Error. Linkage to C++ reference not allowed.\n", input_file, line_number);
		     FatalError();
		   } else {
		     if (temp_typeptr->qualifier) {
		       if (strcmp(temp_typeptr->qualifier,"const") == 0) {
			 /* Okay.  This is really some sort of C++ constant here. */
			 if (yyvsp[0].dtype.type != T_ERROR)
			   create_constant(yyvsp[-2].decl.id, temp_typeptr, yyvsp[0].dtype.id);
		       } else 
			 create_variable(Active_extern,yyvsp[-2].decl.id, temp_typeptr);
		     } else
		       create_variable(Active_extern, yyvsp[-2].decl.id, temp_typeptr);
		   }
		   delete temp_typeptr;
		 }
	       ;
    break;}
case 107:
#line 1849 "parser.y"
{ ;
    break;}
case 108:
#line 1850 "parser.y"
{
		 if (allow) {
		   init_language();
		   temp_typeptr = new DataType(Active_type);
		   temp_typeptr->is_pointer += yyvsp[-4].decl.is_pointer;
		   temp_typeptr->is_reference = yyvsp[-4].decl.is_reference;
		   create_function(Active_extern, yyvsp[-4].decl.id, temp_typeptr, yyvsp[-2].pl);
		   delete temp_typeptr;
		 }
		 delete yyvsp[-2].pl;
	       ;
    break;}
case 109:
#line 1860 "parser.y"
{ ;
    break;}
case 110:
#line 1863 "parser.y"
{
                   yyval.dtype = yyvsp[-1].dtype;
                 ;
    break;}
case 111:
#line 1866 "parser.y"
{
                   yyval.dtype.type = T_SYMBOL;
	       ;
    break;}
case 112:
#line 1869 "parser.y"
{
		 if (Verbose) 
		   fprintf(stderr,"%s : Line %d.  Warning. Unable to parse #define (ignored)\n", input_file, line_number);
		 yyval.dtype.type = T_ERROR;
	       ;
    break;}
case 113:
#line 1877 "parser.y"
{ yyval.ivalue = 1; ;
    break;}
case 114:
#line 1878 "parser.y"
{yyval.ivalue = 0; ;
    break;}
case 115:
#line 1879 "parser.y"
{
		 if (strcmp(yyvsp[0].id,"C") == 0) {
		   yyval.ivalue = 2;
		 } else {
		   fprintf(stderr,"%s : Line %d.  Unrecognized extern type \"%s\" (ignored).\n", input_file, line_number, yyvsp[0].id);
		   FatalError();
		 }
	       ;
    break;}
case 116:
#line 1891 "parser.y"
{ skip_brace(); ;
    break;}
case 117:
#line 1900 "parser.y"
{
                 if ((yyvsp[-1].p->t->type != T_VOID) || (yyvsp[-1].p->t->is_pointer))
		   yyvsp[0].pl->insert(yyvsp[-1].p,0);
		 yyval.pl = yyvsp[0].pl;
		 delete yyvsp[-1].p;
		;
    break;}
case 118:
#line 1906 "parser.y"
{ yyval.pl = new ParmList;;
    break;}
case 119:
#line 1909 "parser.y"
{
		 yyvsp[0].pl->insert(yyvsp[-1].p,0);
		 yyval.pl = yyvsp[0].pl;
		 delete yyvsp[-1].p;
                ;
    break;}
case 120:
#line 1914 "parser.y"
{ yyval.pl = new ParmList;;
    break;}
case 121:
#line 1917 "parser.y"
{
                  yyval.p = yyvsp[0].p;
		  if (typemap_check("ignore",typemap_lang,yyval.p->t,yyval.p->name))
		    yyval.p->ignore = 1;
               ;
    break;}
case 122:
#line 1922 "parser.y"
{
                  yyval.p = yyvsp[0].p;
                  yyval.p->call_type = yyval.p->call_type | yyvsp[-1].ivalue;
		  if (InArray && (yyval.p->call_type & CALL_VALUE)) {
		     fprintf(stderr,"%s : Line %d. Error. Can't use %%val with an array.\n", input_file, line_number);
		     FatalError();
		  }
		  if (!yyval.p->t->is_pointer) {
		     fprintf(stderr,"%s : Line %d. Error. Can't use %%val or %%out with a non-pointer argument.\n", input_file, line_number);
		     FatalError();
		  } else {
		    yyval.p->t->is_pointer--;
		  }
		;
    break;}
case 123:
#line 1937 "parser.y"
{
		    if (InArray) {
		      yyvsp[-1].type->is_pointer++;
		      if (Verbose) {
			fprintf(stderr,"%s : Line %d. Warning. Array %s", input_file, line_number, yyvsp[-1].type->print_type());
			print_array();
			fprintf(stderr," has been converted to %s.\n", yyvsp[-1].type->print_type());
		      }
		      // Add array string to the type
		      yyvsp[-1].type->arraystr = copy_string(ArrayString.get());
		    } 
		    yyval.p = new Parm(yyvsp[-1].type,yyvsp[0].id);
		    yyval.p->call_type = 0;
		    yyval.p->defvalue = DefArg;
		    if ((yyvsp[-1].type->type == T_USER) && !(yyvsp[-1].type->is_pointer)) {
		      if (Verbose)
			fprintf(stderr,"%s : Line %d. Warning : Parameter of type '%s'\nhas been remapped to '%s *' and will be called using *((%s *) ptr).\n",
				input_file, line_number, yyvsp[-1].type->name, yyvsp[-1].type->name, yyvsp[-1].type->name);

		      yyval.p->call_type = CALL_REFERENCE;
		      yyval.p->t->is_pointer++;
		    }
		    delete yyvsp[-1].type;
		    delete yyvsp[0].id;
                 ;
    break;}
case 124:
#line 1963 "parser.y"
{
		   yyval.p = new Parm(yyvsp[-2].type,yyvsp[0].id);
		   yyval.p->t->is_pointer += yyvsp[-1].ivalue;
		   yyval.p->call_type = 0;
		   yyval.p->defvalue = DefArg;
		   if (InArray) {
		     yyval.p->t->is_pointer++;
		     if (Verbose) {
		       fprintf(stderr,"%s : Line %d. Warning. Array %s", input_file, line_number, yyval.p->t->print_type());
		       print_array();
		       fprintf(stderr," has been converted to %s.\n", yyval.p->t->print_type());
		     }
		     // Add array string to the type
		     yyval.p->t->arraystr = copy_string(ArrayString.get());
		    }
		   delete yyvsp[-2].type;
		   delete yyvsp[0].id;
		;
    break;}
case 125:
#line 1982 "parser.y"
{
		  yyval.p = new Parm(yyvsp[-2].type,yyvsp[0].id);
		  yyval.p->t->is_reference = 1;
		  yyval.p->call_type = 0;
		  yyval.p->t->is_pointer++;
		  yyval.p->defvalue = DefArg;
		  if (!CPlusPlus) {
			fprintf(stderr,"%s : Line %d. Warning.  Use of C++ Reference detected.  Use the -c++ option.\n", input_file, line_number);
		  }
		  delete yyvsp[-2].type;
		  delete yyvsp[0].id;
		;
    break;}
case 126:
#line 1994 "parser.y"
{
                  fprintf(stderr,"%s : Line %d. Error. Function pointer not allowed (remap with typedef).\n", input_file, line_number);
		  FatalError();
		  yyval.p = new Parm(yyvsp[-7].type,yyvsp[-4].id);
		  yyval.p->t->type = T_ERROR;
		  yyval.p->name = copy_string(yyvsp[-4].id);
		  strcpy(yyval.p->t->name,"<function ptr>");
		  delete yyvsp[-7].type;
		  delete yyvsp[-4].id;
		  delete yyvsp[-1].pl;
		;
    break;}
case 127:
#line 2005 "parser.y"
{
                  fprintf(stderr,"%s : Line %d. Variable length arguments not supported (ignored).\n", input_file, line_number);
		  yyval.p = new Parm(new DataType(T_INT),"varargs");
		  yyval.p->t->type = T_ERROR;
		  yyval.p->name = copy_string("varargs");
		  strcpy(yyval.p->t->name,"<varargs>");
		  FatalError();
		;
    break;}
case 128:
#line 2015 "parser.y"
{
                    yyval.id = yyvsp[-1].id; 
                    InArray = 0;
		    if (yyvsp[0].dtype.type == T_CHAR)
		      DefArg = copy_string(ConstChar);
		    else
		      DefArg = copy_string(yyvsp[0].dtype.id);
                    if (yyvsp[0].dtype.id) delete yyvsp[0].dtype.id;
                ;
    break;}
case 129:
#line 2024 "parser.y"
{
                    yyval.id = yyvsp[-1].id; 
                    InArray = yyvsp[0].ivalue; 
                    DefArg = 0;
               ;
    break;}
case 130:
#line 2029 "parser.y"
{
                         yyval.id = new char[1];
                         yyval.id[0] = 0;
                         InArray = yyvsp[0].ivalue;
                         DefArg = 0;
               ;
    break;}
case 131:
#line 2035 "parser.y"
{ yyval.id = new char[1];
	                 yyval.id[0] = 0;
                         InArray = 0;
                         DefArg = 0;
               ;
    break;}
case 132:
#line 2042 "parser.y"
{ yyval.dtype = yyvsp[0].dtype; ;
    break;}
case 133:
#line 2043 "parser.y"
{
		 yyval.dtype.id = new char[strlen(yyvsp[0].id)+2];
		 yyval.dtype.id[0] = '&';
		 strcpy(&yyval.dtype.id[1], yyvsp[0].id);
		 yyval.dtype.type = T_USER;
	       ;
    break;}
case 134:
#line 2049 "parser.y"
{
		 skip_brace();
		 yyval.dtype.id = 0; yyval.dtype.type = T_INT;
	       ;
    break;}
case 135:
#line 2053 "parser.y"
{yyval.dtype.id = 0; yyval.dtype.type = T_INT;;
    break;}
case 136:
#line 2056 "parser.y"
{ yyval.ivalue = CALL_VALUE; ;
    break;}
case 137:
#line 2057 "parser.y"
{ yyval.ivalue = CALL_OUTPUT; ;
    break;}
case 138:
#line 2060 "parser.y"
{
                 yyval.ivalue = yyvsp[-1].ivalue | yyvsp[0].ivalue;
               ;
    break;}
case 139:
#line 2063 "parser.y"
{
                 yyval.ivalue = yyvsp[0].ivalue;
	       ;
    break;}
case 140:
#line 2070 "parser.y"
{ yyval.decl.id = yyvsp[0].id;
                      yyval.decl.is_pointer = 0;
		      yyval.decl.is_reference = 0;
                ;
    break;}
case 141:
#line 2074 "parser.y"
{
                      yyval.decl.id = yyvsp[0].id;
		      yyval.decl.is_pointer = yyvsp[-1].ivalue;
		      yyval.decl.is_reference = 0;
	       ;
    break;}
case 142:
#line 2079 "parser.y"
{
		      yyval.decl.id = yyvsp[0].id;
		      yyval.decl.is_pointer = 1;
		      yyval.decl.is_reference = 1;
		      if (!CPlusPlus) {
			fprintf(stderr,"%s : Line %d. Warning.  Use of C++ Reference detected.  Use the -c++ option.\n", input_file, line_number);
		      }
	       ;
    break;}
case 143:
#line 2089 "parser.y"
{ yyval.ivalue = 1; ;
    break;}
case 144:
#line 2090 "parser.y"
{ yyval.ivalue = yyvsp[0].ivalue + 1;;
    break;}
case 145:
#line 2094 "parser.y"
{
		 yyval.ivalue = yyvsp[0].ivalue + 1;
		 "[]" >> ArrayString;
              ;
    break;}
case 146:
#line 2098 "parser.y"
{
                 yyval.ivalue = yyvsp[0].ivalue + 1;
		 "]" >> ArrayString;
		 yyvsp[-2].dtype.id >> ArrayString;
		 "[" >> ArrayString;
              ;
    break;}
case 147:
#line 2105 "parser.y"
{
                 yyval.ivalue = yyvsp[0].ivalue;
              ;
    break;}
case 148:
#line 2108 "parser.y"
{ yyval.ivalue = 0;
                        ArrayString = "";
              ;
    break;}
case 149:
#line 2116 "parser.y"
{
                   yyval.type = yyvsp[0].type;
               ;
    break;}
case 150:
#line 2119 "parser.y"
{
                   yyval.type = yyvsp[-1].type;
	       ;
    break;}
case 151:
#line 2122 "parser.y"
{
                   yyval.type = yyvsp[-1].type;
	       ;
    break;}
case 152:
#line 2125 "parser.y"
{
                   yyval.type = yyvsp[0].type;
	       ;
    break;}
case 153:
#line 2128 "parser.y"
{
                   yyval.type = yyvsp[0].type;
	       ;
    break;}
case 154:
#line 2131 "parser.y"
{
                   yyval.type = yyvsp[0].type;
	       ;
    break;}
case 155:
#line 2134 "parser.y"
{
                   yyval.type = yyvsp[0].type;
	       ;
    break;}
case 156:
#line 2137 "parser.y"
{
                   yyval.type = yyvsp[0].type;
	       ;
    break;}
case 157:
#line 2140 "parser.y"
{
                   if (yyvsp[0].type) yyval.type = yyvsp[0].type;
		   else yyval.type = yyvsp[-1].type;
	       ;
    break;}
case 158:
#line 2144 "parser.y"
{
                   if (yyvsp[0].type) yyval.type = yyvsp[0].type;
		   else yyval.type = yyvsp[-1].type;
	       ;
    break;}
case 159:
#line 2148 "parser.y"
{
		 yyval.type = yyvsp[-1].type;
		 if (strlen(yyvsp[0].id) > 0) {
		    if ((strlen(yyvsp[0].id) + strlen(yyval.type->name)) >= MAX_NAME) {
		      fprintf(stderr,"%s : Line %d. Fatal error. Type-name is too long!\n", 
			      input_file, line_number);
		    } else {
		      strcat(yyval.type->name,yyvsp[0].id);
		    }
		  }
	       ;
    break;}
case 160:
#line 2159 "parser.y"
{
		  yyval.type = new DataType;
		  strcpy(yyval.type->name,yyvsp[-1].id);
		  yyval.type->type = T_USER;
		  /* Do a typedef lookup */
		  yyval.type->typedef_resolve();
		  if (strlen(yyvsp[0].id) > 0) {
		    if ((strlen(yyvsp[0].id) + strlen(yyval.type->name)) >= MAX_NAME) {
		      fprintf(stderr,"%s : Line %d. Fatal error. Type-name is too long!\n", 
			      input_file, line_number);
		    } else {
		      strcat(yyval.type->name,yyvsp[0].id);
		    }
		  }
	       ;
    break;}
case 161:
#line 2174 "parser.y"
{
		  yyval.type = yyvsp[0].type;
                  yyval.type->qualifier = new char[6];
		  strcpy(yyval.type->qualifier,"const");
     	       ;
    break;}
case 162:
#line 2179 "parser.y"
{
                  yyval.type = new DataType;
		  sprintf(yyval.type->name,"%s %s",yyvsp[-1].id, yyvsp[0].id);
		  yyval.type->type = T_USER;
	       ;
    break;}
case 163:
#line 2184 "parser.y"
{
                  yyval.type = new DataType;
                  sprintf(yyval.type->name,"%s::%s",yyvsp[-2].id,yyvsp[0].id);
                  yyval.type->type = T_USER;
		  yyval.type->typedef_resolve();
               ;
    break;}
case 164:
#line 2193 "parser.y"
{
                  yyval.type = new DataType;
                  sprintf(yyval.type->name,"%s", yyvsp[0].id);
                  yyval.type->type = T_USER;
                  yyval.type->typedef_resolve(1);
               ;
    break;}
case 165:
#line 2199 "parser.y"
{
                  yyval.type = new DataType;
                  sprintf(yyval.type->name,"enum %s", yyvsp[0].id);
                  yyval.type->type = T_INT;
                  yyval.type->typedef_resolve(1);
               ;
    break;}
case 166:
#line 2209 "parser.y"
{
                   yyval.type = yyvsp[0].type;
               ;
    break;}
case 167:
#line 2212 "parser.y"
{
                   yyval.type = yyvsp[-1].type;
	       ;
    break;}
case 168:
#line 2215 "parser.y"
{
                   yyval.type = yyvsp[-1].type;
	       ;
    break;}
case 169:
#line 2218 "parser.y"
{
                   yyval.type = yyvsp[0].type;
	       ;
    break;}
case 170:
#line 2221 "parser.y"
{
                   yyval.type = yyvsp[0].type;
	       ;
    break;}
case 171:
#line 2224 "parser.y"
{
                   yyval.type = yyvsp[0].type;
	       ;
    break;}
case 172:
#line 2227 "parser.y"
{
                   yyval.type = yyvsp[0].type;
	       ;
    break;}
case 173:
#line 2230 "parser.y"
{
                   yyval.type = yyvsp[0].type;
	       ;
    break;}
case 174:
#line 2233 "parser.y"
{
                   if (yyvsp[0].type) yyval.type = yyvsp[0].type;
		   else yyval.type = yyvsp[-1].type;
	       ;
    break;}
case 175:
#line 2237 "parser.y"
{
                   if (yyvsp[0].type) yyval.type = yyvsp[0].type;
		   else yyval.type = yyvsp[-1].type;
	       ;
    break;}
case 176:
#line 2241 "parser.y"
{
		   yyval.type = yyvsp[-1].type;
		   strcat(yyval.type->name,yyvsp[0].id);
	       ;
    break;}
case 177:
#line 2245 "parser.y"
{
		  yyval.type = yyvsp[0].type;
                  yyval.type->qualifier = new char[6];
		  strcpy(yyval.type->qualifier,"const");
     	       ;
    break;}
case 178:
#line 2250 "parser.y"
{
                  yyval.type = new DataType;
		  sprintf(yyval.type->name,"%s %s",yyvsp[-1].id, yyvsp[0].id);
		  yyval.type->type = T_USER;
	       ;
    break;}
case 179:
#line 2259 "parser.y"
{
                   yyval.type = (DataType *) 0;
               ;
    break;}
case 180:
#line 2262 "parser.y"
{
                   yyval.type = yyvsp[0].type;
		   yyval.type->type = T_INT;
		   sprintf(temp_name,"signed %s",yyvsp[0].type->name);
		   strcpy(yyval.type->name,temp_name);
	       ;
    break;}
case 181:
#line 2268 "parser.y"
{
                   yyval.type = yyvsp[-1].type;
		   yyval.type->type = T_SHORT;
		   sprintf(temp_name,"signed %s",yyvsp[-1].type->name);
		   strcpy(yyval.type->name,temp_name);
	       ;
    break;}
case 182:
#line 2274 "parser.y"
{
                   yyval.type = yyvsp[-1].type;
		   yyval.type->type = T_LONG;
		   sprintf(temp_name,"signed %s",yyvsp[-1].type->name);
		   strcpy(yyval.type->name,temp_name);
	       ;
    break;}
case 183:
#line 2280 "parser.y"
{
                   yyval.type = yyvsp[0].type;
		   yyval.type->type = T_SCHAR;
		   sprintf(temp_name,"signed %s",yyvsp[0].type->name);
		   strcpy(yyval.type->name,temp_name);
	       ;
    break;}
case 184:
#line 2290 "parser.y"
{
                   yyval.type = (DataType *) 0;
               ;
    break;}
case 185:
#line 2293 "parser.y"
{
                   yyval.type = yyvsp[0].type;
		   yyval.type->type = T_UINT;
		   sprintf(temp_name,"unsigned %s",yyvsp[0].type->name);
		   strcpy(yyval.type->name,temp_name);
	       ;
    break;}
case 186:
#line 2299 "parser.y"
{
                   yyval.type = yyvsp[-1].type;
		   yyval.type->type = T_USHORT;
		   sprintf(temp_name,"unsigned %s",yyvsp[-1].type->name);
		   strcpy(yyval.type->name,temp_name);
	       ;
    break;}
case 187:
#line 2305 "parser.y"
{
                   yyval.type = yyvsp[-1].type;
		   yyval.type->type = T_ULONG;
		   sprintf(temp_name,"unsigned %s",yyvsp[-1].type->name);
		   strcpy(yyval.type->name,temp_name);
	       ;
    break;}
case 188:
#line 2311 "parser.y"
{
                   yyval.type = yyvsp[0].type;
		   yyval.type->type = T_UCHAR;
		   sprintf(temp_name,"unsigned %s",yyvsp[0].type->name);
		   strcpy(yyval.type->name,temp_name);
	       ;
    break;}
case 189:
#line 2319 "parser.y"
{ ;
    break;}
case 190:
#line 2320 "parser.y"
{ ;
    break;}
case 191:
#line 2323 "parser.y"
{ scanner_check_typedef(); ;
    break;}
case 192:
#line 2323 "parser.y"
{
                   yyval.dtype = yyvsp[0].dtype;
		   scanner_ignore_typedef();
		   if (ConstChar) delete ConstChar;
		   ConstChar = 0;
                ;
    break;}
case 193:
#line 2329 "parser.y"
{
                   yyval.dtype.id = yyvsp[0].id;
                   yyval.dtype.type = T_CHAR;
		   if (ConstChar) delete ConstChar;
		   ConstChar = new char[strlen(yyvsp[0].id)+3];
		   sprintf(ConstChar,"\"%s\"",yyvsp[0].id);
		;
    break;}
case 194:
#line 2336 "parser.y"
{
                   yyval.dtype.id = yyvsp[0].id;
		   yyval.dtype.type = T_CHAR;
		   if (ConstChar) delete ConstChar;
		   ConstChar = new char[strlen(yyvsp[0].id)+3];
		   sprintf(ConstChar,"'%s'",yyvsp[0].id);
		 ;
    break;}
case 195:
#line 2348 "parser.y"
{
                 yyval.ilist = yyvsp[-2].ilist;
		 yyval.ilist.names[yyval.ilist.count] = copy_string(yyvsp[0].id);
		 yyval.ilist.count++;
		 yyval.ilist.names[yyval.ilist.count] = (char *) 0;
                ;
    break;}
case 196:
#line 2354 "parser.y"
{
                 yyval.ilist.names = new char *[NI_NAMES];
		 yyval.ilist.count = 0;
		 for (i = 0; i < NI_NAMES; i++) 
		   yyval.ilist.names[i] = (char *) 0;
	       ;
    break;}
case 197:
#line 2364 "parser.y"
{ yyval.id = yyvsp[0].id; ;
    break;}
case 198:
#line 2365 "parser.y"
{ yyval.id = (char *) 0;;
    break;}
case 199:
#line 2371 "parser.y"
{;
    break;}
case 200:
#line 2372 "parser.y"
{;
    break;}
case 201:
#line 2376 "parser.y"
{
		   temp_typeptr = new DataType(T_INT);
		   create_constant(yyvsp[0].id, temp_typeptr, yyvsp[0].id);
		   delete temp_typeptr;
		 ;
    break;}
case 202:
#line 2381 "parser.y"
{ scanner_check_typedef();;
    break;}
case 203:
#line 2381 "parser.y"
{
		   temp_typeptr = new DataType(yyvsp[0].dtype.type);
// Use enum name instead of value
// OLD		   create_constant($1, temp_typeptr, $4.id);
                   create_constant(yyvsp[-3].id, temp_typeptr, yyvsp[-3].id);
		   delete temp_typeptr;
                 ;
    break;}
case 204:
#line 2388 "parser.y"
{ ;
    break;}
case 205:
#line 2389 "parser.y"
{ ;
    break;}
case 206:
#line 2392 "parser.y"
{
                   yyval.dtype = yyvsp[0].dtype;
		   if ((yyval.dtype.type != T_INT) && (yyval.dtype.type != T_UINT) &&
		       (yyval.dtype.type != T_LONG) && (yyval.dtype.type != T_ULONG) &&
		       (yyval.dtype.type != T_SHORT) && (yyval.dtype.type != T_USHORT) && 
		       (yyval.dtype.type != T_SCHAR) && (yyval.dtype.type != T_UCHAR)) {
		     fprintf(stderr,"%s : Lind %d. Type error. Expecting an int\n",
			     input_file, line_number);
		     FatalError();
		   }

                ;
    break;}
case 207:
#line 2404 "parser.y"
{
                   yyval.dtype.id = yyvsp[0].id;
		   yyval.dtype.type = T_CHAR;
		 ;
    break;}
case 208:
#line 2415 "parser.y"
{ 
                  yyval.dtype.id = yyvsp[0].id;
                  yyval.dtype.type = T_INT;
                 ;
    break;}
case 209:
#line 2419 "parser.y"
{
                  yyval.dtype.id = yyvsp[0].id;
                  yyval.dtype.type = T_DOUBLE;
               ;
    break;}
case 210:
#line 2423 "parser.y"
{
                  yyval.dtype.id = yyvsp[0].id;
		  yyval.dtype.type = T_UINT;
	       ;
    break;}
case 211:
#line 2427 "parser.y"
{
                  yyval.dtype.id = yyvsp[0].id;
		  yyval.dtype.type = T_LONG;
	       ;
    break;}
case 212:
#line 2431 "parser.y"
{
                  yyval.dtype.id = yyvsp[0].id;
		  yyval.dtype.type = T_ULONG;
	       ;
    break;}
case 213:
#line 2435 "parser.y"
{
	          yyval.dtype.id = new char[strlen(yyvsp[-1].type->name)+9];
		  sprintf(yyval.dtype.id,"sizeof(%s)", yyvsp[-1].type->name);
		  yyval.dtype.type = T_INT;
	       ;
    break;}
case 214:
#line 2440 "parser.y"
{
		  yyval.dtype.id = new char[strlen(yyvsp[0].dtype.id)+strlen(yyvsp[-2].type->name)+3];
		  sprintf(yyval.dtype.id,"(%s)%s",yyvsp[-2].type->name,yyvsp[0].dtype.id);
		  yyval.dtype.type = yyvsp[-2].type->type;
	       ;
    break;}
case 215:
#line 2445 "parser.y"
{
		 yyval.dtype.id = lookup_symvalue(yyvsp[0].id);
		 if (yyval.dtype.id == (char *) 0)
		   yyval.dtype.id = yyvsp[0].id;
		 else {
		   yyval.dtype.id = new char[strlen(yyval.dtype.id)+3];
		   sprintf(yyval.dtype.id,"(%s)",lookup_symvalue(yyvsp[0].id));
		 }
		 temp_typeptr = lookup_symtype(yyvsp[0].id);
		 if (temp_typeptr) yyval.dtype.type = temp_typeptr->type;
		 else yyval.dtype.type = T_INT;
               ;
    break;}
case 216:
#line 2457 "parser.y"
{
                  yyval.dtype.id = new char[strlen(yyvsp[-2].id)+strlen(yyvsp[0].id)+3];
		  sprintf(yyval.dtype.id,"%s::%s",yyvsp[-2].id,yyvsp[0].id);
                  yyval.dtype.type = T_INT;
		  delete yyvsp[-2].id;
		  delete yyvsp[0].id;
               ;
    break;}
case 217:
#line 2464 "parser.y"
{
	         E_BINARY(yyval.dtype.id,yyvsp[-2].dtype.id,yyvsp[0].dtype.id,"+");
		 yyval.dtype.type = promote(yyvsp[-2].dtype.type,yyvsp[0].dtype.type);
		 delete yyvsp[-2].dtype.id;
		 delete yyvsp[0].dtype.id;
	       ;
    break;}
case 218:
#line 2470 "parser.y"
{
	         E_BINARY(yyval.dtype.id,yyvsp[-2].dtype.id,yyvsp[0].dtype.id,"-");
		 yyval.dtype.type = promote(yyvsp[-2].dtype.type,yyvsp[0].dtype.type);
		 delete yyvsp[-2].dtype.id;
		 delete yyvsp[0].dtype.id;
	       ;
    break;}
case 219:
#line 2476 "parser.y"
{
	         E_BINARY(yyval.dtype.id,yyvsp[-2].dtype.id,yyvsp[0].dtype.id,"*");
		 yyval.dtype.type = promote(yyvsp[-2].dtype.type,yyvsp[0].dtype.type);
		 delete yyvsp[-2].dtype.id;
		 delete yyvsp[0].dtype.id;

	       ;
    break;}
case 220:
#line 2483 "parser.y"
{
	         E_BINARY(yyval.dtype.id,yyvsp[-2].dtype.id,yyvsp[0].dtype.id,"/");
		 yyval.dtype.type = promote(yyvsp[-2].dtype.type,yyvsp[0].dtype.type);
		 delete yyvsp[-2].dtype.id;
		 delete yyvsp[0].dtype.id;

	       ;
    break;}
case 221:
#line 2490 "parser.y"
{
	         E_BINARY(yyval.dtype.id,yyvsp[-2].dtype.id,yyvsp[0].dtype.id,"&");
		 yyval.dtype.type = promote(yyvsp[-2].dtype.type,yyvsp[0].dtype.type);
		 if ((yyvsp[-2].dtype.type == T_DOUBLE) || (yyvsp[0].dtype.type == T_DOUBLE)) {
		   fprintf(stderr,"%s : Line %d. Type error in constant expression (expecting integers).\n", input_file, line_number);
		   FatalError();
		 }
		 delete yyvsp[-2].dtype.id;
		 delete yyvsp[0].dtype.id;

	       ;
    break;}
case 222:
#line 2501 "parser.y"
{
	         E_BINARY(yyval.dtype.id,yyvsp[-2].dtype.id,yyvsp[0].dtype.id,"|");
		 yyval.dtype.type = promote(yyvsp[-2].dtype.type,yyvsp[0].dtype.type);
		 if ((yyvsp[-2].dtype.type == T_DOUBLE) || (yyvsp[0].dtype.type == T_DOUBLE)) {
		   fprintf(stderr,"%s : Line %d. Type error in constant expression (expecting integers).\n", input_file, line_number);
		   FatalError();
		 }
		 yyval.dtype.type = T_INT;
		 delete yyvsp[-2].dtype.id;
		 delete yyvsp[0].dtype.id;

	       ;
    break;}
case 223:
#line 2513 "parser.y"
{
	         E_BINARY(yyval.dtype.id,yyvsp[-2].dtype.id,yyvsp[0].dtype.id,"^");
		 yyval.dtype.type = promote(yyvsp[-2].dtype.type,yyvsp[0].dtype.type);
		 if ((yyvsp[-2].dtype.type == T_DOUBLE) || (yyvsp[0].dtype.type == T_DOUBLE)) {
		   fprintf(stderr,"%s : Line %d. Type error in constant expression (expecting integers).\n", input_file, line_number);
		   FatalError();
		 }
		 yyval.dtype.type = T_INT;
		 delete yyvsp[-2].dtype.id;
		 delete yyvsp[0].dtype.id;

	       ;
    break;}
case 224:
#line 2525 "parser.y"
{
	         E_BINARY(yyval.dtype.id,yyvsp[-2].dtype.id,yyvsp[0].dtype.id,"<<");
		 yyval.dtype.type = promote(yyvsp[-2].dtype.type,yyvsp[0].dtype.type);
		 if ((yyvsp[-2].dtype.type == T_DOUBLE) || (yyvsp[0].dtype.type == T_DOUBLE)) {
		   fprintf(stderr,"%s : Line %d. Type error in constant expression (expecting integers).\n", input_file, line_number);
		   FatalError();
		 }
		 yyval.dtype.type = T_INT;
		 delete yyvsp[-2].dtype.id;
		 delete yyvsp[0].dtype.id;

	       ;
    break;}
case 225:
#line 2537 "parser.y"
{
	         E_BINARY(yyval.dtype.id,yyvsp[-2].dtype.id,yyvsp[0].dtype.id,">>");
		 yyval.dtype.type = promote(yyvsp[-2].dtype.type,yyvsp[0].dtype.type);
		 if ((yyvsp[-2].dtype.type == T_DOUBLE) || (yyvsp[0].dtype.type == T_DOUBLE)) {
		   fprintf(stderr,"%s : Line %d. Type error in constant expression (expecting integers).\n", input_file, line_number);
		   FatalError();
		 }
		 yyval.dtype.type = T_INT;
		 delete yyvsp[-2].dtype.id;
		 delete yyvsp[0].dtype.id;

	       ;
    break;}
case 226:
#line 2549 "parser.y"
{
	          yyval.dtype.id = new char[strlen(yyvsp[0].dtype.id)+2];
		  sprintf(yyval.dtype.id,"-%s",yyvsp[0].dtype.id);
		  yyval.dtype.type = yyvsp[0].dtype.type;
		 delete yyvsp[0].dtype.id;

	       ;
    break;}
case 227:
#line 2556 "parser.y"
{
	          yyval.dtype.id = new char[strlen(yyvsp[0].dtype.id)+2];
		  sprintf(yyval.dtype.id,"~%s",yyvsp[0].dtype.id);
		  if (yyvsp[0].dtype.type == T_DOUBLE) {
		   fprintf(stderr,"%s : Line %d. Type error in constant expression (expecting integers).\n", input_file, line_number);
		   FatalError();
		  }
		  yyval.dtype.type = yyvsp[0].dtype.type;
		  delete yyvsp[0].dtype.id;
	       ;
    break;}
case 228:
#line 2566 "parser.y"
{
	          yyval.dtype.id = new char[strlen(yyvsp[-1].dtype.id)+3];
	          sprintf(yyval.dtype.id,"(%s)", yyvsp[-1].dtype.id);
		  yyval.dtype.type = yyvsp[-1].dtype.type;
		  delete yyvsp[-1].dtype.id;
	       ;
    break;}
case 229:
#line 2577 "parser.y"
{ ;
    break;}
case 230:
#line 2578 "parser.y"
{;
    break;}
case 231:
#line 2584 "parser.y"
{
	       char *iname;
	       if (allow) {
		 init_language();
		 DataType::new_scope();

		 sprintf(temp_name,"CPP_CLASS:%s\n",yyvsp[-2].id);
		 if (add_symbol(temp_name, (DataType *) 0, (char *) 0)) {
		   fprintf(stderr,"%s : Line %d. Error. %s %s is multiply defined.\n", input_file, line_number, yyvsp[-3].id, yyvsp[-2].id);
		   FatalError();
		 }
		 if ((!CPlusPlus) && (strcmp(yyvsp[-3].id,"class") == 0))
		   fprintf(stderr,"%s : Line %d. *** WARNING ***. C++ mode is disabled (enable using -c++)\n", input_file, line_number);

		 iname = make_name(yyvsp[-2].id);
		 doc_entry = new DocClass(iname, doc_parent());
		 if (iname == yyvsp[-2].id) 
		   cplus_open_class(yyvsp[-2].id, 0, yyvsp[-3].id);
		 else
		   cplus_open_class(yyvsp[-2].id, iname, yyvsp[-3].id);
		 if (strcmp(yyvsp[-3].id,"class") == 0)
		   cplus_mode = CPLUS_PRIVATE;
		 else
		   cplus_mode = CPLUS_PUBLIC;
		 doc_stack_top++;
		 doc_stack[doc_stack_top] = doc_entry;
		 scanner_clear_start();
		 nested_list = 0;
		 // Merge in scope from base classes
		 cplus_inherit_scope(yyvsp[-1].ilist.count,yyvsp[-1].ilist.names);
	       }
              ;
    break;}
case 232:
#line 2615 "parser.y"
{
		if (allow) {
		  if (yyvsp[-4].ilist.names) {
		    if (strcmp(yyvsp[-6].id,"union") != 0)
		      cplus_inherit(yyvsp[-4].ilist.count, yyvsp[-4].ilist.names);
		    else {
		      fprintf(stderr,"%s : Line %d.  Inheritance not allowed for unions.\n",input_file, line_number);
		      FatalError();
		    }
		  }
		  // Clean up the inheritance list
		  if (yyvsp[-4].ilist.names) {
		    int j;
		    for (j = 0; j < yyvsp[-4].ilist.count; j++) {
		      if (yyvsp[-4].ilist.names[j]) delete [] yyvsp[-4].ilist.names[j];
		    }
		    delete [] yyvsp[-4].ilist.names;
		  }

		  // Dumped nested declarations (if applicable)
		  dump_nested(yyvsp[-5].id);

		  // Save and collapse current scope
		  cplus_register_scope(DataType::collapse_scope(yyvsp[-5].id));

		  // Restore the original doc entry for this class
		  doc_entry = doc_stack[doc_stack_top];
		  cplus_class_close((char *) 0); 
		  doc_entry = 0;
		  // Bump the documentation stack back down
		  doc_stack_top--;
		  cplus_mode = CPLUS_PUBLIC;
		}
	      ;
    break;}
case 233:
#line 2652 "parser.y"
{
	       if (allow) {
		 char *iname;
		 init_language();
		 DataType::new_scope();

		 sprintf(temp_name,"CPP_CLASS:%s\n",yyvsp[-2].id);
		 if (add_symbol(temp_name, (DataType *) 0, (char *) 0)) {
		   fprintf(stderr,"%s : Line %d. Error. %s %s is multiply defined.\n", input_file, line_number, yyvsp[-3].id, yyvsp[-2].id);
		   FatalError();
		 }
		 if ((!CPlusPlus) && (strcmp(yyvsp[-3].id,"class") == 0))
		   fprintf(stderr,"%s : Line %d. *** WARNING ***. C++ mode is disabled (enable using -c++)\n", input_file, line_number);
		 
		 iname = make_name(yyvsp[-2].id);
		 doc_entry = new DocClass(iname, doc_parent());
		 if (yyvsp[-2].id == iname) 
		   cplus_open_class(yyvsp[-2].id, 0, yyvsp[-3].id);
		 else
		   cplus_open_class(yyvsp[-2].id, iname, yyvsp[-3].id);
		 if (strcmp(yyvsp[-3].id,"class") == 0)
		   cplus_mode = CPLUS_PRIVATE;
		 else
		   cplus_mode = CPLUS_PUBLIC;
		 // Create a documentation entry for the class
		 doc_stack_top++;
		 doc_stack[doc_stack_top] = doc_entry;
		 scanner_clear_start();
		 nested_list = 0;

		 // Merge in scope from base classes
		 cplus_inherit_scope(yyvsp[-1].ilist.count,yyvsp[-1].ilist.names);

	       }
              ;
    break;}
case 234:
#line 2686 "parser.y"
{
		if (allow) {
		  if (yyvsp[-5].ilist.names) {
		    if (strcmp(yyvsp[-7].id,"union") != 0)
		      cplus_inherit(yyvsp[-5].ilist.count, yyvsp[-5].ilist.names);
		    else {
		      fprintf(stderr,"%s : Line %d.  Inheritance not allowed for unions.\n",input_file, line_number);
		      FatalError();
		    }
		  }
		  // Create a datatype for correctly processing the typedef
		  Active_typedef = new DataType();
		  Active_typedef->type = T_USER;
		  sprintf(Active_typedef->name,"%s %s", yyvsp[-7].id,yyvsp[-6].id);
		  Active_typedef->is_pointer = 0;
		  Active_typedef->implicit_ptr = 0;

		  // Clean up the inheritance list
		  if (yyvsp[-5].ilist.names) {
		    int j;
		    for (j = 0; j < yyvsp[-5].ilist.count; j++) {
		      if (yyvsp[-5].ilist.names[j]) delete [] yyvsp[-5].ilist.names[j];
		    }
		    delete [] yyvsp[-5].ilist.names;
		  }

		  if (yyvsp[0].decl.is_pointer > 0) {
		    fprintf(stderr,"%s : Line %d.  typedef struct { } *id not supported properly. Winging it...\n", input_file, line_number);

		  }
		  // Create dump nested class code
		  if (yyvsp[0].decl.is_pointer > 0) {
		    dump_nested(yyvsp[-6].id);
		  } else {
		    dump_nested(yyvsp[0].decl.id);
		  }
		    
		  // Collapse any datatypes created in the the class

		  cplus_register_scope(DataType::collapse_scope(yyvsp[-6].id));

		  doc_entry = doc_stack[doc_stack_top];
		  if (yyvsp[0].decl.is_pointer > 0) {
		    cplus_class_close(yyvsp[-6].id);
		  } else {
		    cplus_class_close(yyvsp[0].decl.id); 
		  }
		  doc_stack_top--;
		  doc_entry = 0;

		  // Create a typedef in global scope

		  if (yyvsp[0].decl.is_pointer == 0)
		    Active_typedef->typedef_add(yyvsp[0].decl.id);
		  else {
		    DataType *t = new DataType(Active_typedef);
		    t->is_pointer += yyvsp[0].decl.is_pointer;
		    t->typedef_add(yyvsp[0].decl.id);
		    cplus_register_type(yyvsp[0].decl.id);
		    delete t;
		  }
		  cplus_mode = CPLUS_PUBLIC;
		}
	      ;
    break;}
case 235:
#line 2749 "parser.y"
{ ;
    break;}
case 236:
#line 2753 "parser.y"
{
	       char *iname;
	       if (allow) {
		 init_language();
		 DataType::new_scope();
		 if ((!CPlusPlus) && (strcmp(yyvsp[-1].id,"class") == 0))
		   fprintf(stderr,"%s : Line %d. *** WARNING ***. C++ mode is disabled (enable using -c++)\n", input_file, line_number);
		 
		 iname = make_name("");
		 doc_entry = new DocClass(iname,doc_parent());
		 if (strlen(iname))
		   cplus_open_class("", iname, yyvsp[-1].id);
		 else
		   cplus_open_class("",0,yyvsp[-1].id);
		 if (strcmp(yyvsp[-1].id,"class") == 0)
		   cplus_mode = CPLUS_PRIVATE;
		 else
		   cplus_mode = CPLUS_PUBLIC;
		 doc_stack_top++;
		 doc_stack[doc_stack_top] = doc_entry;
		 scanner_clear_start();
		 nested_list = 0;
	       }
              ;
    break;}
case 237:
#line 2776 "parser.y"
{
		if (allow) {
		  if (yyvsp[0].decl.is_pointer > 0) {
		    fprintf(stderr,"%s : Line %d. typedef %s {} *%s not supported correctly. Will be ignored.\n", input_file, line_number, yyvsp[-5].id, yyvsp[0].decl.id);
		    cplus_abort();
		  } else {
		    sprintf(temp_name,"CPP_CLASS:%s\n",yyvsp[0].decl.id);
		    if (add_symbol(temp_name, (DataType *) 0, (char *) 0)) {
		      fprintf(stderr,"%s : Line %d. Error. %s %s is multiply defined.\n", input_file, line_number, yyvsp[-5].id, yyvsp[0].decl.id);
		      FatalError();
		    }
		  }
		  // Create a datatype for correctly processing the typedef
		  Active_typedef = new DataType();
		  Active_typedef->type = T_USER;
		  sprintf(Active_typedef->name,"%s",yyvsp[0].decl.id);
		  Active_typedef->is_pointer = 0;
		  Active_typedef->implicit_ptr = 0;
		  
		  // Dump nested classes
		  if (yyvsp[0].decl.is_pointer == 0)  
		    dump_nested(yyvsp[0].decl.id);

		  // Go back to previous scope

		  cplus_register_scope(DataType::collapse_scope((char *) 0));
		  
		  doc_entry = doc_stack[doc_stack_top];
		  // Change name of doc_entry
		  doc_entry->name = copy_string(yyvsp[0].decl.id);
		  if (yyvsp[0].decl.is_pointer == 0) 
		    cplus_class_close(yyvsp[0].decl.id); 
		  doc_entry = 0;
		  doc_stack_top--;
		  cplus_mode = CPLUS_PUBLIC;
		}
	      ;
    break;}
case 238:
#line 2812 "parser.y"
{ ;
    break;}
case 239:
#line 2817 "parser.y"
{
	       char *iname;
		 if (allow) {
		   init_language();
		   iname = make_name(yyvsp[-1].id);
		   lang->cpp_class_decl(yyvsp[-1].id,iname,yyvsp[-2].id);
		 }
	     ;
    break;}
case 240:
#line 2828 "parser.y"
{
	       if (allow) {
		 init_language();
		 if (!CPlusPlus) 
		   fprintf(stderr,"%s : Line %d. *** WARNING ***. C++ mode is disabled (enable using -c++)\n", input_file, line_number);
		 
		 yyvsp[-7].type->is_pointer += yyvsp[-6].decl.is_pointer;
		 yyvsp[-7].type->is_reference = yyvsp[-6].decl.is_reference;
		 // Fix up the function name
		 sprintf(temp_name,"%s::%s",yyvsp[-6].decl.id,yyvsp[-4].id);
		 if (!Rename_true) {
		   Rename_true = 1;
		   sprintf(yy_rename,"%s_%s",yyvsp[-6].decl.id,yyvsp[-4].id);
		 }
		 create_function(yyvsp[-8].ivalue, temp_name, yyvsp[-7].type, yyvsp[-2].pl);
	       }
	       delete yyvsp[-7].type;
	       delete yyvsp[-2].pl;
	      ;
    break;}
case 241:
#line 2849 "parser.y"
{
	       if (allow) {
		 init_language();
		 if (!CPlusPlus) 
		   fprintf(stderr,"%s : Line %d. *** WARNING ***. C++ mode is disabled (enable using -c++)\n", input_file, line_number);

		 yyvsp[-4].type->is_pointer += yyvsp[-3].decl.is_pointer;
		 // Fix up the function name
		 sprintf(temp_name,"%s::%s",yyvsp[-3].decl.id,yyvsp[-1].id);
		 if (!Rename_true) {
		   Rename_true = 1;
		   sprintf(yy_rename,"%s_%s",yyvsp[-3].decl.id,yyvsp[-1].id);
		 }
		 create_variable(yyvsp[-5].ivalue,temp_name, yyvsp[-4].type);
	       }
	       delete yyvsp[-4].type;
	     ;
    break;}
case 242:
#line 2869 "parser.y"
{
	       fprintf(stderr,"%s : Line %d. Operator overloading not supported (ignored).\n", input_file, line_number);
		skip_decl();
		delete yyvsp[-3].type;
	     ;
    break;}
case 243:
#line 2877 "parser.y"
{
	       fprintf(stderr,"%s : Line %d. Templates not currently supported (ignored).\n",
		       input_file, line_number);
	       skip_decl();
	     ;
    break;}
case 244:
#line 2885 "parser.y"
{
	       cplus_mode = CPLUS_PUBLIC;
               doc_entry = cplus_set_class(yyvsp[-1].id);
	       if (!doc_entry) {
		 doc_entry = new DocClass(yyvsp[-1].id,doc_parent());
	       };
	       doc_stack_top++;
	       doc_stack[doc_stack_top] = doc_entry;
	       scanner_clear_start();
	       AddMethods = 1;
	     ;
    break;}
case 245:
#line 2895 "parser.y"
{
	       cplus_unset_class();
	       doc_entry = 0;
	       doc_stack_top--;
	       AddMethods = 0;
	     ;
    break;}
case 246:
#line 2903 "parser.y"
{ ;
    break;}
case 247:
#line 2904 "parser.y"
{ ;
    break;}
case 248:
#line 2905 "parser.y"
{ ;
    break;}
case 249:
#line 2908 "parser.y"
{;
    break;}
case 250:
#line 2909 "parser.y"
{
	           AddMethods = 1;
	     ;
    break;}
case 251:
#line 2911 "parser.y"
{
	           AddMethods = 0;
	     ;
    break;}
case 252:
#line 2913 "parser.y"
{ ;
    break;}
case 253:
#line 2914 "parser.y"
{
	       skip_decl();
		   {
		     static int last_error_line = -1;
		     if (last_error_line != line_number) {
		       fprintf(stderr,"%s : Line %d. Syntax error in input.\n", input_file, line_number);
		       FatalError();
		       last_error_line = line_number;
		     }
		   }
	     ;
    break;}
case 254:
#line 2924 "parser.y"
{ ;
    break;}
case 255:
#line 2925 "parser.y"
{ ;
    break;}
case 256:
#line 2928 "parser.y"
{
                char *iname;
                if (allow) {
		  init_language();
		  if (cplus_mode == CPLUS_PUBLIC) {
		    Stat_func++;
		    yyvsp[-5].type->is_pointer += yyvsp[-4].decl.is_pointer;
		    yyvsp[-5].type->is_reference = yyvsp[-4].decl.is_reference;
		    if (Verbose) {
		      fprintf(stderr,"Wrapping member function : %s\n",yyvsp[-4].decl.id);
		    }
		    iname = make_name(yyvsp[-4].decl.id);
		    doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		    if (iname == yyvsp[-4].decl.id) iname = 0;
		    cplus_member_func(yyvsp[-4].decl.id, iname, yyvsp[-5].type,yyvsp[-2].pl,0);
		  }
		  scanner_clear_start();
		}
		delete yyvsp[-5].type;
		delete yyvsp[-2].pl;
              ;
    break;}
case 257:
#line 2952 "parser.y"
{
	       char *iname;
	       if (allow) {
		 init_language();
		 if (cplus_mode == CPLUS_PUBLIC) {
		   Stat_func++;
		   yyvsp[-5].type->is_pointer += yyvsp[-4].decl.is_pointer;
		   yyvsp[-5].type->is_reference = yyvsp[-4].decl.is_reference;
		   if (Verbose) {
		     fprintf(stderr,"Wrapping virtual member function : %s\n",yyvsp[-4].decl.id);
		   }
		   iname = make_name(yyvsp[-4].decl.id);
		   doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		   if (iname == yyvsp[-4].decl.id) iname = 0;
		   cplus_member_func(yyvsp[-4].decl.id,iname,yyvsp[-5].type,yyvsp[-2].pl,1);
		 }
		 scanner_clear_start();
	       }
	       delete yyvsp[-5].type;
	       delete yyvsp[-2].pl;
	     ;
    break;}
case 258:
#line 2975 "parser.y"
{
		char *iname;
		if (allow) {
		  init_language();
		  if (cplus_mode == CPLUS_PUBLIC) {
		    Stat_func++;
		    if (Verbose) {
		      fprintf(stderr,"Wrapping C++ constructor %s\n", yyvsp[-4].id);
		    }
		    iname = make_name(yyvsp[-4].id);
		    doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		    if (iname == yyvsp[-4].id) iname = 0;
		    cplus_constructor(yyvsp[-4].id,iname, yyvsp[-2].pl);
		  }
		  scanner_clear_start();
		}
		delete yyvsp[-2].pl;
	      ;
    break;}
case 259:
#line 2996 "parser.y"
{
		char *iname;
		if (allow) {
		  init_language();
		  if (cplus_mode == CPLUS_PUBLIC) {
		    Stat_func++;
		    if (Verbose) {
		      fprintf(stderr,"Wrapping C++ destructor %s\n", yyvsp[-4].id);
		    }
		    iname = make_name(yyvsp[-4].id);
		    doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		    if (iname == yyvsp[-4].id) iname = 0;
		    cplus_destructor(yyvsp[-4].id,iname);
		  }
		}
		scanner_clear_start();
	      ;
    break;}
case 260:
#line 3016 "parser.y"
{
 	        char *iname;
		if (allow) {
		  init_language();
		  if (cplus_mode == CPLUS_PUBLIC) {
		    Stat_func++;
		    if (Verbose) {
		      fprintf(stderr,"Wrapping C++ destructor %s\n", yyvsp[-3].id);
		    }
		    iname = make_name(yyvsp[-3].id);
		    doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		    if (iname == yyvsp[-3].id) iname = 0;
		    cplus_destructor(yyvsp[-3].id,iname);
		  }
		}
		scanner_clear_start();
	      ;
    break;}
case 261:
#line 3036 "parser.y"
{
		if (allow) {
		  char *iname;
		  init_language();
		  if (cplus_mode == CPLUS_PUBLIC) {
		    if (Active_type) delete Active_type;
		    Active_type = new DataType(yyvsp[-2].type);
		    yyvsp[-2].type->is_pointer += yyvsp[-1].decl.is_pointer;
		    yyvsp[-2].type->is_reference = yyvsp[-1].decl.is_reference;
		    if (yyvsp[-2].type->qualifier) {
		      if (strcmp(yyvsp[-2].type->qualifier,"const") == 0) {
			// Okay.  This is really some sort of C++ constant here.
	  	          if (yyvsp[0].dtype.type != T_ERROR) {
			    iname = make_name(yyvsp[-1].decl.id);
			    doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
			    if (iname == yyvsp[-1].decl.id) iname = 0;
			    cplus_declare_const(yyvsp[-1].decl.id,iname, yyvsp[-2].type, yyvsp[0].dtype.id);
			  }
		      } else {
			int oldstatus = Status;
			char *tm;
			if (yyvsp[-2].type->status & STAT_READONLY) {
			  if (!(tm = typemap_lookup("memberin",typemap_lang,yyvsp[-2].type,yyvsp[-1].decl.id,"",""))) 
			    Status = Status | STAT_READONLY;
			}
			iname = make_name(yyvsp[-1].decl.id);
			doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
			if (iname == yyvsp[-1].decl.id) iname = 0;
			cplus_variable(yyvsp[-1].decl.id,iname,yyvsp[-2].type);
			Status = oldstatus;
		      }
		    } else {
		      char *tm = 0;
		      int oldstatus = Status;
		      if (yyvsp[-2].type->status & STAT_READONLY) {
			if (!(tm = typemap_lookup("memberin",typemap_lang,yyvsp[-2].type,yyvsp[-1].decl.id,"",""))) 
			  Status = Status | STAT_READONLY;
		      }
		      iname = make_name(yyvsp[-1].decl.id);
		      doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		      if (iname == yyvsp[-1].decl.id) iname = 0;
		      cplus_variable(yyvsp[-1].decl.id,iname,yyvsp[-2].type);
		      Status = oldstatus;
		      if (Verbose) {
			fprintf(stderr,"Wrapping member data %s\n", yyvsp[-1].decl.id);
		      }
		    }
		  }
		  scanner_clear_start();
		}
		delete yyvsp[-2].type;
	      ;
    break;}
case 262:
#line 3087 "parser.y"
{ ;
    break;}
case 263:
#line 3089 "parser.y"
{
		char *iname;
		if (allow) {
		  int oldstatus = Status;
		  char *tm = 0;
		  init_language();
		  if (cplus_mode == CPLUS_PUBLIC) {
		    if (Active_type) delete Active_type;
		    Active_type = new DataType(yyvsp[-3].type);
		    yyvsp[-3].type->is_pointer += yyvsp[-2].decl.is_pointer + 1;
		    yyvsp[-3].type->is_reference = yyvsp[-2].decl.is_reference;
		    yyvsp[-3].type->arraystr = copy_string(ArrayString);
		    if (!(tm = typemap_lookup("memberin",typemap_lang,yyvsp[-3].type,yyvsp[-2].decl.id,"",""))) 
		      Status = STAT_READONLY;

		    iname = make_name(yyvsp[-2].decl.id);
		    doc_entry = new DocDecl(iname, doc_stack[doc_stack_top]);
		    if (iname == yyvsp[-2].decl.id) iname = 0;
		    cplus_variable(yyvsp[-2].decl.id,iname,yyvsp[-3].type);
		    Status = oldstatus;
		    if (!tm)
		      fprintf(stderr,"%s : Line %d. Warning. Array member will be read-only.\n",input_file,line_number);
		  }
		scanner_clear_start();
		}
		delete yyvsp[-3].type;
	      ;
    break;}
case 264:
#line 3120 "parser.y"
{
		char *iname;
		if (allow) {
		  init_language();
		  if (cplus_mode == CPLUS_PUBLIC) {
		    yyvsp[-1].type->is_pointer += yyvsp[0].decl.is_pointer;
		    iname = make_name(yyvsp[0].decl.id);
		    doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		    if (iname == yyvsp[0].decl.id) iname = 0;
		    cplus_static_var(yyvsp[0].decl.id,iname,yyvsp[-1].type);
		    if (Active_type) delete Active_type;
		    Active_type = new DataType(yyvsp[-1].type);
		    if (Verbose) {
		      fprintf(stderr,"Wrapping static member data %s\n", yyvsp[0].decl.id);
		    }
		  }
		  scanner_clear_start();
		}
		delete yyvsp[-1].type;
	      ;
    break;}
case 265:
#line 3139 "parser.y"
{ ;
    break;}
case 266:
#line 3143 "parser.y"
{
		char *iname;
		if (allow) {
		  yyvsp[-5].type->is_pointer += yyvsp[-4].decl.is_pointer;
		  yyvsp[-5].type->is_reference = yyvsp[-4].decl.is_reference;
		  if (cplus_mode == CPLUS_PUBLIC) {
		    iname = make_name(yyvsp[-4].decl.id);
		    doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		    if (iname == yyvsp[-4].decl.id) iname = 0;
		    cplus_static_func(yyvsp[-4].decl.id, iname, yyvsp[-5].type, yyvsp[-2].pl);
		    if (Verbose)
		      fprintf(stderr,"Wrapping static member function %s\n",yyvsp[-4].decl.id);
		  }
		  scanner_clear_start();
		}
		delete yyvsp[-5].type;
		delete yyvsp[-2].pl;
	      ;
    break;}
case 267:
#line 3163 "parser.y"
{
		if (allow) {
		  cplus_mode = CPLUS_PUBLIC;
		  if (Verbose)
		    fprintf(stderr,"Public mode\n");
		  scanner_clear_start();
		}
	      ;
    break;}
case 268:
#line 3174 "parser.y"
{
		if (allow) {
		  cplus_mode = CPLUS_PRIVATE;
		  if (Verbose)
		    fprintf(stderr,"Private mode\n");
		  scanner_clear_start();
		}
	      ;
    break;}
case 269:
#line 3185 "parser.y"
{
		if (allow) {
		  cplus_mode = CPLUS_PROTECTED;
		  if (Verbose)
		    fprintf(stderr,"Protected mode\n");
		  scanner_clear_start();
		}
	      ;
    break;}
case 270:
#line 3196 "parser.y"
{
	       if (allow) {
		 strcpy(yy_rename,yyvsp[-1].id);
		 Rename_true = 1;
	       }
	     ;
    break;}
case 271:
#line 3204 "parser.y"
{
                 NewObject = 1;
             ;
    break;}
case 272:
#line 3206 "parser.y"
{
                 NewObject = 0;
             ;
    break;}
case 273:
#line 3211 "parser.y"
{scanner_clear_start();;
    break;}
case 274:
#line 3211 "parser.y"
{

		 // if ename was supplied.  Install it as a new integer datatype.

		if (allow) {
		  init_language();
		  if (cplus_mode == CPLUS_PUBLIC) {
		   if (yyvsp[-5].id) {
		     cplus_register_type(yyvsp[-5].id);
		     temp_type.type = T_INT;
		     temp_type.is_pointer = 0;
		     temp_type.implicit_ptr = 0;
		     sprintf(temp_type.name,"int");
		     temp_type.typedef_add(yyvsp[-5].id,1); 
		   }
		 }
	       }
	      ;
    break;}
case 275:
#line 3229 "parser.y"
{
		if (allow)
		  Status = Status | STAT_READONLY;
		scanner_clear_start();
              ;
    break;}
case 276:
#line 3234 "parser.y"
{
		if (allow) 
		  Status = Status & ~(STAT_READONLY);
		scanner_clear_start();
	      ;
    break;}
case 277:
#line 3240 "parser.y"
{
		if (allow)
		  fprintf(stderr,"%s : Line %d. Friends are not allowed--members only! (ignored)\n", input_file, line_number);
		skip_decl();
		scanner_clear_start();
	      ;
    break;}
case 278:
#line 3248 "parser.y"
{
		if (allow)
		  fprintf(stderr,"%s : Line %d. Operator overloading not supported (ignored).\n", input_file, line_number);
		skip_decl();
		scanner_clear_start();
	      ;
    break;}
case 279:
#line 3254 "parser.y"
{ 
		scanner_clear_start();
	      ;
    break;}
case 280:
#line 3259 "parser.y"
{ ;
    break;}
case 281:
#line 3263 "parser.y"
{
	      		scanner_clear_start();
	      ;
    break;}
case 282:
#line 3282 "parser.y"
{ start_line = line_number; skip_brace(); 
	      ;
    break;}
case 283:
#line 3283 "parser.y"
{ 

		if (cplus_mode == CPLUS_PUBLIC) {
		  cplus_register_type(yyvsp[-4].id);
		  if (yyvsp[-1].decl.id) {
		    if (strcmp(yyvsp[-5].id,"class") == 0) {
		      fprintf(stderr,"%s : Line %d.  Warning. Nested classes not currently supported (ignored).\n", input_file, line_number);
		      /* Generate some code for a new class */
		    } else {
		      Nested *n = new Nested;
		      n->code << "typedef " << yyvsp[-5].id << " " 
			      << CCode.get() << " $classname_" << yyvsp[-1].decl.id << ";\n";
		      n->name = copy_string(yyvsp[-1].decl.id);
		      n->line = start_line;
		      n->type = new DataType;
		      n->type->type = T_USER;
		      n->type->is_pointer = yyvsp[-1].decl.is_pointer;
		      n->type->is_reference = yyvsp[-1].decl.is_reference;
		      n->next = 0;
		      add_nested(n);
		    }
		  }
		}
	      ;
    break;}
case 284:
#line 3308 "parser.y"
{ start_line = line_number; skip_brace();
              ;
    break;}
case 285:
#line 3309 "parser.y"
{ 
		if (cplus_mode == CPLUS_PUBLIC) {
		  if (strcmp(yyvsp[-4].id,"class") == 0) {
		    fprintf(stderr,"%s : Line %d.  Warning. Nested classes not currently supported (ignored)\n", input_file, line_number);
		    /* Generate some code for a new class */
		  } else {
		    /* Generate some code for a new class */

		    Nested *n = new Nested;
		    n->code << "typedef " << yyvsp[-4].id << " " 
			    << CCode.get() << " $classname_" << yyvsp[-1].decl.id << ";\n";
		    n->name = copy_string(yyvsp[-1].decl.id);
		    n->line = start_line;
		    n->type = new DataType;
		    n->type->type = T_USER;
		    n->type->is_pointer = yyvsp[-1].decl.is_pointer;
		    n->type->is_reference = yyvsp[-1].decl.is_reference;
		    n->next = 0;
		    add_nested(n);

		  }
		}
	      ;
    break;}
case 286:
#line 3333 "parser.y"
{
  		    if (cplus_mode == CPLUS_PUBLIC) {
                       cplus_register_type(yyvsp[-1].id);
                    }
              ;
    break;}
case 287:
#line 3340 "parser.y"
{ 
                     skip_decl();
                     fprintf(stderr,"%s : Line %d. Function pointers not currently supported (ignored).\n", input_file, line_number);
		     
	      ;
    break;}
case 288:
#line 3345 "parser.y"
{
                     skip_decl();
                     fprintf(stderr,"%s : Line %d. Function pointers not currently supported (ignored).\n", input_file, line_number);
		     
	      ;
    break;}
case 289:
#line 3350 "parser.y"
{ 
                     skip_decl();
                     fprintf(stderr,"%s : Line %d. Function pointers not currently supported (ignored).\n", input_file, line_number);
		     
	      ;
    break;}
case 290:
#line 3355 "parser.y"
{ ;
    break;}
case 291:
#line 3358 "parser.y"
{ yyval.decl = yyvsp[0].decl;;
    break;}
case 292:
#line 3359 "parser.y"
{ yyval.decl.id = 0; ;
    break;}
case 293:
#line 3362 "parser.y"
{;
    break;}
case 294:
#line 3363 "parser.y"
{;
    break;}
case 295:
#line 3364 "parser.y"
{;
    break;}
case 296:
#line 3367 "parser.y"
{ ;
    break;}
case 297:
#line 3368 "parser.y"
{
		 if (allow) {
		   int oldstatus = Status;
		   char *tm;

		   init_language();
		   if (cplus_mode == CPLUS_PUBLIC) {
		     temp_typeptr = new DataType(Active_type);
		     temp_typeptr->is_pointer += yyvsp[-1].decl.is_pointer;
		     if (Verbose) {
		       fprintf(stderr,"Wrapping member variable : %s\n",yyvsp[-1].decl.id);
		     }
		     Stat_var++;
		     doc_entry = new DocDecl(yyvsp[-1].decl.id,doc_stack[doc_stack_top]);
		     if (temp_typeptr->status & STAT_READONLY) {
		       if (!(tm = typemap_lookup("memberin",typemap_lang,temp_typeptr,yyvsp[-1].decl.id,"",""))) 
			 Status = Status | STAT_READONLY;
		     }
		     cplus_variable(yyvsp[-1].decl.id,(char *) 0,temp_typeptr);		
		     Status = oldstatus;
		     delete temp_typeptr;
		   }
		   scanner_clear_start();
		 }
	       ;
    break;}
case 298:
#line 3392 "parser.y"
{ ;
    break;}
case 299:
#line 3393 "parser.y"
{
		 if (allow) {
		   int oldstatus = Status;
		   char *tm;

		   init_language();
		   if (cplus_mode == CPLUS_PUBLIC) {
		     temp_typeptr = new DataType(Active_type);
		     temp_typeptr->is_pointer += yyvsp[-2].decl.is_pointer;
		     if (Verbose) {
		       fprintf(stderr,"Wrapping member variable : %s\n",yyvsp[-2].decl.id);
		     }
		     Stat_var++;
		     if (!(tm = typemap_lookup("memberin",typemap_lang,temp_typeptr,yyvsp[-2].decl.id,"",""))) 
		       Status = Status | STAT_READONLY;
		     doc_entry = new DocDecl(yyvsp[-2].decl.id,doc_stack[doc_stack_top]);
		     if (temp_typeptr->status & STAT_READONLY) Status = Status | STAT_READONLY;
		     cplus_variable(yyvsp[-2].decl.id,(char *) 0,temp_typeptr);		
		     Status = oldstatus;
		     if (!tm)
		       fprintf(stderr,"%s : Line %d. Warning. Array member will be read-only.\n",input_file,line_number);
		     delete temp_typeptr;
		   }
		   scanner_clear_start();
		 }
	       ;
    break;}
case 300:
#line 3418 "parser.y"
{ ;
    break;}
case 301:
#line 3421 "parser.y"
{ 
                    CCode = "";
               ;
    break;}
case 302:
#line 3424 "parser.y"
{ skip_brace(); ;
    break;}
case 303:
#line 3427 "parser.y"
{ CCode = ""; ;
    break;}
case 304:
#line 3428 "parser.y"
{ CCode = ""; ;
    break;}
case 305:
#line 3429 "parser.y"
{ skip_brace(); ;
    break;}
case 306:
#line 3432 "parser.y"
{;
    break;}
case 307:
#line 3433 "parser.y"
{;
    break;}
case 308:
#line 3436 "parser.y"
{
                    if (allow) {
		      if (cplus_mode == CPLUS_PUBLIC) {
			if (Verbose) {
			  fprintf(stderr,"Creating enum value %s\n", yyvsp[0].id);
			}
			Stat_const++;
			temp_typeptr = new DataType(T_INT);
			doc_entry = new DocDecl(yyvsp[0].id,doc_stack[doc_stack_top]);
			cplus_declare_const(yyvsp[0].id, (char *) 0, temp_typeptr, (char *) 0);
			delete temp_typeptr;
			scanner_clear_start();
		      }
		    }
                  ;
    break;}
case 309:
#line 3451 "parser.y"
{
		   if (allow) {
		     if (cplus_mode == CPLUS_PUBLIC) {
		       if (Verbose) {
			 fprintf(stderr, "Creating enum value %s = %s\n", yyvsp[-2].id, yyvsp[0].dtype.id);
		       }
		       Stat_const++;
		       temp_typeptr = new DataType(T_INT);
		       doc_entry = new DocDecl(yyvsp[-2].id,doc_stack[doc_stack_top]);
		       cplus_declare_const(yyvsp[-2].id,(char *) 0, temp_typeptr,(char *) 0);
// OLD : Bug with value     cplus_declare_const($1,(char *) 0, temp_typeptr,$3.id);
		       delete temp_typeptr;
		       scanner_clear_start();
		     }
		   }
		 ;
    break;}
case 310:
#line 3467 "parser.y"
{
		   if (allow) {
		     if (cplus_mode == CPLUS_PUBLIC) {
		       if (Verbose) {
			 fprintf(stderr,"Creating enum value %s\n", yyvsp[0].id);
		       }
		       Stat_const++;
		       temp_typeptr = new DataType(T_INT);
		       doc_entry = new DocDecl(yyvsp[-2].id,doc_stack[doc_stack_top]);
		       cplus_declare_const(yyvsp[0].id, yyvsp[-2].id, temp_typeptr, (char *) 0);
		       delete temp_typeptr;
		       scanner_clear_start();
		     }
		   }
		 ;
    break;}
case 311:
#line 3482 "parser.y"
{
		   if (allow) {
		     if (cplus_mode == CPLUS_PUBLIC) {
		       if (Verbose) {
			 fprintf(stderr, "Creating enum value %s = %s\n", yyvsp[-2].id, yyvsp[0].dtype.id);
		       }
		       Stat_const++;
		       temp_typeptr = new DataType(T_INT);
		       doc_entry = new DocDecl(yyvsp[-4].id,doc_stack[doc_stack_top]);
		       cplus_declare_const(yyvsp[-2].id,yyvsp[-4].id, temp_typeptr, (char *) 0);
// Old : bug with value	       cplus_declare_const($5,$3, temp_typeptr,$7.id);
		       delete temp_typeptr;
		       scanner_clear_start();
		     }
		   }
		 ;
    break;}
case 312:
#line 3498 "parser.y"
{ ;
    break;}
case 313:
#line 3499 "parser.y"
{ ;
    break;}
case 314:
#line 3502 "parser.y"
{
		   yyval.ilist = yyvsp[0].ilist;
                ;
    break;}
case 315:
#line 3505 "parser.y"
{
                   yyval.ilist.names = (char **) 0;
		   yyval.ilist.count = 0;
                ;
    break;}
case 316:
#line 3511 "parser.y"
{ 
                   int i;
                   yyval.ilist.names = new char *[NI_NAMES];
		   yyval.ilist.count = 0;
		   for (i = 0; i < NI_NAMES; i++){
		     yyval.ilist.names[i] = (char *) 0;
		   }
                   if (yyvsp[0].id) {
                       yyval.ilist.names[yyval.ilist.count] = copy_string(yyvsp[0].id);
                       yyval.ilist.count++;
		   }
               ;
    break;}
case 317:
#line 3524 "parser.y"
{ 
                   yyval.ilist = yyvsp[-2].ilist;
                   if (yyvsp[0].id) {
		     yyval.ilist.names[yyval.ilist.count] = copy_string(yyvsp[0].id);
		     yyval.ilist.count++;
		   }
               ;
    break;}
case 318:
#line 3533 "parser.y"
{     
                  fprintf(stderr,"%s : Line %d. No access specifier given for base class %s (ignored).\n",
			  input_file,line_number,yyvsp[0].id);
		  yyval.id = (char *) 0;
               ;
    break;}
case 319:
#line 3538 "parser.y"
{ 
                  fprintf(stderr,"%s : Line %d. No access specifier given for base class %s (ignored).\n",
			  input_file,line_number,yyvsp[0].id);
		  yyval.id = (char *) 0;
	       ;
    break;}
case 320:
#line 3543 "parser.y"
{
		 if (strcmp(yyvsp[-1].id,"public") == 0) {
		   yyval.id = yyvsp[0].id;
		 } else {
		   fprintf(stderr,"%s : Line %d. %s inheritance not supported (ignored).\n",
			   input_file,line_number,yyvsp[-1].id);
		   yyval.id = (char *) 0;
		 }
               ;
    break;}
case 321:
#line 3552 "parser.y"
{
		 if (strcmp(yyvsp[-1].id,"public") == 0) {
		   yyval.id = yyvsp[0].id;
		 } else {
		   fprintf(stderr,"%s : Line %d. %s inheritance not supported (ignored).\n",
			   input_file,line_number,yyvsp[-1].id);
		   yyval.id = (char *) 0;
		 }
	       ;
    break;}
case 322:
#line 3561 "parser.y"
{
                 if (strcmp(yyvsp[-2].id,"public") == 0) {
		   yyval.id = yyvsp[0].id;
		 } else {
		   fprintf(stderr,"%s : Line %d. %s inheritance not supported (ignored).\n",
			   input_file,line_number,yyvsp[-2].id);
		   yyval.id = (char *) 0;
		 }
               ;
    break;}
case 323:
#line 3572 "parser.y"
{ yyval.id = "public"; ;
    break;}
case 324:
#line 3573 "parser.y"
{ yyval.id = "private"; ;
    break;}
case 325:
#line 3574 "parser.y"
{ yyval.id = "protected"; ;
    break;}
case 326:
#line 3578 "parser.y"
{ yyval.id = "class"; ;
    break;}
case 327:
#line 3579 "parser.y"
{ yyval.id = "struct"; ;
    break;}
case 328:
#line 3580 "parser.y"
{yyval.id = "union"; ;
    break;}
case 329:
#line 3583 "parser.y"
{;
    break;}
case 330:
#line 3584 "parser.y"
{ delete yyvsp[-1].pl;;
    break;}
case 331:
#line 3585 "parser.y"
{;
    break;}
case 332:
#line 3590 "parser.y"
{ 
                    CCode = "";
               ;
    break;}
case 333:
#line 3593 "parser.y"
{ skip_brace(); ;
    break;}
case 334:
#line 3596 "parser.y"
{;
    break;}
case 335:
#line 3597 "parser.y"
{;
    break;}
case 336:
#line 3600 "parser.y"
{ ;
    break;}
case 337:
#line 3601 "parser.y"
{ ;
    break;}
case 338:
#line 3604 "parser.y"
{ ;
    break;}
case 339:
#line 3605 "parser.y"
{ ;
    break;}
case 340:
#line 3608 "parser.y"
{ ;
    break;}
case 341:
#line 3609 "parser.y"
{ ;
    break;}
case 342:
#line 3617 "parser.y"
{ 
                   ObjCClass = 1;
                   init_language();
		   cplus_mode = CPLUS_PROTECTED;
		   sprintf(temp_name,"CPP_CLASS:%s\n",yyvsp[-1].id);
		   if (add_symbol(temp_name,(DataType *) 0, (char *) 0)) {
		     fprintf(stderr,"%s : Line %d.  @interface %s is multiple defined.\n",
			     input_file,line_number,yyvsp[-1].id);
		     FatalError();
		   }
		   // Create a new documentation entry
		   doc_entry = new DocClass(yyvsp[-1].id,doc_parent());
		   doc_stack_top++;
		   doc_stack[doc_stack_top] = doc_entry;
		   scanner_clear_start();
		   cplus_open_class(yyvsp[-1].id, (char *) 0, "");     // Open up a new C++ class
                ;
    break;}
case 343:
#line 3633 "parser.y"
{ 
		  if (yyvsp[-6].id) {
		      char *inames[1];
		      inames[0] = yyvsp[-6].id;
		      cplus_inherit(1,inames);
		  }
		  // Restore original doc entry for this class
		  doc_entry = doc_stack[doc_stack_top];
		  cplus_class_close(yyvsp[-7].id);
		  doc_entry = 0;
		  doc_stack_top--;
		  cplus_mode = CPLUS_PUBLIC;
		  ObjCClass = 0;
		  delete yyvsp[-7].id;
		  delete yyvsp[-6].id;
                ;
    break;}
case 344:
#line 3650 "parser.y"
{
                 ObjCClass = 1;
		 init_language();
                 cplus_mode = CPLUS_PROTECTED;
                 doc_entry = cplus_set_class(yyvsp[-4].id);
		 if (!doc_entry) {
		   doc_entry = new DocClass(yyvsp[-4].id,doc_parent());
		 }
		 doc_stack_top++;
		 doc_stack[doc_stack_top] = doc_entry;
		 scanner_clear_start();
	       ;
    break;}
case 345:
#line 3661 "parser.y"
{
                 cplus_unset_class();
                 doc_entry = 0;
                 doc_stack_top--;
               ;
    break;}
case 346:
#line 3666 "parser.y"
{ skip_to_end(); ;
    break;}
case 347:
#line 3667 "parser.y"
{ skip_to_end(); ;
    break;}
case 348:
#line 3668 "parser.y"
{
		 char *iname = make_name(yyvsp[-2].id);
                 init_language();
                 lang->cpp_class_decl(yyvsp[-2].id,iname,"");
		 for (int i = 0; i <yyvsp[-1].ilist.count; i++) {
		   if (yyvsp[-1].ilist.names[i]) {
		     iname = make_name(yyvsp[-1].ilist.names[i]);
		     lang->cpp_class_decl(yyvsp[-1].ilist.names[i],iname,"");
		     delete [] yyvsp[-1].ilist.names[i];
		   }
		 } 
		 delete [] yyvsp[-1].ilist.names;
	       ;
    break;}
case 349:
#line 3683 "parser.y"
{ yyval.id = yyvsp[-1].id;;
    break;}
case 350:
#line 3684 "parser.y"
{ yyval.id = 0; ;
    break;}
case 351:
#line 3688 "parser.y"
{ skip_template(); 
                   CCode.strip();           // Strip whitespace
		   CCode.replace("<","< ");
		   CCode.replace(">"," >");
                   yyval.id = CCode.get();
                 ;
    break;}
case 352:
#line 3694 "parser.y"
{
                   yyval.id = "";
               ;
    break;}
case 353:
#line 3699 "parser.y"
{ ;
    break;}
case 354:
#line 3700 "parser.y"
{ 
                    cplus_mode = CPLUS_PUBLIC;
                 ;
    break;}
case 355:
#line 3702 "parser.y"
{ ;
    break;}
case 356:
#line 3703 "parser.y"
{
                    cplus_mode = CPLUS_PRIVATE;
                 ;
    break;}
case 357:
#line 3705 "parser.y"
{ ;
    break;}
case 358:
#line 3706 "parser.y"
{ 
                    cplus_mode = CPLUS_PROTECTED;
                 ;
    break;}
case 359:
#line 3708 "parser.y"
{ ;
    break;}
case 360:
#line 3709 "parser.y"
{
		 if (!Error) {
		   skip_decl();
		   {
		     static int last_error_line = -1;
		     if (last_error_line != line_number) {
		       fprintf(stderr,"%s : Line %d. Syntax error in input.\n", input_file, line_number);
		       FatalError();
		       last_error_line = line_number;
		     }
		     Error = 1;
		   }
		 }
	       ;
    break;}
case 361:
#line 3722 "parser.y"
{ ;
    break;}
case 362:
#line 3723 "parser.y"
{ ;
    break;}
case 363:
#line 3726 "parser.y"
{
  
                ;
    break;}
case 364:
#line 3733 "parser.y"
{ 
                 if (cplus_mode == CPLUS_PUBLIC) {
		   int oldstatus = Status;
		   char *tm;
		   char *iname;
		   if (Active_type) delete Active_type;
		   Active_type = new DataType(yyvsp[-1].type);
		   yyvsp[-1].type->is_pointer += yyvsp[0].decl.is_pointer;
		   yyvsp[-1].type->is_reference = yyvsp[0].decl.is_reference;
		   if (yyvsp[-1].type->status & STAT_READONLY) {
		     if (!(tm = typemap_lookup("memberin",typemap_lang,yyvsp[-1].type,yyvsp[0].decl.id,"",""))) 
		       Status = Status | STAT_READONLY;
		   }
		   iname = make_name(yyvsp[0].decl.id);
		   doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		   if (iname == yyvsp[0].decl.id) iname = 0;
		   cplus_variable(yyvsp[0].decl.id,iname,yyvsp[-1].type);
		   Status = oldstatus; 
		 }
		 scanner_clear_start();
		 delete yyvsp[-1].type;
               ;
    break;}
case 365:
#line 3755 "parser.y"
{ 
		 if (cplus_mode == CPLUS_PUBLIC) {
		   int oldstatus = Status;
		   char *tm, *iname;
		   if (Active_type) delete Active_type;
		   Active_type = new DataType(yyvsp[-2].type);
		   yyvsp[-2].type->is_pointer += yyvsp[-1].decl.is_pointer;
		   yyvsp[-2].type->is_reference = yyvsp[-1].decl.is_reference;
		   yyvsp[-2].type->arraystr = copy_string(ArrayString);
		   if (yyvsp[-2].type->status & STAT_READONLY) {
		     if (!(tm = typemap_lookup("memberin",typemap_lang,yyvsp[-2].type,yyvsp[-1].decl.id,"",""))) 
		       Status = Status | STAT_READONLY;
		   }
		   iname = make_name(yyvsp[-1].decl.id);
		   doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		   if (iname == yyvsp[-1].decl.id) iname = 0;
		   cplus_variable(yyvsp[-1].decl.id,iname,yyvsp[-2].type);
		   Status = oldstatus; 
		 }
		 scanner_clear_start();
		 delete yyvsp[-2].type;
	       ;
    break;}
case 366:
#line 3777 "parser.y"
{
                    strcpy(yy_rename,yyvsp[-1].id);
                    Rename_true = 1;
	       ;
    break;}
case 367:
#line 3780 "parser.y"
{ ;
    break;}
case 368:
#line 3782 "parser.y"
{ 
                 if (cplus_mode == CPLUS_PUBLIC) {
		   int oldstatus = Status;
		   char *tm, *iname;
		   DataType *t = new DataType (Active_type);
		   t->is_pointer += yyvsp[-1].decl.is_pointer;
		   t->is_reference = yyvsp[-1].decl.is_reference;
		   if (t->status & STAT_READONLY) {
		     if (!(tm = typemap_lookup("memberin",typemap_lang,t,yyvsp[-1].decl.id,"",""))) 
		       Status = Status | STAT_READONLY;
		   }
		   iname = make_name(yyvsp[-1].decl.id);
		   doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		   if (iname == yyvsp[-1].decl.id) iname = 0;
		   cplus_variable(yyvsp[-1].decl.id,iname,t);
		   Status = oldstatus; 
		   delete t;
		 }
		 scanner_clear_start();
               ;
    break;}
case 369:
#line 3802 "parser.y"
{
		 char *iname;
                 if (cplus_mode == CPLUS_PUBLIC) {
		   int oldstatus = Status;
		   char *tm;
		   DataType *t = new DataType (Active_type);
		   t->is_pointer += yyvsp[-2].decl.is_pointer;
		   t->is_reference = yyvsp[-2].decl.is_reference;
		   t->arraystr = copy_string(ArrayString);
		   if (t->status & STAT_READONLY) {
		     if (!(tm = typemap_lookup("memberin",typemap_lang,t,yyvsp[-2].decl.id,"",""))) 
		       Status = Status | STAT_READONLY;
		   }
		   iname = make_name(yyvsp[-2].decl.id);
		   doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		   if (iname == yyvsp[-2].decl.id) iname = 0;
		   cplus_variable(yyvsp[-2].decl.id,iname,t);
		   Status = oldstatus; 
		   delete t;
		 }
		 scanner_clear_start();
               ;
    break;}
case 370:
#line 3824 "parser.y"
{ ;
    break;}
case 371:
#line 3827 "parser.y"
{ ;
    break;}
case 372:
#line 3828 "parser.y"
{
                   AddMethods = 1;
	       ;
    break;}
case 373:
#line 3830 "parser.y"
{
                   AddMethods = 0;
               ;
    break;}
case 374:
#line 3833 "parser.y"
{
                     strcpy(yy_rename,yyvsp[-1].id);
                     Rename_true = 1;
	       ;
    break;}
case 375:
#line 3836 "parser.y"
{ ;
    break;}
case 376:
#line 3837 "parser.y"
{
                 skip_decl();		                
		 if (!Error) {
		   {
		     static int last_error_line = -1;
		     if (last_error_line != line_number) {
		       fprintf(stderr,"%s : Line %d. Syntax error in input.\n", input_file, line_number);
		       FatalError();
		       last_error_line = line_number;
		     }
		     Error = 1;
		   }
		 }
	       ;
    break;}
case 377:
#line 3850 "parser.y"
{ ;
    break;}
case 378:
#line 3851 "parser.y"
{ ;
    break;}
case 379:
#line 3854 "parser.y"
{
                 char *iname;
                 // An objective-C instance function
                 // This is like a C++ member function

		 if (strcmp(yyvsp[-2].id,objc_destruct) == 0) {
		   // This is an objective C destructor
                   doc_entry = new DocDecl(yyvsp[-2].id,doc_stack[doc_stack_top]);
                   cplus_destructor(yyvsp[-2].id,(char *) 0);
		 } else {
		   iname = make_name(yyvsp[-2].id);
		   doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		   if (iname == yyvsp[-2].id) iname = 0;
		   cplus_member_func(yyvsp[-2].id,iname,yyvsp[-3].type,yyvsp[-1].pl,0);
		   scanner_clear_start();
		   delete yyvsp[-3].type;
		   delete yyvsp[-2].id;
		   delete yyvsp[-1].pl;
		 }
               ;
    break;}
case 380:
#line 3874 "parser.y"
{ 
                 char *iname;
                 // An objective-C class function
                 // This is like a c++ static member function
                 if (strcmp(yyvsp[-2].id,objc_construct) == 0) {
		   // This is an objective C constructor
		   doc_entry = new DocDecl(yyvsp[-2].id,doc_stack[doc_stack_top]);
                   cplus_constructor(yyvsp[-2].id,0,yyvsp[-1].pl);
		 } else {
		   iname = make_name(yyvsp[-2].id);
		   doc_entry = new DocDecl(iname,doc_stack[doc_stack_top]);
		   if (iname == yyvsp[-2].id) iname = 0;
		   cplus_static_func(yyvsp[-2].id,iname,yyvsp[-3].type,yyvsp[-1].pl);
		 }
                 scanner_clear_start();
                 delete yyvsp[-3].type;
                 delete yyvsp[-2].id;
                 delete yyvsp[-1].pl;
               ;
    break;}
case 381:
#line 3895 "parser.y"
{ CCode = ""; ;
    break;}
case 382:
#line 3896 "parser.y"
{ skip_brace(); ;
    break;}
case 383:
#line 3899 "parser.y"
{ 
                  yyval.type = yyvsp[-1].type;
                ;
    break;}
case 384:
#line 3902 "parser.y"
{ 
                  yyval.type = yyvsp[-2].type;
                  yyval.type->is_pointer += yyvsp[-1].ivalue;
               ;
    break;}
case 385:
#line 3906 "parser.y"
{       /* Empty type means "id" type */
                  yyval.type = new DataType(T_VOID);
		  sprintf(yyval.type->name,"id");
                  yyval.type->is_pointer = 1;
                  yyval.type->implicit_ptr = 1;
               ;
    break;}
case 386:
#line 3914 "parser.y"
{ 
                  yyval.type = new DataType(yyvsp[-1].p->t);
                  delete yyvsp[-1].p;
                 ;
    break;}
case 387:
#line 3918 "parser.y"
{ 
                  yyval.type = new DataType(T_VOID);
		  sprintf(yyval.type->name,"id");
                  yyval.type->is_pointer = 1;
                  yyval.type->implicit_ptr = 1;
               ;
    break;}
case 388:
#line 3926 "parser.y"
{ 
                   Parm *p= new Parm(yyvsp[-1].type,yyvsp[0].id);
		   p->objc_separator = yyvsp[-2].id;
                   yyval.pl = yyvsp[-3].pl;
                   yyval.pl->append(p);
               ;
    break;}
case 389:
#line 3932 "parser.y"
{ 
                 yyval.pl = new ParmList;
               ;
    break;}
case 390:
#line 3937 "parser.y"
{ yyval.id = copy_string(":"); ;
    break;}
case 391:
#line 3938 "parser.y"
{ yyval.id = new char[strlen(yyvsp[-1].id)+2]; 
                    strcpy(yyval.id,yyvsp[-1].id);
		    strcat(yyval.id,":");
		    delete yyvsp[-1].id;
	        ;
    break;}
case 392:
#line 3949 "parser.y"
{
                    yyval.dlist = yyvsp[0].dlist;
		    yyval.dlist.names[yyval.dlist.count] = copy_string(yyvsp[-2].id);
		    yyval.dlist.values[yyval.dlist.count] = copy_string(yyvsp[-1].id);
		    format_string(yyval.dlist.values[yyval.dlist.count]);
		    yyval.dlist.count++;
                 ;
    break;}
case 393:
#line 3959 "parser.y"
{
                    yyval.dlist = yyvsp[-3].dlist;
		    yyval.dlist.names[yyval.dlist.count] = copy_string(yyvsp[-1].id);
		    yyval.dlist.values[yyval.dlist.count] = copy_string(yyvsp[0].id);
		    format_string(yyval.dlist.values[yyval.dlist.count]);
		    yyval.dlist.count++;
                 ;
    break;}
case 394:
#line 3966 "parser.y"
{
                    yyval.dlist.names = new char *[NI_NAMES];
		    yyval.dlist.values = new char *[NI_NAMES];
		    yyval.dlist.count = 0;
	       ;
    break;}
case 395:
#line 3973 "parser.y"
{
                     yyval.id = yyvsp[0].id;
                 ;
    break;}
case 396:
#line 3976 "parser.y"
{
                     yyval.id = yyvsp[0].id;
	       ;
    break;}
case 397:
#line 3979 "parser.y"
{ 
                     yyval.id = 0;
                ;
    break;}
case 398:
#line 3989 "parser.y"
{
                 yyval.id = yyvsp[0].id;
               ;
    break;}
case 399:
#line 3992 "parser.y"
{
                 yyval.id = copy_string("const");
               ;
    break;}
case 400:
#line 3997 "parser.y"
{
                 yyval.tmparm = yyvsp[-1].tmparm;
                 yyval.tmparm->next = yyvsp[0].tmparm;
		;
    break;}
case 401:
#line 4003 "parser.y"
{
                 yyval.tmparm = yyvsp[-1].tmparm;
                 yyval.tmparm->next = yyvsp[0].tmparm;
                ;
    break;}
case 402:
#line 4007 "parser.y"
{ yyval.tmparm = 0;;
    break;}
case 403:
#line 4010 "parser.y"
{
		    if (InArray) {
		      yyvsp[-1].type->is_pointer++;
		      yyvsp[-1].type->arraystr = copy_string(ArrayString);
		    }
		    yyval.tmparm = new TMParm;
                    yyval.tmparm->p = new Parm(yyvsp[-1].type,yyvsp[0].id);
		    yyval.tmparm->p->call_type = 0;
		    yyval.tmparm->args = tm_parm;
		    delete yyvsp[-1].type;
		    delete yyvsp[0].id;
                 ;
    break;}
case 404:
#line 4023 "parser.y"
{
		  yyval.tmparm = new TMParm;
		   yyval.tmparm->p = new Parm(yyvsp[-2].type,yyvsp[0].id);
		   yyval.tmparm->p->t->is_pointer += yyvsp[-1].ivalue;
		   yyval.tmparm->p->call_type = 0;
		   if (InArray) {
		     yyval.tmparm->p->t->is_pointer++;
		     yyval.tmparm->p->t->arraystr = copy_string(ArrayString);
		    }
		   yyval.tmparm->args = tm_parm;
		   delete yyvsp[-2].type;
		   delete yyvsp[0].id;
		;
    break;}
case 405:
#line 4037 "parser.y"
{
                  yyval.tmparm = new TMParm;
		  yyval.tmparm->p = new Parm(yyvsp[-2].type,yyvsp[0].id);
		  yyval.tmparm->p->t->is_reference = 1;
		  yyval.tmparm->p->call_type = 0;
		  yyval.tmparm->p->t->is_pointer++;
		  if (!CPlusPlus) {
			fprintf(stderr,"%s : Line %d. Warning.  Use of C++ Reference detected.  Use the -c++ option.\n", input_file, line_number);
		  }
		  yyval.tmparm->args = tm_parm;
		  delete yyvsp[-2].type;
		  delete yyvsp[0].id;
		;
    break;}
case 406:
#line 4050 "parser.y"
{
                  fprintf(stderr,"%s : Line %d. Error. Function pointer not allowed (remap with typedef).\n", input_file, line_number);
		  FatalError();
                  yyval.tmparm = new TMParm;
		  yyval.tmparm->p = new Parm(yyvsp[-7].type,yyvsp[-4].id);
		  yyval.tmparm->p->t->type = T_ERROR;
		  yyval.tmparm->p->name = copy_string(yyvsp[-4].id);
		  strcpy(yyval.tmparm->p->t->name,"<function ptr>");
		  yyval.tmparm->args = tm_parm;
		  delete yyvsp[-7].type;
		  delete yyvsp[-4].id;
		  delete yyvsp[-1].pl;
		;
    break;}
case 407:
#line 4065 "parser.y"
{
                    yyval.id = yyvsp[-1].id; 
                    InArray = 0;
                ;
    break;}
case 408:
#line 4069 "parser.y"
{ 
                    ArrayBackup = "";
		    ArrayBackup << ArrayString;
                  ;
    break;}
case 409:
#line 4072 "parser.y"
{
                    yyval.id = yyvsp[-3].id;
                    InArray = yyvsp[-2].ivalue;
                    ArrayString = "";
		    ArrayString << ArrayBackup;
                ;
    break;}
case 410:
#line 4078 "parser.y"
{ 
                    ArrayBackup = "";
		    ArrayBackup << ArrayString;
		;
    break;}
case 411:
#line 4081 "parser.y"
{
		    yyval.id = new char[1];
		    yyval.id[0] = 0;
		    InArray = yyvsp[-2].ivalue;
                    ArrayString = "";
                    ArrayString << ArrayBackup;
		;
    break;}
case 412:
#line 4088 "parser.y"
{ yyval.id = new char[1];
  	                  yyval.id[0] = 0;
                          InArray = 0;
                ;
    break;}
case 413:
#line 4094 "parser.y"
{
                  tm_parm = yyvsp[-1].pl;
                ;
    break;}
case 414:
#line 4097 "parser.y"
{
                  tm_parm = 0;
                ;
    break;}
case 415:
#line 4102 "parser.y"
{yyval.id = yyvsp[0].id;;
    break;}
case 416:
#line 4103 "parser.y"
{ yyval.id = yyvsp[0].id;;
    break;}
case 417:
#line 4109 "parser.y"
{ ;
    break;}
case 418:
#line 4110 "parser.y"
{ ;
    break;}
case 419:
#line 4113 "parser.y"
{ ;
    break;}
case 420:
#line 4114 "parser.y"
{ ;
    break;}
case 421:
#line 4115 "parser.y"
{ ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "/usr/lib/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 4149 "parser.y"


void error_recover() {
  int c;
  c = yylex();
  while ((c > 0) && (c != SEMI)) 
    c = yylex();
}

/* Called by the parser (yyparse) when an error is found.*/
void yyerror (char *) {
  //  Fprintf(stderr,"%s : Line %d. Syntax error.\n", input_file, line_number);
  //  error_recover();
}

/*******************************************************************************
 * --- Revision history
 * $Log: parser.y,v $
 * Revision 1.78  1997/07/27 20:30:28  beazley
 * Fixed parsing problem with unsigned long int.
 *
 * Revision 1.77  1997/07/14 03:57:51  beazley
 * Eliminated use of malloc/free
 *
 * Revision 1.76  1997/06/29 17:09:23  beazley
 * Reverted back to old version
 *
 * Revision 1.74  1997/06/23 21:22:45  beazley
 * Eliminated compiler warnings.
 *
 * Revision 1.73  1997/06/23 19:19:36  beazley
 * Fixed some Objective-C parsing problems.  Added %doconly directive.
 *
 * Revision 1.72  1997/06/22 19:21:42  beazley
 * Fixed the import directive.
 *
 * Revision 1.71  1997/06/20 05:23:16  beazley
 * Fixed some bugs related to Objective-C parsing.
 *
 * Revision 1.70  1997/06/17 04:46:30  beazley
 * Tons of parser improvements.  Better error reporting. Cleanup
 * in a few places.
 *
 * Revision 1.69  1997/05/28 06:01:01  beazley
 * Moved revision history to end.
 *
 * Revision 1.68  1997/05/28 05:42:34  beazley
 * Added some template support.  Minor improvements to Objective-C support.
 *
 * Revision 1.67  1997/05/25 23:04:46  beazley
 * Added Objective-C support.
 *
 * Revision 1.66  1997/05/24 04:18:35  beazley
 * Minor changes
 *
 * Revision 1.65  1997/05/05 16:01:57  beazley
 * Whoops. Minor bug fix.
 *
 * Revision 1.64  1997/05/05 15:53:22  beazley
 * Added support for parameterized typemaps.  Also added new directives
 * %apply and %clear.
 *
 * Revision 1.63  1997/04/19 21:59:38  beazley
 * Added the %new directive
 *
 * Revision 1.62  1997/03/29 17:41:04  beazley
 * Improved error handling.
 *
 * Revision 1.61  1997/03/16 21:25:56  beazley
 * Fixed a few bugs in the documentation system.
 *
 * Revision 1.60  1997/03/08 19:22:31  beazley
 * Added better support for multidimensional arrays.
 * Fixed some typedef problems and miscellaneous C++ parsing
 * problems.   Unfortunately introduced one shift-reduce conflict
 * due to the C++ scope resolution operator "::".
 *
 * Revision 1.59  1997/02/19 23:02:07  beazley
 * Added support for exception handling.
 *
 * Revision 1.58  1997/01/17 06:12:42  beazley
 * Fixed obscure memory management problem.
 *
 * Revision 1.57  1997/01/15 05:44:17  beazley
 * Changed implementation of typedef slightly.
 * Modified C++ to allow typedef inside a class.
 * Added support for scope resolution operator.
 *
 * Revision 1.56  1997/01/09 21:16:51  beazley
 * Minor fixes
 *
 * Revision 1.55  1997/01/06 17:13:45  beazley
 * Added typemaps and multiple inheritance.
 * Somewhat better support for arrays added
 *
 * Revision 1.54  1996/12/26 04:46:16  beazley
 * Added a bunch of support for inlined code.
 * First cut at nested classes.
 *
 * Revision 1.53  1996/12/03 08:40:06  beazley
 * Added typedef lists.
 * pre-1.1b2 checkin
 *
 * Revision 1.52  1996/12/03 05:38:38  beazley
 * Many minor changes and bug fixes to documentation system
 *
 * Revision 1.51  1996/11/26 04:09:20  beazley
 * Fixes to support new documentation system
 *
 * Revision 1.50  1996/11/12 19:55:07  beazley
 * Major improvements across the board.
 *       -  Support for new documentation system
 *       -  New CPP support
 *       -  Added casts to expressions
 *       -  Allowed conditional compilation inside enums
 *       -  A few new error messages
 *
 * Revision 1.49  1996/10/30 07:19:35  beazley
 * Fixed minor memory problem handling parameters of function
 * pointers.
 *
 * Revision 1.48  1996/10/29 19:23:41  beazley
 * Added support for new parameter list handling code.   Also took a
 * a stab at improving SWIG's memory efficiency although many
 * internal memory leaks still remain... sigh.
 *
 * Revision 1.47  1996/10/22 16:43:33  beazley
 * Added support for 'bool' type (from David Fletcher)
 *
 * Revision 1.46  1996/10/07 23:00:18  beazley
 * Added support for ignoring CPP macros.  A few minor
 * changes for better preprocessor handling.
 *
 * Revision 1.45  1996/10/07 20:05:35  beazley
 * Removed requirement that interface files start with the
 * header block.
 *
 * Revision 1.44  1996/09/26 21:48:20  dmb
 * Somewhat better C parsing.  Added support for %extern directive
 *
 * Revision 1.43  1996/09/16 22:57:57  dmb
 * First cut at %extern directive
 *
 * Revision 1.42  1996/09/11 20:10:08  dmb
 * Now ignores static declarations.  Added support for skipping
 * over default arguments set to complex structures.
 *
 * Revision 1.41  1996/08/27 22:59:45  dmb
 * Minor change to error handling.
 *
 * Revision 1.40  1996/08/26 23:35:10  dmb
 * Added super-secret %addmethods directive.
 *
 * Revision 1.39  1996/08/25 00:03:56  dmb
 * Added %pragma directive
 *
 * Revision 1.38  1996/08/21 16:49:24  dmb
 * Minor cleanup to eliminate compiler warnings.  Minor bug fixes.
 *
 * Revision 1.37  1996/08/21 05:49:11  dmb
 * Made lots of changes to improve C++ parsing.   Fixed a few minor
 * bugs.  Added some more error checking.
 *
 * Revision 1.36  1996/08/15 05:06:00  dmb
 * More cleanup.  Add feature to emit typedefs when using %typedef.
 * Also added support for "&" when creating constants.
 *
 * Revision 1.35  1996/08/12 01:53:43  dmb
 * Major changes.  Cleanup up type-handling, added more C++ support.
 * Lot's of bug fixes (and hopefully not too many new bugs).
 *
 * Revision 1.34  1996/06/18 16:29:57  dmb
 * Fixed ALLOC definition.
 *
 * Revision 1.33  1996/06/18 15:33:27  dmb
 * Fixed external linkage of yylex and yyerror (maybe)
 *
 * Revision 1.32  1996/06/16 02:28:13  beazley
 * A few minor bug fixes with constants
 *
 * Revision 1.31  1996/06/14  19:56:28  beazley
 * Added check for C++ mode
 *
 * Revision 1.30  1996/06/02  00:16:41  beazley
 * More C++ bug fixes
 *
 * Revision 1.29  1996/05/28  23:17:48  beazley
 * Added arrays, check for pointers to functions
 *
 * Revision 1.28  1996/05/22  20:24:44  beazley
 * More cleanup.  Somewhat improved error handling.
 *
 * Revision 1.27  1996/05/20  23:37:41  beazley
 * Lot's of improvements.  Added more constant types.  Fixed bugs in C++.
 * Cleaned things up---added a few missing rules.
 *
 * Revision 1.26  1996/05/17  19:54:49  beazley
 * Changed error message
 *
 * Revision 1.25  1996/05/17  05:54:40  beazley
 * Changes too numerous to mention.  Lots of bug fixes.  More support
 * for odd syntax and header file parsing.
 *
 * Revision 1.24  1996/05/13  23:44:39  beazley
 * Substantial changes to clean things up abit.
 *
 * Revision 1.23  1996/05/10  23:39:59  beazley
 * Added some improved documentation handling.
 * Added enum and %name directives for C++.
 *
 * Revision 1.22  1996/05/09  22:34:55  beazley
 * Added structs and a little more C++
 *
 * Revision 1.21  1996/05/07  14:42:25  beazley
 * Added C++ reference (&) symbol.  SWIG interprets it quite
 * literally which may lead to confusion.  Need to think about
 * it some more.
 *
 * Revision 1.20  1996/05/06  23:10:52  beazley
 * Added even more C++ support.
 *
 * Revision 1.19  1996/05/03  22:29:51  dmb
 * Preliminary C++ support.
 *
 * Revision 1.18  1996/04/16 17:07:09  dmb
 * Fixed minor problem with free().
 *
 * Revision 1.17  1996/04/14 15:25:34  dmb
 * Fixed header files.
 *
 * Revision 1.16  1996/04/08 19:44:34  beazley
 * Added support for constant expressions and enums.
 *
 * Revision 1.15  1996/04/07  20:31:25  beazley
 * Cleaned up a few things.  Added support for enums.
 *
 * Revision 1.14  1996/04/03  22:49:43  beazley
 * Minor improvements
 *
 * Revision 1.13  1996/03/28  06:32:52  beazley
 * Oops.  Screwed up the %typedef directive, but fixed it again.
 *
 * Revision 1.12  1996/03/28  02:49:21  beazley
 * Minor changes to %typedef rule.
 *
 * Revision 1.11  1996/03/22  23:44:29  beazley
 * Major changes. Cleaned up error messages.   Improved handling
 * of constants.  Took out some obsolete directives.
 *
 * Revision 1.10  1996/03/16  06:30:59  beazley
 * Major changes.   Better error messages, does more.
 *
 * Revision 1.9  1996/03/04  21:30:38  beazley
 * Changed the way documentation is handled.
 *
 * Revision 1.8  1996/02/19  05:32:11  beazley
 * Cleaned up a few things.
 *
 * Revision 1.7  1996/02/17  23:38:14  beazley
 * Fixed problem with documentation system.
 *
 * Revision 1.6  1996/02/16  06:39:18  beazley
 * Fixed a few things related to using YACC.
 *
 * Revision 1.5  1996/02/15  22:34:42  beazley
 * Changed copyright notice.  Added %typedef directive.
 *
 * Revision 1.4  1996/02/07  05:21:34  beazley
 * Radical changes in parser.   Now allows lists of variables and functions.
 * Supports the new documentation system.
 *
 * Revision 1.3  1996/01/16  00:56:25  beazley
 * Minor changes
 *
 * Revision 1.2  1996/01/05  22:40:27  dmb
 * *** empty log message ***
 *
 * Revision 1.1  1995/12/30 04:33:51  dmb
 * Initial revision
 *
 *
 *******************************************************************************/

