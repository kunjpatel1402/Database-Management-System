#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>



struct row
{
    long long int sr_no;
    int no_of_int_values;
    int no_of_double_values;
    int no_of_char_values;
    int no_of_string_values;
    long long int *int_values;
    double *double_values;
    char *char_values;
    char **string_values;
};

void row_contruct(int int_fields, int double_fields, int char_fields, int string_fields, struct row *new_row, long long int last_srno)
{
    //printf("ok1");
    new_row->sr_no = last_srno+1;
    new_row->int_values = (long long int *)malloc(int_fields * sizeof(long long int));
    new_row->double_values = (double *)malloc(double_fields * sizeof(double));
    new_row->char_values = (char *)malloc(char_fields * sizeof(char));
    new_row->string_values = (char **)malloc(string_fields * sizeof(char *));
    new_row->no_of_int_values = int_fields;
    new_row->no_of_double_values = double_fields;
    new_row->no_of_char_values = char_fields;
    new_row->no_of_string_values = string_fields;

}

//copy row
void row_copy(struct row *dest, const struct row *src)
{
    dest->sr_no = src->sr_no;
    dest->no_of_int_values = src->no_of_int_values;
    dest->no_of_double_values = src->no_of_double_values;
    dest->no_of_char_values = src->no_of_char_values;
    dest->no_of_string_values = src->no_of_string_values;
    dest->int_values = (long long int *)malloc(src->no_of_int_values * sizeof(long long int));
    dest->double_values = (double *)malloc(src->no_of_double_values * sizeof(double));
    dest->char_values = (char *)malloc(src->no_of_char_values * sizeof(char));
    dest->string_values = (char **)malloc(src->no_of_string_values * sizeof(char *));
    for (int i = 0; i < src->no_of_int_values; i++)
    {
        dest->int_values[i] = src->int_values[i];
    }
    for (int i = 0; i < src->no_of_double_values; i++)
    {
        dest->double_values[i] = src->double_values[i];
    }
    for (int i = 0; i < src->no_of_char_values; i++)
    {
        dest->char_values[i] = src->char_values[i];
    }
    for (int i = 0; i < src->no_of_string_values; i++)
    {
        dest->string_values[i] = (char *)malloc(strlen(src->string_values[i]) * sizeof(char));
        strcpy(dest->string_values[i], src->string_values[i]);
    }
}
//print row
void row_print(struct row *row)
{
    printf("%lld\t", row->sr_no);
   /* printf("%d\t", row->no_of_int_values);
    printf("%d\t", row->no_of_double_values);
    printf("%d\t", row->no_of_char_values);
    printf("%d\t", row->no_of_string_values);*/
    for (int i = 0; i < row->no_of_int_values; i++)
    {
        printf("%lld\t\t", row->int_values[i]);
    }
    for (int i = 0; i < row->no_of_double_values; i++)
    {
        printf("%lf\t\t", row->double_values[i]);
    }
    for (int i = 0; i < row->no_of_char_values; i++)
    {
        printf("%c\t\t", row->char_values[i]);
    }
    for (int i = 0; i < row->no_of_string_values; i++)
    {
        printf("%s\t\t", row->string_values[i]);
    }
    printf("\n");
}