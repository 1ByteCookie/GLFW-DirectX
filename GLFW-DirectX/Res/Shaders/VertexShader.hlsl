
struct VS_INPUT
{
    float2 VertexPosition   : POSITION;
    float3 VertexColor      : COLOR;
};

struct VS_OUTPUT
{
    float4 VertexPosition   : SV_Position;
    float3 VertexColor      : ALBEDO;
};

VS_OUTPUT main(VS_INPUT InputData)
{
    VS_OUTPUT OutputData;
    OutputData.VertexPosition   = float4(InputData.VertexPosition, 0.0f, 1.0f);
    OutputData.VertexColor      = InputData.VertexColor;
    
    return OutputData;
}
