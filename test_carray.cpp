//
// Created by thomas on 29/09/17.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "carray.h"

/*
 * step I : until push method (included) ->
 *     _carray_example & _carray_example_alt
 * TODO: carray_safeset;
 *
 *
 *     if (c == NULL)
    {
        return;
    } ->> 554
 */

/**
 * Tests if the carray is holding the same values as the vanilla array.
 * @param c the carray to test
 * @param vanilla_array the vanilla array to test
 * @return true if both arrays hold the same value, false otherwise
 */
bool _array_carray_equal(int *vanilla_array, size_t v_size, carray *c)
{
    if (v_size != c->_size)
    {
        printf("%d <> %d\n", v_size, c->_size);
        return false;
    }
    for (size_t i = 0; i < c->_size; ++i)
    {
        if (of_Int(c->_array[i]) != vanilla_array[i])
        {
            printf("%d <> %d\n", of_Int(c->_array[i]), vanilla_array[i]);
            return false;
        }
    }
    return true;
}

/**
 * Tests if both carrays are equal.
 * @param a first carray to test
 * @param b second carray to test
 * @return true if both carrays are equal; false otherwise
 */
bool _carray_carray_equal(carray *a, carray *b)
{
    if (a->_size != b->_size)
    {
        printf("%d <> %d\n", a->_size, b->_size);
        return false;
    }
    for (size_t i = 0; i < a->_size; ++i)
    {
        if (a->_array[i] != b->_array[i])
        {
            for (size_t j = 0; i < a->_size; ++i)
            {
                printf("%p <> %p\n", a->_array[j], b->_array[j]);
            }
            return false;
        }
    }
    return true;
}

int _example[] = {12, -3, 2};
int _example_size = 3;
int _example_alt[] = {8, -4};
int _example_alt_size = 2;
int _both_examples[] = {12, -3, 2, 8, -4};
int _both_examples_size = 5;

/*
 * Should not be used before LVL [8]!
 */
carray *_carray_example()
{
    carray *c = carray_new();
    for (size_t i = 0; i < sizeof(_example) / sizeof(int); ++i)
    {
        carray_push(c, Int(_example[i]));
    }
    return c;
}

/*
 * Should not be used before LVL [8]!
 */
carray *_carray_example_alt()
{
    carray *c = carray_new();
    for (size_t i = 0; i < sizeof(_example_alt) / sizeof(int); ++i)
    {
        carray_push(c, Int(_example_alt[i]));
    }
    return c;
}

TEST_CASE("carray_new", "[default space]")
{
    carray *c = carray_new();
    REQUIRE(c != NULL);
    REQUIRE(c->_space >= DEFAULT_SPACE_INIT_FLAT);

    carray_free(c, free_Obj);
}

TEST_CASE("carray_new_ISC", "[init space]")
{
    carray *c;

    c = carray_new_ISC(0);
    REQUIRE(c == NULL);

    c = carray_new_ISC(12);
    REQUIRE(c->_space >= 12);

    carray_free(c, free_Obj);
}

TEST_CASE("carray_new_CC", "[copy][require new_ISC]")
{
    REQUIRE(carray_new_CC(NULL) == NULL);

    carray *cc = carray_new_ISC(3);
    cc->_array[0] = Int(2);
    cc->_array[1] = Int(-1);
    cc->_array[2] = Int(3);
    cc->_size = 3;

    carray *r = carray_new_CC(cc);
    REQUIRE(_carray_carray_equal(r, cc));

    carray_free(cc, free_Obj);
}

TEST_CASE("carray_new_CISC", "[copy + init space][require new_ISC]")
{
    carray *cc = carray_new_ISC(3);
    cc->_array[0] = Int(2);
    cc->_array[1] = Int(-1);
    cc->_array[2] = Int(3);
    cc->_size = 3;

    REQUIRE(carray_new_CISC(NULL, 2) == NULL);
    REQUIRE(carray_new_CISC(cc, 0) == NULL);

    REQUIRE(carray_new_CISC(cc, 2) == NULL);

    carray *r = carray_new_CISC(cc, 5);
    bool ok = _carray_carray_equal(r, cc) && r->_space >= 5;
    REQUIRE(ok);

    carray_free(cc, free_Obj);
}

