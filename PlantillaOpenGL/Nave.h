#pragma once
#include "Modelo.h"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"

class Nave : public Modelo {
public:
	Nave();
	enum Direccion {Izquierda, Derecha};
	vec3 coordenadas;
	float angulo;
	float velocidadAngular = 320.0f;
	float velocidadMaxima = 1.4f;
	float velocidadActual = 0.0f;
	float aceleracion = 0.007f;
	float desaceleracion = 0.004f;
	void rotar(Direccion direccion);
	void avanzar();
	void frenar();
	void calcularTiempo();
	void colisionPared();
	double tiempoAnterior = 0.0f;
	double tiempoActual = 0.0f;
	double tiempoDiferencial = 0.0f;
	void actualizarMatrizTransformacion();
};

