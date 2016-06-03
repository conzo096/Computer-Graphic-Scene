#version 440

// Model view projection matrix
uniform mat4 MVP;
// layout locations of vetrex positions and colours.
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 in_colour;

layout (location = 0) out vec4 out_colour;

void main()
{
	// Calculate screen position of vertex
	gl_Position = vec4(1.0f);
	// Output colour to the fragment shader
	out_colour = in_colour;
}