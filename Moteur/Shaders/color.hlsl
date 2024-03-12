//***************************************************************************************
// color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

Texture2D g_texture : register(t0); // Texture bound to t0, register space 0
SamplerState g_sampler : register(s0); // Sampler bound to s0, register space 0

cbuffer cbPerObject : register(b0)
{
	float4x4 gWorld; 
    //float4x4 gTexTransform;
};
cbuffer cbPerPass : register(b1)
{
    float4x4 gViewProj;
};

struct VertexIn
{
	float3 PosL  : POSITION;
    //float4 Color : COLOR;
    float2 TexC : TEXCOORD;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    //float4 Color : COLOR;
    float2 TexC : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to homogeneous clip space.
	float4 pos = mul(float4(vin.PosL, 1.0f), gWorld);
    vout.PosH = mul(pos, gViewProj);
	
	// Just pass vertex color into the pixel shader.
    //vout.Color = vin.Color;
    //vout.TexC = mul(float4(vin.TexC, 0.0f, 1.0f), gTexTransform);
    vout.TexC = vin.TexC;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    //return float4(1, 0, 0, 1);
    //return pin.Color;
   return g_texture.Sample(g_sampler, pin.TexC);
}


