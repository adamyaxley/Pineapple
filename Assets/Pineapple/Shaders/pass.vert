#version 100

// Output data ; will be interpolated for each fragment.
varying vec2 UV;

// Input vertex data, different for all executions of this shader
attribute vec3 pa_Position;

void main()
{
	gl_Position =  vec4(pa_Position, 1);
	UV = (pa_Position.xy + vec2(1, 1)) / 2.0;
}