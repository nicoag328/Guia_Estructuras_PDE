// Guia Estructuras Programacion de Dispositivos
// Nicolas Gestro
// Ejercicio 2

#include <stdio.h>
#include <string.h>
#include "scan_wrappers.h"

struct vuelo_t
{
	char codigo[8];
	char ciudad_origen [30];
	char ciudad_destino[30];
};

int main()
{
	int vuelos_presentes = 0;
	struct vuelo_t vuelos[4];
	char ciudad_entrada[30];

	// Obtener datos de los vuelos
	for (int i = 0; i < 4; i++)
	{
		printf("Ingrese los datos del vuelo %d\n", i + 1);

		printf("Codigo: ");
		fgets(vuelos[i].codigo, 8, stdin);
		vuelos[i].codigo[strlen(vuelos[i].codigo) - 1] = 0;

		printf("Ciudad origen: ");
		fgets(vuelos[i].ciudad_origen, 30, stdin);
		vuelos[i].ciudad_origen[strlen(vuelos[i].ciudad_origen) - 1] = 0;

		printf("Ciudad destino: ");
		fgets(vuelos[i].ciudad_destino, 30, stdin);
		vuelos[i].ciudad_destino[strlen(vuelos[i].ciudad_destino) - 1] = 0;
	}

	// Pedir al usuario que ingrese la ciudad a buscar
	printf("\nIngrese ciudad para buscar vuelos: ");
	fgets(ciudad_entrada, 30, stdin);
	ciudad_entrada[strlen(ciudad_entrada) - 1] = 0;

	printf("\nCodigo\tOrigen\t\t\tDestino\n");

	// Mostrar vuelos con igual ciudad origen a la ingresada
	for (int i = 0; i < 4; i++)
	{
		if (strcmp(vuelos[i].ciudad_origen, ciudad_entrada) == 0)
		{
			vuelos_presentes = 1;
			printf("%s\t%s\t\t\t%s\n", vuelos[i].codigo, vuelos[i].ciudad_origen, vuelos[i].ciudad_destino);
		}
	}

	// Mostrar vuelos con igual ciudad destino a la ingresada
	for (int i = 0; i < 4; i++)
	{
		if (strcmp(vuelos[i].ciudad_destino, ciudad_entrada) == 0)
		{
			vuelos_presentes = 1;
			printf("%s\t%s\t\t\t%s\n", vuelos[i].codigo, vuelos[i].ciudad_origen, vuelos[i].ciudad_destino);
		}
	}

	// Mostrar mensaje de error si no se encontraron vuelos
	if (vuelos_presentes == 0)
		printf("\nNo se encontraron vuelos que partan o arriben de %s\n", ciudad_entrada);

	return 0;
}
