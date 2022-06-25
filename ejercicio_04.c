// Guia Estructuras Programacion de Dispositivos
// Nicolas Gestro
// Ejercicio 4

#include <stdio.h>
#include <string.h>
#include "csv_file.c"

struct fecha_t
{
	int mes;
	int dia;
};

struct factura_t
{
	int numero;
	struct fecha_t fecha;
	char cliente[30];
	float monto;
};

int main(int argc, char* argv[])
{

	// Nombre de archivo por defecto
	char default_file[] = "ejercicio_04.csv";
	char *filename = default_file;

	// Verificar los argumentos
	if (argc < 2)
	{
		printf("Modo de uso: ejercicio_04 <archivo.csv>\nUsando archivo por defecto ejercicio_04.csv\n\n");
	}
	else
	{
		filename = argv[1];
	}

	// Declaracion de variables
	struct factura_t facturas[10];
	struct csv_file_t csv_file;
	char buf[30];
	float totales_meses[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int mejor_mes = 0;

	// Abrir archivo csv
	if(csv_open(&csv_file, filename) != 0)
		return -1;

	
	// Leer los datos de las facturas del archivo csv
	for (int i = 0; i < 10; i++)
	{
		// Leer numero de la factura
		if(csv_get_field(&csv_file, buf, 30, i, 0) != 0)
			return -1;
	
		if(sscanf(buf, "%d", &facturas[i].numero) != 1)
		{
			printf("Datos invalidos\n");
			return -1;
		}

		// Leer mes de la factura
		if(csv_get_field(&csv_file, buf, 30, i, 1) != 0)
			return -1;

		if(sscanf(buf, "%d", &facturas[i].fecha.mes) != 1)
		{
			printf("Datos invalidos\n");
			return -1;
		}
		
		// Leer dia de la factura
		if(csv_get_field(&csv_file, buf, 30, i, 2) != 0)
			return -1;
		
		if(sscanf(buf, "%d", &facturas[i].fecha.dia) != 1)
		{
			printf("Datos invalidos\n");
			return -1;
		}

		// Leer nombre de cliente de la factura
		if(csv_get_field(&csv_file, buf, 30, i, 3) != 0)
			return -1;
		
		strcpy(facturas[i].cliente, buf);

		// Leer monto de la factura
		if(csv_get_field(&csv_file, buf, 30, i, 4) != 0)
			return -1;
		
		if(sscanf(buf, "%f", &facturas[i].monto) != 1)
		{
			printf("Datos invalidos\n");
			return -1;
		}
	}

	// Sumar los totales de cada mes
	for (int i = 0; i < 10; i++)
	{
		totales_meses[facturas[i].fecha.mes - 1] += facturas[i].monto;
	}

	// Encotrar el mes en el que mas se recaudo
	for(int i = 0; i < 12; i++)
	{
		if(totales_meses[i] >= totales_meses[mejor_mes])
			mejor_mes = i;
	}

	// Mostrar cual fue el mejor mes
	printf("El mejor mes fue el %d con un total de %.02f\n", mejor_mes + 1, totales_meses[mejor_mes]);

	return 0;
}
