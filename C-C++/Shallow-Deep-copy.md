# Summary
- `Shallow Copy`: Copies only the immediate data, duplicating pointers rather than the data they point to. Quick but risky for shared data.
- `Deep Copy`: Duplicates everything, including memory pointed to by pointers, ensuring full independence between copies. Requires more memory and careful manual management.

<br>

# Shallow Copy
`Shallow copying` is a process of creating a new object and then copying the non-static fields of the current object to the new object. If the field is a primitive type, its value is copied.

Duplicates only the outermost layer of data. If a structure or object contains pointers to other memory locations, a shallow copy will copy only the pointer values, not the memory they point to. This results in two objects sharing the same referenced memory.



```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int age;
} Person;

int main() {
    // Initialize a Person with a dynamically allocated name
    Person person1;
    person1.name = malloc(20);
    strcpy(person1.name, "Alice");
    person1.age = 30;

    // Perform a shallow copy using memcpy
    Person person2;
    memcpy(&person2, &person1, sizeof(Person));

    // Modify person2's name
    strcpy(person2.name, "Bob");

    // Both person1 and person2 now have the name "Bob" due to shared pointer
    printf("Person 1 Name: %s, Age: %d\n", person1.name, person1.age);
    printf("Person 2 Name: %s, Age: %d\n", person2.name, person2.age);

    // Free allocated memory
    free(person1.name);  // person2.name points to the same memory

    return 0;
}
```
**Output**:
- `person2` now has a copy of person1's name pointer, not a separate copy of the name string itself.
- If we change `person2.name`, it will affect `person1.name` as well since they both point to the same memory.
- This can lead to unintended consequences or bugs if we modify one copy expecting the other to remain unchanged.

```
Person 1 Name: Bob, Age: 30
Person 2 Name: Bob, Age: 30
```
<br>

# Deep Copy
A deep copy duplicates the entire data structure and all the data it references. 

This means that if a structure contains pointers, a deep copy will allocate new memory for the referenced data and copy the actual data (not just the pointer value) into the new memory.

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

    // Deep copy
    Person person2;
    person2.name = malloc(50 * sizeof(char)); // Allocate separate memory for the name
    strcpy(person2.name, person1.name);       // Copy the actual string data
    person2.age = person1.age;                // Copy age

    // Modify the name in person2
    strcpy(person2.name, "Bob");

    // Each name is now independent
    printf("\nAfter modifying person2's name:\n");
    printf("Person 1 Name: %s\n", person1.name);
    printf("Person 2 Name: %s\n", person2.name);

    // Free the allocated memory for both person1 and person2
    free(person1.name);
    free(person2.name);

    return 0;
}
```
**Output**:
- `person2.name` has its own memory, independent of `person1.name`.
- Modifying `person2.name` does not affect person1.name.
```
After modifying person2's name:
Person 1 Name: Alice
Person 2 Name: Bob
```

