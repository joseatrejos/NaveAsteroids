#version 330 core
// La primera linea SIEMPRE es la version

// Atributos de entrada (vienen desde c++)
in vec4 posicion;
in vec4 color;

// Uniforms
uniform mat4 transformaciones;

// Atributos de salida (Van hacia el fragment shader)
out vec4 fragmentColor;

// Función main
void main() {
	// Es la posicion de salida del vertice
	// Es del tipo vec4
	gl_Position = transformaciones * posicion;

	// Establecer valores de atributos de salida
	fragmentColor = color;
}