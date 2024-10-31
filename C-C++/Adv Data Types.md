# signed & unsigned

| Data Type              | Size (bits) | Signed Range                                      | Unsigned Range                           |
|------------------------|-------------|---------------------------------------------------|------------------------------------------|
| `int16_t` / `short`    | 16          | -32,768 to 32,767                                 | 0 to 65,535                              |
| `int32_t` / `int`      | 32          | -2,147,483,648 to 2,147,483,647                   | 0 to 4,294,967,295                       |
| `int64_t` / `long long`| 64          | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 | 0 to 18,446,744,073,709,551,615 |


#### Signed Data Types
Signed data types can represent both positive and negative values. 

The most significant bit (MSB) is used as the sign bit:
- 0 indicates a positive number.
- 1 indicates a negative number.

#### Unsigned Data Types
Unsigned data types can only represent non-negative values. 

All bits are used to represent the magnitude of the number, allowing for a larger positive range compared to signed data types of the same size.

### Choosing Between Signed and Unsigned
- **When to Use Unsigned**: 
    - When you know the values will `never be negative` (e.g., `counts`, `sizes`, `array indices`). To maximize the range of positive values you can store.
- **When to Use Signed**:
    - When you need to represent `both positive and negative values`. 
    - Default choice for integers, as it avoids overflow issues that can arise from unsigned arithmetic (e.g., when subtracting values).

```c
#include <stdio.h>
#include <stdint.h>

int main() {
    int16_t signedShort = -12345;
    uint16_t unsignedShort = 12345U;

    int32_t signedInt = -123456789;
    uint32_t unsignedInt = 123456789U;

    int64_t signedLongLong = -1234567890123456789LL;
    uint64_t unsignedLongLong = 1234567890123456789ULL;

    printf("Signed 16-bit: %d\n", signedShort);
    printf("Unsigned 16-bit: %u\n", unsignedShort);

    printf("Signed 32-bit: %d\n", signedInt);
    printf("Unsigned 32-bit: %u\n", unsignedInt);

    printf("Signed 64-bit: %lld\n", signedLongLong);
    printf("Unsigned 64-bit: %llu\n", unsignedLongLong);

    return 0;
}
```

<br>

# size_t
`size_t` is an unsigned data type defined in the C and C++ standard libraries. It is used to represent the size of objects in bytes and is the type returned by the sizeof operator. 

The exact type of `size_t` varies depending on the platform and compiler, but it is guaranteed to be able to represent the size of the largest possible object on the target platform.

| Property            | Description                                                                 |
|---------------------|-----------------------------------------------------------------------------|
| Type                | Unsigned integer                                                            |
| Use Case            | Memory sizes, counts, and indices                                           |
| Returned by         | `sizeof` operator, `std::vector::size()`, `malloc` parameter, etc.          |
| Platform-Dependent  | Width varies based on platform (32-bit or 64-bit)                           |
| Common Applications | Loop counters, array indexing, and memory allocation                        |
| Size                | Its size can vary (e.g., 32-bit on a 32-bit system, 64-bit on a 64-bit system) |

### Why Use size_t?
- **Portability**: Using size_t ensures that your code is portable across different platforms and compilers.
- **Correctness**: Since size_t is unsigned, it avoids potential issues with negative values when dealing with sizes and counts.
- **Consistency**: It is the standard type for sizes and counts in the C and C++ standard libraries, making your code consistent with library functions.

```c
#include <stdio.h>
#include <stddef.h> // For size_t

int main() {
    // Using size_t to store the size of an array
    int arr[10];
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("The size of the array is: %zu\n", arr_size);

    // Using size_t in a loop
    for (size_t i = 0; i < arr_size; i++) {
        arr[i] = i * 2;
    }

    // Printing the array elements
    for (size_t i = 0; i < arr_size; i++) {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    return 0;
}
```
**Explanation**
- ***Array Size Calculation***:
    - `sizeof(arr)` gives the total size of the array in bytes.
    - `sizeof(arr[0])` gives the size of one element in the array.
    - Dividing these two values gives the number of elements in the array, which is stored in a `size_t` variable arr_size.
- ***Looping with size_t***:
    - `size_t` is used as the type for the loop counter i to ensure it can represent all possible array indices.
- ***Printing with %zu***:
    - The printf format specifier `%zu` is used to print `size_t` values.
