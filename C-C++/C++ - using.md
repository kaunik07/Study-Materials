# using
In C++11 and later, `using` can create type aliases, serving as a more modern and flexible alternative to `typedef`.

In C++, the `using` keyword has several important uses that improve code readability and flexibility. It can be used to create type aliases, introduce names into a scope, simplify the syntax for complex template types, and more.

### Syntax
```c
using new_type = existing_type;
```

Example
```c
#include <iostream>
#include <vector>
#include <map>

// Simple type aliases
using intPtr = int*;                 // intPtr is now an alias for int*
using String = std::string;           // String is an alias for std::string

// Aliasing complex types
using StringIntMap = std::map<std::string, int>;

int main() {
    int a = 5;
    intPtr ptr = &a;                  // intPtr is used as int*
    String name = "Alice";            // String is used as std::string

    StringIntMap ageMap;              // Using alias for map
    ageMap["Alice"] = 30;
    ageMap["Bob"] = 25;

    std::cout << "Name: " << name << ", Age: " << ageMap["Alice"] << std::endl;
    //Output: Name: Alice, Age: 30

    return 0;
}
```

With `template` example
```c
#include <iostream>
#include <vector>
#include <map>

// Template alias for a map with string keys
template <typename T>
using StringMap = std::map<std::string, T>;

int main() {
    StringMap<int> ageMap;            // StringMap<int> is now a std::map<std::string, int>
    ageMap["Alice"] = 30;
    ageMap["Bob"] = 25;

    std::cout << "Alice's Age: " << ageMap["Alice"] << std::endl;
    // Output : Alice's Age: 30

    return 0;
}
```
