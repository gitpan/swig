
// ------------------------------------------------------------------------
// A very simple SWIG Language module
//
// ------------------------------------------------------------------------

class MYLANG : public Language {
private:
  char             *module;          // Name of the module
public :
  MYLANG() {
    module = 0;
  };

  // Virtual functions required by the SWIG parser

  void parse_args(int, char *argv[]);
  void parse();
  void create_function(char *, char *, DataType *, ParmList *);
  void link_variable(char *, char *, DataType *);
  void declare_const(char *, char *, DataType *, char *);
  void initialize(void);
  void headers(void);
  void close(void);
  void set_module(char *,char **);
  void create_command(char *, char *);
};






