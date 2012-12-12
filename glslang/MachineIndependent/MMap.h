//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
//FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
//COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//POSSIBILITY OF SUCH DAMAGE.
//

#ifndef _MMAP_INCLUDED_
#define _MMAP_INCLUDED_

//
// Encapsulate memory mapped files
//

class TMMap {
public:
    TMMap(const char* fileName) : 
        fSize(-1), // -1 is the error value returned by GetFileSize()
        fp(NULL),
        fBuff(0)   // 0 is the error value returned by MapViewOfFile()
    {
        if ((fp = fopen(fileName, "r")) == NULL)
            return;
        char c = getc(fp);
        fSize = 0;
        while (c != EOF) {
            fSize++;
            c = getc(fp);
        }
        if (c == EOF)
            fSize++;
        rewind(fp);
        fBuff = (char*)malloc(sizeof(char) * fSize);
        int count = 0;
        c = getc(fp);
        while (c != EOF) {
            fBuff[count++] = c;
            c = getc(fp);
        }
        fBuff[count++] = c;
    }

    char* getData() { return fBuff; }
    int   getSize() { return fSize; }

    ~TMMap() {
        if (fp != NULL)
            fclose(fp);
    }
    
private:
    int             fSize;      // size of file to map in
    FILE *fp;
    char*           fBuff;      // the actual data;
};

#endif // _MMAP_INCLUDED_
