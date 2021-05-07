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

void drawTri() {
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, 0, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0, 1, 0);
	glEnd();
}

void drawRhombus() {
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, 0, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0, 1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, 0, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0, -1, 0);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(-0.5, 0, 0);
		glVertex3f(0.5, 0, 0);
	glEnd();
}

void drawRect() {
	glBegin(GL_QUADS);
		glVertex3f(-0.5, 0, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0.5, 2, 0);
		glVertex3f(-0.5, 2, 0);
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

	/*glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(static_cast<const float*>(glm::value_ptr(model_view)));*/

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

void Plane(float x, float y, float theta) {
	treenode head = treenode();
	treenode body = treenode();
	treenode l_wing = treenode();
	treenode r_wing = treenode();
	treenode l_canon = treenode();
	treenode r_canon = treenode();

	head.child = &body;
	head.m = glm::translate(head.m, glm::vec3(x, y, 0.0f));
	head.m = glm::scale(head.m, glm::vec3(0.05, 0.05, 0.0f));
	head.f = drawTri;
	head.sibling = NULL;
	head.col = fillWhite;

	body.child = &l_wing;
	body.m = glm::translate(body.m, glm::vec3(0, -2, 0.0f));
	body.f = drawRect;
	body.sibling = NULL;
	body.col = fillWhite;

	l_wing.child = &l_canon;
	l_wing.m = glm::translate(l_wing.m, glm::vec3(0.0f, 1.0f, 0.0f));
	l_wing.m = glm::rotate(l_wing.m, glm::radians(theta), glm::vec3(0.0f, 0.0f, 1.0f));
	//l_wing.m = glm::scale(l_wing.m, glm::vec3(0.8f, 1.0f, 0.0f));
	l_wing.f = drawRect;
	l_wing.sibling = &r_wing;
	l_wing.col = fillWhite;

	l_canon.child = NULL;
	l_canon.m = glm::translate(l_canon.m, glm::vec3(-0.5f, 2.1f, 0.0f));
	l_canon.m = glm::rotate(l_canon.m, glm::radians(theta - 220), glm::vec3(0.0f, 0.0f, 1.0f));
	l_canon.m = glm::scale(l_canon.m, glm::vec3(0.8f, 1.3f, 0.0f));
	l_canon.f = drawRect;
	l_canon.sibling = NULL;
	l_canon.col = fillWhite;

	r_wing.child = &r_canon;
	r_wing.m = glm::translate(r_wing.m, glm::vec3(0.0f, 1.0f, 0.0f));
	r_wing.m = glm::rotate(r_wing.m, glm::radians(-theta), glm::vec3(0.0f, 0.0f, 1.0f));
	//r_wing.m = glm::scale(r_wing.m, glm::vec3(0.8f, 1.0f, 0.0f));
	r_wing.f = drawRect;
	r_wing.sibling = NULL;
	r_wing.col = fillWhite;

	r_canon.child = NULL;
	
	r_canon.m = glm::translate(r_canon.m, glm::vec3(0.5f, 2.1f, 0.0f));
	r_canon.m = glm::rotate(r_canon.m, glm::radians(220 - theta), glm::vec3(0.0f, 0.0f, 1.0f));
	r_canon.m = glm::scale(r_canon.m, glm::vec3(0.8f, 1.3f, 0.0f));
	//
	r_canon.f = drawRect;
	r_canon.sibling = NULL;
	r_canon.col = fillWhite;

	traverse(&head);
}

void Bullet_(float x, float y, float radius){
	treenode bullet;

	bullet.child = NULL;
	bullet.m = glm::translate(bullet.m, glm::vec3(x, y, 0.0f));
	bullet.m = glm::scale(bullet.m, glm::vec3(radius, radius, 0.0f));
	bullet.f = drawFilledCircle;
	bullet.col = fillWhite;
	bullet.sibling = NULL;

	traverse(&bullet);
}

void Item(float x, float y, float length) {
	treenode item;

	item.child = NULL;
	item.m = glm::translate(item.m, glm::vec3(x, y, 0.0f));
	item.m = glm::scale(item.m, glm::vec3(length, length, 0.0f));
	item.f = drawRhombus;
	item.col = fillWhite;
	item.sibling = NULL;

	traverse(&item);
}

#endif
