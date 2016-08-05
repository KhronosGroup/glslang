#version 450 core

layout(vertices = 4) out;

patch out vec4 patchOut;

struct S {
    float sMem1;  // should not see a patch decoration
    float sMem2;  // should not see a patch decoration
};

layout(location = 12) patch out TheBlock {
    highp float bMem1;  // should not see a location decoration
    highp float bMem2;
    S s;                // should see a patch decoration
} tcBlock[2];

layout(location = 2) patch out SingleBlock {
    highp float bMem1;  // should not see a location decoration
    highp float bMem2;
    S s;                // should see a patch decoration
} singleBlock;

void main()
{
}
