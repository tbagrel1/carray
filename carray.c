//
// Created by thomas on 09/09/17.
//

/**
 * \file carray.c
 * \brief Implementation of the carray class.
 * Contains all the function implementations and documentation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#include "carray.h"

/**
 * \addtogroup carray_group C-Array class
 * @{
 */

/**
 * Prints an error message
 * @param message message to print
 */
void fatal_error(char message[])
{
    printf("%s", message);
}

/**
 * Constructor for carray. Returns a pointer to the created carray which
 * must be freed after use.
 * @return a pointer to the created carray
 */
carray *carray_new()
{
    carray *c = malloc(sizeof(carray));
    c->_space = DEFAULT_SPACE_INIT_FLAT;
    c->_size = 0;
    c->_read_position = 0;
    c->_array = malloc(c->_space * sizeof(type));
    return c;
}

/**
 * Constructor for carray with specified init_space. This carray have at least
 * init_space slots at instanciation. Returns a pointer to the created
 * carray which must be freed after use; if init_space is not valid, returns
 * NULL.
 * @param init_space Initial space (number of elements) of the carray
 * @return a pointer to the created carray
 */
carray *carray_new_ISC(size_t init_space)
{
    if (init_space < 0)
    {
        return NULL;
    }
    carray *c = malloc(sizeof(carray));
    c->_space = init_space;
    c->_size = 0;
    c->_read_position = 0;
    c->_array = malloc(c->_space * sizeof(type));
    return c;
}

/**
 * Copy constructor for carray. The created carray is the exact copy of the
 * specified one with a bit more space than the length of the specified one.
 * Returns a pointer to the created carray which must be freed after use.
 * @param copy_carray the carray to be copied
 * @return a pointer to the created carray
 */
carray *carray_new_CC(carray *copy_carray)
{
    carray *c = malloc(sizeof(carray));
    c->_space = (size_t) (copy_carray->_size * DEFAULT_SPACE_INIT_PERCENT);
    c->_size = copy_carray->_size;
    c->_read_position = 0;
    c->_array = malloc(c->_space * sizeof(type));
    memcpy(c->_array, copy_carray->_array, c->_size);
    return c;
}

/**
 * Copy constructor for carray with init_space specified. This carray have
 * at least init_space slots at instanciation, and hold the exact content of
 * the specified carray. Returns a pointer to the created carray which must
 * be freed after use; if init_space is shorter than the length of the
 * carray to be copied, returns NULL.
 * @param copy_carray the carray to be copied
 * @param init_space Initial space (number of elements) of the carray
 * @return a pointer to the created carray
 */
carray *carray_new_CISC(carray *copy_carray, size_t init_space)
{
    if (init_space < 0 || init_space < copy_carray->_size)
    {
        return NULL;
    }
    carray *c = malloc(sizeof(carray));
    c->_space = init_space;
    c->_size = copy_carray->_size;
    c->_read_position = 0;
    c->_array = malloc(c->_space * sizeof(type));
    memcpy(c->_array, copy_carray->_array, c->_size);
    return c;
}

/**
 * Destructor for carray. Frees the carray internal array representation and
 * the carray itself. If voidfunc is not NULL, applies this function to each
 * element of the carray before freeing the whole struct.
 * @param c the carray
 * @param voidfunc a function to be applied on each element of the carray to
 * free it; can be NULL
 */
void carray_free(carray *c, void(*voidfunc)(type))
{
    if (voidfunc != NULL)
    {
        for (size_t i = 0; i < c->_size; ++i)
        {
            (*voidfunc)(c->_array[i]);
        }
    }
    free(c->_array);
    free(c);
}

/**
 * Size getter.
 * @param c the carray
 * @return the size of the carray
 */
size_t carray_getsize(carray *c)
{
    return c->_size;
}

/**
 * Space getter.
 * @param c the carray
 * @return the space (in nb of elements) of the carray
 */
size_t carray_getspace(carray *c)
{
    return c->_space;
}

/**
 * Space setter. Can be used to modify the space allowed for the internal
 * representation of the carray.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param new_space new space (in nb of elements) for the carray
 * @param validation flag
 */
