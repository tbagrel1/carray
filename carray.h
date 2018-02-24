//
// Created by thomas on 09/09/17.
//

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \file carray.h
 * \brief Header of the carray class.
 * Contains all function declarations and preprocessor directives.
 */

#ifndef TBAGREL_PROJECT_CARRAY_H
#define TBAGREL_PROJECT_CARRAY_H

#include <stdbool.h>
#include <string.h>

/**
 * \addtogroup carray_group C-Array class
 * @{
 */

/**
 * \addtogroup cst_group Constants for C-Array class
 * @{
 */

/**
 * Initial space for the internal representation of a carray.
 */
#define DEFAULT_SPACE_INIT_FLAT 8

/**
 * Initial space factor used when a carray is created from an existing one.
 */
#define DEFAULT_SPACE_INIT_PERCENT 1.25

/**
 * Space factor used when a carray becomes too short.
 */
#define DEFAULT_SPACE_INCR 2.0

/**
 * Space threshold from which the carray is shrinked.
 */
#define DEFAULT_SHRINK_THRESHOLD 2.5

/**
 * Space factor used when the carray is shrinked.
 */
#define DEFAULT_SHRINK_PERCENT 1.25

/**
 * Alias for carray struct.
 */
typedef struct carray carray;

/**
 * @}
 */

/**
 * \addtogroup impl_group Implementation specific constants and aliases
 * @{
 */
typedef unsigned int hashtype;
#define DEFAULT_HASHTYPE_VALUE 0
#define PRIME_CST 31
typedef void *type;
#define DEFAULT_TYPE_VALUE NULL
/**
 * @}
 */

/**
 * \addtogroup prep_group Preprocessor macros
 * @{
 */
#define of_Char *(char*)
#define of_sChar *(signed char*)
#define of_uChar *(unsigned char*)
#define of_Short *(short*)
#define of_sShort *(signed short*)
#define of_uShort *(unsigned short*)
#define of_Int *(int*)
#define of_sInt *(signed int*)
#define of_uInt *(unsigned int*)
#define of_Long *(long*)
#define of_lLong *(long long*)
#define of_sLong *(signed long*)
#define of_slLong *(signed long long*)
#define of_uLong *(unsigned long*)
#define of_ulLong *(unsigned long long*)
#define of_Float *(float*)
#define of_Double *(double*)
#define of_lDouble *(long double*)
#define of_Bool *(bool*)
#define of_String (char*)

char *Char_holder;
#define Char(expr) \
    (Char_holder = (char*)malloc(sizeof(char)), \
     *Char_holder = (expr), (void*)(Char_holder))

signed char *sChar_holder;
#define sChar(expr) \
    (sChar_holder = (signed char*)malloc(sizeof(signed char)), \
     *sChar_holder = (expr), (void*)(sChar_holder))

unsigned char *uChar_holder;
#define uChar(expr) \
    (uChar_holder = (unsigned char*)malloc(sizeof(unsigned char)), \
     *uChar_holder = (expr), (void*)(uChar_holder))

short *Short_holder;
#define Short(expr) \
    (Short_holder = (short*)malloc(sizeof(short)), \
     *Short_holder = (expr), (void*)(Short_holder))

signed short *sShort_holder;
#define sShort(expr) \
    (sShort_holder = (signed short*)malloc(sizeof(signed short)), \
     *sShort_holder = (expr), (void*)(sShort_holder))

unsigned short *uShort_holder;
#define uShort(expr) \
    (uShort_holder = (unsigned short*)malloc(sizeof(unsigned short)), \
     *uShort_holder = (expr), (void*)(uShort_holder))

int *Int_holder;
#define Int(expr) \
    (Int_holder = (int*)malloc(sizeof(int)), \
     *Int_holder = (expr), (void*)(Int_holder))

signed int *sInt_holder;
#define sInt(expr) \
    (sInt_holder = (signed int*)malloc(sizeof(signed int)), \
     *sInt_holder = (expr), (void*)(sInt_holder))

unsigned int *uInt_holder;
#define uInt(expr) \
    (uInt_holder = (unsigned int*)malloc(sizeof(unsigned int)), \
     *uInt_holder = (expr), (void*)(uInt_holder))

long *Long_holder;
#define Long(expr) \
    (Long_holder = (long*)malloc(sizeof(long)), \
     *Long_holder = (expr), (void*)(Long_holder))

