#include <iostream>         // For basic I/O (only used before daemonizing)
#include <fstream>          // For logging to a file
#include <unistd.h>         // For fork(), getpid(), chdir(), etc.
#include <thread>           // For running the logging task in a separate thread
#include <chrono>           // For sleep intervals
#include <sys/types.h>      // For system-level types like pid_t
#include <sys/stat.h>       // For umask()
#include <fcntl.h>          // For open(), file creation flags
#include <sys/file.h>       // For flock() to lock the PID file
#include <cstring>          // For strerror()
#include <csignal>          // For signal handling
#include <cstdlib>          // For exit(), EXIT_FAILURE

const std::string PID_FILE_PATH = "/tmp/mydaemon.pid"; // Path to store the PID of the daemon
int pidFileFD = -1;  // File descriptor for PID file — used for locking and cleaning on exit

// 🧹 Signal handler to clean up PID file on SIGTERM
void handleSignal(int sig) {
    if (sig == SIGTERM) {                        // If process receives termination signal
        if (pidFileFD != -1) {
            unlink(PID_FILE_PATH.c_str());       // Delete the PID file
            close(pidFileFD);                    // Release file descriptor and lock
        }
        exit(0);                                 // Exit gracefully
    }
}

// 🔁 Function run by a background thread — logs a timestamp every second
void runDaemonTask() {
    while (true) {
        std::ofstream log("/tmp/daemon_log.txt", std::ios::app); // Open log file in append mode
        log << "Daemon is alive at " << time(nullptr) << "\n";   // Write current time
        log.close();                                              // Close the log
        std::this_thread::sleep_for(std::chrono::seconds(1));    // Sleep for 1 second
    }
}

// 🔒 Checks if daemon is already running and writes PID to file (with locking)
void checkAndWritePIDFile(const std::string& path) {
    pidFileFD = open(path.c_str(), O_RDWR | O_CREAT, 0666);  // Open or create PID file
    if (pidFileFD < 0) {
        std::cerr << "Failed to open PID file: " << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }

    if (flock(pidFileFD, LOCK_EX | LOCK_NB) < 0) {           // Try to get exclusive lock
        std::cerr << "Another instance is already running.\n";
        close(pidFileFD);                                    // Release FD
        exit(EXIT_FAILURE);                                  // Exit if lock fails
    }

    ftruncate(pidFileFD, 0);                                 // Clear any previous content
    std::string pid = std::to_string(getpid()) + "\n";       // Get current process ID
    write(pidFileFD, pid.c_str(), pid.length());             // Write PID into the file
}

// 🧙 Converts the process into a proper daemon
void becomeDaemon() {
    pid_t pid = fork();                        // Fork to run in background
    if (pid < 0) exit(EXIT_FAILURE);           // Fork failed
    if (pid > 0) exit(EXIT_SUCCESS);           // Parent exits, child continues

    umask(0);                                  // Reset file mode creation mask
    if (setsid() < 0) exit(EXIT_FAILURE);      // Start new session and detach from terminal
    chdir("/");                                // Change working dir to root (best practice)

    // 🔇 Close standard file descriptors since daemon runs in background
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    checkAndWritePIDFile(PID_FILE_PATH);       // 🔐 Ensure only one instance and save PID

    std::signal(SIGTERM, handleSignal);        // Set signal handler for graceful termination

    std::thread t(runDaemonTask);              // Start logging in background thread
    t.detach();                                // Detach thread to let it run independently

    // 💤 Keep the daemon alive (main thread sleep loop)
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Idle loop
    }
}

// 🚀 Entry point of the program
int main() {
    becomeDaemon();                            // Start the daemon
    return 0;
}

