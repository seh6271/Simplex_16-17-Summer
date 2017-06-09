#version 330
out vec4 Fragment;
in vec3 Color;
void main()
{
	Fragment = vec4(Color,1);
	return;
}