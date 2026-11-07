RWByteAddressBuffer rbuf[2];

float4 main(uint idx : IDX) : SV_Target0
{
    return rbuf.Load(idx);
}
