
#include "swig.h"
#include "matlab.h"

//-----------------------------------------------------------------
// main()
//
// Main program.    Initializes the files and starts the parser.
//-----------------------------------------------------------------

int main(int argc, char **argv) {

  int i;

  Language *dl = new MATLAB;
  extern int SWIG_main(int, char **, Language *, Documentation *);

  init_args(argc,argv);

  SWIG_main(argc,argv,dl,0);
  return 0;
}
