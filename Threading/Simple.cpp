#include <iostream>
#include <thread>
#include <string>

using namespace std;

void printMessage(const string &str){
    cout << str << endl;
}

int main() {
    thread t1(printMessage, "Hello from thread 1");
    thread t2(printMessage, "Hello from thread 2");

    // Ensure main waits for the threads to complete
    t1.join();
    t2.join();
    
    std::cout << "Threads have finished execution." << std::endl;
    return 0;

}