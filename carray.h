//
// Created by thomas on 09/09/17.
//

#ifndef TBAGREL_PROJECT_CARRAY_H
#define TBAGREL_PROJECT_CARRAY_H

#include <stdbool.h>

#define DEFAULT_SPACE_INIT_FLAT 8
#define DEFAULT_SPACE_INIT_PERCENT 1.25
#define DEFAULT_SPACE_INCR 2.0
#define DEFAULT_SHRINK_THRESHOLD 2.5
#define DEFAULT_SHRINK_PERCENT 1.25

typedef struct carray carray;
typedef unsigned int uint;

typedef uint hashtype;
#define PRIME_CST 31
typedef void *type;
#define DEFAULT_TYPE_VALUE NULL

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

char *Char_holder;
#define Char(expr) \
    (Char_holder = malloc(sizeof(char)), \
     *Char_holder = (expr), Char_holder)

signed char *sChar_holder;
#define sChar(expr) \
    (sChar_holder = malloc(sizeof(signed char)), \
     *sChar_holder = (expr), sChar_holder)

unsigned char *uChar_holder;
#define uChar(expr) \
    (uChar_holder = malloc(sizeof(unsigned char)), \
     *uChar_holder = (expr), uChar_holder)

short *Short_holder;
#define Short(expr) \
    (Short_holder = malloc(sizeof(short)), \
     *Short_holder = (expr), Short_holder)

signed short *sShort_holder;
#define sShort(expr) \
    (sShort_holder = malloc(sizeof(signed short)), \
     *sShort_holder = (expr), sShort_holder)

unsigned short *uShort_holder;
#define uShort(expr) \
    (uShort_holder = malloc(sizeof(unsigned short)), \
     *uShort_holder = (expr), uShort_holder)

int *Int_holder;
#define Int(expr) \
    (Int_holder = malloc(sizeof(int)), \
     *Int_holder = (expr), Int_holder)

signed int *sInt_holder;
#define sInt(expr) \
    (sInt_holder = malloc(sizeof(signed int)), \
     *sInt_holder = (expr), sInt_holder)

unsigned int *uInt_holder;
#define uInt(expr) \
    (uInt_holder = malloc(sizeof(unsigned int)), \
     *uInt_holder = (expr), uInt_holder)

long *Long_holder;
#define Long(expr) \
    (Long_holder = malloc(sizeof(long)), \
     *Long_holder = (expr), Long_holder)

long long *lLong_holder;
#define lLong(expr) \
    (lLong_holder = malloc(sizeof(long long)), \
     *lLong_holder = (expr), lLong_holder)

signed long *sLong_holder;
#define sLong(expr) \
    (sLong_holder = malloc(sizeof(signed long)), \
     *sLong_holder = (expr), sLong_holder)

signed long long *slLong_holder;
#define slLong(expr) \
    (slLong_holder = malloc(sizeof(signed long long)), \
     *slLong_holder = (expr), slLong_holder)

unsigned long *uLong_holder;
#define uLong(expr) \
    (uLong_holder = malloc(sizeof(unsigned long)), \
     *uLong_holder = (expr), uLong_holder)

unsigned long long *ulLong_holder;
#define ulLong(expr) \
    (ulLong_holder = malloc(sizeof(unsigned long long)), \
     *ulLong_holder = (expr), ulLong_holder)

float *Float_holder;
#define Float(expr) \
    (Float_holder = malloc(sizeof(float)), \
     *Float_holder = (expr), Float_holder)

double *Double_holder;
#define Double(expr) \
    (Double_holder = malloc(sizeof(double)), \
     *Double_holder = (expr), Double_holder)

long double *lDouble_holder;
#define lDouble(expr) \
    (lDouble_holder = malloc(sizeof(long double)), \
     *lDouble_holder = (expr), lDouble_holder)

bool *Bool_holder;
#define Bool(expr) \
    (Bool_holder = malloc(sizeof(bool)), \
     *Bool_holder = (expr), Bool_holder)

void carray_free_obj(type);

#define free_Obj &carray_free_obj

struct carray
{
    type *_array;
    size_t _size;
    size_t _space;
    size_t _read_position;
};

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

type *carray_subarray_TF(carray *, int, int, void **);

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

#endif //TBAGREL_PROJECT_CARRAY_H
