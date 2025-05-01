# 🧿 C++ Daemon Process

This is a sample implementation of a Unix-style **daemon process in C++**. It runs a background logging task that writes a heartbeat to a log file every second. It also includes:

- Proper **daemonization** (fork, setsid, umask, no stdio)
- **PID file** to track the running process
- **Flock-based locking** to prevent multiple instances
- **Graceful shutdown** with `SIGTERM` and PID cleanup

---

## 🚀 Features

- ✅ Converts a regular C++ program into a daemon
- ✅ Writes logs to `/tmp/daemon_log.txt`
- ✅ Saves PID to `/tmp/mydaemon.pid`
- ✅ Prevents multiple instances with `flock()`
- ✅ Handles `SIGTERM` to clean up resources

---

## 🛠️ Build Instructions

```bash
g++ -std=c++17 daemon.cpp -o daemon

