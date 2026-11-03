Texture2D<float4> textures[6] : register(t0);

float sampleRow(Texture2D<float4> inputs[3])
{
    return inputs[2].Load(int3(0, 0, 0)).x;
}

float4 main() : SV_Target0
{
    Texture2D<float4> local[2][3];
    local[0][0] = textures[0];
    local[0][1] = textures[1];
    local[0][2] = textures[2];
    local[1][0] = textures[3];
    local[1][1] = textures[4];
    local[1][2] = textures[5];

    // Widening ordinary stride/column constants must not create specialization
    // operations that prevent legalization of this local resource array.
    uint64_t row = 1;
    uint64_t column = 2;
    float variableRow = local[row][1].Load(int3(0, 0, 0)).x;
    float variableColumn = local[1][column].Load(int3(0, 0, 0)).x;

    // Pure 64-bit literal multiplication and addition must also stay folded.
    const uint64_t constantRow = 1;
    const uint64_t constantColumn = 1;
    float constants = local[constantRow][constantColumn].Load(int3(0, 0, 0)).x;

    // A partially indexed row uses the same arithmetic when copying elements.
    float passed = sampleRow(local[row]);
    uint64_t zero = 0;
    float zeroRow = local[zero][column].Load(int3(0, 0, 0)).x;

    // Select descriptors 4, 5, 4, 5, then add the first component of descriptor 2.
    return float4(variableRow, variableColumn, constants, passed) + zeroRow;
}
