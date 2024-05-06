#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 4) out;

#define ZNEARCLIP vec3(-1.0)
#define ZFARCLIP vec3(1.0)
#define ZINSIDECLIP 0.0
#define ZOUTSIDECLIP -2.0

uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;
uniform vec2 halfPixelSize;


void voxelizationEngine(void) {

	vec4 triV0, triV1, triV2, AABB;
	vec3 depths;
	float zd1, zd2;
	triV0 = vProjection * vView * vModel * gl_in[0].gl_Position;
	triV1 = vProjection * vView * vModel * gl_in[1].gl_Position;
	triV2 = vProjection * vView * vModel * gl_in[2].gl_Position;
	depths = vec3(triV0.z, triV1.z, triV2.z);
	AABB = triV0.xyxy;
	if (all(lessThan(depths, ZNEARCLIP) ) || all(greaterThan(depths, ZFARCLIP))) {
		gl_Position = vec4(AABB.xw, ZOUTSIDECLIP, 1.0);
		EmitVertex();
		gl_Position = vec4(AABB.xy, ZOUTSIDECLIP, 1.0);
		EmitVertex();
		gl_Position = vec4(AABB.zw, ZOUTSIDECLIP, 1.0);
		EmitVertex();
		gl_Position = vec4(AABB.zy, ZOUTSIDECLIP, 1.0);
		EmitVertex();
	}
	else {
		AABB = vec4(min(min(AABB.xy, triV1.xy), triV2.xy), max(max(AABB.zw, triV1.xy), triV2.xy) );
		AABB += vec4(-halfPixelSize, halfPixelSize);
		gl_Position = vec4(AABB.xw, ZINSIDECLIP, 1.0);
		EmitVertex();
		gl_Position = vec4(AABB.xy, ZINSIDECLIP, 1.0);
		EmitVertex();
		gl_Position = vec4(AABB.zw, ZINSIDECLIP, 1.0);
		EmitVertex();
		gl_Position = vec4(AABB.zy, ZINSIDECLIP, 1.0);
		EmitVertex();
	}

	EndPrimitive();
}

void main(){
	voxelizationEngine();
	return;
}