//
// Copyright (C) 2016 Google, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of Google Inc. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef GLSLANG_GTESTS_MUTEX_H
#define GLSLANG_GTESTS_MUTEX_H

// glslangtest::mutex will be defined and specialized
// depending on the platform that is being compiled.
// It is more or less conformant to the C++11 specification of std::mutex.
// However it does not implement try_lock.

#ifdef _WIN32
// windows.h #defines min and max if we don't define this.
// this means things like std::min and std::max break
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
namespace glslangtest {

// As the name suggests, this mutex class is for running on windows.
// It conforms to the c++11 mutex implementation, and should be a
// drop in replacement.
class windows_mutex {
public:
    using native_handle_type = HANDLE;

    windows_mutex() { mutex_ = CreateMutex(nullptr, false, nullptr); }

    ~windows_mutex()
    {
        if (mutex_ != INVALID_HANDLE_VALUE)
        {
            CloseHandle(mutex_);
        }
    }

    windows_mutex(const windows_mutex &) = delete;
    windows_mutex &operator=(const windows_mutex &) = delete;

    // Locks this mutex, waiting until the mutex is unlocked if it is not already.
    // It is not valid to lock a mutex that has already been locked.
    void lock() { WaitForSingleObject(mutex_, INFINITE); }

    // Unlocks this mutex. It is invalid to unlock a mutex that this thread
    // has not already locked.
    void unlock() { ReleaseMutex(mutex_); }

    // Returns the native handle for this mutex. In this case a HANDLE object.
    native_handle_type native_handle() { return mutex_; }

private:
    HANDLE mutex_;
};

using mutex = windows_mutex;
}

#else
#include <memory>
#include <pthread.h>
namespace glslangtest {

// As the name suggests, this mutex class is for running with pthreads.
// It conforms to the c++11 mutex implementation, and should be a
// drop in replacement.
class posix_mutex {
public:
    using native_handle_type = pthread_mutex_t *;

    posix_mutex() { pthread_mutex_init(&mutex_, nullptr); }

    ~posix_mutex() { pthread_mutex_destroy(&mutex_); }

    posix_mutex(const posix_mutex &) = delete;
    posix_mutex &operator=(const posix_mutex &) = delete;

    // Locks this mutex, waiting until the mutex is unlocked if it is not already.
    // It is not valid to lock a mutex that has already been locked.
    void lock() { pthread_mutex_lock(&mutex_); }

    // Unlocks this mutex. It is invalid to unlock a mutex that this thread
    // has not already locked.
    void unlock() { pthread_mutex_unlock(&mutex_); }

    // Returns the native handle for this mutex. In this case a pthread_mutex_t*.
    native_handle_type native_handle() { return &mutex_; }

private:
    pthread_mutex_t mutex_;
};

using mutex = posix_mutex;
}
#endif

#endif // GLSLANG_GTESTS_MUTEX_H
