# template
`templates` are a powerful feature that allow you to write generic, reusable code. 

`Templates` enable functions and classes to operate with generic types, which means you can create a function or a class that works with any data type without duplicating code.

**There are two main types of templates in C++:**
- Function Templates
- Class Templates

### Function Example
```c
#include <iostream>
using namespace std;

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    int intResult = add(10, 20);       // T is deduced as int
    double doubleResult = add(5.5, 2.3); // T is deduced as double

    cout << "Integer addition: " << intResult << endl;    // Output: 30
    cout << "Double addition: " << doubleResult << endl;  // Output: 7.8

    return 0;
}
```

### Class Example
```c
#include <iostream>
using namespace std;

template <typename T>
class Container {
public:
    T value;

    // Constructor to initialize value
    Container(T v) : value(v) {}
    
    // Member function to display the value
    void display() const {
        cout << "Value: " << value << endl;
    }
};

int main() {
    Container<int> intContainer(10);  // Instantiating Container with int
    intContainer.display();           // Output: Value: 10

    Container<double> doubleContainer(3.14);  // Instantiating Container with double
    doubleContainer.display();                // Output: Value: 3.14

    return 0;
}
```

### Pointer Example
```c
#include <iostream>
using namespace std;

template <typename T>
class Container {
private:
    T* ptr;  // T is expected to be a pointer type

public:
    Container(T* p) : ptr(p) {}

    void display() const {
        std::cout << "Value: " << *ptr << std::endl;
    }
};

int main() {
    int value = 42;
    Container<int*> container(&value);  // Instantiating with int*
    container.display();                // Output: Value: 42

    return 0;
}
```