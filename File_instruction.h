#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct Line
{
    char **words;
    int Length;
};

// doubly linked list
struct LineListNode
{
    struct LineListNode *next;
    struct LineListNode *prev;
    struct Line line;
};

struct LineList
{
    struct LineListNode *head;
    struct LineListNode *tail;
    int length;
};

// count words in string
int count_words(char *str)
{
    int count = 0;
    int i = 0;
    int prev = 0;
    while (str[i] != '\0')
    {
        if (isspace(str[i]) || str[i] == '\n' || str[i] == '\0')
        {
            if (i > prev)
            {
                count++;
                prev = i + 1;
            }
            else
            {
                prev = i + 1;
            }
        }
        i++;
    }
    return count;
}

// convert string to array of words
struct Line string_to_array(char *str)
{
    int count = count_words(str);
    struct Line NewLine;
    NewLine.words = (char **)malloc(sizeof(char *) * count);
    NewLine.Length = count;
    int i = 0;
    int j = 0;
    int index = 0;
    while (str[i] != '\0')
    {
        if (isspace(str[i]) || str[i] == '\n' || str[i] == '\0')
        {
            NewLine.words[index] = (char *)malloc(sizeof(char) * (i - j + 1));
            int k = 0;
            if (i - j)
            {
                while (k < i - j)
                {
                    NewLine.words[index][k] = str[k + j];
                    // printf("%c", NewLine.words[j][k]);
                    k++;
                }
                NewLine.words[index][k] = '\0';
                // printf("%d %d \n",i, index);
                // printf("%d ", i);
                j = i + 1;
                index++;
            }
        }
        i++;
    }
    if (isspace(str[i]) || str[i] == '\n' || str[i] == '\0')
    {
        NewLine.words[index] = (char *)malloc(sizeof(char) * (i - j + 1));
        int k = 0;
        if (i - j)
        {
            while (k < i - j)
            {
                NewLine.words[index][k] = str[k + j];
                // printf("%c", NewLine.words[j][k]);
                k++;
            }
            NewLine.words[index][k] = '\0';
            // printf("%d %d \n",i, index);
            // printf("%d ", i);
            j = i + 1;
            index++;
        }
    }
    /* printf("%d\n",count);
     for (int i = 0; i < count; i++){
         printf("%s %d\n", NewLine.words[i], i);
     }*/
    return NewLine;
}

// insert in line list
void insert_line(struct LineList *list, struct Line line)
{
    struct LineListNode *new_node = (struct LineListNode *)malloc(sizeof(struct LineListNode));
    new_node->line = line;
    new_node->next = NULL;
    new_node->prev = NULL;
    if (list->length == 0)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    list->length++;
}

// delete full line list
void delete_line_list(struct LineList *list)
{
    struct LineListNode *current = list->head;
    struct LineListNode *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}
