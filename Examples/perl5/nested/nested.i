// Handling of a simple nested structure

%module nested

// A Typemap to safely set a char [] member.

%typemap(memberin) char[ANY] {
	strncpy($target,$source,$dim0);
}

%inline %{
typedef struct {  
                  unsigned int dataType;
                  union {
			int       intval;
			double    doubleval;
			char     *charval;
			void     *ptrvalue;
			long      longval;
			struct {
                               int    i;
			       double f;
                               void   *v;
  			       char name[32];

                        } v;
		} u;
} ValueStruct;

/* Create a new structure */

ValueStruct *new_value(unsigned int type) {
	ValueStruct *v;
	v = (ValueStruct *) malloc(sizeof(ValueStruct));
	v->dataType = type;
	return v;
}

%}
	
