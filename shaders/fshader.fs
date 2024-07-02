#version 330 core

out vec4 outColor;
in float ai;

void main() {
        //outColor = vec4(TexCoord, 1.0);
        outColor = vec4(ai, ai, ai, 1.0);
}
