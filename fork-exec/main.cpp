#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <cassert>

using namespace std::literals::chrono_literals;

int main() {
    pid_t pid = fork();
    if (pid == -1) {
        std::cout << "Fork failed" << std::endl;
        exit(1);
    } else if (pid == 0) {
        std::cout << "[" << std::to_string(getpid()) << "] ";
        std::cout << "I am the child" << std::endl;
        std::this_thread::sleep_for(5s);
        char* argv[] = { nullptr };
        char* envp[] = { nullptr };
        execve("./child", argv, envp);
        assert(false);
    } else if (pid) {
        std::cout << "[" << std::to_string(getpid()) << "] ";
        std::cout << "I am the parent, my child is: " << std::to_string(pid) << std::endl;
        std::this_thread::sleep_for(5s);
        exit(0);
    }
}
