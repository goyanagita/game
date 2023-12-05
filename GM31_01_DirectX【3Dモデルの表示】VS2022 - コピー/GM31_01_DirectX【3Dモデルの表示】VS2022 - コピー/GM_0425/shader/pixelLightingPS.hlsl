
#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//法線を正規化して格納する
	float4 normal = normalize(In.Normal);

	//光源の向きと回転済みの法線とで内積を計算し、符号を反転して輝度を求める
	float light = -dot(Light.Direction.xyz, normal.xyz);
	//飽和演算(0.0～1.0の値にクランプする)
	light = saturate(light);

	//テクスチャから色をサンプリングする
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	//テクスチャの色に輝度を乗算する
	outDiffuse.rgb *= light;
	//透明度は輝度に影響しないのでそのまま使う
	outDiffuse.a *= In.Diffuse.a;
	//フォグ
	float fog_start = 10.0;
	float fog_end = 25.0;

	float dist = distance(In.WorldPosition.xyz, CameraPosition.xyz);
	float fog = (fog_end - dist) / (fog_end - fog_start);//線形での計算
	fog = saturate(fog);
	outDiffuse.rgb = outDiffuse.rgb*fog + float3(1.0f, 3.0f, 1.0f)*(1.0 - fog);//float3値はフォグのRGB値
}
