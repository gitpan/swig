/* File : array.i */
%module array

%inline %{

double *new_double(int s) {
	double *a = (double *) malloc(s*sizeof(double));
	return a;
}

void delete_double(double *a) {
	free(a);
}

double get_double(double *a, int index) {
	return a[index];
}

void set_double(double *a, int index, double val) {
	a[index] = val;
}

float *new_float(int size) {
	return (float *) malloc(size*sizeof(float));
}

void delete_float(float *a) {
	free(a);
}

float get_float(float *a, int index) {
	return a[index];
}

void set_float(float *a, int index, float val) {
	a[index] = val;
}

int *new_int(int size) {
	return (int *) malloc(size*sizeof(int));
}

void delete_int(int *a) {
	free(a);
}

int get_int(int *a, int index) {
	return a[index];
}

int set_int(int *a, int index, int val) {
	a[index] = val;
}
%}


