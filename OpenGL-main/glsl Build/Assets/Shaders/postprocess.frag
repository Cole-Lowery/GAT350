#version 430

#define GRAYSCALE	(1 << 0)
#define COLORTINT	(1 << 1)
#define SCANLINE	(1 << 2)
#define GRAIN		(1 << 3)
#define INVERT		(1 << 4)
#define VIGNETTE	(1 << 5)

in vec2 v_texcoord;

out vec4 f_color;

// post process controls
uniform uint u_parameters = 0;
uniform vec3 u_colorTint = vec3(1, 1, 1);

uniform float u_time = 0.0;	// used in random function
uniform float u_blend = 1.0; // blend between original and postprocess color (0..1)

uniform float u_grainStrength = 0.2;    // grain amount
uniform float u_vignetteStrength = 0.5; // vignette amount

uniform sampler2D u_baseMap;

// simple pseudo random from The Book of Shaders
float random(vec2 st) 
{
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
	vec4 color = texture(u_baseMap, v_texcoord);
	vec3 post = color.rgb;

	// GRAYSCALE -> use luminance
	if ((u_parameters & GRAYSCALE) != 0u) {
		float l = dot(post, vec3(0.299, 0.587, 0.114));
		post = vec3(l);
	}

	// COLORTINT -> multiply by tint
	if ((u_parameters & COLORTINT) != 0u) {
		post *= u_colorTint;
	}

	// SCANLINE -> darken alternating horizontal lines
	if ((u_parameters & SCANLINE) != 0u) {
		// use screen-space y coord; thinner/bolder lines controlled by modulo value
		float line = mod(gl_FragCoord.y, 3.0);
		if (line < 1.0) post *= 0.3; // dark line
	}

	// GRAIN -> add subtle noise
	if ((u_parameters & GRAIN) != 0u) {
		// noise based on uv + time for animation
		float n = random(v_texcoord * vec2(800.0, 600.0) + u_time);
		// center noise around 0
		n = (n - 0.5) * u_grainStrength;
		post += vec3(n);
	}

	// INVERT -> invert color
	if ((u_parameters & INVERT) != 0u) {
		post = vec3(1.0) - post;
	}

	// VIGNETTE -> darken edges
	if ((u_parameters & VIGNETTE) != 0u) {
		// distance from center (0..~0.707)
		float dist = distance(v_texcoord, vec2(0.5));
		// smoothstep for smooth falloff; control by vignette strength
		float vig = smoothstep(0.3, 0.9, dist);
		post *= mix(1.0, 1.0 - u_vignetteStrength, vig);
	}

	// combine original and postprocess using blend
	f_color = mix(color, vec4(post, color.a), clamp(u_blend, 0.0, 1.0));
}