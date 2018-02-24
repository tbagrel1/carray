# *C*-Vector: *Python*-like `list` for *C*

## Goal

Have you ever experienced the full power of *Python* `list` with tons of useful methods and then switching back to a *C* project with poor but incredibly 
fast arrays?

This lightweight library provides a simple way to use *Python*-like `list` in a *C* environment without too much overhead.

## Implementation details

This library is much inspired by both *Python* `list` and *Java* `List` interface, to provide something similar in *C* without impacting performance.
It uses a lot of C Preprocessor commands to provide support for any desired 
type in the same project (but not inside the same vector).

## Disclaimer

Be careful! This library comes with only a few security measures, and should not be used in security-dependant apps. The library is still in alpha 
phase, any comment or bug/issue report would be useful!

## Documentation

The full documentation is generated by *Doxygen*! [Just read it there !](http://tbagrel1.github.io/cvector/doc/index.html)

Link to the documentation: [online documentation](http://tbagrel1.github.io/cvector/doc/index.html)  
You can also download the offline documentation there: [PDF documentation](http://tbagrel1.github.io/cvector/doc/latex/refman.pdf)

## Minimal example

```C
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    TODO: Make minimal example
    return 0;
}

```

## Author

Thomas BAGREL, student in Lycée H. Poincaré, Nancy, France  
[Contact me at: tomsb07 _at_ gmail _dot_ com!](mailto:tomsb07@gmail.com)
