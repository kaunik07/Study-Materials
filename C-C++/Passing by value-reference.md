# Summary
| Passing Method     | Syntax                | Creates Copy? | Modifies Original? | Efficiency                      | Typical Use Case                                |
|--------------------|-----------------------|---------------|--------------------|---------------------------------|------------------------------------------------|
| Pass by Value      | `void func(int x)`    | Yes           | No                 | Low overhead for small types    | Basic data types (e.g., int, char)             |
| Pass by Reference  | `void func(int& x)`   | No            | Yes                | High efficiency for large objects | Modifying original object                      |
| Const Reference    | `void func(const int& x)` | No        | No                 | High efficiency, safe from mutation | Large objects without modification intent      |

<br>

# Passing by Reference
When you `pass by reference`, the function receives a reference to the original argument rather than a copy. This allows the function to directly access and modify the original variable.

**How it Works**
- The function works directly with the original variable, not a copy.
- Changes made to the parameter inside the function affect the original variable.

In C++, passing by reference is achieved by using the & symbol after the parameter type.

```c
#include <iostream>

void modifyReference(int& x) {  // x is a reference to the original variable
    x = 100;  // This changes the original variable
    std::cout << "Inside function (pass by reference): x = " << x << std::endl;
}

int main() {
    int a = 10;
    modifyReference(a);  // Pass by reference, so no copy is made

    std::cout << "After function call: a = " << a << std::endl;  // a is now 100
    return 0;
}
```
**Explanation**
- `modifyReference` takes `x` as `a` reference to `a`, so any change made to `x` also affects a.
- After calling `modifyReference`, the value of `a` is 100 because the function directly modified the original variable.

**Use Cases for Pass by Reference**
- Use `pass by reference` when you want the function to modify the original argument.
- Efficient for large data structures (like `std::vector` or `std::string`), where copying could be costly.
- Essential when returning results through function parameters, or when you want to `avoid the overhead of copying large objects`.

<br>

# Passing by Const Reference
A const reference allows you to pass a variable by reference without allowing the function to modify it. This is a good choice when you want the efficiency of passing by reference but still want to protect the original data from changes.

**How it Works**
- The function receives a reference to the original argument, but with const protection, so it cannot modify the argument.
- This is typically used with large objects to avoid unnecessary copying, while ensuring data remains unchanged.

```c
#include <iostream>

void displayValue(const int& x) {  // x is a constant reference
    std::cout << "Inside function (const reference): x = " << x << std::endl;
    // x = 100;  // ERROR: x is a const reference, so it cannot be modified
}

int main() {
    int a = 10;
    displayValue(a);  // Pass by const reference, no copy is made, and a cannot be modified

    std::cout << "After function call: a = " << a << std::endl;  // a is still 10
    return 0;
}
```
**Explanation**
- `displayValue` accepts `x` as a const reference, meaning the function can read but not modify the original value of `a`.
- `a` remains 10 after the function call since `displayValue` cannot alter it.

**Use Cases for `Pass by Const Reference`**
- Use `pass by const reference` when you want to `avoid copying large objects but don’t want the function to modify the data`.
- Ideal for passing large objects (like `std::vector`, `std::map`) where copying is unnecessary and inefficient.

<br>

# Passing by Value
When you `pass by value`, a copy of the argument is made, and this copy is passed to the function. Any modifications made to the parameter inside the function do not affect the original argument, since the function is working with a separate copy.

**How it Works**
- The function creates a local copy of the argument’s value.
- Changes made to the parameter within the function affect only the copy, not the original variable.

This is the default behavior in C++.
```c
#include <iostream>

void modifyValue(int x) {
    x = 100;  // This changes only the copy of x
    std::cout << "Inside function (pass by value): x = " << x << std::endl;
}

int main() {
    int a = 10;
    modifyValue(a);  // Pass by value, so a copy of a is made

    std::cout << "After function call: a = " << a << std::endl;  // a is still 10
    return 0;
}
```
**Explanation**
- `modifyValue` receives a copy of `a`, so when it changes `x` to 100, it affects only `x` (the `local copy`).
- After the function call, `a` remains 10 in `main` because it was `passed by value`, and changes inside the function didn’t affect the original variable.

**Use Cases for Pass by Value**
- Use `pass by value` when you don’t want the function to modify the original argument.
- Ideal for small data types (like int, char, float), where copying is inexpensive.

