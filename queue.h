//queue using linked list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <row.h>

struct queue{
    struct row *head;
    struct queue *next;
};


void queue_construct(struct queue **q){
    *q = (struct queue *)malloc(sizeof(struct queue));
    (*q)->head = NULL;
    (*q)->next = NULL;
}

void InsertNewNodeinQueue(struct row r, struct queue **q){
    struct queue *temp = (struct queue *)malloc(sizeof(struct queue));
    row_contruct(r.int_values, r.double_values, r.char_values, r.string_values, &temp->head);
    temp->next = NULL;
    if((*q)->head == NULL){
        (*q)->head = temp->head;
        (*q)->next = temp->next;
    }
    else{
        struct queue *temp1 = (*q);
        while(temp1->next != NULL){
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
}