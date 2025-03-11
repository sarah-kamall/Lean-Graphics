#version 330

layout(location = 0) in vec3 position; // sent as attribute cause uniform is slow and low mem 
layout(location = 1) in vec4 color;
out vec4 vertex_color;
uniform mat4 MVP; // what's MVP: Model View Projection
void main() {

    // const vec4 colors[3] = vec4[3](vec4(0.5, 0.5, 0.0, 1.0), vec4(0.5, 0.5, 0.0, 1.0), vec4(0.0, 0.5, 1.0, 1.0));
    vertex_color = color;
    gl_Position = MVP * vec4(position, 1.0);

}