void carray_setspace(carray *c, size_t new_space, void **ok)
{
    if (new_space < 0 || new_space < c->_size)
    {
        *ok = NULL;
        return;
    }
    type *temp_carray = realloc(c->_array, new_space);
    /* Should never happen */
    if (temp_carray == NULL)
    {
        *ok = NULL;
        fatal_error("Fatal Error in \"carray_setspace\": realloc failed.");
        return;
    }
    *ok = c;
    c->_space = new_space;
    c->_array = temp_carray;
}

/**
 * Increases space allowed for the internal representation of the carray.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param ok validation flag
 */
void carray_addspace(carray *c, void **ok)
{
    carray_setspace(c, (size_t) (c->_space * DEFAULT_SPACE_INCR + 1), ok);
}

/**
 * Used to set an element somewhere in the carray even if this cell is not
 * already used by the carray, for example, to set carray[8] with a length-4
 * carray. Unused cells until the specified one are set with the default
 * type value.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param index index where to put the specified value; can be larger than
 * the carray size
 * @param value value to be put at the specified index
 * @param ok validation flag
 */
void carray_safeset(carray *c, int index, type value, void **ok)
{
    if (index < 0)
    {
        index = (int) (c->_size + index);
    }
    if (index < 0)
    {
        *ok = NULL;
        return;
    }
    if (index < c->_size)
    {
        c->_array[index] = value;
    }
    else if (index < c->_space)
    {
        *ok = c;
        for (size_t i = c->_size; i < index; ++i)
        {
            c->_array[i] = DEFAULT_TYPE_VALUE;
        }
        c->_array[index] = value;
        c->_size = (size_t) (index + 1);
    }
    else
    {
        carray_setspace(
            c, (size_t) (DEFAULT_SPACE_INIT_PERCENT * (index + 1)), ok);
        if (*ok != NULL)
        {
            return carray_safeset(c, index, value, ok);
        }
    }
}

/**
 * Append the second specified carray at the end of the first one.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param o the carray to put at the end of the first one
 * @param ok validation flag
 */
void carray_append(carray *c, carray *o, void **ok)
{
    if (c->_size + o->_size <= c->_space)
    {
        *ok = c;
        memcpy(c->_array + c->_size, o->_array, o->_size);
    }
    else
    {
        carray_setspace(
            c,
            (size_t) (DEFAULT_SPACE_INIT_PERCENT * (c->_size + o->_size)),
            ok);
        if (*ok != NULL)
        {
            return carray_append(c, o, ok);
        }
    }
}

/**
 * Read position getter.
 * @param c the carray
 * @return the current read position
 */
size_t carray_getreadposition(carray *c)
{
    return c->_read_position;
}

/**
 * Read position setter.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param new_read_position new read position
 * @param ok validation flag
 */
void carray_setreadposition(carray *c, int new_read_position, void **ok)
{
    if (new_read_position < 0)
    {
        new_read_position = (int) (c->_size + new_read_position);
    }
    if (new_read_position < 0 || new_read_position > c->_size)
    {
        *ok = NULL;
        return;
    }
    *ok = c;
    c->_read_position = (size_t) new_read_position;
}

/**
 * Gets the number of read operation remaining before reaching the end of
 * the carray.
 * @param c the carray
 * @return the number of read possible before the end of the carray
 */
size_t carray_readingsremaining(carray *c)
{
    return c->_size - c->_read_position;
}

/**
 * Internal array getter.
 * @param c the carray
 * @return the internal representation of the carray
 */
type *carray_getarray(carray *c)
{
    return c->_array;
}

/**
 * Read method. Returns elt at the current read position and increases read
 * position by 1.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param ok validation flag
 * @return the element at the current read position; default type value if
 * there's no element to be read
 */
type carray_read(carray *c, void **ok)
{
    if (carray_readingsremaining(c) == 0)
    {
        *ok = NULL;
        return DEFAULT_TYPE_VALUE;
    }
    *ok = c;
    return c->_array[c->_read_position++];
}

/**
 * Pushes the specified value at the end of the carray.
 * @param c the carray
 * @param value the element to push at the end of the carray
 */
void carray_push(carray *c, type value)
{
    void *ok = NULL;
    carray_add(c, (int) c->_size, value, &ok);
}

/**
 * Inserts the specified value at the beginning of the carray.
 * @param c the carray
 * @param value the element to insert at the end of the carray
 */
void carray_ins(carray *c, type value)
{
    void *ok = NULL;
    carray_add(c, 0, value, &ok);
}

/**
 * Removes the last element of the carray and returns it.
 * @param c the carray
 * @return the last element of the carray
 */
