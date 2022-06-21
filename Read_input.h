#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "File_instruction.h"

struct LineList *read_file(char *filename)
{
    // read file line wise
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    // read file line wise
    char line[1024];
    struct LineList *list = (struct LineList *)malloc(sizeof(struct LineList));
    list->length = 0;
    while (fgets(line, 1024, fp) != NULL)
    {
        // printf("%s\n", line);
        struct Line NewLine = string_to_array(line);
        if (NewLine.Length != 0)
        {
            insert_line(list, NewLine);
            /* printf("%d\n", NewLine.Length);
             for (int i = 0; i < NewLine.Length; i++){
                 printf("%s %d\n", NewLine.words[i], i);
             }*/
            // printf("\n");
            // printf("%d\n", list->length);
            /* if (list->length!= 0){
                 for (int i = 0; i < list->head->line.Length; i++){
                     printf("%s ", list->head->line.words[i]);
                 }
                 printf("\n");
                 for (int i = 0; i < list->tail->line.Length; i++){
                     printf("%s ", list->tail->line.words[i]);
                 }
                 printf("\n");
             }*/
        }
    }
    fclose(fp);
    return list;
}

/*int main(int argc, char *argv[])
{
    // read file
    struct LineList *list = read_file("Test.txt");
    struct LineListNode *current = list->head;
    int r = 0;
    while (current != NULL)
    {
        for (int i = 0; i < current->line.Length; i++)
        {
            printf("%d %d %s\n", r, i, current->line.words[i]);
        }
        r++;
        current = current->next;
    }
    delete_line_list(list);
    return 0;
}*/