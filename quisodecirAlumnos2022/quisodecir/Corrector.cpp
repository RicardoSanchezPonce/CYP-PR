/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)
{

	//Sustituya estas lineas por su c�digo

	//Cargar diccionario y contar palabras
	FILE *fp;
	int i = 0;
	fopen_s(&fp, szNombre, "r");
	if (fp != NULL) {

		for (i = 0; fscanf_s(fp, "%s", szPalabras[i], TAMTOKEN) == 1; i++);
		
	}
	iNumElementos = i;
	//Limpiar signos de puntación
	for (int h = 0; h < iNumElementos; h++)
		for (int j = 0; j < strlen(szPalabras[h]); j++) {
			if (szPalabras[h][j] == '.' || szPalabras[h][j] == ','|| szPalabras[h][j] == ';' || szPalabras[h][j] == ')'|| szPalabras[h][j] == '\n'|| szPalabras[h][j] == '\t'){

				szPalabras[h][j] = '\0';
			}
			else
			{
				if (szPalabras[h][j] == '(') {

					
					for(int l = 0; l < strlen(szPalabras[h]); l++)
					szPalabras[h][l] = szPalabras[h][l + 1];
				}
			}


		}

	for (int h = 0; h < i; h++)
	{
		printf("%s\n", szPalabras[h]);
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

	//Sustituya estas lineas por su c�digo
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su c�digo
	int NumSugeridas = 0;
	int auxcont;
	char letras[39] = "abcdefghijklmnñopqrstuvwxyzáéíóú";
	int longi = strlen(szPalabraLeida);

	//Eliminación de un caracter

	for (int h = 0; h < longi; h++) {
		char buffer[50];
		strcpy_s(buffer, szPalabraLeida);
		for (int i = 0; i < longi; i++) {
			szPalabraLeida[i + h] = szPalabraLeida[i + 1 + h];
		}
		strcpy_s(szPalabrasSugeridas[h], szPalabraLeida);
		strcpy_s(szPalabraLeida, 50, buffer);
		NumSugeridas++;
	}
	auxcont = NumSugeridas;

	//Transposicion de caracteres

	for (int h = 0; h < longi - 1; h++) {
		char bufferc, buffer[50];
		strcpy_s(buffer, szPalabraLeida);
		bufferc = szPalabraLeida[h];

		szPalabraLeida[h] = szPalabraLeida[h + 1];
		szPalabraLeida[h + 1] = bufferc;

		strcpy_s(szPalabrasSugeridas[h + auxcont], szPalabraLeida);
		strcpy_s(szPalabraLeida, 50, buffer);
		NumSugeridas++;
	}
	auxcont = NumSugeridas;

	//Sustitucion de cada caracter por letra del alfabeto

	for (int h = 0; h < longi; h++) {
		char buffer[50];
		strcpy_s(buffer, szPalabraLeida);
		for (int i = 0; i < 32; i++) {
			szPalabraLeida[h] = letras[i];
			strcpy_s(szPalabrasSugeridas[i + auxcont], szPalabraLeida);
			NumSugeridas++;
		}
		auxcont = NumSugeridas;
		strcpy_s(szPalabraLeida, 50, buffer);
	}

	//Insertar abecedario en cada espacio de la cadena

	for (int h = 0, p = 0; h < longi + 1; h++) {
		char buffer[50];

		strcpy_s(buffer, szPalabraLeida);
		for (int i = 0; i < 50; i++)
			if (buffer[i] == '\0') {
				buffer[i + 1] = '\0';
				i = 51;
			}
		for (int i = 0; i < 50; i++)
			if (szPalabraLeida[i] == '\0') {
				szPalabraLeida[i + 1] = '\0';
				i = 51;
			}
		for (int i = 0; i < longi - p; i++) {
			szPalabraLeida[i + 1 + h] = buffer[i + h];
		}
		for (int j = 0; j < 32; j++) {
			szPalabraLeida[h] = letras[j];
			strcpy_s(szPalabrasSugeridas[j + auxcont], szPalabraLeida);
			NumSugeridas++;
		}
		auxcont = NumSugeridas;
		p++;
		strcpy_s(szPalabraLeida, 50, buffer);

	}

	iNumSugeridas = NumSugeridas;
}
