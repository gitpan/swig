#include <stdio.h>

#include "widget.h"

/* Create a new widget */

Widget *new_widget() {
  Widget *w;
  w = (Widget *) malloc(sizeof(Widget));
  w->method = 0;
  w->clientdata = 0;
};

/* Register a callback function with the widget */

void widget_add_callback(Widget *w, CALLBACK callback, void *clientdata) {
  w->method = callback;
  w->clientdata = clientdata;
};

/* Perform a widget operation */

double widget_op(Widget *w, double a) {
  if (w->method)
    return (w->method)(a, w->clientdata);
  else 
    printf("Error! No callback function specified!\n");
  return 0;
}





