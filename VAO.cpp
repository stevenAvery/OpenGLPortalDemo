
#include "VAO.h"

void VAO::loadObj(GLuint program, char *filename) {
	GLfloat *vertices;
	GLfloat *normals;
	GLuint *indices;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	int nv;
	int nn;
	int ni;

	/*  Load the obj file */
	std::string err = tinyobj::LoadObj(shapes, materials, filename, 0);

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	/*  Retrieve the vertex coordinate data */
	nv = shapes[0].mesh.positions.size();
	vertices = new GLfloat[nv];
	for (int i = 0; i<nv; i++) {
		vertices[i] = shapes[0].mesh.positions[i];
	}

	/*  Retrieve the vertex normals */
	nn = shapes[0].mesh.normals.size();
	normals = new GLfloat[nn];
	for (int i = 0; i<nn; i++) {
		normals[i] = shapes[0].mesh.normals[i];
	}

	/*  Retrieve the triangle indices */
	ni = shapes[0].mesh.indices.size();
	indices = new GLuint[ni];
	for (int i = 0; i<ni; i++) {
		indices[i] = shapes[0].mesh.indices[i];
	}

	genObj(program, vertices, normals, indices, nv, nn, ni);
}

void VAO::genObj(GLuint program, GLfloat *vertices, GLfloat *normals, GLuint *indices, int nv, int nn, int ni) {
	GLuint ibuffer;
	GLint vPosition;
	GLint vNormal;

	this->triangles = ni / 3;

	glGenVertexArrays(1, &this->vaoID);
	glBindVertexArray(this->vaoID);

	// load the vertex coordinate data
	glGenBuffers(1, &this->vboID);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(GL_ARRAY_BUFFER, (nv + nn)*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, nv*sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, nv*sizeof(GLfloat), nn*sizeof(GLfloat), normals);

	// load the vertex indexes
	glGenBuffers(1, &ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ni*sizeof(GLuint), indices, GL_STATIC_DRAW);

	// link the vertex coordinates, and normals to vPosition, and vNormal
	glUseProgram(program);
	vPosition = glGetAttribLocation(program, "vPosition");
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
	vNormal = glGetAttribLocation(program, "vNormal");
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*)(nv*sizeof(GLfloat)));
	glEnableVertexAttribArray(vNormal);

	// output the creation of the VAO
	std::cout << "Model created: \n\tvaoID: " << this->vaoID << "\n\ttriangles: " << this->triangles << std::endl;
}

GLuint VAO::getVaoID() {
	return this->vaoID;
}

GLuint VAO::getVboID() {
	return this->vboID;
}

int VAO::getTriangles() {
	return this->triangles;
}
