#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 8) out;

void Voxel(){
	float fact = 2.0; 
	gl_Position = gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0) * fact;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-0.5, 0.5, -0.5, 0.0) * fact;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.5, -0.5, -0.5, 0.0) * fact;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.5, 0.5, -0.5, 0.0) * fact;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-0.5, -0.5, 0.5, 0.0) * fact;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-0.5, 0.5, 0.5, 0.0) * fact;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.5, -0.5, 0.5, 0.0) * fact;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.5, 0.5, 0.5, 0.0) * fact;
	EmitVertex();
	EndPrimitive();
}


void main(){
	Voxel();
	return;
}
