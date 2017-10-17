
struct Data {
    float4 v;
};

ConsumeStructuredBuffer<Data> buf_in : register(u0, space1);
AppendStructuredBuffer<Data>  buf_out : register(u2, space3);

float4 main(float4 sv_pos : SV_POSITION) : SV_TARGET
{
    Data val = buf_in.Consume();       
    buf_out.Append(val);
    return sv_pos;
}
