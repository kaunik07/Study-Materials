# Summary
| Smart Pointer   | Usage                                                                                           |
|-----------------|-------------------------------------------------------------------------------------------------|
| `unique_ptr`    | Use `unique_ptr` when you need exclusive ownership and don’t want to share the resource.        |
| `shared_ptr`    | Use `shared_ptr` when you need shared ownership of a resource across multiple parts of your program. |
| `weak_ptr`      | Use `weak_ptr` to reference a `shared_ptr` without affecting its lifetime or to break circular dependencies. |
<br>

# unique_ptr
`std::unique_ptr` is a smart pointer that owns and manages a dynamically allocated object through a pointer and 
disposes of that object when the `std::unique_ptr` goes out of scope. It ensures that there is only one `std::unique_ptr` pointing to a given object.

Since unique_ptr does not allow copying, you can transfer ownership using `std::move`.
```c
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass Constructor\n"; }
    ~MyClass() { std::cout << "MyClass Destructor\n"; }
};

int main() {
    std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>();

    // std::unique_ptr<MyClass> ptr2 = ptr1; // Error: Cannot copy unique_ptr
    std::unique_ptr<MyClass> ptr2 = std::move(ptr1); // Transfer ownership

    if (!ptr1) {
        std::cout << "ptr1 is null\n";
    }

    return 0;
}
```
<br>

# shared_ptr
`std::shared_ptr` is a smart pointer that allows multiple pointers to share ownership of a single dynamically allocated object. The object is destroyed when the last shared_ptr pointing to it is destroyed (i.e., when the reference count drops to zero).

**Key Characteristics:**
- Manages reference counting automatically.
- Allows multiple shared_ptr instances to share ownership of the same resource.

```c
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass Constructor\n"; }
    ~MyClass() { std::cout << "MyClass Destructor\n"; }
};

int main() {
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();  // Reference count = 1
    std::cout << "Reference count after ptr1: " << ptr1.use_count() << std::endl;

    {
        std::shared_ptr<MyClass> ptr2 = ptr1;  // ptr2 shares ownership with ptr1, reference count = 2
        std::cout << "Reference count after ptr2: " << ptr1.use_count() << std::endl;

        {
            std::shared_ptr<MyClass> ptr3 = ptr1;  // ptr3 also shares ownership, reference count = 3
            std::cout << "Reference count after ptr3: " << ptr1.use_count() << std::endl;
        }  // ptr3 goes out of scope, reference count = 2

        std::cout << "Reference count after ptr3 is out of scope: " << ptr1.use_count() << std::endl;
    }  // ptr2 goes out of scope, reference count = 1

    std::cout << "Reference count after ptr2 is out of scope: " << ptr1.use_count() << std::endl;

    // ptr1 goes out of scope at the end of main, reference count = 0, object is destroyed
    return 0;
}
```
Output:
- `ptr1` is created with `std::make_shared<MyClass>()`, setting the reference count to `1`.
- `ptr2` and `ptr3` are created as copies of `ptr1`, each increasing the reference count.
- When `ptr3` and `ptr2` go out of scope, the reference count decreases back to `1`.
- Finally, when `ptr1` goes out of scope, the reference count drops to `0`, and the MyClass object is deleted.
```
Reference count after ptr1: 1
Reference count after ptr2: 2
Reference count after ptr3: 3
Reference count after ptr3 is out of scope: 2
Reference count after ptr2 is out of scope: 1
MyClass Destructor
```

### Instead of `make_shared` we can use `new` also but not suggested

```c
#include <iostream>
#include <memory>

int main() {
    // Create a std::shared_ptr with new
    std::shared_ptr<int> ptr(new int(42));  // Allocate an int with the value 42

    std::cout << "Value: " << *ptr << std::endl;         // Output: 42
    std::cout << "Reference count: " << ptr.use_count() << std::endl;  // Output: 1

    return 0;  // ptr goes out of scope, memory is freed automatically
}
```
| Method                          | Efficiency                                      | Exception Safety                                      |
|---------------------------------|-------------------------------------------------|-------------------------------------------------------|
| `std::make_shared<int>(42)`     | Single allocation for control block and object  | Exception-safe, no risk of memory leaks               |
| `std::shared_ptr<int>(new int(42))` | Separate allocations for control block and object | Potential risk of memory leaks if exception occurs    |

<br>

# weak_ptr
`std::weak_ptr` is a smart pointer that holds a `non-owning` ("weak") reference to an object that is managed by `std::shared_ptr`. 
It is used to break circular references that can occur with `std::shared_ptr` and prevent memory leaks.

**Key Characteristics:**
- Doesn’t affect the reference count of `shared_ptr`.
- Used to observe (but not own) an object managed by `shared_ptr`.
- Must be converted to `std::shared_ptr` to access the object.

```c
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass Constructor\n"; }
    ~MyClass() { std::cout << "MyClass Destructor\n"; }
};

int main() {
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>();
    std::weak_ptr<MyClass> weakPtr = sharedPtr; // Weak reference

    std::cout << "Use count: " << sharedPtr.use_count() << "\n"; // Output: 1

    if (auto tempPtr = weakPtr.lock()) { // Check if the object is still alive
        std::cout << "Object is still alive\n";
    } else {
        std::cout << "Object has been destroyed\n";
    }

    sharedPtr.reset(); // Destroy the object

    if (auto tempPtr = weakPtr.lock()) { // Check again
        std::cout << "Object is still alive\n";
    } else {
        std::cout << "Object has been destroyed\n";
    }

    return 0;
}
```
Output:
```
MyClass Constructor
Use count: 1
Object is still alive
MyClass Destructor
Object has been destroyed
```