long long *lLong_holder;
#define lLong(expr) \
    (lLong_holder = (long long*)malloc(sizeof(long long)), \
     *lLong_holder = (expr), (void*)(lLong_holder))

signed long *sLong_holder;
#define sLong(expr) \
    (sLong_holder = (signed long*)malloc(sizeof(signed long)), \
     *sLong_holder = (expr), (void*)(sLong_holder))

signed long long *slLong_holder;
#define slLong(expr) \
    (slLong_holder = (signed long long*)malloc(sizeof(signed long long)), \
     *slLong_holder = (expr), (void*)(slLong_holder))

unsigned long *uLong_holder;
#define uLong(expr) \
    (uLong_holder = (unsigned long*)malloc(sizeof(unsigned long)), \
     *uLong_holder = (expr), (void*)(uLong_holder))

unsigned long long *ulLong_holder;
#define ulLong(expr) \
    (ulLong_holder = (unsigned long long*)malloc(sizeof(unsigned long long)), \
     *ulLong_holder = (expr), (void*)(ulLong_holder))

float *Float_holder;
#define Float(expr) \
    (Float_holder = (float*)malloc(sizeof(float)), \
     *Float_holder = (expr), (void*)(Float_holder))

double *Double_holder;
#define Double(expr) \
    (Double_holder = (double*)malloc(sizeof(double)), \
     *Double_holder = (expr), (void*)(Double_holder))

long double *lDouble_holder;
#define lDouble(expr) \
    (lDouble_holder = (long double*)malloc(sizeof(long double)), \
     *lDouble_holder = (expr), (void*)(lDouble_holder))

bool *Bool_holder;
#define Bool(expr) \
    (Bool_holder = (bool*)malloc(sizeof(bool)), \
     *Bool_holder = (expr), (void*)(Bool_holder))

char *String_holder;
#define String(expr) \
    (String_holder = malloc(sizeof(expr) / sizeof(char)), \
     strcpy(String_holder, (expr)), \
     String_holder)

void carray_free_obj(type);

#define free_Obj &carray_free_obj

/**
 * @}
 */

/**
 * \addtogroup core_group C-Array core
 * @{
 */

/**
 * Carray class implementation.
 * Provides Python-like list for C.
 */
struct carray
{
    type *_array;
    size_t _size;
    size_t _space;
    size_t _read_position;
};

/**
 * @}
 */

/**
 * \addtogroup method_group C-Array methods
 * @{
 */

carray *carray_new();

carray *carray_new_ISC(size_t);

carray *carray_new_CC(carray *);

carray *carray_new_CISC(carray *, size_t);

void carray_free(carray *, void(type));

size_t carray_getsize(carray *);

void carray_clear(carray *);

bool carray_isempty(carray *);

size_t carray_getspace(carray *);

void carray_setspace(carray *, size_t, void **);

void carray_addspace(carray *, void **);

void carray_adjust(carray *, void **);

size_t carray_getreadposition(carray *);

size_t carray_readingsremaining(carray *);

void carray_setreadposition(carray *, int, void **);

type *carray_getarray(carray *);

type carray_read(carray *, void **ok);

void carray_reverse(carray *);

carray *carray_reversed_TF(carray *);

void carray_append(carray *, carray *, void **);

carray *carray_concat_TF(carray *, carray *);

char *
carray_tostring_TF(carray *, char *(type), char *, char *, char *, char *);

hashtype carray_hashcode(carray *, hashtype(type));

bool carray_equal(carray *, carray *, bool(type, type));

int carray_indexof(carray *, type, bool(type, type));

int carray_lastindexof(carray *, type, bool(type, type));

bool carray_contains(carray *, type, bool(type, type));

carray *carray_subcarray_TF(carray *, int, int, void **);

carray *carray_subcarraystep_TF(carray *, int, int, int, void **);

type *carray_subarray_TF(carray *, int, int, void **);

type *carray_subarraystep_TF(carray *, int, int, int, void **);

type *carray_toarray_TF(carray *);

type carray_get(carray *, int, void **);

void carray_add(carray *, int, type, void **);

void carray_push(carray *, type);

void carray_ins(carray *, type);

void carray_set(carray *, int, type, void **);

void carray_safeset(carray *, int, type, void **);

type carray_remove(carray *, int, void **);

type carray_pop(carray *);

bool carray_remove_elt(carray *, type, bool(type, type));

/**
 * @}
 */

/**
 * @}
 */

#endif //TBAGREL_PROJECT_CARRAY_H

#ifdef __cplusplus
}
#endif
