#version 330 core

uniform vec2 color;

out vec4 fragColor0;


void main(){
	float x = pow(2, floor(color.y)) / 256.00;
	if(color.x <= 0.5){
		// r less than 1
		fragColor0 += vec4(x, 0.0, 0.0, 0.0);
	} else if(color.x <= 1.5){
		// g less than 2
		fragColor0 += vec4(0.0, x, 0.0, 0.0);
	} else if(color.x <= 2.5){
		// b less than 3
		fragColor0 += vec4(0.0, 0.0, x, 0.0);
	} else{
		// a less than 4
		fragColor0 += vec4(0.0, 0.0, 0.0, x);
	}
	return;
}