#version 330 core


out vec2 texCoord;

void main()
{
    texCoord = vec2((gl_VertexId << 1) & 2, gl_VertexId & 2);
    gl_position = vec4(texCoord * 2.0f - 1.0f, 0.0f, 1.0f);
}
