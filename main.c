#include <stdio.h>
#include <stdlib.h>

#include "carray.h"

#define STRING_OF_INT_SIZE 32

/*
 * Be careful, this function is called "chara_of_Int" but takes a "type"
 * param and not a "Int" param !
 */
char *chara_of_Int(type val)
{
    char *result = calloc(STRING_OF_INT_SIZE, sizeof(char));
    sprintf(result, "%d", of_Int (val));
    return result;
}

char *chara_of_String(type val)
{
    char *result = malloc(sizeof(val) / sizeof(char));
    strcpy(result, (char *) (val));
    return result;
}

int main_a(int argc, char **argv)
{
    carray *my_c = carray_new();
    char *repr;

    my_c = carray_new();
    carray_push(my_c, Int(10));
    carray_push(my_c, Int(11));
    repr = carray_tostring_TF(my_c, &chara_of_Int, "[", "]", "", ", ");
    printf("%s\n", repr);
    free(repr);
    carray_free(my_c, free_Obj);

    my_c = carray_new();
    carray_push(my_c, String("coucou"));
    carray_push(my_c, String("test"));
    repr = carray_tostring_TF(my_c, &chara_of_String, "{", "}", "", ", ");
    printf("%s\n", repr);
    free(repr);
    carray_free(my_c, free_Obj);

    return 0;
}

int main_b(int argc, char **argv)
{
    for (size_t i = 0; i < 3; ++i)
    {
        printf("%d ,", "abcd"[i]);
    }
    return 0;
}

int main(int argc, char **argv)
{
    return main_b(argc, argv);
}
