# Threads
The C++ Threads module provides tools for creating and managing threads. This module is part of the C++ Standard Library and is included in C++11 and newer. 

The main components of the C++ Threads module include `thread`, `mutex`, `lock_guard`, `condition_variable`, and `atomic`. 


## `thread`
### Purpose: 
`std::thread` is used to create and manage threads. It allows a C++ program to run code concurrently in multiple threads.

### Basic Operations:
- **Creating a Thread**: A thread can be created using a function, lambda, or a callable object.
- **Joining a Thread**: The `join()` method makes the calling thread wait for the created thread to finish.
- **Detaching a Thread**: The `detach()` method allows a thread to run independently without blocking the main thread.

### Syntax:
```c
std::thread threadName(functionName, arg1, arg2, ...);
```

Example
```c
#include <iostream>
#include <thread>

void printMessage(const std::string& message) {
    std::cout << message << std::endl;
}

int main() {
    std::thread t1(printMessage, "Hello from thread 1!"); // Creates and starts the thread

    // Ensure the thread completes before the main thread finishes
    t1.join();

    return 0;
}
```

Advance Example
```c
#include <iostream>
#include <thread>

// Function 1 with arguments and return value
int function1(int a, int b) {
    std::cout << "Function 1 is running" << std::endl;
    return a + b;
}

// Function 2 with arguments and return value
std::string function2(const std::string& str) {
    std::cout << "Function 2 is running" << std::endl;
    return str + " World!";
}

int main() {
    int arg1 = 5, arg2 = 10;
    std::string arg3 = "Hello";

    // Create a thread to run multiple functions using a lambda
    std::thread t([arg1, arg2, arg3]() {
        int result1 = function1(arg1, arg2);
        std::cout << "Result of function1: " << result1 << std::endl;

        std::string result2 = function2(arg3);
        std::cout << "Result of function2: " << result2 << std::endl;
    });

    // Ensure main waits for the thread to complete
    t.join();

    std::cout << "Thread has finished execution." << std::endl;
    return 0;
}
```
- Arguments `arg1`, `arg2`, and `arg3` are captured by the lambda.
- The lambda calls `function1` and `function2` sequentially, passing the captured arguments.
- The results of the functions are printed within the lambda.
- `t.join()` ensures that the main thread waits for t to complete before proceeding.

<br>

## Joining and Detaching Threads
`join()`: Makes the calling thread wait until the specified thread completes its execution.

`detach()`: Makes the thread run independently from the main thread. Once detached, it cannot be joined.

Syntax
```c
threadName.join();  // Wait for the thread to complete
threadName.detach(); // Run the thread independently
```

Example
```c
std::thread t2([]() {
    std::cout << "Hello from detached thread!" << std::endl;
});
t2.detach(); // The main thread won't wait for this thread to finish
```
**Important**: Always join or detach threads before the main function ends; otherwise, `terminate()` is called if any joinable thread is not joined or detached.

<br>

## Using `mutex` for Synchronization
Inlcude `#include <mutex>` to use mutexes.
- `std::mutex` is used to prevent data races by locking a section of code.
- `lock()` and `unlock()` methods manage locking manually, while `lock_guard<mutex>` provides RAII-based locking, ensuring the mutex is released automatically when the scope ends.
- `unique_lock<mutex>`: A more flexible RAII class that can be locked and unlocked multiple times during its lifetime and supports deferred locking (i.e., the `mutex` can be locked later after the `unique_lock` is created).

`Resource Acquisition Is Initialization (RAII)`, which means that the acquisition (e.g., locking a `mutex`) and release (e.g., unlocking the `mutex`) of a resource are tied to the lifetime of an object. This technique ensures that resources are properly released when they are no longer needed, which helps prevent resource leaks and makes code more robust and maintainable.

### Example - with `lock_guard<mutex> guard(myMutex)`
```c
#include <iostream>
#include <thread>
#include <mutex>

std::mutex myMutex;
int counter = 0;

void safeIncrement() {
    for (int i = 0; i < 100; ++i) {
        std::lock_guard<std::mutex> guard(myMutex); // Locks mutex and unlocks automatically
        ++counter;
    }
}

int main() {
    std::thread t1(safeIncrement);
    std::thread t2(safeIncrement);

    t1.join();
    t2.join();

    std::cout << "Counter value: " << counter << std::endl; // Safely incremented
    return 0;
}
```

### Example - with `lock()` and `unlock()`

```c
#include <iostream>
#include <thread>
#include <mutex>

std::mutex myMutex;
int counter = 0;

void safeIncrement() {
    for (int i = 0; i < 100; ++i) {
        myMutex.lock(); // Manually lock the mutex
        ++counter;      // Critical section code
        myMutex.unlock(); // Manually unlock the mutex
    }
}

int main() {
    std::thread t1(safeIncrement);
    std::thread t2(safeIncrement);

    t1.join();
    t2.join();

    std::cout << "Counter value: " << counter << std::endl; // Safely incremented
    return 0;
}
```

