# Summary 

- `memcpy` → `std::copy`: Safer and type-aware copying, with iterator support.
- `memmove` → `std::copy` (for overlapping regions): std::copy is designed to handle overlapping ranges safely.
- `memset` → `std::fill` / `std::fill_n`: Type-safe, high-level way to initialize or set values.
- `memcmp` → `std::equal`: Compares ranges with type safety and iterator support.
- `memchr` → `std::find`: Searches for a value within a container or range safely

<br>

# copy & move 
These functions from the C++ Standard Library are safer and more flexible for copying and moving data, as they work with iterators and handle overlapping ranges for objects properly.

`std::copy`: Copies a range of elements (like memcpy but with type safety).<br>
`std::move`: Transfers (moves) elements from one range to another, generally used with move semantics to avoid unnecessary copying in C++.

```c
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2(5);

    // Copy vec1 to vec2
    std::copy(vec1.begin(), vec1.end(), vec2.begin());

    for (int val : vec2) {
        std::cout << val << " ";  // Output: 1 2 3 4 5
    }

    return 0;
}
```

<br>

# fill & fill_n
`std::fill` and `std::fill_n` provide a safer alternative to memset for initializing or setting a range of values in containers or arrays.

`std::fill`: Sets all elements in a range to a specified value.

```c
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec(10);

    // Set all elements to 5
    std::fill(vec.begin(), vec.end(), 5);

    for (int val : vec) {
        std::cout << val << " ";  // Output: 5 5 5 5 5 5 5 5 5 5
    }

    return 0;
}
```

`std::fill_n`: Sets the first n elements of a range to a specified value.
```c
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec(10, 0);  // Initialize vector of size 10 with all elements set to 0

    // Set the first 5 elements to 42
    std::fill_n(vec.begin(), 5, 42);

    // Print the vector contents
    for (int val : vec) {
        std::cout << val << " ";  // Expected output: 42 42 42 42 42 0 0 0 0 0
    }

    return 0;
}
```

<br>

# equal
`std::equal `provides a safer alternative to memcmp for comparing containers or ranges. It compares two ranges of elements for equality, ensuring they contain the same values in the same order.

```c
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {1, 2, 3, 4, 5};

    if (std::equal(vec1.begin(), vec1.end(), vec2.begin())) {
        std::cout << "Vectors are equal\n";  // Output: Vectors are equal
    }

    return 0;
}
```

<br>

# find
`std::find` is a safer alternative to memchr for searching within containers or ranges. It locates the first occurrence of a specified value within a range.

```c
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Find the value 3 in the vector
    auto it = std::find(vec.begin(), vec.end(), 3);
    if (it != vec.end()) {
        std::cout << "Found value: " << *it << "\n";  // Output: Found value: 3
    } else {
        std::cout << "Value not found\n";
    }

    return 0;
}
```