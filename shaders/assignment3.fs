
#version 130

in vec3 normal;
in vec3 position;
in vec3 colour;

void main() {
	vec3 nNormal = normalize(normal);
	float absNormal = (nNormal.x+nNormal.y+nNormal.z)/3;

	vec3 N = absNormal*0.2 + colour*0.8;
	gl_FragColor = vec4(N, 1.0);
}
