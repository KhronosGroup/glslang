Texture2D<float4> textures[6] : register(t0);
Texture2D<float4> matrixTextures[2][3] : register(t6);
Texture2D<float4> cubeTextures[2][2][3] : register(t12);

float4 sampleRow(Texture2D<float4> inputs[3], uint index)
{
    return inputs[index].Load(int3(0, 0, 0));
}

float4 sampleConstRow(const Texture2D<float4> inputs[3])
{
    return inputs[2].Load(int3(0, 0, 0));
}

float4 sampleMatrix(Texture2D<float4> inputs[2][3])
{
    return sampleRow(inputs[1], 2);
}

void replaceRow(out Texture2D<float4> outputs[3])
{
    outputs[0] = textures[0];
    outputs[1] = textures[1];
    outputs[2] = textures[2];
}

void swapRow(inout Texture2D<float4> inputs[3])
{
    Texture2D<float4> first = inputs[0];
    inputs[0] = inputs[2];
    inputs[2] = first;
}

cbuffer Indices : register(b24)
{
    uint row;
};

float4 main() : SV_Target0
{
    Texture2D<float4> localTextures[2][3];
    localTextures[0][0] = textures[0];
    localTextures[0][1] = textures[1];
    localTextures[0][2] = textures[2];
    localTextures[1][0] = textures[3];
    localTextures[1][1] = textures[4];
    localTextures[1][2] = textures[5];

    // The second local row must select textures[5].
    float local = sampleRow(localTextures[1], 2).x;
    // Constant and dynamic rows of a descriptor interface both carry an offset.
    float global = sampleRow(matrixTextures[1], 2).x;
    global += sampleRow(matrixTextures[row & 1], 2).x;

    // Assignment and out/inout copy-back must update only the selected row.
    localTextures[0] = localTextures[1];
    swapRow(localTextures[0]);
    replaceRow(localTextures[1]);
    float copied = sampleConstRow(localTextures[1]).x;
    copied += localTextures[0][0].Load(int3(0, 0, 0)).x;

    // A two-dimensional slice forwarded to another function selects element 11.
    float forwarded = sampleMatrix(cubeTextures[1]).x;
    return float4(local, global, copied, forwarded);
}
