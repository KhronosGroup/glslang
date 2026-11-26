struct Data {
    float4 value;
};

ConstantBuffer<Data> buffers[2][3] : register(b0);
ConstantBuffer<Data> cubeBuffers[2][2][3] : register(b1);
ConstantBuffer<Data> rowBuffers[3] : register(b2);

cbuffer Indices : register(b3) {
    uint row;
    uint column;
};

float4 readRow(ConstantBuffer<Data> inputs[3], uint index)
{
    return inputs[index].value;
}

float4 readMatrix(ConstantBuffer<Data> inputs[2][3], uint i, uint j)
{
    return readRow(inputs[i], j);
}

struct Reader {
    float scale;

    float4 read(ConstantBuffer<Data> inputs[3], uint index)
    {
        return readRow(inputs, index) * scale;
    }
};

float4 main() : SV_Target0
{
    // Reference arguments carry the row offset into the callee.
    float4 fixedRow = readRow(buffers[1], 2);
    float4 dynamicRow = readRow(buffers[row & 1], column % 3);
    // Forwarding a two-dimensional slice must select descriptor 11.
    float4 forwarded = readMatrix(cubeBuffers[1], 1, 2);
    float4 wholeRow = readRow(rowBuffers, 2);

    // A specialized HLSL method must preserve its implicit this parameter.
    Reader reader;
    reader.scale = 2.0;
    float4 methodRow = reader.read(buffers[1], 2);
    return float4(fixedRow.x + methodRow.x, dynamicRow.y, forwarded.z, wholeRow.w);
}
