/* A *very* simple "widget" structure */

typedef double (*CALLBACK)(double, void *);
typedef struct {
    CALLBACK method;
    void     *clientdata;
} Widget;

extern Widget *new_widget();
extern void    widget_add_callback(Widget *w, CALLBACK c, void *);
extern double  widget_op(Widget *w, double a);
