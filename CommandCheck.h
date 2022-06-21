#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table.h"
//#include "row.h"
//#include "File_instructions.h"
#include "Read_input.h"
#include <sys/types.h>
#include "checker.h"
#include <sys/wait.h>
#include <unistd.h>


struct table get_Table(char *file_name,bool *created)
{
    struct LineList *list = read_file(file_name);
    struct LineListNode *current = list->head;
    int r = 0;
    struct table myTable;
    table_construct(0, 0, 0, 0, &myTable);
    // printf("%d\n", list->length);
    int cnt = 0;
    while (current != NULL)
    {
        if (current->line.Length != 0)
        {
            if (strcmp(current->line.words[0], "create") == 0)
            {
                *created = true;
                table_construct(atoi(current->line.words[1]), atoi(current->line.words[2]), atoi(current->line.words[3]), atoi(current->line.words[4]), &myTable);
                for (int j = 0; j < myTable.int_fields; j++)
                {
                    myTable.int_fields_name[j] = (char *)malloc(sizeof(char) * strlen(current->line.words[j + 5]));
                    strcpy(myTable.int_fields_name[j], current->line.words[j + 5]);
                    // strcpy(current->line.words[j + 5], myTable.int_fields_name[j]);
                    //  printf("%s\t",current->line.words[j+5]);
                }
                for (int j = 0; j < myTable.double_fields; j++)
                {
                    myTable.double_fields_name[j] = (char *)malloc(sizeof(char) * strlen(current->line.words[j + 5 + myTable.int_fields]));
                    strcpy(myTable.double_fields_name[j], current->line.words[j + 5 + myTable.int_fields]);
                    // strcpy(current->line.words[j + 5 + myTable.int_fields], myTable.double_fields_name[j]);
                    //  printf("%s\t",current->line.words[j+5+myTable.int_fields]);
                }
                for (int j = 0; j < myTable.char_fields; j++)
                {
                    myTable.char_fields_name[j] = (char *)malloc(sizeof(char) * strlen(current->line.words[j + 5 + myTable.int_fields + myTable.double_fields]));
                    strcpy(myTable.char_fields_name[j], current->line.words[j + 5 + myTable.int_fields + myTable.double_fields]);
                    // strcpy(current->line.words[j + 5 + myTable.int_fields + myTable.double_fields], myTable.char_fields_name[j]);
                    //   printf("%s\t",current->line.words[j+5+myTable.int_fields+myTable.double_fields]);
                }
                for (int j = 0; j < myTable.string_fields; j++)
                {
                    myTable.string_fields_name[j] = (char *)malloc(sizeof(char) * strlen(current->line.words[j + 5 + myTable.int_fields + myTable.double_fields + myTable.char_fields]));
                    strcpy(myTable.string_fields_name[j], current->line.words[j + 5 + myTable.int_fields + myTable.double_fields + myTable.char_fields]);
                    // strcpy(current->line.words[j + 5 + myTable.int_fields + myTable.double_fields + myTable.char_fields], myTable.string_fields_name[j]);
                    //  printf("%s\t",current->line.words[j+5+myTable.int_fields+myTable.double_fields+myTable.char_fields]);
                }
                goto here;
            }
            if (!created){
                printf("PLease create a Table\n");
                return myTable;
            }
            if (strcmp(current->line.words[0], "insert") == 0)
            {

                struct row new_row;
                row_contruct(myTable.int_fields, myTable.double_fields, myTable.char_fields, myTable.string_fields, &new_row, myTable.manager->mysize);
                for (int j = 0; j < myTable.int_fields; j++)
                {
                    new_row.int_values[j] = atoi(current->line.words[j + 1]);
                }
                for (int j = 0; j < myTable.double_fields; j++)
                {
                    new_row.double_values[j] = atof(current->line.words[j + 1 + myTable.int_fields]);
                }
                for (int j = 0; j < myTable.char_fields; j++)
                {
                    new_row.char_values[j] = current->line.words[j + 1 + myTable.int_fields + myTable.double_fields][0];
                }
                for (int j = 0; j < myTable.string_fields; j++)
                {
                    new_row.string_values[j] = (char *)malloc(sizeof(char) * strlen(current->line.words[j + 1 + myTable.int_fields + myTable.double_fields + myTable.char_fields]));
                    new_row.string_values[j] = current->line.words[j + 1 + myTable.int_fields + myTable.double_fields + myTable.char_fields];
                }
                // new_row.sr_no = myTable.no_of_rows;
                insert_into_table(&myTable, new_row); // remaining
            }
            else if (strcmp(current->line.words[0], "change") == 0)
            {
                char *replace_value = current->line.words[1];
                int sr_no = atoi(current->line.words[2]);
                int col = atoi(current->line.words[3]);
                // replace
                replace_in_table(&myTable, col, replace_value, sr_no);
            }
            else if (strcmp(current->line.words[0], "delete") == 0)
            {
                int sr_no = atoi(current->line.words[1]);
                // delete_row(atoi(current->line.words[1]),&myTable);
                delete_in_table(&myTable, sr_no);
            }
            else if (strcmp(current->line.words[0], "search") == 0)
            {
                char *search_value = current->line.words[1];
                int col = atoi(current->line.words[2]);
                // search_value(atoi(current->line.words[1]),current->line.words[2],&myTable);
                // column no,value
                search_in_table(&myTable, search_value, col);
            }
            else if (strcmp(current->line.words[0], "sort") == 0)
            {
                int col = atoi(current->line.words[1]);
                // sort(atoi(current->line.words[1]),atoi(current->line.words[2]),&myTable);
                sort_table(&myTable, col);
            }
            else if (strcmp(current->line.words[0], "print") == 0)
            {
                print_table(&myTable);
            }
            else
            {
                printf("Invalid command\n");
            }
            //print_table(&myTable);
        }
        here:{;}
        r++;
        current = current->next;
        cnt++;
    }
    delete_line_list(list);
    return myTable;
}


