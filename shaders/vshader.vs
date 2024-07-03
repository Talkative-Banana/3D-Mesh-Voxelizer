#version 330 core

layout(location = 0) in vec4 vVertex;

uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;

// uniform vec4 vColor;
out float ai;

void main() {
	gl_Position = vProjection * vView * vModel * vec4(vVertex.x - 160.0, vVertex.y - 160.0, vVertex.z - 160.0, 1.0);
	ai = vVertex.w;
}
