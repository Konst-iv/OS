
#include "process_runner.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/wait.h>
#endif

bool launch_program(const char* program_command, bool wait_until_finished, int* result_code) {

#ifdef _WIN32
    STARTUPINFOA startup_info;
    PROCESS_INFORMATION process_info;

    ZeroMemory(&startup_info, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    ZeroMemory(&process_info, sizeof(process_info));

    char* command_line = strdup(program_command);

    if (!CreateProcessA(NULL, command_line, NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_info)) {
        free(command_line);
        return false;
    }

    free(command_line);

    if (wait_until_finished) {
        WaitForSingleObject(process_info.hProcess, INFINITE);

        if (result_code != nullptr) {
            DWORD code;
            GetExitCodeProcess(process_info.hProcess, &code);
            *result_code = code;
        }
    }

    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);

    return true;

#else
    pid_t child_pid = fork();

    if (child_pid < 0) {
        return false;
    }

    if (child_pid == 0) {
        execl("/bin/sh", "sh", "-c", program_command, nullptr);
        exit(127);
    }
    else {
        if (wait_until_finished) {
            int process_status;
            waitpid(child_pid, &process_status, 0);

            if (result_code != nullptr) {
                if (WIFEXITED(process_status)) {
                    *result_code = WEXITSTATUS(process_status);
                }
                else {
                    *result_code = -1;
                }
            }
        }

        return true;
    }
#endif
}
