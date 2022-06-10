// Guia Estructuras Programacion de Dispositivos
// Nicolas Gestro
// Ejercicio 1

#include <stdio.h>
#include "scan_wrappers.h"

struct estudiante_t
{
	int dni;
	float notas[2];
};

int main()
{

	struct estudiante_t estudiantes[5];

	// Obtener datos de los estudiantes
	for (int i = 0; i < 5; i++)
	{
		printf("Ingrese los datos del estudiante %d\n", i + 1);

		printf("DNI: ");
		estudiantes[i].dni = scan_int();

		printf("Nota del primer cuatrimestre: ");
		estudiantes[i].notas[0] = scan_float();

		printf("Nota del segundo cuatrimestre: ");
		estudiantes[i].notas[1] = scan_float();
	}

	printf("\nDNI\tPromedio\n");

	// Calcular promedios de cada estudiante y mostrarlos en pantalla
	for (int i = 0; i<5; i++)
	{
		float promedio = (estudiantes[i].notas[0] + estudiantes[i].notas[1]) / 2;

		printf("%d\t%.02f\n", estudiantes[i].dni, promedio);
	}

	return 0;
}
