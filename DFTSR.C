/* Modelo compacto de memoria */
#pragma -mc

#include <dos.h>
#include <stdio.h>
#include <string.h>
#include "dftsr.h"

static unsigned char controlStructure[512];

/**
 * Procedimiento principal
 */
void main() {
	/* Estructura que almacena los segregs */
	struct SREGS segregs;
	unsigned long offset, segment, address, i, x, y, psp;

  printf("Star Wars: Dark Forces Advanced Controller Interface\n");

	/* Obtenemos el Program Segment Prefix. */
	psp = getpsp();
	printf("\tProgram Segment Prefix: %d\n", psp);

	/**
	 * Obtenemos los registros de segmentos.
	 * CS - Code Segment
	 * DS - Data Segment
	 * ES - Extra Segment
	 * SS - Stack Segment
	 */
	segread(&segregs);
	printf("\tCS: %u  DS: %u  ES: %u  SS: %u\n", segregs.cs, segregs.ds, segregs.es, segregs.ss);

	/* Establece todos los valores de la memoria a 0. */
	memset(controlStructure, sizeof(controlStructure), 0xFF);

	/* Establecemos todos los valores necesarios para arrancar el programa. */
	controlStructure[ADDR_VERSION_MAJOR] = VERSION_MAJOR;
	controlStructure[ADDR_VERSION_MINOR] = VERSION_MINOR;

	/* Esto es en teoria el texto que aparece en el J_Init (aunque no aparece) */
	controlStructure[ADDR_NAME 		+ 0x00] = 'A';
	controlStructure[ADDR_NAME 		+ 0x01] = 'I';
	controlStructure[ADDR_NAME 		+ 0x02] = 'T';
	controlStructure[ADDR_NAME 		+ 0x03] = '\0';

	/**
	 * Obtenemos la direcci�n (esta direcci�n
	 * es a partir del
	 */
	offset = (unsigned long)&controlStructure;
	segment = segregs.ss << 4;
	address = segment + offset;

	printf("\tControl Structure Address: %d %x\n", address, address);
	printf("\tUsing %s\n", &controlStructure[ADDR_NAME]);

	/**
	 * Imprimimos los valores de la estructura de control.
	 */
	/*
	for (y = 0; y < 32; y++) {
		for (x = 0; x < 16; x++) {
			i = y * 16 + x;
			printf("%02X ", controlStructure[i]);
		}
		printf("\n");
	}
	*/

	/* Salimos con 0 y reservamos X bytes en memoria */
	keep(0, sizeof(controlStructure) + 4);

}
