## Summary
| Type                          | Description                                                      |
|-------------------------------|------------------------------------------------------------------|
| **Null Pointer**                  | Points to no valid memory location.                              |
| **Void Pointer**                  | Can point to any data type.                                      |
| **Wild Pointer**                  | Uninitialized pointer pointing to arbitrary memory.              |
| **Dangling Pointer**              | Points to memory that has been freed.                            |
| **Function Pointer**              | Points to a function.                                            |
| **Array of Pointers**             | An array where each element is a pointer.                        |
| **Pointer to Pointer**            | Points to another pointer.                                       |
| **Constant Pointer**          | The address it points to cannot be changed.                      |
| **Pointer to Constant**        | The value at the address cannot be changed.                      |
| **Constant Pointer to Constant**  | Neither the address nor the value can be changed.                |

### Remeber
```int* ptr1, ptr2;```

only `ptr1` is a pointer to an integer. `ptr2` is just an integer.

Explanation:
`int* ptr1` declares `ptr1` as a pointer to an integer.
`ptr2` is declared as an integer because the `*` operator only applies to `ptr1`.

## NULL/nullpt Pointer
A null pointer is a pointer that does not point to any valid memory location. It is often used to indicate that the pointer is not currently pointing to any object.

```c
#include <stdio.h>

int main() {
    int *ptr = NULL; // Null pointer
    if (ptr == NULL) {
        printf("Pointer is null.\n");
    }
    return 0;
}
```

<br>

## Void Pointer
A void pointer is a generic pointer that can point to any data type. It is often used for generic functions that can handle different data types.

```c
#include <stdio.h>

void printValue(void *ptr, char type) {
    if (type == 'i') {
        printf("Integer: %d\n", *(int *)ptr);
    } else if (type == 'f') {
        printf("Float: %f\n", *(float *)ptr);
    }
}

int main() {
    int i = 10;
    float f = 3.14;

    printValue(&i, 'i');
    printValue(&f, 'f');

    return 0;
}
```
Output:
```
Integer: 10
Float: 3.140000
```

<br>

## Wild Pointer
A wild pointer is an uninitialized pointer that points to some arbitrary memory location. Using wild pointers can lead to undefined behavior.

```c
#include <stdio.h>

int main() {
    int *ptr; // Wild pointer
    // *ptr = 10; // Dangerous: Writing to an uninitialized pointer
    return 0;
}
```

<br>

## Dangling Pointer
A dangling pointer is a pointer that points to a memory location that has been freed or deallocated. Accessing a dangling pointer can lead to undefined behavior.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 10;
    free(ptr); // ptr is now a dangling pointer
    // printf("%d\n", *ptr); // Dangerous: Accessing a dangling pointer
    return 0;
}
```
<br>

## Function Pointer
A function pointer is a pointer that points to a function. It can be used to call functions dynamically.

```c
#include <stdio.h>

void printHello() {
    printf("Hello, World!\n");
}

int main() {
    void (*funcPtr)() = printHello; // Function pointer
    funcPtr(); // Calling the function using the pointer
    return 0;
}
```
<br>

## Pointer to Pointer
A pointer to pointer is a pointer that points to another pointer. It is often used in dynamic memory allocation and multi-dimensional arrays.

```c
#include <stdio.h>

int main() {
    int a = 10;
    int *ptr = &a;
    int **ptr2 = &ptr; // Pointer to pointer

    printf("Value of a: %d\n", **ptr2);

    return 0;
}
```
Output
```
Value of a: 10
```
<br>

## Constant Pointer
A constant pointer is a pointer whose value (the address it points to) cannot be changed after initialization.
```c
#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;
    int *const ptr = &a; // Constant pointer

    // ptr = &b; // Error: Cannot change the address stored in ptr
    *ptr = 15; // Allowed: Can change the value at the address

    printf("Value of a: %d\n", a);

    return 0;
}
```
<br>

## Pointer to Constant
A pointer to constant is a pointer that points to a constant value. The value at the address cannot be changed through the pointer.

Pointer to Constant: `const int* ptr;` or `int const* ptr;`
- You cannot modify the value at the address ptr points to.
- You can change where ptr points.

```c
#include <iostream>

int main() {
    int x = 10;
    int y = 20;

    const int* ptr = &x;  // Pointer to a constant integer
    std::cout << "Value pointed to by ptr: " << *ptr << std::endl;

    // *ptr = 15;  // ERROR: Cannot modify the value pointed to by a pointer to constant

    ptr = &y;  // Allowed: Changing the pointer to point to a different address
    std::cout << "Value pointed to by ptr: " << *ptr << std::endl;

    return 0;
}
```
Output:
```
Value pointed to by ptr: 10
Value pointed to by ptr: 20
```


<br>

## Constant Pointer to Constant
A constant pointer to constant is a pointer that cannot change the address it points to, nor can it change the value at that address.

```c
#include <stdio.h>

int main() {
    int a = 10;
    const int *const ptr = &a; // Constant pointer to constant

    // *ptr = 15; // Error: Cannot change the value at the address
    // ptr = &a; // Error: Cannot change the address stored in ptr

    printf("Value of a: %d\n", a);

    return 0;
}
```

<br>

## Dynamic Memory Allocation for Structs (C++ `new` keyword)
When working with structs, you can allocate memory dynamically using pointers. This is especially useful when creating structs at runtime, for instance, when handling large datasets or managing linked data structures (e.g., linked lists, trees).

### C++ - `new`
```c
#include <iostream>
#include <string>

struct Person {
    std::string name;
    int age;
};

int main() {
    // Dynamically allocate a Person struct
    Person* ptr = new Person{"Bob", 25};

    std::cout << "Name: " << ptr->name << std::endl;  // Output: Bob
    std::cout << "Age: " << ptr->age << std::endl;    // Output: 25

    // Free the allocated memory
    delete ptr;

    return 0;
}
```
Output:
- `new Person{"Bob", 25};` dynamically allocates memory for a `Person` struct and initializes it.
- We use `delete` to free the memory once we are done using the struct, preventing memory leaks.

```
Name: Bob
Age: 25
```

### C - `malloc`
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
};

int main() {
    // Dynamically allocate memory for a struct in C
    struct Person* ptr = (struct Person*) malloc(sizeof(struct Person));
    
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize struct members
    strcpy(ptr->name, "Charlie");
    ptr->age = 40;

    // Access struct members
    printf("Name: %s\n", ptr->name);
    printf("Age: %d\n", ptr->age);

    // Free the allocated memory
    free(ptr);

    return 0;
}
```
Output:
- `malloc` allocates memory for `Person` without initializing it. We initialize the members manually.
- We use `free` to deallocate the memory after we’re done.
```
Name: Charlie
Age: 40
```


## Array of Pointers
An array of pointers is an array where each element is a pointer to a data type.

```c
#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;
    int *arr[3] = {&a, &b, &c}; // Array of pointers

    for (int i = 0; i < 3; i++) {
        printf("Value at arr[%d] = %d\n", i, *arr[i]);
    }

    return 0;
}
```
