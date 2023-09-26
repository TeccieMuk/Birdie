#version 330 core
#define M_PI 3.1415926535897932384626433832795
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vertexColor;
out vec3 normal;
out vec3 fragPos;
uniform float wave_time;
uniform float wave_amp;
uniform float wave_length;
uniform float wave_speed;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	float length = (M_PI * 2) / wave_length;
	float f = length * (aPos.x - wave_speed * wave_time);
	float height = wave_amp * sin(wave_length * (aPos.x - (wave_speed * wave_time)));
	vec4 modelPosition = vec4(aPos.x, aPos.y, aPos.z + height, 1.0);
	gl_Position = projection * view * model * modelPosition;
	fragPos = vec3(model * vec4(aPos, 1.0));

	vec3 tangent = normalize(vec3(1, length * wave_amp * cos(f), 0));
	normal = vec3(-tangent.y, tangent.x, 0);

	float minBlue = 0.8;
	float maxBlue = 1;
	float color = (1-height) * (maxBlue - minBlue) + minBlue;
	vertexColor = vec3(0.03f, 0.56f, 1);
}