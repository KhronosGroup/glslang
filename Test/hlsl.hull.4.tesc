
// Test mixed output structure: user and builtin members.  Hull shaders involve extra
// logic in this case, over and above e.g. pixel or vertex stages, which is related to
// the implicit array dimension.
struct HS_Output
{
    float tessFactor[3] : SV_TessFactor;
    float coord         : TEXCOORD0;
};

[domain("tri")]
[outputcontrolpoints(3)]
HS_Output main ( )
{ 
    HS_Output output = (HS_Output)0;
    return output;
}
