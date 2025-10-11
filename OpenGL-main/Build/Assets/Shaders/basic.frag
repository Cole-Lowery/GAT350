#version 460 core

out vec4 fragColor;
in vec3 v_color;

uniform float u_time;

void main(){
fragColor = vec4(v_color, 1.0);
float offset = sin(u_time + gl_FragCoord.y);
}
