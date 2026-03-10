#!/bin/bash

# Copyright (C) 2020 Google, Inc.
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#    Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#
#    Neither the name of Google Inc. nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

set -e # Fail on any error.

. /bin/using.sh # Declare the bash `using` function for configuring toolchains.

set -x # Display commands being run.

using ninja-1.10.0
using python-3.12

# The gclient sync command needs the "python" executable, not just "python2" or "python3".
pyenv local 3.12.4

# Disable git's "detected dubious ownership" error - kokoro checks out the repo
# with a different user, and we don't care about this warning.
git config --global --add safe.directory '*'

echo "Fetching external projects..."
./update_glslang_sources.py

echo "Fetching depot_tools..."
[ -d /tmp ] || mkdir -p /tmp
cd /tmp
git clone --depth 1 https://chromium.googlesource.com/chromium/tools/depot_tools.git depot_tools
export PATH="/tmp/depot_tools:$PATH"

echo "Syncing client..."
gclient sync --gclientfile=standalone.gclient
gn gen out/Default

echo "Building..."
cd out/Default
ninja
