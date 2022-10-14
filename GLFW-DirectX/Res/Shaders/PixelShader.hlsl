
struct VS_OUTPUT
{
    float4 VertexPosition   : SV_Position;
    float3 VertexColor      : ALBEDO;
};

float4 main(VS_OUTPUT InputData) : SV_Target
{
    return float4(InputData.VertexColor, 1.0f);
}