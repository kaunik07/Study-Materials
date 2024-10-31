# decltype
`decltype` is a powerful keyword introduced in C++11 that allows you to query the type of an expression at compile time. 

This makes it possible to determine the type of variables, expressions, or return values automatically, which is particularly useful in generic programming and templates.

### Syntax
```c 
decltype(expression) variableName;
```

### When to Use decltype
- **Automatic Type Deduction**: To get the type of a complex expression without needing to manually figure it out.
- **Templates and Generic Code**: For deducing return types of functions in template-based code.
- **Consistency**: Ensures that the type matches the original expression’s type, helping avoid accidental type mismatches.

```c
#include <iostream>

int x = 10;
int& getX() {
    return x;
}

int main() {
    int x = 10;
    decltype(x) y = 20;  // y has the same type as x (int)
    std::cout << "Type of y is the same as x: " << y << std::endl;

    int a = 5;
    double b = 10.5;
    decltype(a + b) result = a + b;  // Deduces the type of a + b, which is double
    
    decltype(auto) y = getX();  // y is int&, same type as getX()
    y=20
    std::cout << "x: " << x << ", y: " << y << std::endl;  // Output: x: 20, y: 20

    return 0;
}
```

## Summary of `decltype`
- `decltype` allows you to deduce the type of an expression at compile time.
- It’s often used in generic code, templates, and for deducing return types based on complex expressions.
- `decltype(auto)` provides more precise type deduction than auto, as it preserves references and const qualifiers.


