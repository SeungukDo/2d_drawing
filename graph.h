#ifndef GRAPH_H
#define GRAPH_H
#include "mode.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <math.h>

std::stack<glm::mat4> mvstack;
glm::mat4 model_view = glm::mat4(1.0f);

typedef struct treenode
{
	glm::mat4 m = glm::mat4(1.0f);
	void (*f) ();
	void (*col) ();
	struct treenode* sibling;
	struct treenode* child;
} treenode;

void drawFilledCircle() {
	int i;
	int triangleAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.141592;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			cos(i * twicePi / triangleAmount),
			sin(i * twicePi / triangleAmount)
		);
	}
	glEnd();
}

void Rotatete() {
	model_view = glm::rotate(model_view, (float)glm::radians(180.0), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Move(float x, float y) {
	model_view = glm::scale(model_view, glm::vec3(0.03, 0.03, 0.0f));
	model_view = glm::translate(model_view, glm::vec3(x, y, 0.0f));
}

void Origin() {
	model_view = glm::mat4(1.0f);
}

void fillGray() {
	glColor3f(0.5, 0.5, 0.0);
}

void fillWhite() {
	
}

void fillRed() {
	glColor3f(0.5, 0.0, 0.0);
}

void fillGreen() {
	glColor3f(0.0, 0.5, 0.0);
}

void traverse(treenode* root) {
	if (root == NULL) return;
	
	mvstack.push(model_view);
	model_view = model_view * root->m;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(static_cast<const float*>(glm::value_ptr(model_view)));

	root->col();
	root->f();

	if (root->child != NULL)
		traverse(root->child);

	model_view = mvstack.top();
	mvstack.pop();
	
	if (root->sibling != NULL)
		traverse(root->sibling);
}

void Planet_System(float x, float y, float x_len, float y_len, float theta) {
	treenode star = treenode();
	treenode planet = treenode();
	treenode satell = treenode();

	glColor3f(1.0, 0.0, 1.0);
	star.child = &planet;
	star.m = glm::translate(star.m, glm::vec3(x, y, 0.0f));
	star.m = glm::scale(star.m, glm::vec3(x_len, y_len, 0.0f));
	star.f = drawFilledCircle;
	star.col = fillGray;
	star.sibling = NULL;

	planet.child = &satell;
	planet.m = glm::rotate(planet.m, glm::radians(theta), glm::vec3(0.0f, 0.0f, 1.0f));
	planet.m = glm::translate(planet.m, glm::vec3(1.5f, 1.5f, 0.0f));
	planet.m = glm::scale(planet.m, glm::vec3(0.3, 0.3, 0.0f));
	planet.f = drawFilledCircle;
	planet.col = fillRed;
	planet.sibling = NULL;
	
	satell.child = NULL;
	satell.m = glm::rotate(satell.m, glm::radians(theta * 2), glm::vec3(0.0f, 0.0f, 1.0f));
	satell.m = glm::translate(satell.m, glm::vec3(1.5f, 1.5f, 0.0f));
	satell.m = glm::scale(satell.m, glm::vec3(0.3, 0.3, 0.0f));
	satell.f = drawFilledCircle;
	satell.col = fillGreen;
	satell.sibling = NULL;

	traverse(&star);
}

#endif
