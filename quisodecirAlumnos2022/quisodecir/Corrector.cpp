/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ricardo Sanchez Ponce 426115542
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#include <ctype.h>

//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{


	FILE* fp;
	char c;
	char tmp[TAMTOKEN];
	int h = 0;                      // índice de tmp
	int n = 0;                      // número de palabras únicas almacenadas

	fopen_s(&fp, szNombre, "r");
	if (fp != NULL) {

		while (fscanf_s(fp, "%c", &c, 1) == 1) {

			int esSeparador = 0;

			if (c == ' ' || c == ',' || c == '\n' || c == '\t' ||
				c == '\r' || c == '.' || c == '(' || c == ')' || c == ';')
				esSeparador = 1;

			if (!esSeparador) {

				if (h < TAMTOKEN - 1) {

					// pasar a minúscula al momento de leer
					c = tolower(c);

					tmp[h++] = c;
				}

			}
			else {

				if (h > 0) {

					tmp[h] = '\0';

					// buscar si ya existe (búsqueda lineal)
					int existe = -1;
					for (int k = 0; k < n; k++) {
						if (strcmp(szPalabras[k], tmp) == 0) {
							existe = k;
							break;
						}
					}

					if (existe == -1) {
						if (n < NUMPALABRAS) {
							strcpy_s(szPalabras[n],50, tmp);
							iEstadisticas[n] = 1;
							n++;
						}
					}
					else {
						iEstadisticas[existe]++;
					}

					h = 0;   // reiniciar índice
				}
			}
		}

		// Última palabra si no terminó con separador
		if (h > 0) {
			tmp[h] = '\0';

			int existe = -1;
			for (int k = 0; k < n; k++) {
				if (strcmp(szPalabras[k], tmp) == 0) {
					existe = k;
					break;
				}
			}

			if (existe == -1) {
				if (n < NUMPALABRAS) {
					strcpy_s(szPalabras[n],50, tmp);
					iEstadisticas[n] = 1;
					n++;
				}
			}
			else {
				iEstadisticas[existe]++;
			}
		}

		fclose(fp);
	}

	iNumElementos = n;

	

	//Ordenar alfabeticamente
	for (int i = 0; i < iNumElementos - 1; i++) {
		char buffer[TAMTOKEN];
		int aux;
		for (int j = i + 1; j < iNumElementos; j++) {
			if (strcmp(szPalabras[i], szPalabras[j]) > 0) {
				strcpy_s(buffer, 50, szPalabras[i]);
				strcpy_s(szPalabras[i], 50, szPalabras[j]);
				strcpy_s(szPalabras[j], 50, buffer);

				aux = iEstadisticas[i];
				iEstadisticas[i] = iEstadisticas[j];
				iEstadisticas[j] = aux;
				

			}
		}
	}
	

}
/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su c?digo

	
	iNumLista = 0;
	int conta = 0;
	for (int i = 0; i < iNumElementos; i++) {
		for (int h = 0; h < iNumSugeridas; h++) {
			if (strcmp(szPalabras[i], szPalabrasSugeridas[h]) == 0) {
				
				iPeso[conta] = iEstadisticas[i];
				strcpy_s(szListaFinal[conta++],TAMTOKEN, szPalabrasSugeridas[h]);
				iNumLista++;

			}
		}
	}
	//Eliminar repetidas
	int nuevo = 0;  // cantidad final sin repetidas

	for (int i = 0; i < iNumLista; i++) {

		int yaExiste = 0;

		// comprobar si la palabra ya está en la nueva lista
		for (int j = 0; j < nuevo; j++) {
			if (strcmp(szListaFinal[j], szListaFinal[i]) == 0) {
				yaExiste = 1;
			}
		}

		// si no existía, copiar a la lista limpia
		if (yaExiste == 0) {
			strcpy_s(szListaFinal[nuevo], TAMTOKEN, szListaFinal[i]);
			iPeso[nuevo] = iPeso[i];
			nuevo++;
		}
	}

	iNumLista = nuevo;

	//Ordenar de mayor a menor peso
	for (int i = 0; i < iNumLista - 1; i++) {

		for (int h = 0; h < iNumLista - 1 - i; h++) {

			if (iPeso[h] < iPeso[h + 1]) {

				int aux = iPeso[h];
				iPeso[h] = iPeso[h + 1];
				iPeso[h + 1] = aux;

				char waux[TAMTOKEN];
				strcpy_s(waux, TAMTOKEN, szListaFinal[h]);
				strcpy_s(szListaFinal[h], TAMTOKEN, szListaFinal[h + 1]);
				strcpy_s(szListaFinal[h + 1], TAMTOKEN, waux);
			}
		}
	}

	
	
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(char * szPalabraLeida, char	szPalabrasSugeridas[][TAMTOKEN], int &	iNumSugeridas)						
{
	
	//Sustituya estas lineas por su c?digo
	int NumSugeridas = 0;
	int auxcont = 0;
	char letras[33] = "abcdefghijklmnñopqrstuvwxyzáéíóú";
	int longi = strlen(szPalabraLeida);
	char szPalabraLeidaAux[TAMTOKEN];
	int flag = 0;
	strcpy_s(szPalabraLeidaAux, szPalabraLeida);

	//Eliminación de un caracter
	while (flag != 1) {

		if (strlen(szPalabraLeida) == 1)
		{
			flag = 1;
		}
		else {

			for (int h = 0; h < longi; h++) {
				char buffer[50];
				strcpy_s(buffer, szPalabraLeidaAux);
				for (int i = h; i < longi; i++) {
					szPalabraLeidaAux[i] = szPalabraLeidaAux[i + 1];
				}
				strcpy_s(szPalabrasSugeridas[h], TAMTOKEN, szPalabraLeidaAux);
				strcpy_s(szPalabraLeidaAux, buffer);
				NumSugeridas++;
			}
			auxcont = NumSugeridas;
			flag = 1;
		}
	}
	flag = 0;
	
	//Transposicion de caracteres

	while (flag != 1) {

		if (strlen(szPalabraLeida) == 1) {

			flag = 1;
		}
		else {
			for (int h = 0; h < longi - 1; h++) {
				char bufferc, buffer[50];
				strcpy_s(buffer, szPalabraLeidaAux);
				bufferc = szPalabraLeidaAux[h];

				szPalabraLeidaAux[h] = szPalabraLeidaAux[h + 1];
				szPalabraLeidaAux[h + 1] = bufferc;

				strcpy_s(szPalabrasSugeridas[h + auxcont], TAMTOKEN, szPalabraLeidaAux);
				strcpy_s(szPalabraLeidaAux, buffer);
				NumSugeridas++;
			}
			auxcont = NumSugeridas;
			flag = 1;
		}
	}
	

	//Sustitucion de cada caracter por letra del alfabeto

	for (int h = 0; h < longi; h++) {
		char buffer[50];
		strcpy_s(buffer, szPalabraLeidaAux);
		for (int i = 0; i < 32; i++) {
			szPalabraLeidaAux[h] = letras[i];
			strcpy_s(szPalabrasSugeridas[i + auxcont], TAMTOKEN, szPalabraLeidaAux);
			NumSugeridas++;
		}
		auxcont = NumSugeridas;
		strcpy_s(szPalabraLeidaAux, buffer);
	}

	//Insertar abecedario en cada espacio de la cadena

	for (int h = 0, p = 0; h < longi + 1; h++) {
		char buffer[50];

		strcpy_s(buffer, szPalabraLeidaAux);
		for (int i = 0; i < 50; i++)
			if (buffer[i] == '\0') {
				buffer[i + 1] = '\0';
				i = 51;
			}
		for (int i = 0; i < 50; i++)
			if (szPalabraLeidaAux[i] == '\0') {
				szPalabraLeidaAux[i + 1] = '\0';
				i = 51;
			}
		for (int i = 0; i < longi - p; i++) {
			szPalabraLeidaAux[i + 1 + h] = buffer[i + h];
		}
		for (int j = 0; j < 32; j++) {
			szPalabraLeidaAux[h] = letras[j];
			strcpy_s(szPalabrasSugeridas[j + auxcont], TAMTOKEN, szPalabraLeidaAux);
			NumSugeridas++;
		}
		auxcont = NumSugeridas;
		p++;
		strcpy_s(szPalabraLeidaAux, buffer);

	}

	//Colocar la palabra misma como parte de la sugerencia
	NumSugeridas = NumSugeridas + 1;
	strcpy_s(szPalabrasSugeridas[NumSugeridas - 1], TAMTOKEN, szPalabraLeida);


	//Ordenamos alfabeticamente
	iNumSugeridas = NumSugeridas;
	for (int i = 0; i < iNumSugeridas - 1; i++) {
		char buffer[TAMTOKEN];
		for (int j = i + 1; j < iNumSugeridas; j++) {
			if (strcmp(szPalabrasSugeridas[i], szPalabrasSugeridas[j]) > 0) {
				strcpy_s(buffer,TAMTOKEN, szPalabrasSugeridas[i]);
				strcpy_s(szPalabrasSugeridas[i], TAMTOKEN, szPalabrasSugeridas[j]);
				strcpy_s(szPalabrasSugeridas[j], TAMTOKEN, buffer);
			}
		}
	}
	

}
	


