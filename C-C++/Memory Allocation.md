# Summary
**C Functions:**
- `malloc` allocates a raw chunk of memory without initializing.
- `calloc` allocates and zeroes out memory.
- `realloc` resizes memory to a new size.
- `free` releases the memory back to the system.<br>

**C++ Operators:**
- `new` allocates a specific object and optionally initializes it.
- `delete` releases memory allocated by new.
- `new[]` allocates an array of objects.
- `delete[]` frees an array allocated by new[].

<br>

# malloc

The `malloc` function in C is used to allocate a specified amount of memory during the execution of a program. It returns a `void*` pointer to the allocated memory. If the allocation fails, it returns `NULL`.

In this example, `malloc` returns a` void*` pointer, which is then cast to an `int*` pointer to be used as an array of integers. This is a common practice when using `malloc` to allocate memory for specific data types.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n, i;

    // Get the number of elements for the array
    n = 5;
    printf("Number of elements: %d\n", n);

    // Dynamically allocate memory using malloc()
    ptr = (int*)malloc(n * sizeof(int));

    // Check if the memory has been successfully allocated by malloc or not
    if (ptr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    } else {
        // Memory has been successfully allocated
        printf("Memory successfully allocated using malloc.\n");

        // Get the elements of the array
        for (i = 0; i < n; ++i) {
            ptr[i] = i + 1;
        }

        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i) {
            printf("%d ", ptr[i]);
        }
    }

    // Free the allocated memory
    free(ptr);

    return 0;
}
```

# calloc

The `malloc` function in C is used to allocate memory for an array of elements, initialize them to zero, and then return a pointer to the memory. If the allocation fails, it returns `NULL`.


```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n, i;

    // Get the number of elements for the array
    n = 5;
    printf("Number of elements: %d\n", n);

    // Dynamically allocate memory using calloc()
    ptr = (int*)calloc(n, sizeof(int));

    // Check if the memory has been successfully allocated by calloc or not
    if (ptr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    } else {
        // Memory has been successfully allocated
        printf("Memory successfully allocated using calloc.\n");

        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i) {
            printf("%d ", ptr[i]);
        }
    }

    // Free the allocated memory
    free(ptr);

    return 0;
}
```

# realloc
The `realloc` function in C is used to resize the memory block that was previously allocated with `malloc` or `calloc`. It changes the size of the memory block without losing the old data. If the new size is larger, the new memory will be uninitialized. If the allocation fails, it returns `NULL`.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n, i;

    // Initial number of elements
    n = 5;
    printf("Number of elements: %d\n", n);

    // Dynamically allocate memory using malloc()
    ptr = (int*)malloc(n * sizeof(int));

    // Check if the memory has been successfully allocated by malloc or not
    if (ptr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    } else {
        // Memory has been successfully allocated
        printf("Memory successfully allocated using malloc.\n");

        // Get the elements of the array
        for (i = 0; i < n; ++i) {
            ptr[i] = i + 1;
        }
    }

    // Resize the memory block using realloc
    n = 10;
    ptr = (int*)realloc(ptr, n * sizeof(int));

    // Check if the memory has been successfully reallocated by realloc or not
    if (ptr == NULL) {
        printf("Memory not reallocated.\n");
        exit(0);
    } else {
        // Memory has been successfully reallocated
        printf("\nMemory successfully reallocated using realloc.\n");

        // Get the new elements of the array
        for (i = 5; i < n; ++i) {
            ptr[i] = i + 1;
        }

        // Print the new elements of the array
        printf("The new elements of the array are: ");
        for (i = 0; i < n; ++i) {
            printf("%d ", ptr[i]);
        }
    }

    // Free the allocated memory
    free(ptr);

    return 0;
}
```

# free
The `free` function in C is used to deallocate the memory that was previously allocated by `malloc`, `calloc`, or `realloc`. It helps to prevent memory leaks by releasing memory that is no longer needed.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n, i;

    // Get the number of elements for the array
    n = 5;
    printf("Number of elements: %d\n", n);

    // Dynamically allocate memory using malloc()
    ptr = (int*)malloc(n * sizeof(int));

    // Free the allocated memory
    free(ptr);
    printf("\nMemory successfully freed.\n");

    return 0;
}
```

# new (C++)
In C++, the `new` operator is used to dynamically allocate memory for an object or array of objects. It returns a pointer to the allocated memory. If the allocation fails, it throws a `std::bad_alloc` exception.

1. int *singleInt = `new` int; allocates memory for a single integer.
2. int *arrayInt = `new` int[n]; allocates memory for an array of n integers.

```c
#include <iostream>

int main() {
    int *ptr;
    int n, i;

    // Get the number of elements for the array
    n = 5;
    std::cout << "Number of elements: " << n << std::endl;

    // Dynamically allocate memory using new
    ptr = new int[n];

    // Check if the memory has been successfully allocated by new or not
    if (ptr == nullptr) {
        std::cout << "Memory not allocated." << std::endl;
        return 1;
    } else {
        // Memory has been successfully allocated
        std::cout << "Memory successfully allocated using new." << std::endl;

        // Get the elements of the array
        for (i = 0; i < n; ++i) {
            ptr[i] = i + 1;
        }

        // Print the elements of the array
        std::cout << "The elements of the array are: ";
        for (i = 0; i < n; ++i) {
            std::cout << ptr[i] << " ";
        }
        std::cout << std::endl;
    }

    // Free the allocated memory using delete
    delete[] ptr;
    std::cout << "Memory successfully freed." << std::endl;

    return 0;
}
```

# delete (C++)
The `delete` operator in C++ is used to deallocate memory that was previously allocated with the `new` operator. It helps to prevent memory leaks by releasing memory that is no longer needed. There are two forms of the delete operator:

1. `delete` for single objects. 
2. `delete[]` for arrays of objects.

The `delete` operator does not have a return type; it simply frees the allocated memory.

```c
#include <iostream>

int main() {
    // Allocate memory for a single integer
    int *singleInt = new int;
    *singleInt = 42;
    std::cout << "Value of singleInt: " << *singleInt << std::endl;

    // Deallocate memory for the single integer
    delete singleInt;

    // Allocate memory for an array of integers
    int n = 5;
    int *arrayInt = new int[n];

    // Initialize the array
    for (int i = 0; i < n; ++i) {
        arrayInt[i] = i + 1;
    }

    // Deallocate memory for the array of integers
    delete[] arrayInt;

    return 0;
}
'''


