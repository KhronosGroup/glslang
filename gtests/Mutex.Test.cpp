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

#include "Mutex.h"

#include <gtest/gtest.h>
#include <thread>

namespace {

TEST(MutexTest, CanCreateMutex)
{
    glslangtest::mutex mutex;
    mutex.lock();
    mutex.unlock();
}

void increment_by_1000(glslangtest::mutex &mut, int &i)
{
    for (size_t j = 0; j < 1000; ++j)
    {
        mut.lock();
        i = i + 1;
        mut.unlock();
    }
}

TEST(MutexTest, MutexLocks)
{
    glslangtest::mutex mutex;
    int i = 0;
    std::thread t1([&mutex, &i]() { increment_by_1000(mutex, i); });
    std::thread t2([&mutex, &i]() { increment_by_1000(mutex, i); });
    std::thread t3([&mutex, &i]() { increment_by_1000(mutex, i); });
    t1.join();
    t2.join();
    t3.join();
    EXPECT_EQ(3000, i);
}
} // anonymous namespace
