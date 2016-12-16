
#version 130

in vec3 normal;
in vec3 position;

void main() {
	vec3 N = normalize(normal)*0.2 + vec3(0.6, 0.6, 0.6);

	gl_FragColor = vec4(N, 1.0);
}
