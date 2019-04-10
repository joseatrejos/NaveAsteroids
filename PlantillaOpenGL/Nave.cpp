#include "stdafx.h"
#include "Nave.h"

Nave::Nave() {
	angulo = 0.0f;
	coordenadas = vec3(0.0f, 0.0f, 0.0f);
	// Establece el valor como una matriz identidad
	transformaciones = mat4(1.0f);

	Vertice v1 = {
		vec4(0.0f,0.1f,0.0f,1.0f),
		vec4(1.0f,0.0f,0.0f,1.0f)
	};
	Vertice v2 = {
		vec4(-0.1f,-0.1f,0.0f,1.0f),
		vec4(1.0f,0.8f,0.0f,1.0f)
	};
	Vertice v3 = {
		vec4(0.1f,-0.1f,0.0f,1.0f),
		vec4(1.0f,0.8f,0.0f,1.0f)
	};
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
}

void Nave::rotar(Direccion direccion) {

	float rotacion = velocidadAngular * tiempoDiferencial;
	if (rotacion < 0)
	{
		rotacion += 360;
	}
	if (direccion == Direccion::Derecha) {
		rotacion = -rotacion;
	}
	angulo += rotacion;
	actualizarMatrizTransformacion();
}

void Nave::avanzar() {
	float anguloDesfasado = angulo + 90.0f;

	if (velocidadActual <= velocidadMaxima) {
		velocidadActual += aceleracion;
	}
	else
	{
		velocidadActual = velocidadMaxima;
	}

	vec3 traslacion = vec3(
		cos(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual * tiempoDiferencial, // X
		sin(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual * tiempoDiferencial, // Y
		0.0f
	);

	coordenadas += traslacion;
	actualizarMatrizTransformacion();
}

void Nave::frenar() {
	float anguloDesfasado = angulo + 90.0f;

	if (velocidadActual > 0)
	{
		velocidadActual -= desaceleracion;
		if (velocidadActual < 0)
		{
			velocidadActual = 0.0f;
		}
	}

	vec3 traslacion = vec3(
		cos(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual * tiempoDiferencial, // X
		sin(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual * tiempoDiferencial, // Y
		0.0f
	);

	coordenadas += traslacion;
	actualizarMatrizTransformacion();
}

void Nave::calcularTiempo() {
	tiempoActual = glfwGetTime();
	tiempoDiferencial = tiempoActual - tiempoAnterior;
}

void Nave::colisionPared() {
	
	if (coordenadas.x > 1.1f)
	{
		coordenadas.x = -1.0f;
	}

	if (coordenadas.x < -1.1f)
	{
		coordenadas.x = 1.00f;
	}

	if (coordenadas.y > 1.1f)
	{
		coordenadas.y = -1.00f;
	}
	
	if (coordenadas.y < -1.1f)
	{
		coordenadas.y = 1.00f;
	}
}

void Nave::actualizarMatrizTransformacion() {
	// Partir siempre de una matriz identidad
	transformaciones = mat4(1.0f);

	// Aplicar las transformaciones
	transformaciones = translate(transformaciones, coordenadas);
	transformaciones = rotate(transformaciones, angulo * 3.14159f / 180.0f, vec3(0.0f, 0.0f, 1.0f));
}