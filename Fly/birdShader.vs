#version 330 core
#define M_PI 3.1415926535897932384626433832795
layout (location = 0) in vec3 aPos;
layout (location = 1) in int isWingtip;
out vec3 vertexColor;
out vec3 normal;
out vec3 fragPos;
uniform float flapSpeed;
uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	if (isWingtip > 0)
	{
		float f = flapSpeed * time;
		float height = 0.5 * sin(f);
		vec4 modelPosition = vec4(aPos.x, aPos.y + height, aPos.z, 1.0);
		gl_Position = projection * view * model * modelPosition;
	}
	else
	{
		vec4 modelPosition = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		gl_Position = projection * view * model * modelPosition;
	}

	fragPos = vec3(model * vec4(aPos, 1.0));
	normal = vec3(1, 0, 0);
	vertexColor = vec3(1, 1, 1);
}