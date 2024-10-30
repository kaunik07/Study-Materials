# Summary
| Storage Class       | Scope                | Lifetime          | Purpose                                                                 |
|---------------------|----------------------|-------------------|-------------------------------------------------------------------------|
| `auto`              | Block                | Temporary         | Default for local variables; rarely used explicitly.                    |
| `static`            | Function/File scope  | Program lifetime  | Retains value across calls or limits global scope to a file.            |
| `extern`            | Global               | Program lifetime  | Declares a variable/function in another file, sharing across multiple files. |
| `register`          | Block                | Temporary         | Requests storage in a CPU register for fast access (not guaranteed).    |
| `mutable` (C++)     | Class/Member scope   | Object lifetime   | Allows modification of const objects, used for specific mutable class members. |
| `thread_local` (C++11+) | Global/Static/Block | Thread lifetime   | Creates a unique variable instance for each thread, useful for multi-threaded applications. |


<br>

# Static Storage (static)
- Scope: In functions, `static` variables have function scope (only accessible within that function), but they persist across function calls. If declared outside functions, they have file scope (only accessible within the same file).
- Lifetime: Static duration — they are created when the program starts and destroyed when it ends.
- Memory Location: Stored in a specific memory section for `static` variables.
- Use Case:
    - Inside functions, `static` allows a variable to retain its value between function calls.
    - Outside functions, `static` limits a global variable's scope to the file it’s declared in.

```c
#include <stdio.h>

void count() {
    static int counter = 0;  // Initialized only once, retains value across calls
    counter++;
    printf("Counter: %d\n", counter);
}

int main() {
    count();  // Output: Counter: 1
    count();  // Output: Counter: 2
    return 0;
}
```
Output
```
Counter: 1
Counter: 2
```

<br>

# Mutable Storage (mutable)

The `mutable` keyword in C++ allows you to modify specific member variables of a class, even if the object itself is declared as const.

In other words, `mutable` enables modifications of particular member variables inside a const member function or through a const object.

**When to Use mutable**

- Caching: For example, storing the result of a calculation so you don’t have to recompute it each time a function is called. The cache variable can be mutable so that it can be updated within a const function.

- Tracking Internal State: For instance, counting the number of times a function is called (like the Counter example above) without affecting the “logical” constness of the object.

- Debugging Flags or Logs: Variables used only for debugging or logging can be marked as mutable so they can be modified in const contexts without breaking const correctness.



```c
#include <iostream>

class Counter {
public:
    mutable int count = 0;  // Mutable member variable to track calls

    // const member function that modifies a mutable variable
    void increment() const {
        count++;  // Allowed because count is mutable
    }

    void displayCount() const {
        std::cout << "Count: " << count << std::endl;
    }
};

int main() {
    const Counter c;  // `c` is a const object

    // Even though c is const, we can still modify `count` because it's mutable
    c.increment();
    c.increment();
    c.displayCount();  // Output: Count: 2

    return 0;
}

```
Output:
- `mutable int count`: The `count` variable is marked as `mutable`, so it can be modified even when accessed through a `const` object.
- `increment` as a `const` function: The `increment` function is `const`, meaning it can be called on a `const` object.  Normally, this would prevent any modification of member variables, but because `count` is `mutable`, it can still be changed.
- Result: Despite `c` being a `const` Counter object, `increment()` successfully modifies count because `count` is `mutable`.
```
Count: 2
```

# External Storage (extern)
- Purpose: Used to declare a `global variable` or function that is defined in `another file`.
- Scope: Depends on the location — if declared outside all functions, it has global scope.
- Lifetime: Static duration; the variable exists for the duration of the program.
- Use Case: `extern` is useful for sharing global variables across multiple files. It doesn’t allocate memory but rather refers to a global variable or function defined elsewhere.

Example: File1.c
```c
#include <stdio.h>

int counter = 5;  // Global variable definition

void printCounter() {
    printf("Counter: %d\n", counter);
}
```
File2.c
```c
extern int counter;  // Declare the variable, defined in File1.c

int main() {
    printCounter();  // Output: Counter: 5
    return 0;
}
```
<br>


