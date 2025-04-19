# `multiple_return.h`
Experiment in C to allow Go-style multiple return values from a function using
macros. 

Requires support for `__auto_type` (gcc & clang) and doesn't support using
types with spaces in them (`struct foo`), i.e. need to `typedef` your structs.

Usage code:
```c
#include "multiple_return.h"

ret(float, int) multiple_ret(int a) {
    int err = -1;
    mreturn(float, int){4.2 + a, err};
}

int main() {
    m(float, int)(a, b) = multiple_ret(3);
    printf("%.1f %d\n", a, b); // 7.2 -1
}
```
