/*
Programul afiseaza un patrat pe care il translateaza pe axa x la apasarea sagetilor stanga, dreapta
*/
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat z = 0;
static GLfloat alpha = 0;

GLUquadricObj* quadricObj = 0;



void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK MutaStanga()
{
    x = x - 10;
}

void CALLBACK MutaDreapta()
{
    x = x + 10;
}

void CALLBACK rot_z_up(AUX_EVENTREC* event) {
    alpha -= 10;
}

void CALLBACK rot_z_down(AUX_EVENTREC* event) {
    alpha += 10;
}

void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(x, 0, 0.0);
    glRotatef(alpha, 1, 1, 1);

    quadricObj = gluNewQuadric();
    gluQuadricDrawStyle(quadricObj, GLU_LINE);
    gluQuadricNormals(quadricObj, GLU_SMOOTH);
    gluQuadricTexture(quadricObj, GL_TRUE);
    gluQuadricOrientation(quadricObj, GLU_OUTSIDE);

    // Sphere
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0, 10, 0);
    gluSphere(quadricObj, 30, 100, 20);
    glPopMatrix();

    glFlush();
}

#define ISOTROPIC
#ifdef ISOTROPIC
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) {
        return;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w, -160.0 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
    }
    else {
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -100.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}
#else
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;			//transformare anizotropica, forma se modifica functie de forma(dimens) viewportului
    glViewport(0, 0, w, h);	//daca w>h stabilim ca baza inaltime, si stab unit logica de dimens in fct de h(h/320, 320 lungime lat patrat)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-160.0, 160.0, -160.0, 160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}
#endif

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 800, 600);
    auxInitWindow("Quadrics");
    myInit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);

    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_down);
    auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_up);

    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}
