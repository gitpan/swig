// ---------------------------------------------------------------------
// A simple SWIG Language module
// ---------------------------------------------------------------------

#include "swig.h"
#include "lang.h"

// ---------------------------------------------------------------------
// MYLANG::parse_args(int argc, char *argv[])
//
// Parse command line options and initializes variables.
// ---------------------------------------------------------------------
void MYLANG::parse_args(int argc, char *argv[]) {
  printf("Getting command line options\n");
  typemap_lang = "mylang";

}

// ---------------------------------------------------------------------
// void MYLANG::parse()
//
// Start parsing an interface file.
// ---------------------------------------------------------------------
void MYLANG::parse() {
  fprintf(stderr,"Making wrappers for My Language\n");
  headers();
  yyparse();       // Run the SWIG parser
}

// ---------------------------------------------------------------------
// MYLANG::set_module(char *mod_name,char **mod_list)
//
// Sets the module name.  Does nothing if it's already set (so it can
// be overriddent as a command line option).
//
// mod_list is a NULL-terminated list of additional modules.  This
// is really only useful when building static executables.
//----------------------------------------------------------------------

void MYLANG::set_module(char *mod_name, char **mod_list) {
  if (module) return;
  module = new char[strlen(mod_name)+1];
  strcpy(module,mod_name);
}

// ----------------------------------------------------------------------
// MYLANG::headers(void)
//
// Generate the appropriate header files for MYLANG interface.
// ----------------------------------------------------------------------
void MYLANG::headers(void) {
  emit_banner(f_header); // Print the SWIG banner message
  fprintf(f_header,"/* Implementation : My Language */\n\n");
}

// ---------------------------------------------------------------------
// MYLANG::initialize(void)
//
// Produces an initialization function.   Assumes that the init function
// name has already been specified.
// ---------------------------------------------------------------------
void MYLANG::initialize() {
  // Start generating the initialization function
  fprintf(f_init,"int %s_initialize() {\n", module);
}

// ---------------------------------------------------------------------
// MYLANG::close(void)
//
// Finish the initialization function. Close any additional files and
// resources in use.
// ---------------------------------------------------------------------
void MYLANG::close(void) {
  // Finish off our init function
  fprintf(f_init,"}\n");
}

// ---------------------------------------------------------------------
// MYLANG::create_command(char *cname, char *iname)
//
// Creates a new command from a C function.
// cname = Name of the C function
//iname = Name of function in scripting language
// ---------------------------------------------------------------------
void MYLANG::create_command(char *cname, char *iname) {
  fprintf(f_init,"\t Creating command %s\n", iname);
}

// ---------------------------------------------------------------------
// MYLANG::create_function(char *name, char *iname, DataType *d, ParmList *l)
//
// Create a function declaration and register it with the interpreter.
//name = Name of real C function
//iname = Name of function in scripting language
//d = Return datatype
//l = Function parameters
// ---------------------------------------------------------------------
void MYLANG::create_function(char *name, char *iname, DataType *d, ParmList *l) {
  fprintf(f_wrappers,"\nwrap_%s() { }\n\n", name);
  create_command(name,iname);
}


// ---------------------------------------------------------------------
// MYLANG::link_variable(char *name, char *iname, DataType *t)
//
// Create a link to a C variable.
//name = Name of C variable
//iname = Name of variable in scripting language
//t = Datatype of the variable
// ---------------------------------------------------------------------
void MYLANG::link_variable(char *name, char *iname, DataType *t) {
  fprintf(f_init,"\t Linking variable : %s\n", iname);
}

// ---------------------------------------------------------------------
// MYLANG::declare_const(char *name, char *iname, DataType *type, char *value)
//
// Makes a constant. 
//name = Name of the constant
// iname = Scripting language name of constant
//type = Datatype of the constant
//value = Constant value (as a string)
// ---------------------------------------------------------------------
void MYLANG::declare_const(char *name, char *iname, DataType *type, char *value) {
  fprintf(f_init,"\t Creating constant : %s = %s\n", name, value);
}

