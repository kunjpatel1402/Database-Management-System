#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "temp_tree.h"

struct table
{
    int int_fields;
    int double_fields;
    int char_fields;
    int string_fields;
    char** int_fields_name;
    char** double_fields_name;
    char** char_fields_name;
    char** string_fields_name;
    struct MyAVLManager *manager;
};

void table_construct(int int_fields, int double_fields, int char_fields, int string_fields, struct table *new_table){
    new_table->int_fields = int_fields;
    new_table->double_fields = double_fields;
    new_table->char_fields = char_fields;
    new_table->string_fields = string_fields;
    new_table->int_fields_name = (char**)malloc(int_fields * sizeof(char*));
    new_table->double_fields_name = (char**)malloc(double_fields * sizeof(char*));
    new_table->char_fields_name = (char**)malloc(char_fields * sizeof(char*));
    new_table->string_fields_name = (char**)malloc(string_fields * sizeof(char*));
    struct MyAVLManager *manager1 = myAVLManager_construct();
    new_table->manager = manager1;
}

void insert_into_table(struct table* myTable, struct row new_row){
    avl_insert(myTable->manager, new_row);
}

void replace_in_table(struct table* myTable, int col, char* replace_value, int sr_no){
    replace(myTable->manager, col, replace_value, sr_no);
}

void delete_in_table(struct table* myTable, int sr_no){
    avl_delete(myTable->manager, sr_no);
}

void search_in_table(struct table* myTable,char* search_value, int col){
    search(myTable->manager, search_value, col);
}

void sort_table(struct table* myTable, int col){
    printf("\n");
    printf("Sr_no\t");
    for (int i = 0; i < myTable->int_fields; i++)
    {
        printf("%s\t\t", myTable->int_fields_name[i]);
    }
    for (int i = 0; i < myTable->double_fields; i++)
    {
        printf("%s\t\t", myTable->double_fields_name[i]);
    }
    for (int i = 0; i < myTable->char_fields; i++)
    {
        printf("%s\t\t", myTable->char_fields_name[i]);
    }
    for (int i = 0; i < myTable->string_fields; i++)
    {
        printf("%s\t\t", myTable->string_fields_name[i]);
    }
    printf("\n");
    sort_rows(myTable->manager, col);
}
void print_table(struct table* myTable){
    printf("\n");
    printf("Sr_no\t");
    for (int i = 0; i < myTable->int_fields; i++){
        printf("%s\t\t", myTable->int_fields_name[i]);
    }
    for (int i = 0; i < myTable->double_fields; i++)
    {
        printf("%s\t\t", myTable->double_fields_name[i]);
    }
    for (int i = 0; i < myTable->char_fields; i++)
    {
        printf("%s\t\t", myTable->char_fields_name[i]);
    }
    for (int i = 0; i < myTable->string_fields; i++)
    {
        printf("%s\t\t", myTable->string_fields_name[i]);
    }
    avl_print(myTable->manager);
}