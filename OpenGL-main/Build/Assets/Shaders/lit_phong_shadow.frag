#version 460 core

#define	BASE_MAP		(1 << 0)
#define	SPECULAR_MAP	(1 << 1)
#define	EMISSIVE_MAP	(1 << 2)
#define	NORMAL_MAP		(1 << 3)
#define    SHADOW_MAP     (1 << 4)

in vec2 v_texcoord;

out vec4 f_color;

struct Material
{
	vec3 baseColor;
	vec3 emissiveColor;
	vec2 tiling;
	vec2 offset;
	uint parameters;
};

uniform Material u_material;
uniform sampler2D u_baseMap;

float calculateShadow(in vec4 shadowCoord, in float bias)
{
return texture(u_shadowMap, shadowCoord.xy).r < (shadowCoord.z - bias) ? 0.0 : 1.0;

}

void main()
{
float shadow = (u_lights[i].shadowCaster && ((u_material.parameters & SHADOW_MAP) != 0u))
			   ? calculateShadow(v_shadowCoord, u_lights[i].shadowBias)
			   : 1.0;

	vec4 color = ((u_material.parameters & BASE_MAP) != 0u)
				 ? texture(u_baseMap, v_texcoord) * vec4(u_material.baseColor, 1)
				 : vec4(u_material.baseColor, 1);

	f_color = color;
}
