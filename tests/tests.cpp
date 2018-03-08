#include <gtest/gtest.h>

#include "cvector_import.h"

TEST(_cvector_new__and__cvector_free, int) {
    int_vect *p_cvector = int_vect__new();
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GT(p_cvector->_space, 0);
    ASSERT_NE(p_cvector->_vector, nullptr);
    int_vect__free(p_cvector);
}

TEST(_cvector_new__and__cvector_free, str) {
    str_vect *p_cvector = str_vect__new();
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GT(p_cvector->_space, 0);
    ASSERT_NE(p_cvector->_vector, nullptr);
    str_vect__free(p_cvector);
}

TEST(_cvector_new_space, int) {
    int_vect *p_cvector = int_vect__new_space(12);
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GE(p_cvector->_space, 12);
    ASSERT_NE(p_cvector->_vector, nullptr);
    for (index_t i = 0; i < 12; i++) {
        p_cvector->_vector[i] = i;
    }
    int_vect__free(p_cvector);
}

TEST(_cvector_new_space, str) {
    str_vect *p_cvector = str_vect__new_space(15);
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GE(p_cvector->_space, 15);
    ASSERT_NE(p_cvector->_vector, nullptr);
    str my_string = "Hello World!";
    for (index_t i = 0; i < 15; i++) {
        p_cvector->_vector[i] = my_string;
    }
    str_vect__free(p_cvector);
}

TEST(_cvector_new_space, zero) {
    int_vect *p_cvector = int_vect__new_space(0);
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GE(p_cvector->_space, 0);
    int_vect__free(p_cvector);
}

TEST(_cvector_new_space, negative) {
    int_vect *p_cvector = int_vect__new_space(-4);
    ASSERT_EQ(CVECTOR_ERRORNO, 1);
    ASSERT_EQ(p_cvector, nullptr);
}

TEST(_cvector_new_copy, int) {
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

TEST(_cvector_new_copy, str) {
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

TEST(_cvector_new_copy, zero) {
    int_vect *p_original = int_vect__new_space(0);
    int_vect *p_clone = int_vect__new_copy(p_original);
    ASSERT_EQ(p_clone->_size, 0);
    ASSERT_GE(p_clone->_space, 0);
    ASSERT_NE(p_clone->_vector, nullptr);
    int_vect__free(p_clone);
    int_vect__free(p_original);
}

TEST(_cvector_add, int_without_addspace) {
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
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
