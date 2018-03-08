#ifndef DEF_CVECTOR_IMPORT
#define DEF_CVECTOR_IMPORT

void no_error_func(int level, const char *message) {
    return;
}

typedef char *str;
#define CVECTOR_T str
#define CVECTOR_DEFAULT_VALUE NULL
#define CVECTOR_ERROR_FUNC no_error_func

#include "../cvector.h"

#define CVECTOR_T int
#define CVECTOR_ERROR_FUNC no_error_func

#include "../cvector.h"

#endif  // DEF_CVECTOR_IMPORT
