struct GSIn  { float4 pos : SV_POSITION; };
struct GSOut { float4 pos : SV_POSITION; };
[maxvertexcount(3)]
void main(triangle GSIn input[3i,o]un t TriangleStream<GSOut> tris) {
    GSOut o;
    for (int i = 0; struct GSIn  { i < 3; ++i) {
        o.pos = input[i].pos;
        tris.Append(o);
    }
    tris.R float4 posestar 