void Exec_Command(struct table* myTable, char** commands, int len, char* filename, bool* created){
    /*printf("%s %d\n",commands[0], len);
    for (int i = 0; i <= len; i++){
        printf("%s|",commands[i]);
    }*/
    len++;
    //printf("File_: %s", filename);

    if (strcmp(commands[0], "create") == 0)
    {   //printf("1");
        printf("ok");
        if(len>=5){    
            if(!(is_int(commands[1]) && is_int(commands[2]) && is_int(commands[3]) && is_int(commands[4]))){
                printf("Invalid command\n");
                return;
            }
            int int_fields = atoi(commands[1]);
            int double_fields = atoi(commands[2]);
            int char_fields = atoi(commands[3]);
            int string_fields = atoi(commands[4]);
            if ((len) != 5 + int_fields + double_fields + char_fields + string_fields){
                printf("Invalid command\n");
                return;
            }
        }
        else{
            printf("Invalid command\n");
            return;
        }
        *created=true;
        table_construct(atoi(commands[1]), atoi(commands[2]), atoi(commands[3]), atoi(commands[4]), myTable);
        for (int j = 0; j < myTable->int_fields; j++)
        {
            myTable->int_fields_name[j] = (char *)malloc(sizeof(char) * strlen(commands[j + 5]));
            strcpy(myTable->int_fields_name[j], commands[j + 5]);
            // strcpy(commands[j + 5], myTable.int_fields_name[j]);
            //  printf("%s\t",commands[j+5]);
        }
        for (int j = 0; j < myTable->double_fields; j++)
        {
            myTable->double_fields_name[j] = (char *)malloc(sizeof(char) * strlen(commands[j + 5 + myTable->int_fields]));
            strcpy(myTable->double_fields_name[j], commands[j + 5 + myTable->int_fields]);
            // strcpy(commands[j + 5 + myTable->int_fields], myTable->double_fields_name[j]);
            //  printf("%s\t",commands[j+5+myTable->int_fields]);
        }
        for (int j = 0; j < myTable->char_fields; j++)
        {
            myTable->char_fields_name[j] = (char *)malloc(sizeof(char) * strlen(commands[j + 5 + myTable->int_fields + myTable->double_fields]));
            strcpy(myTable->char_fields_name[j], commands[j + 5 + myTable->int_fields + myTable->double_fields]);
            // strcpy(commands[j + 5 + myTable->int_fields + myTable->double_fields], myTable->char_fields_name[j]);
            //   printf("%s\t",commands[j+5+myTable->int_fields+myTable->double_fields]);
        }
        for (int j = 0; j < myTable->string_fields; j++)
        {
            myTable->string_fields_name[j] = (char *)malloc(sizeof(char) * strlen(commands[j + 5 + myTable->int_fields + myTable->double_fields + myTable->char_fields]));
            strcpy(myTable->string_fields_name[j], commands[j + 5 + myTable->int_fields + myTable->double_fields + myTable->char_fields]);
            // strcpy(commands[j + 5 + myTable->int_fields + myTable->double_fields + myTable->char_fields], myTable->string_fields_name[j]);
            //  printf("%s\t",commands[j+5+myTable->int_fields+myTable->double_fields+myTable->char_fields]);
        }
        return;
    }
    if (!created){
        printf("PLease create a Table\n");
        return;
    }
    if (strcmp(commands[0], "insert") == 0)
    {
        //printf("2");
        struct row new_row;
        row_contruct(myTable->int_fields, myTable->double_fields, myTable->char_fields, myTable->string_fields, &new_row, myTable->manager->mysize);
        //printf("ok");
        if (len != myTable->int_fields + myTable->double_fields + myTable->char_fields + myTable->string_fields + 1)
        {
            printf("Invalid command\n");
            return ;
        }
        for (int j = 0; j < myTable->int_fields; j++)
        {
            new_row.int_values[j] = atoi(commands[j + 1]);
        }
        for (int j = 0; j < myTable->double_fields; j++)
        {
            new_row.double_values[j] = atof(commands[j + 1 + myTable->int_fields]);
        }
        for (int j = 0; j < myTable->char_fields; j++)
        {
            new_row.char_values[j] = commands[j + 1 + myTable->int_fields + myTable->double_fields][0];
        }
        for (int j = 0; j < myTable->string_fields; j++)
        {
            new_row.string_values[j] = (char *)malloc(sizeof(char) * strlen(commands[j + 1 + myTable->int_fields + myTable->double_fields + myTable->char_fields]));
            new_row.string_values[j] = commands[j + 1 + myTable->int_fields + myTable->double_fields + myTable->char_fields];
        }
        // new_row.sr_no = myTable->no_of_rows;
        insert_into_table(myTable, new_row); // remaining
    }
    else if (strcmp(commands[0], "change") == 0)
    {
        //printf("3");
        if((len)!=4){
            printf("Invalid command\n");
            return ;
        }
        char *replace_value = commands[1];
        int sr_no = atoi(commands[2]);
        int col = atoi(commands[3]);
        //if ()
        // replace
        replace_in_table(myTable, col, replace_value, sr_no);
    }
    else if (strcmp(commands[0], "delete") == 0)
    {
        //printf("4");
        if((len)!=2){
            printf("Invalid command\n");
            return ;
        }
        int sr_no = atoi(commands[1]);
        // delete_row(atoi(commands[1]),&myTable);
        delete_in_table(myTable, sr_no);
    }
    else if (strcmp(commands[0], "search") == 0)
    {
        //printf("5");
        if((len)!=3){
            printf("Invalid command\n");
            return;
        }
        char *search_value = commands[1];
        int col = atoi(commands[2]);
        // search_value(atoi(commands[1]),commands[2],&myTable);
        // column no,value
        search_in_table(myTable, search_value, col);
    }
    else if (strcmp(commands[0], "sort") == 0)
    {
        //printf("6");
        if((len)!=2){
            printf("Invalid command\n");
            return;
        }
        int col = atoi(commands[1]);
        // sort(atoi(commands[1]),atoi(commands[2]),&myTable);
        sort_table(myTable, col);
    }
    else if (strcmp(commands[0], "print") == 0)
    {
        //printf("7");
        print_table(myTable);
    }
    else
    {
        printf("Invalid command\n");
    }
    //print_table(myTable);
}