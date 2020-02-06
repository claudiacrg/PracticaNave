// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>

using namespace std;

float angulo = 0.0f;

//declarar una ventana
GLFWwindow* window;
double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 0.8;


void dibujarTriangulo() {
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(0.0f+angulo, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES);

	glColor3f(0.9f, 0.4f, 0.8f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(-0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);

	glEnd();
	glPopMatrix();

	//

	glPushMatrix();

	glRotatef(0.0f + angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES);

	glColor3f(0.9f, 0.4f, 0.8f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.3f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);

	glEnd();
	glPopMatrix();

	//

	glPushMatrix();

	glRotatef(0.0f + angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES);

	glColor3f(0.9f, 0.4f, 0.8f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.1f, 0.4f, 0.0f);

	glEnd();
	glPopMatrix();
}

float posXTriangulo = 0.0f;
float posYTriangulo = 0.0f;
float anguloNave = 0.0f;
float velocidadGiro = 900;

void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT && key ==GLFW_KEY_RIGHT) {
		posXTriangulo += 0.05;
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_LEFT) {
		posXTriangulo -= 0.05;
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_UP) {
		posYTriangulo += 0.05;
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_DOWN) {
		posYTriangulo -= 0.05;
	}

}

void actualizar() {
	tiempoActual = glfwGetTime();
	double tiempoDiferencial = tiempoActual - tiempoAnterior;
	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		anguloNave -= velocidadGiro*tiempoDiferencial;
	}

	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		
		posYTriangulo += sin((anguloNave + 90.0) * 3.141592 / 180.0) * (velocidadTriangulo * tiempoDiferencial);
		posXTriangulo += cos((anguloNave + 90.0) * 3.141592 / 180.0) * (velocidadTriangulo * tiempoDiferencial);
	}

	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		anguloNave += velocidadGiro*tiempoDiferencial;
	}

	/*int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS) {
		posYTriangulo -= velocidadTriangulo * tiempoDiferencial;
	}*/

	tiempoAnterior = tiempoActual;
}

void dibujar() {
	glPushMatrix();

	glTranslatef(posXTriangulo, posYTriangulo, 0.0f);
	glRotatef(anguloNave, 0.0f, 0.0f, 1.0f);
	glScalef(0.4f, 0.7f, 0.7f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.2, 0.6, 0.1);

	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);

	glEnd();

	glPopMatrix();
}

int main()
{
	

	//Si no se pudo iniciar glfw
	//terminamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo inicial glfw
	//inicializamos la ventana
	window = glfwCreateWindow(600, 600, "Ventana", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto se activan las funciones "modernas" (GPU)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK)
	{
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//Establecemos que con cada evento de teclado
	//se llama a la funcion teclado_callback
	//glfwSetKeyCallback(window, teclado_callback);

	tiempoActual = glfwGetTime();
	tiempoAnterior = tiempoActual;

	//ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 600, 600);
		//Establecemos el color de borrado
		//Valores RGBA
		glClearColor(0.9, 0.2, 0.5, 1);
		//Borrar!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Actualizar valores y dibujar
		actualizar();
		dibujar();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//Despues del ciclo de dibujo
	//Eliminamos ventana y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}

