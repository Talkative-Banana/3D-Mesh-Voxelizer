#version 330 core

in vec3 vPoint;

uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;

void main() {
	gl_Position = vProjection* vView * vModel * vec4(vPoint, 1.0);
}