type carray_pop(carray *c)
{
    void *ok = NULL;
    return carray_remove(c, (int) (c->_size - 1), ok);
}

/**
 * Enventually shrinks the size of the internal representation of the carray
 * if free space exceed the threshold.
 * ok will hold the carray address if a shrinking was made, and NULL otherwise.
 * @param c the carray
 * @param ok validation flag
 */
void carray_adjust(carray *c, void **ok)
{
    if ((double) (c->_space) / (double) (c->_size) > DEFAULT_SHRINK_THRESHOLD)
    {
        carray_setspace(c, (size_t) (c->_size * DEFAULT_SHRINK_PERCENT), ok);
    }
    else
    {
        *ok = NULL;
    }
}

/**
 * Reverses the specified carray in-place.
 * @param c the carray
 */
void carray_reverse(carray *c)
{
    const size_t n = c->_size;
    for (size_t i = 0; i < n / 2; ++i)
    {
        type temp_value = c->_array[i];
        c->_array[i] = c->_array[n - 1 - i];
        c->_array[n - 1 - 1] = temp_value;
    }
}

/**
 * Returns a reversed copy of the specified carray which must be freed after
 * use.
 * @param c the carray
 * @return a reversed copy of the specified carray
 */
carray *carray_reversed_TF(carray *c)
{
    const size_t n = c->_size;
    carray *result_array = carray_new_ISC(n);
    result_array->_size = n;
    for (size_t i = 0; i < n; ++i)
    {
        result_array->_array[n - i - 1] = c->_array[i];
    }
    return result_array;
}

/**
 * Concatenates both specified carrays into a new one which must be freed
 * after use.
 * @param a the first carray to concatenate
 * @param b the second carray to concatenate
 * @return a concatenated version of carrays a and b
 */
carray *carray_concat_TF(carray *a, carray *b)
{
    carray *c = carray_new_CISC(
        a, (size_t) (DEFAULT_SPACE_INIT_PERCENT * (a->_size + b->_size)));
    /* TEMP */
    void *verif = NULL;
    carray_append(c, b, &verif);
    return c;
}

/**
 * Returns the hashcode of the carray according to the specified elements
 * hash code function.
 * @param c the carray
 * @param hashfunc hashcode function to apply on each element of the carray
 * @return the hashcode of the carray
 */
hashtype carray_hashcode(carray *c, hashtype(*hashfunc)(type))
{
    hashtype result_hash = 0;
    for (size_t i = 0; i < c->_size; ++i)
    {
        result_hash = PRIME_CST * result_hash + (*hashfunc)(c->_array[i]);
    }
    return result_hash;
}

/**
 * Returns true if both carrays are equal and false otherwise, according to
 * the specified elements equality function.
 * @param a the first carray to test
 * @param b the second carray to test
 * @param eqfunc equality function to apply on two elements
 * @return true if both carrays are equal, false otherwise
 */
bool carray_equal(carray *a, carray *b, bool(*eqfunc)(type, type))
{
    if (a->_size != b->_size)
    {
        return false;
    }
    for (size_t i = 0; i < a->_size; ++i)
    {
        if (!(*eqfunc)(a->_array[i], b->_array[i]))
        {
            return false;
        }
    }
    return true;
}

/**
 * Returns a representation of the specified carray.
 * @param c the carray
 * @param strfunc the function to apply on each element to convert it into
 * string
 * @param opener opening string
 * @param closer closing string
 * @param prefix prefix string added before each cell except for the first one
 * @param suffix suffix string added after each cell except for the lats one
 * @return a string representing the carray
 */
