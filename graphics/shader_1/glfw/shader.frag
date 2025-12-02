#version 330 core

precision mediump float;

uniform float uTime;
uniform sampler2D screenTexture;

in vec2 texCoord;
out vec4 FragColor;

void main() {

    float blue = cos(uTime) * 0.5 + 0.5;
    FragColor = vec4(screenTexture, blue,1.0);
}

