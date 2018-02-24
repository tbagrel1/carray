# Error No.

## Description

This is the list of values that the global variable `CVECTOR_ERRORNO` can take.

Be careful, only functions which can fail in some cases modify 
`CVECTOR_ERRORNO`.

## Table

`0` always indicate that the operation worked. `$` indicates that the 
following name is a parameter of the function, and `.` denotes an attribute 
of the object.

| Code          | Description                                                 |
|:-------------:|:------------------------------------------------------------|
| `0`           | Successful operation                                        |
| `1`           | `$space < 0` *in* `new_space`                               |
| `2`           | `$space < 0` *in* `new_copy_space`                          |
| `3`           | `$space < $p_original.size` *in* `new_copy_space`           |
| `4`           | `$index > $p_cvector.size` *in* `addi`                      |
| `5`           | `$index < 0` & invalid *in* `addi`                          |

TODO: Table
