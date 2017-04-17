#version 100

uniform float pa_Scale;
uniform float pa_Rotation;
uniform vec3 pa_Translation;
uniform vec3 pa_Origin;

attribute vec3 pa_Position;
attribute vec2 pa_TexCoord;

varying vec2 UV;

void main()
{
	UV = pa_TexCoord.xy;

	mat3 scale;
	scale *= pa_Scale;

	mat3 rotation(
		cos(pa_Rotation), sin(pa_Rotation), 0.0,
		-sin(pa_Rotation), cos(pa_Rotation), 0.0,
		0.0, 0.0, 1.0);

	gl_Position = vec4(pa_Origin + scale * rotation * (pa_Position + pa_Translation), 1.0);
}