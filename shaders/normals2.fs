
#version 130

in vec3 normal;
in vec3 position;
in vec3 colour;

void main() {
	vec3 N;
	vec3 Lposition = vec3(-8.0, 5.0, 8.0);
	vec4 colour4 = vec4(colour, 1.0);
	vec4 Lcolour = vec4(1.0, 1.0, 1.0, 1.0);
	vec3 H;
	float diffuse;
	float specular;
	float n = 100.0;
	vec3 L;

	N = normalize(normal);
	L = Lposition - position.xyz;
	L = normalize(L);
	H = normalize(L + vec3(0.0, 0.0, 1.0));
	diffuse = dot(N,L);
	if(diffuse < 0.0) {
		diffuse = 0.0;
		specular = 0.0;
	} else {
		specular = pow(max(0.0, dot(N,H)),n);
	}

	vec4 phongColour = min(0.1*colour4 + 0.7*diffuse*colour4*Lcolour + 0.01*Lcolour*specular, vec4(1.0));
	gl_FragColor = min(phongColour*0.8 + vec4(normalize(normal)*0.05, 1.0), vec4(1.0));
	gl_FragColor.a = colour4.a;
}
