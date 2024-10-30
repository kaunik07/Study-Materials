# Summary
- `memcpy`: Copies a specified number of bytes from a source to a destination. Does not handle overlaps.<br>

- `memmove`: Similar to memcpy, but handles overlapping memory regions safely by copying forward or backward as needed.<br>
- `memset`: Sets each byte in a block of memory to a specified value (often used to initialize memory to zero or another byte).<br>
- `memcmp`: Compares two memory blocks byte-by-byte. Returns 0 if they’re identical, or a positive/negative value indicating which is greater.
- `memchr`: Searches for the first occurrence of a specified byte in a memory block. Returns a pointer to the byte or NULL if not found.<br>

<br>

# memset

memset is a function in C that fills a block of memory with a specified value. It is defined in the <string.h> header file.
**Syntax**

```c
void *memset(void *s, int c, size_t n);
```
`s`: Pointer to the block of memory to fill.<br>
`c`: Value to be set. The value is passed as an int, but the function fills the block of memory using the unsigned char conversion of this value.<br>
`n`: Number of bytes to be set to the value.<br>

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[50] = "Hello, World!";

    // Using memset to fill the array with '*'
    memset(str, '*', 5); // Fill the first 5 characters with '*'

    printf("Result: %s\n", str); // Output will be "***** World!"

    return 0;
}
```
Output : In this example, `memset` is used to fill the first 5 characters of the string str with the character '*'. The result is "***** World!".
```
Result: *****, World!
```
**Struct Example**
```c
#include <stdio.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
};

int main() {
    struct Person person;

    // Using memset to initialize the structure to zero
    memset(&person, 0, sizeof(struct Person));

    printf("Name: %s, Age: %d\n", person.name, person.age); // Output will be "Name: , Age: 0"

    return 0;
}
```
Output : In this example, memset is used to initialize all bytes of the person structure to zero. This effectively sets the name array to an empty string and the age to 0.
```
Name: , Age: 0
```

<br>

# memcpy
`memcpy` is a function in C that copies a specified number of bytes from a source memory location to a destination memory location. It is defined in the `<string.h>` header file.

**Syntax**

```c
void *memcpy(void *dest, const void *src, size_t n);
```

`dest`: Pointer to the destination array where the content is to be copied.<br>
`src`: Pointer to the source of data to be copied.<br>
`n`: Number of bytes to copy.

**Step-by-Step Process of memcpy**
1. `Pointer Interpretation`: memcpy treats both src and dest as void*, meaning it doesn’t assume any specific data type—it’s simply copying raw bytes from one location to another.
2. `Byte-by-Byte Copying`: The function copies each byte individually, starting from the first byte of src and moving to dest, continuing this process for n bytes.
3. `No Overlap Handling`: memcpy does not handle overlapping memory regions. If src and dest overlap, it could lead to unexpected results because memcpy might overwrite parts of src before copying them. For overlapping memory, you’d use memmove instead, which handles overlaps correctly.

**Summary**
- `memcpy` is like duplicating a sequence of raw bytes from one memory location to another.
- It’s flexible because it works with `void*`, allowing copying of any `data type`.
- `memcpy` is fast but should be used carefully to avoid issues with overlapping memory or incorrect byte sizes.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char src[50] = "Hello, World!";
    char dest[50];

    // Copying data from src to dest
    memcpy(dest, src, strlen(src) + 1); // +1 to include the null terminator

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}
```

Struct Example

```c
#include <stdio.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
};

int main() {
    struct Person person1 = {"Alice", 30};
    struct Person person2;

    // Copying data from person1 to person2
    memcpy(&person2, &person1, sizeof(struct Person));

    printf("Person 1: Name = %s, Age = %d\n", person1.name, person1.age);
    printf("Person 2: Name = %s, Age = %d\n", person2.name, person2.age);

    return 0;
}
```

`memcpy` naturally performs a `shallow copy` because it copies bytes as-is from one location to another without checking if those bytes represent pointers or dynamically allocated memory. When using `memcpy` on structures with pointers, you only get a copy of the pointers themselves, not the data they point to.

Example
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int age;
} Person;

int main() {
    // Original person
    Person person1;
    person1.name = malloc(50 * sizeof(char));
    strcpy(person1.name, "Alice");
    person1.age = 30;

    // Shallow copy using memcpy
    Person person2;
    memcpy(&person2, &person1, sizeof(Person));

    // Verify the shallow copy
    printf("Person 1 Name: %s, Age: %d\n", person1.name, person1.age);
    printf("Person 2 Name: %s, Age: %d\n", person2.name, person2.age);

    // Modify the name in person2
    strcpy(person2.name, "Bob");

    // Both names are now "Bob" due to shared pointer
    printf("\nAfter modifying person2's name:\n");
    printf("Person 1 Name: %s\n", person1.name);
    printf("Person 2 Name: %s\n", person2.name);

    // Free the allocated memory for person1 and person2
    free(person1.name); // person2.name points to the same memory
    return 0;
}
```
Output 
```
Person 1 Name: Alice, Age: 30
Person 2 Name: Alice, Age: 30

