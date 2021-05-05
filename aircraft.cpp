#define GL_SILENCE_DEPRECATION
#include "aircraft.hpp"
#include "GL/freeglut.h"

GLfloat vertices[][3] = 
{ 
	{-1.0, -1.0, -1.0},	// vertex 0
	{1.0, -1.0, -1.0},	// vertex 1
	{1.0, 1.0, -1.0},	// vertex 2
	{-1.0, 1.0, -1.0},	// vertex 3
	{-1.0, -1.0, 1.0},	// vertex 4
	{1.0, -1.0, 1.0},	// vertex 5
	{1.0, 1.0, 1.0},	// vertex 6
	{-1.0, 1.0, 1.0},	// vertex 
};

GLfloat colors[][3] = 
{ 
	{0.0,0.0,0.0},		//color 0
	{1.0,0.0,0.0},		//color 1
	{1.0,1.0,0.0},		//color 2
	{0.0,1.0,0.0},		//color 3
	{0.0,0.0,1.0},		//color 4
	{1.0,0.0,1.0},		//color 5
	{1.0,1.0,1.0},		//color 6
	{0.0,1.0,1.0}		//color 7	
};

//정사각형
void draw_polygon(int a, int b, int c , int d)
{
	glBegin(GL_TRIANGLES);
	{
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	{
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
	}
	glEnd();
}

//정육면체
void draw_cube() {
	draw_polygon(4,5,6,7);
	draw_polygon(0,3,2,1);
	draw_polygon(1,2,6,5);
	draw_polygon(0,4,7,3);
	draw_polygon(3,7,6,2);
	draw_polygon(0,1,5,4);

}

void draw_pyramid(float length, float width, float height) {

	glPushMatrix();

		glScalef(length, width, height);

		glBegin(GL_TRIANGLE_STRIP);
		{
			glVertex3f(-1.0, -1.0, 0.0);
			glVertex3f(-1.0, 1.0, 0.0);
			glVertex3f(1.0, -1.0, 0.0);
			glVertex3f(1.0, 1.0, 0.0);
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		{
			glVertex3f(-1.0, -1.0, 0.0);
			glVertex3f(-1.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0);
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		{
			glVertex3f(-1.0, 1.0, 0.0);
			glVertex3f(1.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0);
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		{
			glVertex3f(1.0, 1.0, 0.0);
			glVertex3f(1.0, -1.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0);
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		{
			glVertex3f(1.0, -1.0, 0.0);
			glVertex3f(-1.0, -1.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0);
		}
		glEnd();

	glPopMatrix();
}

//직육면체
void draw_cuboid(float length, float width, float height) {
	glPushMatrix();
		glScalef(length, width, height);
		draw_cube();
	glPopMatrix();
}

void draw_aircraft() {
	//glColor3f(0.0, 1.0, 0.0);
	draw_cuboid(1.0, 1.0, 1.5);	//body
	//glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();	//right up wing
		glTranslatef(1.5, 1.0, 0.0);
		glRotatef(22, 0.0, 0.0, 1.0);
		draw_cuboid(1.0, 0.1, 1.5);
		glPushMatrix();	//right down wing
			glTranslatef(1.3, -0.45, 0.0);
			glRotatef(-50, 0.0, 0.0, 1.0);
			draw_cuboid(0.5, 0.1, 1.5);
		glPopMatrix();
	glPopMatrix();	//left up wing
	glPushMatrix();
		glTranslatef(-1.5, 1.0, 0.0);
		glRotatef(-22, 0.0, 0.0, 1.0);
		draw_cuboid(1.0, 0.1, 1.5);
		glPushMatrix();	//left down wing
			glTranslatef(-1.3, -0.45, 0.0);
			glRotatef(50, 0.0, 0.0, 1.0);
			draw_cuboid(0.5, 0.1, 1.5);
		glPopMatrix();
	glPopMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();	//head
		glTranslatef(0.0, 0.0, 1.5);
		draw_pyramid(1.0, 1.0, 1.5);
	glPopMatrix();
}