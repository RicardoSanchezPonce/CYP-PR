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
	int i = 0;
	int h = 0;
	char c;

	fopen_s(&fp, szNombre, "r");
	if (fp != NULL) {

		while (fscanf_s(fp, "%c", &c, 1) == 1) {

			int esSeparador = 0;

			if (c == ' ' || c == ',' || c == '\n' || c == '\t' || c == '\r' || c == '.' || c == '(' || c == ')' || c == ';')
				esSeparador = 1;

			if (!esSeparador) {

				if (h < TAMTOKEN - 1) {
					szPalabras[i][h++] = c;
				}

			}
			else {

				if (h > 0) {
					szPalabras[i][h] = '\0';
					i++;
					h = 0;

					// *** EVITA DESBORDES ***
					if (i >= NUMPALABRAS) {
						break;
					}
				}
			}
		}

		// Cerrar última palabra si no excede el límite
		if (h > 0 && i < NUMPALABRAS) {
			szPalabras[i][h] = '\0';
			i++;
		}

		fclose(fp);
	}

	iNumElementos = i;
	//Pasar todos los elementos a minusculas

	for (int i = 0; i < iNumElementos; i++) {         // Recorre cada cadena
		for (int j = 0; szPalabras[i][j] != '\0'; j++) {   // Recorre cada carácter
			szPalabras[i][j] = tolower(szPalabras[i][j]);         // Convierte a minúscula
		}
	}

	//Ordenar alfabeticamente
	for (int i = 0; i < iNumElementos - 1; i++) {
		char buffer[TAMTOKEN];
		for (int j = i + 1; j < iNumElementos; j++) {
			if (strcmp(szPalabras[i], szPalabras[j]) > 0) {
				strcpy_s(buffer, 50, szPalabras[i]);
				strcpy_s(szPalabras[i], 50, szPalabras[j]);
				strcpy_s(szPalabras[j], 50, buffer);
			}
		}
	}
	//Quitar palabras repetidas y contar en iEstadisticas
	int nuevo = 0;

	for (int i = 0; i < iNumElementos; i++) {
		if (i == 0 || strcmp(szPalabras[i], szPalabras[i - 1]) != 0) {
			strcpy_s(szPalabras[nuevo], 50, szPalabras[i]);
			iEstadisticas[nuevo] = 1;
			nuevo++;
		}
		else
		{
			iEstadisticas[nuevo - 1]++;
		}
	}
	iNumElementos = nuevo;

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
	int conta = 0, contaux = 0;
	for (int i = 0; i < iNumElementos; i++) {
		for (int h = 0; h < iNumSugeridas; h++) {
			if (strcmp(szPalabras[i], szPalabrasSugeridas[h]) == 0) {
				
				iPeso[conta] = iEstadisticas[i];
				strcpy_s(szListaFinal[conta++],TAMTOKEN, szPalabrasSugeridas[h]);
				iNumLista++;

			}
		}
	}

	//Ordenar de mayor a menor peso
	for (int i = 0; i < iNumLista - 1; i++) {
		int numaux = 0;
		char wordaux[TAMTOKEN];
		for (int h = 0; h < iNumLista; h++) {

			if(iPeso[h] > iPeso[h + 1]){}
			else {
				if (iPeso[h] < iPeso[h + 1]) {
					numaux = iPeso[h + 1];
					iPeso[h + 1] = iPeso[h];
					iPeso[h] = numaux;

					strcpy_s(wordaux, szListaFinal[h + 1]);
					strcpy_s(szListaFinal[h + 1], 50, szListaFinal[h]);
					strcpy_s(szListaFinal[h], 50, wordaux);


				}

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
	


