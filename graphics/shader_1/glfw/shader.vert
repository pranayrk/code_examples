#version 330 core

in vec3 vPos;

out vec2 fragCoord;

void main()
{
    gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);
    fragCoord = vPos.xy;
}
