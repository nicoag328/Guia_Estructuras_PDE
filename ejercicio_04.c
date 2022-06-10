// Guia Estructuras Programacion de Dispositivos
// Nicolas Gestro
// Ejercicio 4

#include <stdio.h>
#include <errno.h>
#include "scan_wrappers.h"
#include "csv_parse.h"

struct fecha_t
{
	int mes;
	int dia;
}

struct factura_t
{
	int numero;
	struct fecha_t fecha;
	char cliente[30];
	float monto;
};

int main(int argc, char* argv[])
{

	// Verificar la cantidad de argumentos
	if (argc < 2)
	{
		printf("Modo de uso: ejercicio04 <archivo.csv>");
		return -1;
	}

	// Abrir archivo
	FILE* fp = fopen(argv[1], "r");

	// Verificar si el archivo se abrio correctamente
	if (fp = NULL)
	{
		perror("Error opening file: ");
		return -1;
	}

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