# Thread-local Storage (thread_local) (C++11 and Later)
The thread_local storage class ensures that each thread has its own separate instance of a variable, meaning each thread can access and modify its own copy independently of other threads.

This is particularly useful in multi-threaded programs where you want to avoid data races by giving each thread its own copy of a variable.

**Key Characteristics of thread_local**
- ***Storage Duration***: The lifetime of a `thread_local` variable is tied to the lifetime of the thread that accesses it. Each thread’s instance of a thread_local variable is created when the thread starts and is destroyed when the thread terminates.

- ***Scope and Linkage***: `thread_local` can be applied to variables with various scopes:
    - ***Global or Namespace Scope***: The variable is globally accessible, but each thread has its own independent instance.
    - ***Static and Function Scope***: Inside functions, `thread_local` can be applied to static local variables, giving each thread its own static variable that persists across function calls within the same thread.
- ***Initialization***: Each thread’s instance of a `thread_local` variable is initialized independently, and if it has a complex type (like a class or struct), the constructor will run separately for each thread.

**Benefits of thread_local**
- Avoids Data Races: Since each thread has its own independent instance of a thread_local variable, it removes the need for locks or other synchronization mechanisms on that variable, reducing the chance of data races.
- Performance: By eliminating the need for synchronization, thread_local can improve performance in situations where each thread needs its own working copy of a variable.

**Global Scope Example**
```c
#include <iostream>
#include <thread>

thread_local int counter = 0;  // Each thread has its own independent counter

void incrementCounter() {
    ++counter;
    std::cout << "Thread " << std::this_thread::get_id() << " counter: " << counter << std::endl;
}

int main() {
    std::thread t1(incrementCounter);  // Thread t1
    std::thread t2(incrementCounter);  // Thread t2

    t1.join();
    t2.join();

    return 0;
}
```
Output : 
``` 
Thread 140559867905792 counter: 1
Thread 140559859513088 counter: 1
```
<br>

**Local Scope Example** : 
When you declare a `thread_local` variable, even if it’s within a function, it behaves similarly to a `static` variable. 
```c
#include <iostream>
#include <thread>

// Function with a local thread_local variable
void threadFunction() {
    // Each thread has its own independent `call_count` that persists across calls
    thread_local int call_count = 0;
    ++call_count;

    std::cout << "Thread " << std::this_thread::get_id() 
              << " call count: " << call_count << std::endl;
}

int main() {
    // Launch two threads that call threadFunction multiple times
    std::thread t1([]() {
        threadFunction();
        threadFunction();
        threadFunction();
    });

    std::thread t2([]() {
        threadFunction();
        threadFunction();
    });

    t1.join();
    t2.join();

    return 0;
}
```
Output:
```
Thread 140360067270400 call count: 1
Thread 140360067270400 call count: 2
Thread 140360067270400 call count: 3
Thread 140360058877696 call count: 1
Thread 140360058877696 call count: 2
```

<br>

# Automatic Storage (auto)
- Default Storage for Local Variables: In both C and C++, local variables declared within a function or block are `auto` by default.
- Scope: Block scope, meaning they’re only accessible within the block where they are defined.
- Lifetime: Exists only while the function/block is active. Created when the function is entered and destroyed when it exits.
- Memory Location: Stored on the stack.
- Explicit Use: While `auto` is the default, you rarely see it explicitly used in C and C++ (though `auto` in modern C++ is also used for type inference, which is different).

```c
void example() {
    auto int x = 10;  // `auto` is implied, so this is the same as `int x = 10;`
    int y = 20;       // `y` is also an automatic variable, as `auto` is implied
}
```

<br>

# Register Storage (register)
- Purpose: Requests the compiler to store the variable in a CPU register for faster access. (The compiler may ignore this request if registers are unavailable.)
- Scope: Block scope, similar to `auto`.
- Lifetime: Exists only during the function or block where it is defined.
- Memory Location: Stored in a CPU register if possible; otherwise, stored on the stack.
- Restrictions: Since it’s intended for CPU registers, you cannot take the address of a `register` variable (using `&` operator).
```c
void func() {
    register int counter = 0;  // Request fast access
    for (register int i = 0; i < 100; i++) {
        counter += i;
    }
}
```

