# Summary
| Context                  | Description                                                                                   |
|--------------------------|-----------------------------------------------------------------------------------------------|
| **Static Variable**          | Retains its value across function calls; scope can be local (in function) or file-level (global). |
| **Static Function**          | Limited to file scope if outside a class; in a class, accessible without an instance.          |
| **Static Member Variable**   | Shared by all instances of a class or struct; only one copy exists for all objects.            |
| **Static Member Function**   | Callable without an instance, can only access other static members.                           |
| **Static Pointer**          | Holds a persistent memory address across function calls, allowing it to point to the same location. |

<br>

# Static Variables

- **Lifetime**: It is allocated once and retains its value across function calls. This applies both to variables inside functions (local static variables) and global variables.
- **Scope**:
    - Inside Functions: A `static` variable inside a function is local to that function but retains its value between function calls.
    - Outside Functions: A `static` global variable limits the variable's visibility to the file it’s declared in (file scope). It helps if want to have same variable names in different files.

Global variable limits
```c
#include <iostream>
static int counter = 0;  // Static global variable, visible only in File1.cpp

void increment() {
    counter++;
    std::cout << "Counter in File1: " << counter << std::endl;
}
```
Inside Functions
```c
#include <iostream>

void countCalls() {
    static int count = 0;  // This is a local static variable
    count++;
    std::cout << "Function called " << count << " times\n";
}

int main() {
    countCalls();  // Output: Function called 1 times
    countCalls();  // Output: Function called 2 times
    countCalls();  // Output: Function called 3 times
    return 0;
}
```
Output:
```
Function called 1 times
Function called 2 times
Function called 3 times
```

<br>

# Static Pointer
A `static pointer` variable retains its value across function calls, similar to any other `static variable`. A `static pointer` points to a memory address that persists between function calls or across a program’s lifetime.

```c
#include <iostream>

void printAddress() {
    static int* ptr = new int(5);  // Static pointer, points to dynamic memory
    std::cout << "Address of static pointer: " << ptr << ", Value: " << *ptr << std::endl;
}

int main() {
    printAddress();
    printAddress();
    printAddress();
    return 0;
}
```
Output:
```
Address of static pointer: 0x5ba26d1d82b0, Value: 5
Address of static pointer: 0x5ba26d1d82b0, Value: 5
Address of static pointer: 0x5ba26d1d82b0, Value: 5
```

<br>

# Static Function
A `static function` declared at the `file scope` (outside any class) is only visible within that file, similar to a static global variable. 

This is useful for functions that are meant to be used only in a specific file, preventing name conflicts with functions in other files.

**Example**: Static Function with File Scope<br>

File1.cpp
```c
#include <iostream>

static void printMessage() {  // Static function, only accessible within File1.cpp
    std::cout << "Hello from a static function!" << std::endl;
}

int main() {
    printMessage();  // Works fine here
    return 0;
}
```
File2.cpp
```c
printMessage();
```
**Output**: The `printMessage` function is limited to `File1.cpp`. It cannot be used or linked to from `File2.cpp`, again ensuring encapsulation and avoiding linkage conflicts.
```
If you try to call printMessage() here, it will cause an error because printMessage() is static to File1.cpp
```

<br>

# Static Member Variable in Classes
In a class, a `static` member variable is shared across all instances of that class. There is only one copy of the static member variable, regardless of how many objects are created.
```c
#include <iostream>

class Counter {
public:
    static int count;  // Static member variable declaration

    Counter() {
        count++;
    }
};

// Define the static variable outside the class
int Counter::count = 0;

int main() {
    Counter c1;
    Counter c2;
    Counter c3;

    std::cout << "Number of objects created: " << Counter::count << std::endl;  // Output: 3
    return 0;
}
```
Output:
- `count` is a static member variable, meaning there’s only one copy of `count`, shared by all instances of `Counter`.
- Each time a `Counter` object is created, count increments. By the end, `count` reflects the total number of `Counter` objects created.
```
Number of objects created: 3
```

<br>

# Static Member Functions in Classes
A `static member function` in C++ is a function that belongs to the class rather than any particular object instance. It can be called on the class itself, rather than on instances of the class. 

Static member functions have the following characteristics:
- **Access**: They can only access other static members (variables or functions) of the class. They cannot access non-static members because they do not have a `this` pointer.
- **Invocation**: They can be called using the class name, without needing to create an instance of the class.
- **Scope**: They have the same scope as the class in which they are declared.

```c
#include <iostream>

class MyClass {
public:
    static int count; // Static member variable

    MyClass() {
        count++;
    }

    // Static member function
    static void displayCount() {
        std::cout << "Count: " << count << std::endl;
    }
};

// Definition of static member variable
int MyClass::count = 0;

int main() {
    MyClass obj1;
    MyClass obj2;

    // Calling static member function using class name
    MyClass::displayCount(); // Output: Count: 2

    // Calling static member function using an object (not recommended)
    obj1.displayCount(); // Output: Count: 2
    return 0;
}
```
**Use Cases for Static Members**

- ***Counters and Shared Data***: Static member variables are commonly used as counters (e.g., tracking the number of instances created) or to share configuration data across all instances.
- ***Utility Functions***: Static member functions are useful for operations that don’t depend on instance-specific data, such as mathematical calculations, string manipulations, or helper functions.
- ***Singleton Patterns***: In design patterns like the Singleton pattern, static member variables and functions can ensure only one instance of a class exists and provide a global point of access to it.
- ***Configuration Settings***: Static variables can hold configuration or environmental settings that apply globally across instances of the class.



 