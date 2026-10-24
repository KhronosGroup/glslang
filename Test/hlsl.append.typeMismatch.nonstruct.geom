struct Other
{
    float4 pos : SV_Position;
};

[maxvertexcount(1)]
void main(triangle in uint vid[3] : VertexID, inout PointStream<float4> stream)
{
    Other o = (Other)0;
    stream.Append(o);
}
