#version 330

out vec4 frag_color;
in vec4 vertex_color;
void main() {
    frag_color = vertex_color;
}