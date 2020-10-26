#include <iostream>
#include <unistd.h>
#include "windows.h"
#include <cstring>

#define INITIAL_STRING "TRY_TO_CHANGE_ME"

char *string;

[[noreturn]] void infiniteLoop() {
    while (true) {
        sleep(5);
        std::cout << string << std::endl;
    }
}

int main() {
    string = (char*)calloc(1024, sizeof(char));
    strcpy(string, INITIAL_STRING);
    std::cout << "Hello, World! Pid = ";

    pid_t pid = getpid();
    std::cout << pid << std::endl;
    infiniteLoop();

    return 0;
}