TEST_CASE("set_space", "[set space][require new_ISC]")
{
    carray *c = carray_new_ISC(3);
    c->_array[0] = Int(12);
    c->_array[1] = Int(-3);
    c->_array[2] = Int(2);
    c->_size = 3;

    void *ok = c;

    carray_setspace(NULL, 2, &ok);
    REQUIRE(ok == NULL);

    carray_setspace(c, 1, &ok);
    REQUIRE(ok == NULL);
    REQUIRE(c->_space == 3);

    carray_setspace(c, 5, &ok);
    REQUIRE(ok == c);
    REQUIRE(c->_space >= 5);

    carray_free(c, free_Obj);
}

TEST_CASE("add_space", "[add space][require new_ISC]")
{
    carray *c = carray_new_ISC(4);
    c->_space = 0;

    void *ok = c;
    carray_addspace(NULL, &ok);
    REQUIRE(ok == NULL);

    carray_addspace(c, &ok);
    REQUIRE(ok == c);
    REQUIRE(c->_space >= 1);

    size_t p_space = c->_space;

    carray_addspace(c, &ok);
    REQUIRE(ok == c);
    REQUIRE(c->_space >= DEFAULT_SPACE_INCR * p_space);

    carray_free(c, free_Obj);
}

TEST_CASE("carray_add", "[insert new value anywhere][require new_ISC]")
{
    carray *c = carray_new_ISC(3);
    c->_array[0] = Int(12);
    c->_array[1] = Int(-3);
    c->_array[2] = Int(2);
    c->_size = 3;

    void *ok = c;

    carray_add(NULL, 0, NULL, &ok);
    REQUIRE(ok == NULL);

    carray_add(c, -4, Int(3), &ok);
    REQUIRE(ok == NULL);

    carray_add(c, 0, Int(3), &ok);
    REQUIRE(ok == c);
    REQUIRE(c->_size == 4);
    REQUIRE(of_Int(c->_array[0]) == 3);
    REQUIRE(of_Int(c->_array[1]) == 12);
    REQUIRE(of_Int(c->_array[2]) == -3);
    REQUIRE(of_Int(c->_array[3]) == 2);

    carray_add(c, -2, Int(8), &ok);
    REQUIRE(ok == c);
    REQUIRE(of_Int(c->_array[c->_size - 3]) == 8);
    REQUIRE(of_Int(c->_array[c->_size - 2]) == -3);

    carray_add(c, c->_size, Int(6), &ok);
    REQUIRE(ok == c);
    REQUIRE(of_Int(c->_array[c->_size - 1]) == 6);

    carray_add(c, 2, Int(18), &ok);
    REQUIRE(ok == c);
    REQUIRE(of_Int(c->_array[2]) == 18);
    REQUIRE(of_Int(c->_array[3]) == 8);

    carray_free(c, free_Obj);
}

TEST_CASE("carray_push", "[push value][require new_ISC]")
{
    carray *c = carray_new_ISC(1);
    carray_push(c, Int(12));
    carray_push(c, Int(-3));
    carray_push(c, Int(2));
    REQUIRE(of_Int(c->_array[0]) == 12);
    REQUIRE(of_Int(c->_array[1]) == -3);
    REQUIRE(of_Int(c->_array[2]) == 2);
    REQUIRE(c->_size == 3);

    carray_free(c, free_Obj);
}

TEST_CASE("getsize", "[get size][require I]")
{
    carray *c = _carray_example();
    REQUIRE(carray_getsize(c) == c->_size);
    carray_free(c, free_Obj);
}

TEST_CASE("getspace", "[get space][require I]")
{
    carray *c = _carray_example();
    REQUIRE(carray_getspace(c) == c->_space);
    carray_free(c, free_Obj);
}

TEST_CASE("append", "[append][require I]")
{
    carray *a = _carray_example();
    carray *b = _carray_example_alt();
    void *ok = NULL;
    carray_append(a, b, &ok);
    REQUIRE(_array_carray_equal(_both_examples, 5, a));
}

TEST_CASE("getreadposition")
