#include <stdio.h>
#include <stdlib.h>

#include "includes/int_vect.h"
#include "includes/str_vect.h"
#include "includes/virtual_lib.h"

#define ASSERT(cond, a, b, s) ( \
    (cond) ? \
        NULL : \
        printf("ERROR [%s]: %ld %s %ld", name, a, s, b) \
)

#define ASSERT_GT(a, b) ASSERT((a) > (b), a, b, ">")
#define ASSERT_GE(a, b) ASSERT((a) >= (b), a, b, ">=")
#define ASSERT_EQ(a, b) ASSERT((a) == (b), a, b, "==")
#define ASSERT_NE(a, b) ASSERT((a) != (b), a, b, "!=")
#define ASSERT_LE(a, b) ASSERT((a) <= (b), a, b, "<=")
#define ASSERT_LT(a, b) ASSERT((a) < (b), a, b, "<")

void cvector_new__and__cvector_free_int() {
    str name = "cvector_new__and__cvector_free_int";
    int_vect *p_cvector = int_vect__new();
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GT(p_cvector->_space, 0);
    ASSERT_NE(p_cvector->_vector, NULL);
    int_vect__free(p_cvector);
}

void cvector_new__and__cvector_free_str() {
    str name = "cvector_new__and__cvector_free_str";
    str_vect *p_cvector = str_vect__new();
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GT(p_cvector->_space, 0);
    ASSERT_NE(p_cvector->_vector, NULL);
    str_vect__free(p_cvector);
}

void cvector_new_space_int() {
    str name = "cvector_new_space_int";
    int_vect *p_cvector = int_vect__new_space(12);
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GE(p_cvector->_space, 12);
    ASSERT_NE(p_cvector->_vector, NULL);
    for (index_t i = 0; i < 12; i++) {
        p_cvector->_vector[i] = i;
    }
    int_vect__free(p_cvector);
}

void cvector_new_space_str() {
    str name = "cvector_new_space_str";
    str_vect *p_cvector = str_vect__new_space(15);
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GE(p_cvector->_space, 15);
    ASSERT_NE(p_cvector->_vector, NULL);
    str my_string = "Hello World!";
    for (index_t i = 0; i < 15; i++) {
        p_cvector->_vector[i] = my_string;
    }
    str_vect__free(p_cvector);
}

void cvector_new_space_zero() {
    str name = "cvector_new_space_zero";
    int_vect *p_cvector = int_vect__new_space(0);
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GE(p_cvector->_space, 0);
    int_vect__free(p_cvector);
}

void cvector_new_space_negative() {
    str name = "cvector_new_space_negative";
    int_vect *p_cvector = int_vect__new_space(-4);
    // TODO: ASSERT_EQ(CVECTOR_ERRORNO, 1);
    ASSERT_EQ(p_cvector, NULL);
}

void cvector_new_copy_int() {
    str name = "cvector_new_copy_int";
    int_vect *p_original = int_vect__new();
    index_t n = p_original->_space;
    ASSERT_GT(n, 0);
    for (index_t i = 0; i < n; i++) {
        p_original->_vector[i] = i;
        p_original->_size++;
    }
    int_vect *p_clone = int_vect__new_copy(p_original);
    ASSERT_EQ(p_original->_size, p_clone->_size);
    ASSERT_GE(p_clone->_space, p_original->_size);
    for (index_t i = 0; i < n; i++) {
        ASSERT_EQ(p_original->_vector[i], p_clone->_vector[i]);
    }
    int_vect__free(p_clone);
    int_vect__free(p_original);
}

void cvector_new_copy_str() {
    str name = "cvector_new_copy_str";
    str_vect *p_original = str_vect__new();
    index_t n = p_original->_space;
    ASSERT_GT(n, 0);
    str my_string = "Hello World!";
    for (index_t i = 0; i < n; i++) {
        p_original->_vector[i] = my_string;
        p_original->_size++;
    }
    str_vect *p_clone = str_vect__new_copy(p_original);
    ASSERT_EQ(p_original->_size, p_clone->_size);
    ASSERT_GE(p_clone->_space, p_original->_size);
    for (index_t i = 0; i < n; i++) {
        ASSERT_EQ(p_original->_vector[i], p_clone->_vector[i]);
    }
    str_vect__free(p_clone);
    str_vect__free(p_original);
}

void cvector_new_copy_zero() {
    str name = "cvector_new_copy_zero";
    int_vect *p_original = int_vect__new_space(0);
    int_vect *p_clone = int_vect__new_copy(p_original);
    ASSERT_EQ(p_clone->_size, 0);
    ASSERT_GE(p_clone->_space, 0);
    ASSERT_NE(p_clone->_vector, NULL);
    int_vect__free(p_clone);
    int_vect__free(p_original);
}

void cvector_add_int_without_addspace() {
    str name = "cvector_add_int_without_addspace";
    int_vect *p_cvector = int_vect__new();
    int_vect__add(p_cvector, 12);
    ASSERT_EQ(p_cvector->_vector[0], 12);
    ASSERT_EQ(p_cvector->_size, 1);
    ASSERT_LE(p_cvector->_size, p_cvector->_space);
    int_vect__add(p_cvector, -4);
    ASSERT_EQ(p_cvector->_vector[0], 12);
    ASSERT_EQ(p_cvector->_vector[1], -4);
    ASSERT_LE(p_cvector->_size, p_cvector->_space);
    int_vect__free(p_cvector);
}

int main(int argc, char **argv) {
    cvector_new__and__cvector_free_int();
    cvector_new__and__cvector_free_str();
    cvector_new_space_int();
    cvector_new_space_str();
    cvector_new_space_zero();
    cvector_new_space_negative();
    cvector_new_copy_int();
    cvector_new_copy_str();
    cvector_new_copy_zero();
    cvector_add_int_without_addspace();
    return 0;
}
