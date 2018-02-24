#include <gtest/gtest.h>

#include "cvector_import.h"

TEST(cvector_new__and__cvector_free, int) {
    int_vect *p_cvector = int_vect__new();
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GT(p_cvector->_space, 0);
    ASSERT_NE(p_cvector->_vector, nullptr);
    int_vect__free(p_cvector);
}

TEST(cvector_new__and__cvector_free, str) {
    str_vect *p_cvector = str_vect__new();
    ASSERT_EQ(p_cvector->_size, 0);
    ASSERT_GT(p_cvector->_space, 0);
    ASSERT_NE(p_cvector->_vector, nullptr);
    str_vect__free(p_cvector);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
