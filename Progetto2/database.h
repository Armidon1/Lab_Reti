
// This represent a record in the only schema of this database
typedef struct Persona {
    char name[20];
    char surname[50];
    char address[100];
    int age;
} Persona;

// This is a node of an index that hold a string
typedef struct IndexNodeString {
    char * value;
    Persona* person; //added this poiter associated to his value
    struct IndexNodeString * left;
    struct IndexNodeString * right;
} IndexNodeString;

// This is a node of an index that hold an int
typedef struct IndexNodeInt {
    int value;
    Persona* person; //added this poiter associated to his value
    struct IndexNodeInt * left;
    struct IndexNodeInt * right;
} IndexNodeInt;

// A database hold a set of records and a set of indexes
typedef struct {
    IndexNodeString * name;
    IndexNodeString * surname;
    IndexNodeString * address;
    IndexNodeInt * age;
} Database;

//AUX
IndexNodeString* createIndexNodeString(char* string, Persona* persona);
IndexNodeInt* createIndexNodeInt(int i, Persona* persona);
void print_tree_string(IndexNodeString * root);
void print_tree_int(IndexNodeInt * root);
int insertByName(IndexNodeString* node, Persona* persona);
int insertBySurname(IndexNodeString* node, Persona* persona);
int insertByAddress(IndexNodeString* node, Persona* persona);
int insertByAge(IndexNodeInt* node, Persona* persona);

Persona* findByNameRecursive(IndexNodeString* root, char* name);
Persona* findBySurnameRecursive(IndexNodeString* root, char* surname);
Persona* findByAddressRecursive(IndexNodeString* root, char* address);
Persona* findByAgeRecursive(IndexNodeInt* root, int age);

// TODO implement the following methods
// The method return a Persona or NULL 

void insert(Database * database, Persona * persona);
Persona* findByName(Database * database, char * name);
Persona* findBySurname(Database * database, char * surname);
Persona* findByAddress(Database * database, char * address);
Persona* findByAge(Database * database, int age);

Persona* create_person(const char* name, const char* surname, const char* address, int age);
void free_person(Persona* p);

void free_tree(IndexNodeInt* root);
void free_tree(IndexNodeString* root);
void free_database(Database* database);