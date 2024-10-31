# namespace 

`namespace` is a declarative region that provides a way to group related classes, functions, variables, and other identifiers under a common name.

Namespaces help organize code and avoid name conflicts by isolating code in separate logical spaces, especially when large projects or libraries may have identifiers with similar or identical names.

### Why Use Namespaces?
Namespaces help solve two main problems:

- **Avoiding Name Conflicts**: In large projects or when using third-party libraries, you may encounter identifiers with the same name. Namespaces prevent these conflicts by encapsulating identifiers within specific namespaces.
- **Organizing Code**: Namespaces logically group related code, making it easier to navigate and manage.

Examples:

```c
#include <iostream>

// Define a namespace
namespace MathOperations {
    int add(int a, int b) {
        return a + b;
    }

    int multiply(int a, int b) {
        return a * b;
    }
}

//Nested
namespace Company {
    namespace Software {
        void display() {
            std::cout << "Inside Company::Software namespace" << std::endl;
        }
    }
}

int main() {
    // Access functions using the namespace
    std::cout << "Addition: " << MathOperations::add(3, 4) << std::endl;
    std::cout << "Multiplication: " << MathOperations::multiply(3, 4) << std::endl;

    Company::Software::display();

    return 0;
}
```

Example with `using`
the `using` directive allows you to bring all members of a namespace into the current scope, so you don’t have to prefix each identifier.
```c
#include <iostream>

namespace Math {
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
}

using namespace Math;  // Brings all of Math into the global scope
using Math::add;  // Bring only add into the current scope

int main() {
    std::cout << "Addition: " << add(5, 3) << std::endl;        // No need for Math::
    std::cout << "Subtraction: " << subtract(5, 3) << std::endl; // No need for Math::
    return 0;
}
```

## Anonymous Namespaces
An anonymous `namespace` (a namespace without a name) is used to make identifiers local to a specific `translation unit` (usually a single .cpp file). This is useful for `preventing external linkage`, ensuring that identifiers in the anonymous namespace cannot be accessed from other files.

```c
#include <iostream>

namespace {
    void display() {
        std::cout << "Inside anonymous namespace" << std::endl;
    }
}

int main() {
    display();  // Can call display directly
    return 0;
}
```
