#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"

//funzioni AUX
IndexNodeString* createIndexNodeString(char* string, Persona* persona) {
    IndexNodeString *node = malloc(sizeof(IndexNodeString));
    if (node == NULL) {
        return NULL;
    } 
    node->value = string;
    node->person = persona;
    node->left = NULL;
    node->right = NULL;
    return node;
}
IndexNodeInt* createIndexNodeInt(int i, Persona* persona) {
    IndexNodeInt *node = malloc(sizeof(IndexNodeInt));
    if (node == NULL) {
        return NULL;
    } 
    node->value = i;
    node->person = persona;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void print_tree_string(IndexNodeString * root) {
    if (root == NULL) {
        return;
    }
    print_tree_string(root->left);
    printf("%s\n", root->value);
    print_tree_string(root->right);
}
void print_tree_int(IndexNodeInt * root) {
    if (root == NULL) {
        return;
    }
    print_tree_int(root->left);
    printf("%d\n", root->value);
    print_tree_int(root->right);
}
//
int insertByName(IndexNodeString* node, Persona* persona){
    if (node == NULL) {
        return 0;
    }
    if (strcmp(persona->name, node->value) <= 0) {
        if (node->left == NULL) {
            IndexNodeString *newNode = createIndexNodeString(persona->name, persona); 
            node->left = newNode;
            return 1;
        }
        return insertByName(node->left, persona);
        
    }
    if (node->right == NULL) {
        IndexNodeString *newNode = createIndexNodeString(persona->name, persona);
        node->right = newNode;
        return 1;
    }
    return insertByName(node->right, persona);
}
int insertBySurname(IndexNodeString* node, Persona* persona){
    if (node == NULL) {
        return 0;
    }
    if (strcmp(persona->surname, node->value) <= 0) { //se str1 è minore o uguale di str2
        if (node->left == NULL) {
            IndexNodeString *newNode = createIndexNodeString(persona->surname, persona); 
            node->left = newNode;
            return 1;
        }
        return insertBySurname(node->left, persona);
        
    }
    if (node->right == NULL) {
        IndexNodeString *newNode = createIndexNodeString(persona->surname, persona);
        node->right = newNode;
        return 1;
    }
    return insertBySurname(node->right, persona);
}
int insertByAddress(IndexNodeString* node, Persona* persona){
    if (node == NULL) {
        return 0;
    }
    if (strcmp(persona->address, node->value) <= 0) {
        if (node->left == NULL) {
            IndexNodeString *newNode = createIndexNodeString(persona->address, persona); 
            node->left = newNode;
            return 1;
        }
        return insertByAddress(node->left, persona);
        
    }
    if (node->right == NULL) {
        IndexNodeString *newNode = createIndexNodeString(persona->address, persona);
        node->right = newNode;
        return 1;
    }
    return insertByAddress(node->right, persona);
}
int insertByAge(IndexNodeInt* node, Persona* persona){
    if (node == NULL) {
        return 0;
    }
    if (persona->age <= node->value) {
        if (node->left == NULL) {
            IndexNodeInt *newNode = createIndexNodeInt(persona->age, persona); 
            node->left = newNode;
            return 1;
        }
        return insertByAge(node->left, persona);
        
    }
    if (node->right == NULL) {
        IndexNodeString *newNode = createIndexNodeInt(persona->age, persona);
        node->right = newNode;
        return 1;
    }
    return insertByAge(node->right, persona);
}

Persona* findByNameRecursive(IndexNodeString* root, char* name){
    if (root == NULL) return NULL; //base case
    if (strcmp(root->value, name) == 0) return root->person; //base case
    else if (strcmp(root->value, name) < 0) return findByNameRecursive(root->left, name); //recursive case
    else return findByNameRecursive(root->right, name); //recursive case
}
Persona* findBySurnameRecursive(IndexNodeString* root, char* surname){
    if (root == NULL) return NULL; //base case
    if (strcmp(root->value, surname) == 0) return root->person; //base case
    else if (strcmp(root->value, surname) < 0) return findBySurnameRecursive(root->left, surname); //recursive case
    else return findBySurnameRecursive(root->right, surname); //recursive case
}
Persona* findByAddressRecursive(IndexNodeString* root, char* address){
    if (root == NULL) return NULL; //base case
    if (strcmp(root->value, address) == 0) return root->person; //base case
    else if (strcmp(root->value, address) < 0) return findByAddressRecursive(root->left, address); //recursive case
    else return findByAddressRecursive(root->right, address); //recursive case
}
Persona* findByAgeRecursive(IndexNodeInt* root, int age){
    if (root == NULL) return NULL; //base case
    if ((root->value - age) == 0) return root->person; //base case
    else if ((root->value - age) < 0) return findByAgeRecursive(root->left, age); //recursive case
    else return findByAgeRecursive(root->right, age); //recursive case
}

//funzioni TODO
void insert(Database * database, Persona * persona){
    if (!insertByName(database->name, persona)) printf("inserimento by name FALLITO");
    if (!insertBySurname(database->surname, persona)) printf("inserimento by surname FALLITO");
    if (!insertByAddress(database->address, persona)) printf("inserimento by address FALLITO");
    if (!insertByAge(database->age, persona)) printf("inserimento by age FALLITO");
}
Persona* findByName(Database * database, char * name){
    return findByNameRecursive(database->name, name);
}
Persona* findBySurname(Database * database, char * surname){
    return findBySurnameRecursive(database->surname, surname);
}
Persona* findByAddress(Database * database, char * address){
    return findByAddressRecursive(database->address, address);
}   
Persona* findByAge(Database * database, int age){
    return findByAgeRecursive(database->age, age);
}

Persona* create_person(const char* name, const char* surname, const char* address, int age) {
    Persona* p = malloc(sizeof(Persona));
    p->name = strdup(name); //alloca dinamicamente p->name con una copia di name
    p->surname = strdup(surname);
    p->address = strdup(address);
    p->age = age;
    return p;
}
void free_person(Persona* p) {
    if (p == NULL) return;
    free(p->name);
    free(p->surname);
    free(p->address);
    free(p);
}


void free_tree_int(IndexNodeInt* root){
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
void free_tree_string(IndexNodeString* root){
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
void free_database(Database* database){
    free_tree_string(database->name);
    free_tree_string(database->surname);
    free_tree_string(database->address);
    free_tree_int(database->age);
    free(database);
}