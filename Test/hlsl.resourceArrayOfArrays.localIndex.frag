Texture2D<float4> textures[6] : register(t0);

void reverseRow(inout Texture2D<float4> inputs[3])
{
    Texture2D<float4> first = inputs[0];
    inputs[0] = inputs[2];
    inputs[2] = first;
}

void replaceRow(out Texture2D<float4> outputs[3])
{
    outputs[0] = textures[0];
    outputs[1] = textures[1];
    outputs[2] = textures[2];
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

    // Ordinary local indices must be resolved during default HLSL legalization.
    uint row = 1;
    float direct = local[row][2].Load(int3(0, 0, 0)).x;

    uint destination = 0;
    uint source = 1;
    local[destination++] = local[source++];
    float copied = local[0][0].Load(int3(0, 0, 0)).x;

    // Both kinds of copy-back preserve the row and evaluate its index once.
    uint reversed = 1;
    reverseRow(local[reversed++]);
    float swapped = local[1][2].Load(int3(0, 0, 0)).x;

    uint replaced = 0;
    replaceRow(local[replaced++]);
    float written = local[0][2].Load(int3(0, 0, 0)).x;

    // Select descriptors 5, 3, 3, 2 and add the index values 1, 2, 2, 1.
    return float4(direct, copied, swapped, written) + float4(destination, source, reversed, replaced);
}
