// This file shows how one can access array members of structures and
// classes.

%module arraymember
%{

typedef struct {
	char    name[32];
	int     numbers[100];
} Arrays;

%}

// Now here's some SWIG code for the above

typedef struct {
	Arrays();
	~Arrays();
	%addmethods {
		char *name;
		int numbers_get(int index);
		int numbers_set(int index, int value);
	}
} Arrays;

%{
char * Arrays_name_get(Arrays *a) {
	return &a->name[0];
}

char * Arrays_name_set(Arrays *a, char *value) {
	if (strlen(value) < 32)
		strcpy(a->name,value);
	else
		printf("Name '%s' too long!\n", value);
	return &a->name[0];
}

int Arrays_numbers_get(Arrays *a, int index) {
	if ((index >= 0) && (index < 100))
		return a->numbers[index];
	else
		printf("Index out of range.\n");
	return 0;
};

int Arrays_numbers_set(Arrays *a, int index, int value) {
	if ((index >= 0) && (index < 100))
		return a->numbers[index] = value;
	else 
		printf("Index out of range.\n");
	return 0;
};
%}