After modifying person2's name:
Person 1 Name: Bob
Person 2 Name: Bob
```

<br>

# memmove
`memmove` is a function in C that copies a specified number of bytes from a source memory location to a destination memory location. Unlike `memcpy`, `memmove` is safe to use when the source and destination overlap. It is defined in the `<string.h>` header file.

**Syntax**

```c
void *memmove(void *dest, const void *src, size_t n);
```
`dest`: Pointer to the destination array where the content is to be copied.<br>
`src`: Pointer to the source of data to be copied.<br>
`n`: Number of bytes to copy.

**How memmove Handles Overlapping Regions**<br>
To understand why memmove works safely with overlapping memory, let’s go through its internal logic:

1. If there’s `no overlap`, memmove can copy forward, just like memcpy.
If there’s overlap, memmove determines whether to copy forward or backward based on the positions of src and dest.
2. `Backward Copying` (Destination > Source): If dest is at a higher memory address than src and overlaps with it, memmove copies bytes from the end of the source region to the beginning. This way, it avoids overwriting the original data as it’s copied.

3. `Forward Copying` (Destination < Source): If dest is lower in memory than src or there’s no overlap, memmove copies bytes forward, as this doesn’t risk overwriting any uncopied data.

`memmove` does `not split` the data. Instead, it shifts the `entire block` of data either forward or backward as needed to prevent data corruption due to overlapping memory regions.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, World!";

    // Using memmove to copy overlapping memory regions
    memmove(str + 7, str, 5); // Copy "Hello" to the position starting at index 7

    printf("Result: %s\n", str); // Output will be "Hello, Hello!"

    return 0;
}
```

<br>

# memcmp
`memcmp` is a function in C that compares two blocks of memory. It is defined in the `<string.h>` header file.
`memcmp` compares two blocks of memory byte-by-byte. It’s useful when you want to check if two memory regions contain the same data or if one region is "less than" or "greater than" the other in lexicographical order.

`memcmp` is useful for comparing raw data, binary structures, or byte arrays, especially when working with files, network data, or system buffers.

**Syntax**

```c
int memcmp(const void *s1, const void *s2, size_t n);
```
`s1`: Pointer to the first block of memory.<br>
`s2`: Pointer to the second block of memory.<br>
`n`: Number of bytes to compare.<br>

**Return Value**:
- `0` if the memory blocks are equal.
- A positive or negative integer if `ptr1` is greater or less than `ptr2`, respectively.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "Hello";
    char str2[] = "Hello00000";
    char str3[] = "World";

    // Compare str1 and str2
    if (memcmp(str1, str2, strlen(str1)) == 0) {
        printf("str1 and str2 are equal\n");
    }

    // Compare str1 and str3
    if (memcmp(str1, str3, strlen(str1)) != 0) {
        printf("str1 and str3 are not equal\n");
    }

    return 0;
}
```
Output
```
str1 and str2 are equal
str1 and str3 are not equal
```

<br>

# memchr
`memchr` is a function in C that searches for the first occurrence of a specified character in a block of memory. It is defined in the `<string.h>` header file.<br>

`memchr` searches for the first occurrence of a specific byte value within a block of memory. This function is similar to strchr for strings but operates on raw memory.<br>

`memchr` is often used in low-level programming where you need to find a specific byte in a buffer, such as locating markers in binary data.

**Syntax**

```c
void *memchr(const void *s, int c, size_t n);
```
`s`: Pointer to the block of memory to be searched.<br>
`c`: Character to be located. The value is passed as an `int`, but it is internally converted to an `unsigned char`.<br>
`n`: Number of bytes to be analyzed.<br>

**Return Value**
- Returns a pointer to the first occurrence of the character `c` in the block of memory pointed to by `s`.
- If the character is not found within the given number of bytes, the function returns `NULL`.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, World!";
    char ch = 'W';

    // Using memchr to find the first occurrence of 'W'
    char *result = memchr(str, ch, strlen(str));

    if (result != NULL) {
        printf("Character '%c' found at position: %ld\n", ch, result - str);
    } else {
        printf("Character '%c' not found.\n", ch);
    }

    return 0;
}
```
Output: 
- `memchr` is used to find the first occurrence of the character `'W'` in the string `str`.
- If the character is found, `memchr` returns a pointer to the location of the character, and the position is calculated by subtracting the base address of the string from the returned pointer.
- If the character is not found, `memchr` returns `NULL`.

```
Character 'W' found at position: 7
```

---

