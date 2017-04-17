#version 100

varying vec2 UV;

uniform sampler2D pa_QuadTexture;

void main()
{
	gl_FragColor = texture2D(pa_QuadTexture, UV);
}