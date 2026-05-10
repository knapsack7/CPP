#ifndef PROFILER_H
#define PROFILER_H

#ifdef ENABLE_PROFILING
#include <gperftools/profiler.h>
#include <string>
#include <iostream>

class Profiler {
public:
    static void start(const std::string& profile_name) {
        ProfilerStart(profile_name.c_str());
        std::cout << "Profiling started: " << profile_name << std::endl;
    }

    static void stop() {
        ProfilerStop();
        std::cout << "Profiling stopped" << std::endl;
    }

    static void flush() {
        ProfilerFlush();
    }
};

class ScopedProfiler {
public:
    explicit ScopedProfiler(const std::string& profile_name) {
        Profiler::start(profile_name);
    }

    ~ScopedProfiler() {
        Profiler::stop();
    }
};

#define PROFILE_SCOPE(name) ScopedProfiler profiler_##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__)

#else
// No-op versions when profiling is disabled
class Profiler {
public:
    static void start(const std::string&) {}
    static void stop() {}
    static void flush() {}
};

class ScopedProfiler {
public:
    explicit ScopedProfiler(const std::string&) {}
};

#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif

#endif // PROFILER_H 