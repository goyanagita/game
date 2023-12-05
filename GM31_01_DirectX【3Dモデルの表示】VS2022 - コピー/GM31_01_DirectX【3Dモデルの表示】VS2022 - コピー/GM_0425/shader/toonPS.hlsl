
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureToon : register(t1);

SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//法線を正規化して格納する
	float4 normal = normalize(In.Normal);

	//ランバート
    float light = -dot(Light.Direction.xyz, normal.xyz);
    light = saturate(light);

    
    //プログラムをセル塗り風に変換
    if (light > 0.8)
        light = 1.0;
    else if (light > 0.4)
        light = 0.6;
    else
        light = 0.4;
    
    //3
    light = clamp(light, 0.03, 0.8);
    
    //4
    
    float2 toonUV = float2(light, 0.5);
    float3 toon = g_TextureToon.Sample(g_SamplerState,toonUV);
    
    
	//テクスチャから色をサンプリングする
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= toon;
    outDiffuse.a *= In.Diffuse.a;
   
	//エッジの作成
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    float d = dot(eyev, normal.xyz);
    
    if (d > -0.3)
    {
        outDiffuse.rgb *= 0.7;
        
    }
       
}
