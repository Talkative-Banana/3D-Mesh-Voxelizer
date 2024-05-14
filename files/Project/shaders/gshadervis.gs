#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 18) out;
//layout (line_strip, max_vertices = 18) out;

uniform float voxel_dim;
uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;
void Voxel(){
	float fact = voxel_dim * 1;
	// Faces	
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0) * fact); // 0
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, 0.5, -0.5, 0.0) * fact);  // 1
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, -0.5, -0.5, 0.0) * fact);  // 3
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, 0.5, -0.5, 0.0) * fact);   // 2
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, -0.5, 0.5, 0.0) * fact);   // 7
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, 0.5, 0.5, 0.0) * fact);    // 6
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, -0.5, 0.5, 0.0) * fact);  // 4
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, 0.5, 0.5, 0.0) * fact);   // 5
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0) * fact); // 0
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, 0.5, -0.5, 0.0) * fact);  // 1
	EmitVertex();
	EndPrimitive();
	

	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0) * fact); // 0
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, -0.5, -0.5, 0.0) * fact);  // 3
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, -0.5, 0.5, 0.0) * fact);  // 4
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, -0.5, 0.5, 0.0) * fact);   // 7
	EmitVertex();
	EndPrimitive();


	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, 0.5, -0.5, 0.0) * fact);  // 1
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, 0.5, -0.5, 0.0) * fact);   // 2
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, 0.5, 0.5, 0.0) * fact);   // 5
	EmitVertex();
	gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, 0.5, 0.5, 0.0) * fact);    // 6
	EmitVertex();
	EndPrimitive();




	//EmitVertex();
	//EmitVertex();
	//gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, 0.5, -0.5, 0.0) * fact);
	//EmitVertex();
	//gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, -0.5, -0.5, 0.0) * fact);
	//EmitVertex();
	//gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0) * fact);
	//EmitVertex();
	//EndPrimitive();




	//gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, 0.5, -0.5, 0.0) * fact);
	//EmitVertex();
	//gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, -0.5, 0.5, 0.0) * fact);
	//EmitVertex();
	//gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(-0.5, 0.5, 0.5, 0.0) * fact);
	//EmitVertex();
	//gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, -0.5, 0.5, 0.0) * fact);
	//EmitVertex();
	//gl_Position = vProjection* vView * vModel * (gl_in[0].gl_Position + vec4(0.5, 0.5, 0.5, 0.0) * fact);
	//EmitVertex();
	//EndPrimitive();






//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, 0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();
	
//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, 0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(0.5, 0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();

//	gl_Position = gl_in[0].gl_Position + vec4(0.5, 0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(0.5, -0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();

//	gl_Position = gl_in[0].gl_Position + vec4(0.5, -0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();





//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, -0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, 0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();
	
//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, 0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(0.5, 0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();

//	gl_Position = gl_in[0].gl_Position + vec4(0.5, 0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(0.5, -0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();

//	gl_Position = gl_in[0].gl_Position + vec4(0.5, -0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, -0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();







//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, -0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();

//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, 0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(-0.5, 0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();

//	gl_Position = gl_in[0].gl_Position + vec4(0.5, 0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(0.5, 0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();

//	gl_Position = gl_in[0].gl_Position + vec4(0.5, -0.5, -0.5, 0.0) * fact;
//	EmitVertex();
//	gl_Position = gl_in[0].gl_Position + vec4(0.5, -0.5, 0.5, 0.0) * fact;
//	EmitVertex();
//	EndPrimitive();
}


void main(){
	Voxel();
	return;
}
