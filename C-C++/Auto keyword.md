-# auto

The `auto` keyword in C++ is used for type inference, allowing the compiler to automatically deduce the type of a variable from its initializer. 

```c
auto x = 10; // x is deduced to be of type int
auto y = 3.14; // y is deduced to be of type double
auto str = "Hello"; // str is deduced to be of type const char*
```

# auto&
When you use auto&, you are telling the compiler to deduce the type as a reference. This is useful when you want to avoid copying large objects or when you need to modify the original object.

```c
std::vector<int> vec = {1, 2, 3, 4, 5};
for (auto& elem : vec) {
    elem *= 2; // Modify the original elements in the vector
}
```

### `for (auto x : list)` - Copying Elements
In this loop, x is a copy of each element in list. This means:
- Each element is copied into x on every iteration.
- Any modification to x inside the loop does not affect the original elements in list.
- Copying can incur a performance cost, especially for large objects.
```c
#include <iostream>
#include <vector>

int main() {
    std::vector<int> list = {1, 2, 3, 4, 5};

    for (auto x : list) {
        x += 10;  // Modifies the copy, not the original
        std::cout << x << " ";  // Prints: 11 12 13 14 15
    }
    std::cout << std::endl;

    // Original list remains unchanged
    for (auto x : list) {
        std::cout << x << " ";  // Prints: 1 2 3 4 5
    }
    std::cout << std::endl;

    return 0;
}
```

### `for (auto& x : list)` - Referencing Elements
In this loop, x is a reference to each element in list. This means:

- x directly references each element, so no copies are made.
- Any modification to x directly affects the original elements in list.
- This approach is more efficient, especially for large objects, since it avoids copying.

```c
#include <iostream>
#include <vector>

int main() {
    std::vector<int> list = {1, 2, 3, 4, 5};

    for (auto& x : list) {
        x += 10;  // Directly modifies each element in the list
    }

    // Print modified list
    for (auto x : list) {
        std::cout << x << " ";  // Prints: 11 12 13 14 15
    }
    std::cout << std::endl;

    return 0;
}
```
<br>

# Auto with References and Const
When using `auto` with references or `const`-qualified types, the behavior is slightly different. The compiler will deduce the type based on the initializer expression, but the reference and `const` qualifiers need special consideration.

### `auto` with `const`
When using const, the deduced type will maintain the const qualifier of the initializer.
```c
const int x = 10;
auto y = x;  // y is int, not const int
const auto z = x;  // z is const int

auto& ref = x;  // ref is const int& because x is const int
```