### Example - with `unique_lock<mutex> lock(myMutex);`
```c
#include <iostream>
#include <thread>
#include <mutex>

std::mutex myMutex;
int counter = 0;

void flexibleIncrement() {
    std::unique_lock<std::mutex> lock(myMutex); // RAII-based locking with `std::unique_lock`
    for (int i = 0; i < 100; ++i) {
        ++counter; // Critical section
    }
    // lock is automatically released when it goes out of scope
}

int main() {
    std::thread t1(flexibleIncrement);
    std::thread t2(flexibleIncrement);

    t1.join();
    t2.join();

    std::cout << "Counter value: " << counter << std::endl; // Safely incremented
    return 0;
}
```
`unique_lock` Features:
- **Flexibility**: Can be locked and unlocked manually if needed (`lock.lock()`, `lock.unlock()`).
- **Deferred Locking**: Can be initialized in an unlocked state and locked later using `lock.lock()`.

Example - Deferred Locking
```c
unique_lock<mutex> lock(myMutex, defer_lock); // Created but not locked

// Perform some non-critical operations
lock.lock(); // Lock when needed
++counter; // Critical section

// lock is automatically released when it goes out of scope
```

## Condition Variables for Synchronization Between Threads
Declaring and Using `std::condition_variable`:
- Used for signaling between threads to notify when certain conditions are met.
- Works alongside `std::unique_lock<std::mutex>` for conditional waiting.

### Syntax
```c
std::condition_variable cv;
std::mutex cvMutex;

void threadFunction() {
    std::unique_lock<std::mutex> lock(cvMutex);
    cv.wait(lock, [] { return condition_met; }); // Waits until condition_met is true
}
cv.notify_one(); // Notifies one waiting thread
cv.notify_all(); // Notifies all waiting threads
```

### Example
```c
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex mtx;
bool ready = false;

void waitThread() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; }); // Wait until 'ready' is true
    std::cout << "Thread notified, condition met." << std::endl;
}

void signalThread() {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate some work
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one(); // Notify waiting thread
}

int main() {
    std::thread t1(waitThread);
    std::thread t2(signalThread);

    t1.join();
    t2.join();

    return 0;
}
```
Explanation:
- `cv.wait(lock, [] { return ready; });` waits until `ready` becomes `true`.
- `cv.notify_one();` signals `t1` to proceed when `ready` is set to `true`.

<br>

## Using `std::atomic` for Lock-Free Operations
Declaring and Using `std::atomic`:
- For simple atomic operations on a single variable without using locks.
- Guarantees thread-safe increments, decrements, and other operations.
- Arithmetic Operations: ++, --, +=, -=, etc.
- Load and Store:
    - `load()`: Atomically reads the value.
    - `store(value)`: Atomically sets the value.
- Exchange:
    - `exchange(newValue)`: Atomically sets the value to newValue and returns the old value.
- Compare and Swap:
    - `compare_exchange_weak(expected, desired)`: Attempts to set the value to desired if it matches expected. This is often used in lock-free data structures for atomic compare-and-swap operations.
### Syntax
```c
#include <atomic>

std::atomic<int> atomicVariable(initialValue);
atomicVariable++; // Thread-safe increment
```

### Example
```c
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> atomicCounter(0);
std::atomic<int> sharedValue(10);

void incrementAtomic() {
    for (int i = 0; i < 1000; ++i) {
        atomicCounter++; // Safe and lock-free
    }
}

void updateValue(int expected, int newValue) {
    int current = sharedValue.load();
    if (sharedValue.compare_exchange_strong(expected, newValue)) {
        std::cout << "Thread " << std::this_thread::get_id() << ": Value updated to " << newValue << std::endl;
    } else {
        std::cout << "Thread " << std::this_thread::get_id() << ": Expected " << expected << ", but found " << current << std::endl;
    }
}

int main() {
    std::thread t1(incrementAtomic);
    std::thread t2(incrementAtomic);
    std::thread t3(updateValue, 10, 30);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Atomic counter value: " << atomicCounter.load() << std::endl;
    std::cout << "Final shared value: " << sharedValue.load() << std::endl;

    return 0;
}
```
**Explanation**
The `atomicCounter++` operation is thread-safe, and `atomicCounter.load()` fetches its value.


## Thread Pooling
Thread pools manage a set of worker threads that can be reused to execute tasks. This is more efficient than creating and destroying threads for each task because thread creation and destruction have a non-trivial performance cost.

Implementation Overview:
- Create a thread pool that continuously runs worker threads.
- Use a task queue to assign new tasks to threads as they become available.
- Use `std::condition_variable` to notify worker threads when tasks are available.