char *carray_tostring_TF(
    carray *c,
    char *(*strfunc)(type),
    char *opener,
    char *closer,
    char *prefix,
    char *suffix)
{
    size_t opener_size = 0;
    while (opener[opener_size] != '\0')
    {
        ++opener_size;
    }
    size_t closer_size = 0;
    while (closer[closer_size] != '\0')
    {
        ++closer_size;
    }
    size_t prefix_size = 0;
    while (prefix[prefix_size] != '\0')
    {
        ++prefix_size;
    }
    size_t suffix_size = 0;
    while (suffix[suffix_size] != '\0')
    {
        ++suffix_size;
    }
    char **parts = malloc(sizeof(char *) * c->_size);
    size_t total_size = 1;
    size_t individual_size;
    for (size_t i = 0; i < c->_size; ++i)
    {
        individual_size = 0;
        parts[i] = (*strfunc)(c->_array[i]);
        while (parts[i][individual_size] != '\0')
        {
            ++individual_size;
        }
        total_size += individual_size;
    }
    total_size += opener_size + closer_size;
    if (c->_size > 0)
    {
        total_size += (c->_size - 1) * (prefix_size + suffix_size);
    }
    char *result = calloc(total_size, sizeof(char));
    size_t i = 0;
    strcpy(result + i, opener);
    i += opener_size;
    for (size_t k = 0; k < c->_size; ++k)
    {
        if (k > 0)
        {
            strcpy(result + i, prefix);
            i += prefix_size;
        }
        strcpy(result + i, parts[k]);
        size_t l = 0;
        while (parts[k][l] != '\0')
        {
            ++l;
        }
        i += l;
        free(parts[k]);
        if (k < (c->_size - 1))
        {
            strcpy(result + i, suffix);
            i += suffix_size;
        }
    }
    strcpy(result + i, closer);
    i += closer_size;
    free(parts);
    /* Debug point */
    /* printf("%zu <> %zu", total_size, i); */
    return result;
}

/**
 * Returns true if the carray is empty, false otherwise
 * @param c the carray
 * @return true if the carray is empty, false otherwise
 */
bool carray_isempty(carray *c)
{
    return c->_size == 0;
}

/**
 * Tests if the carray contains the test_element according to the specified
 * equality function
 * @param c the carray
 * @param test_element the element to be compared to the carray elements
 * @param eqfunc the function to test equality between elements
 * @return true if the specified element is inside the carray, and false
 * otherwise
 */
bool carray_contains(carray *c, type test_element, bool(*eqfunc)(type, type))
{
    size_t i = 0;
    bool found = false;
    while (i < c->_size && !found)
    {
        if ((*eqfunc)(test_element, c->_array[i]))
        {
            found = true;
        }
        ++i;
    }
    return found;
}

/**
 * Returns a vanilla array version of the carray.
 * @param c the carray
 * @return a vanilla array version of the carray
 */
type *carray_toarray_TF(carray *c)
{
    type *result = malloc(sizeof(type) * c->_size);
    memcpy(result, c->_array, c->_size);
    return result;
}

/**
 * Removes the specified element from the carray if and only if this one is
 * present.
 * @param c the carray
 * @param test_element element to be removed if present
 * @param eqfunc the function to test equality between elements
 * @return true if the specified element was in the carray and thus was 
 * removed, false if nothing was made.
 */
bool carray_remove_elt(carray *c, type test_element, bool(*eqfunc)(type, type))
{
    bool found = false;
    int index = carray_indexof(c, test_element, eqfunc);
    if (index != -1)
    {
        void *ok = NULL;
        carray_remove(c, index, &ok);
    }
    return found;
}

/**
 * Clears the content of the carray. Be careful, this function DOESN'T free
 * the space allowed for the internal representation of the carray. Use
 * carray_adjust for that.
 * @param c the carray
 */
void carray_clear(carray *c)
{
    c->_size = 0;
}

/**
 * Gets the element at the specified index in the carray.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param index index where element will be retrieved
 * @param ok validation flag
 * @return the element at the specified index if index is correct; default
 * type value otherwise
 */
type carray_get(carray *c, int index, void **ok)
{
    if (index < 0)
    {
        index += c->_size;
    }
    type result;
    if (index < 0 || index >= c->_size)
    {
        *ok = NULL;
        result = DEFAULT_TYPE_VALUE;
    }
    else
    {
        *ok = c;
        result = c->_array[index];
    }
    return result;
}

/**
 * Sets the element at the specified index in the carray to the specified
 * value.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param index index where element will be set
 * @param new_value new value for this element
 * @param ok validation flag
 */
void carray_set(carray *c, int index, type new_value, void **ok)
{
    if (index < 0)
    {
        index += c->_size;
    }
    if (index < 0 || index >= c->_size)
    {
        *ok = NULL;
    }
    else
    {
        *ok = c;
        c->_array[index] = new_value;
    }
}

/**
 * Adds the specified element at the specified index in the carray.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param index index where to insert the specified element. The element
 * will be inserted at this exact position, and subsequent elements will be
 * shifted.
 * @param new_value element to insert at the specified index
 * @param ok validation flag
 */
