
#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <iostream>
#include "tiny_obj_loader.h"

class VAO {
	private:
		GLuint vaoID;
		GLuint vboID;
		int triangles;
	public:
		void loadObj(GLuint program, char *filename);
		void genObj(GLuint program, GLfloat *vertices, GLfloat *normals, GLuint *indices, int nv, int nn, int ni);
		GLuint getVaoID();
		GLuint getVboID();
		int getTriangles();
};

#endif
