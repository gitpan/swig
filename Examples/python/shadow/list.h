class List {
  private:
  struct node {
    	char *value;
	node *next;
  };
  node *head;
  node *z;
  public:
    List();
    ~List();
    void insert(char *value);
    int search(char *value);
    char *get(int i);
    void output();
};

