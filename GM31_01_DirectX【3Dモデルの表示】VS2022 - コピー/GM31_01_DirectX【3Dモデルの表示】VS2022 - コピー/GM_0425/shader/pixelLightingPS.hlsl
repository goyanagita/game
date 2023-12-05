
#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�@���𐳋K�����Ċi�[����
	float4 normal = normalize(In.Normal);

	//�����̌����Ɖ�]�ς݂̖@���Ƃœ��ς��v�Z���A�����𔽓]���ċP�x�����߂�
	float light = -dot(Light.Direction.xyz, normal.xyz);
	//�O�a���Z(0.0�`1.0�̒l�ɃN�����v����)
	light = saturate(light);

	//�e�N�X�`������F���T���v�����O����
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	//�e�N�X�`���̐F�ɋP�x����Z����
	outDiffuse.rgb *= light;
	//�����x�͋P�x�ɉe�����Ȃ��̂ł��̂܂܎g��
	outDiffuse.a *= In.Diffuse.a;
	//�t�H�O
	float fog_start = 10.0;
	float fog_end = 25.0;

	float dist = distance(In.WorldPosition.xyz, CameraPosition.xyz);
	float fog = (fog_end - dist) / (fog_end - fog_start);//���`�ł̌v�Z
	fog = saturate(fog);
	outDiffuse.rgb = outDiffuse.rgb*fog + float3(1.0f, 3.0f, 1.0f)*(1.0 - fog);//float3�l�̓t�H�O��RGB�l
}
