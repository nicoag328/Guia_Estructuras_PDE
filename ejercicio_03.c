// Guia Estructuras Programacion de Dispositivos
// Nicolas Gestro
// Ejercicio 3

#include <stdio.h>
#include "scan_wrappers.h"

struct estudiante_t
{
	int dni;
	float notas[10];
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

		for (int j = 0; j < 10; j++)
		{
			printf("Nota %d: ", j + 1);
			estudiantes[i].notas[j] = scan_float();
		}
	}

	printf("\nDNI\tPromedio\n");

	// Calcular promedios de cada estudiante y mostrarlos en pantalla
	for (int i = 0; i<5; i++)
	{
		float promedio = 0;
		int cantidad_notas = 0;
		for (int j = 0; j < 10; j++)
			if (estudiantes[i].notas[j] >= 0) 
			{
				promedio += estudiantes[i].notas[j];
				cantidad_notas++;
			}

		if (cantidad_notas == 0)
		{
			printf("\nIngrese al menos una nota por alumno\n");
			return -1;
		}

		promedio = promedio / (float)(cantidad_notas);
		
		printf("%d\t%.02f\n", estudiantes[i].dni, promedio);
	}

	return 0;
}
