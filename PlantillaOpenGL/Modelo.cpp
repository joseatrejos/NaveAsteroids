#include "stdafx.h"
#include "Modelo.h"

Modelo::Modelo() {
	// Establecemos las transformaciones con una matriz identidad
	transformaciones = mat4(1.0f);
}

void Modelo::inicializarVertexArray
(GLuint posicionID, GLuint colorID, GLuint transformacionesID) {
	this->transformacionesID = transformacionesID;
	
	// Crear un vertex array
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Crear vertex buffer
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);

	// Llenado del buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	// Habilitar atributos de shader
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);

	// Especificar a OpenGL como se va a comunicar
	glVertexAttribPointer(posicionID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec4));
}

void Modelo::dibujar(GLenum modoDibujo) {
	shader->enlazar();
		glBindVertexArray(vertexArrayID);
			glUniformMatrix4fv(transformacionesID, 1, GL_FALSE, &transformaciones[0][0]);
			glDrawArrays(modoDibujo, 0, vertices.size());
		glBindVertexArray(0); 
	shader->desenlazar();
}