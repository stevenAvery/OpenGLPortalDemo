
#version 130

in vec3 normal;
in vec3 position;
in vec3 colour;

void main() {
	vec3 N = normalize(normal)*0.2 + colour*0.8;

	gl_FragColor = vec4(N, 1.0);
}
