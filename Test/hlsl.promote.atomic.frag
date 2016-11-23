
RWBuffer<uint> s_CellCounts;  // UINT RWBuffer ...

float4 main() : SV_Target
{
    int Loc;  // ... with INT variables
    int Inc;
    int Orig;

    // This must select the uint flavor of SPIR-V atomic op, and promote
    // the other arguments as required.  The output value from the
    // imageAtomicAdd AST will be converted to an int for 'Orig'.
    InterlockedAdd(s_CellCounts[Loc], Inc, Orig);

    return float4(0,0,0,0);
}
