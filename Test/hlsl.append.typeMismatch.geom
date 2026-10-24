struct PSInput
{
    float4 pos : SV_Position;
    float4 color : COLOR0;
};

struct Other
{
    float4 pos : SV_Position;
};

[maxvertexcount(3)]
void main(triangle in uint vid[3] : VertexID, inout TriangleStream<PSInput> stream)
{
    Other o = (Other)0;
    stream.Append(o);
    stream.Append(1.0);
}
