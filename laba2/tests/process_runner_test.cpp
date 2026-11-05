
#include <iostream>
#include "process_runner.h"

int main() {
    std::cout << "--- Program test started ---" << std::endl;

    int result = 0;

#ifdef _WIN32
    const char* test_command = "whoami";
#else
    const char* test_command = "whoami";
#endif

    std::cout << "Launching child process..." << std::endl;

    bool started = launch_program(test_command, true, &result);

    if (started) {
        std::cout << "Child process finished!" << std::endl;
        std::cout << "Return code: " << result << std::endl;
    }
    else {
        std::cout << "Error: Could not launch the process." << std::endl;
    }

    return 0;
}