void carray_add(carray *c, int index, type new_value, void **ok)
{
    if (index < 0)
    {
        index += c->_size;
    }
    if (index < 0 || index > c->_size)
    {
        *ok = NULL;
    }
    else
    {
        if (c->_size < c->_space)
        {
            if (c->_read_position > index)
            {
                c->_read_position = 0;
            }
            c->_array[c->_size] = DEFAULT_TYPE_VALUE;
            type next_value = c->_array[index];
            type temp;
            for (size_t i = (size_t) index; i < c->_size; ++i)
            {
                temp = c->_array[i + 1];
                c->_array[i + 1] = next_value;
                next_value = temp;
            }
            c->_array[index] = new_value;
            ++c->_size;
            *ok = c;
        }
        else
        {
            carray_addspace(c, ok);
            if (*ok != NULL)
            {
                carray_add(c, index, new_value, ok);
            }
        }
    }
}

/**
 * Removes the element at the specified index and returns it.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param index index where element will be removed. The element will be
 * removed at this exact position, and subsequent elements will be shifted.
 * @param ok validation flag
 * @return the element which have been removed if the index is correct,
 * default type value otherwise.
 */
type carray_remove(carray *c, int index, void **ok)
{
    if (index < 0)
    {
        index += c->_size;
    }
    type result;
    if (index < 0 || index >= c->_size)
    {
        *ok = NULL;
        result = DEFAULT_TYPE_VALUE;
    }
    else
    {
        *ok = c;
        result = c->_array[index];
        for (size_t i = (size_t) (index + 1); i < c->_size; ++i)
        {
            c->_array[i - 1] = c->_array[i];
        }
        --c->_size;
    }
    return result;
}

/**
 * Returns the index of the specified element in the carray, and -1 if this
 * element wasn't found. The carray is read left to right and this function
 * returns the index of the first occurence met.
 * @param c the carray
 * @param test_value the element to find in the carray
 * @param eqfunc the function to test equality between elements
 * @return the index of the specified element if this one was found, -1
 * otherwise
 */
int carray_indexof(carray *c, type test_value, bool(*eqfunc)(type, type))
{
    int index = -1;
    int i = 0;
    while (i < c->_size && index == -1)
    {
        if ((*eqfunc)(test_value, c->_array[i]))
        {
            index = i;
        }
        ++i;
    }
    return index;
}

/**
 * Returns the index of the specified element in the carray, and -1 if this
 * element wasn't found. The carray is read right to left and this function
 * returns the index of the first occurence met.
 * @param c the carray
 * @param test_value the element to find in the carray
 * @param eqfunc the function to test equality between elements
 * @return the index of the specified element if this one was found, -1
 * otherwise
 */
int carray_lastindexof(carray *c, type test_value, bool(*eqfunc)(type, type))
{
    int index = -1;
    int i = (int) (c->_size - 1);
    while (i >= 0 && index == -1)
    {
        if ((*eqfunc)(test_value, c->_array[i]))
        {
            index = i;
        }
        ++i;
    }
    return index;
}

/**
 * Returns a smaller carray which holds values from index "from_index"
 * (included) to index "to_index" (excluded).
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param from_index beginning index
 * @param to_index ending index
 * @param ok validation flag
 * @return the sub-carray if the indices are correct, NULL otherwise
 */
carray *carray_subcarray_TF(carray *c, int from_index, int to_index, void **ok)
{
    if (from_index < 0)
    {
        from_index += c->_size;
    }
    if (to_index < 0)
    {
        to_index += c->_size;
    }
    carray *result;
    if (from_index < 0 ||
        from_index >= c->_size ||
        to_index < 0 ||
        to_index > c->_size ||
        to_index < from_index)
    {
        *ok = NULL;
        result = NULL;
    }
    else
    {
        *ok = c;
        size_t new_size = (size_t) (to_index - from_index);
        result = carray_new_ISC((size_t) (
            DEFAULT_SPACE_INIT_PERCENT * new_size));
        memcpy(result->_array, c->_array + from_index, new_size);
        result->_size = new_size;
    }
    return result;
}

/**
 * Returns a smaller carray which holds values from index "from_index"
 * (included) to index "to_index" (excluded) according to the specified step.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param from_index beginning index
 * @param to_index ending index
 * @param step item selecting step
 * @param ok validation flag
 * @return the sub-carray if the indices are correct, NULL otherwise
 */
