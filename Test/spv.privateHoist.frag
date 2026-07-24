#version 450

// Verifies that constant arrays accessed with a runtime index are hoisted
// to a single module-scope Private OpVariable (memoized across access sites
// AND across different functions) rather than being copied into a
// Function-storage temp at every access. Two distinct constants share the
// same access pattern; we expect exactly two Private OpVariables, no
// OpStores of either constant, and OpAccessChain ops in BOTH functions
// referencing the same Private variable for the same constant.

layout(location = 0) flat in int index;
layout(location = 0) out vec4 color;

const float tableA[8] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
const float tableB[8] = { 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };

// Helper accesses tableA from outside main(). Its access sites must share
// the same Private variable that main()'s tableA accesses use.
float helper(int i)
{
    return tableA[i & 7] + tableA[(i + 1) & 7];
}

void main()
{
    // Multiple access sites of tableA from main() -- should share one
    // Private var with the two access sites in helper().
    float a0 = tableA[index];
    float a1 = tableA[(index + 1) & 7];

    // Multiple access sites of tableB from main() only -- should produce
    // a second Private var, distinct from tableA's.
    float b0 = tableB[index];
    float b1 = tableB[(index + 1) & 7];
    float b2 = tableB[(index + 2) & 7];
    float b3 = tableB[(index + 3) & 7];

    float h = helper(index);

    color = vec4(a0 + a1 + h, b0 + b1 + b2 + b3, 0.0, 1.0);
}
