#include <stdio.h>
#include <stdlib.h>

#include "carray.h"

#define STRING_OF_INT_SIZE 32

/*
 * Be careful, this function is called "string_of_Int" but takes a "type"
 * param and not a "Int" param !
 */
char *string_of_Int(type val)
{
    char *result = calloc(STRING_OF_INT_SIZE, sizeof(char));
    sprintf(result, "%d", of_Int (val));
    return result;
}

int main(int argc, char **argv)
{
    carray *my_c = carray_new();

    carray_push(my_c, Int(10));
    carray_push(my_c, Int(11));
    char *repr = carray_tostring_TF(my_c, &string_of_Int, "[", "]", "", ", ");
    printf("%s\n", repr);
    free(repr);
    carray_free(my_c, free_Obj);
    return 0;
}
