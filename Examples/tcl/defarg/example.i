/* File : example.i */
%module example

extern int    print_error(int code, char *message = 0);
extern void   set_range(int width, int height, double xmin=-1.0,double xmax=1.0,
                        double ymin=-1, double ymax = 1);


