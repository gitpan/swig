// Very simple C++ examples

class List {
private:
  struct node {
    char *value;
    node *next;
  };
  struct node *head, *z;
public:
  List();
  ~List();
  int  search(char *value);
  void insert(char *);
  void remove(char *);
  char *get(int n);
  int  length;
static void print(List *l);
static void print1(List &l);
};



  
      