carray *carray_subcarraystep_TF(
    carray *c, int from_index, int to_index, int step, void **ok)
{
    carray *result;
    if (step > 0)
    {
        if (from_index < 0 ||
            from_index >= c->_size ||
            to_index < 0 ||
            to_index > c->_size ||
            to_index < from_index)
        {
            *ok = NULL;
            result = NULL;
        }
        else
        {
            size_t new_size = ((to_index - from_index) / step) + 1;
            result = carray_new_ISC((size_t) (
                DEFAULT_SPACE_INIT_PERCENT * new_size));
            for (size_t i = 0; i < new_size; ++i)
            {
                result->_array[i] = c->_array[from_index + i * step];
            }
            result->_size = new_size;
        }
    }
    else if (step < 0)
    {
        if (from_index >= c->_size ||
            from_index <= -1 ||
            to_index < -1 ||
            to_index >= c->_size ||
            from_index < to_index)
        {
            *ok = NULL;
            result = NULL;
        }
        else
        {
            size_t new_size = ((from_index - to_index) / step) + 1;
            result = carray_new_ISC((size_t) (
                DEFAULT_SPACE_INIT_PERCENT * new_size));
            for (size_t i = 0; i < new_size; ++i)
            {
                result->_array[i] = c->_array[from_index + i * step];
            }
            result->_size = new_size;
        }
    }
    else /* step = 0 */
    {
        *ok = NULL;
        result = NULL;
    }
    return result;
}

/**
 * Returns a smaller vanilla array which holds values from index "from_index"
 * (included) to index "to_index" (excluded).
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param from_index beginning index
 * @param to_index ending index
 * @param ok validation flag
 * @return the sub-vanilla array if the indices are correct, NULL otherwise
 */
type *carray_subarray_TF(carray *c, int from_index, int to_index, void **ok)
{
    if (from_index < 0)
    {
        from_index += c->_size;
    }
    if (to_index < 0)
    {
        to_index += c->_size;
    }
    type *result;
    if (from_index < 0 ||
        from_index >= c->_size ||
        to_index < 0 ||
        to_index > c->_size ||
        to_index < from_index)
    {
        *ok = NULL;
        result = NULL;
    }
    else
    {
        *ok = c;
        size_t new_size = (size_t) (to_index - from_index);
        result = malloc(sizeof(type) * new_size);
        memcpy(result, c->_array + from_index, new_size);
    }
    return result;
}

/**
 * Returns a smaller vanilla array which holds values from index "from_index"
 * (included) to index "to_index" (excluded) according to the specified step.
 * If params are correct and if the operation works, ok will hold the carray
 * address; otherwise, it will hold NULL.
 * @param c the carray
 * @param from_index beginning index
 * @param to_index ending index
 * @param step item selecting step
 * @param ok validation flag
 * @return the sub-vanilla array if the indices are correct, NULL otherwise
 */
type *carray_subarraystep_TF(
    carray *c, int from_index, int to_index, int step, void **ok)
{
    type *result;
    if (step > 0)
    {
        if (from_index < 0 ||
            from_index >= c->_size ||
            to_index < 0 ||
            to_index > c->_size ||
            to_index < from_index)
        {
            *ok = NULL;
            result = NULL;
        }
        else
        {
            size_t new_size = ((to_index - from_index) / step) + 1;
            result = malloc(sizeof(type) * new_size);
            for (size_t i = 0; i < new_size; ++i)
            {
                result[i] = c->_array[from_index + i * step];
            }
        }
    }
    else if (step < 0)
    {
        if (from_index >= c->_size ||
            from_index <= -1 ||
            to_index < -1 ||
            to_index >= c->_size ||
            from_index < to_index)
        {
            *ok = NULL;
            result = NULL;
        }
        else
        {
            size_t new_size = ((from_index - to_index) / step) + 1;
            result = malloc(sizeof(type) * new_size);
            for (size_t i = 0; i < new_size; ++i)
            {
                result[i] = c->_array[from_index + i * step];
            }
        }
    }
    else /* step = 0 */
    {
        *ok = NULL;
        result = NULL;
    }
    return result;
}

/**
 * Frees the specified primitive-wrapped element.
 * @param val primitive-wrapped element to free
 */
void carray_free_obj(type val)
{
    free(val);
}

/**
 * @}
 */
