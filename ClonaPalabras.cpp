#include <stdio.h>
#include <string.h>
#define TAMTOKEN 50

//ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo

void ClonaPalabras(char szPalabraLeida[50] // Palabra a clonar
	, char szPalabrasSugeridas[2000][TAMTOKEN] //Lista de palabras clonadas
	, int *iNumSugeridas //Numero de elementos en la lista
) {

	int NumSugeridas = 0;
	int auxcont;
	char letras[27] = "abcdefghijklmnopqrstuvwxyz";
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
		strcpy_s(szPalabraLeida, 50 , buffer);
		NumSugeridas++;
	}
	auxcont = NumSugeridas;

	//Sustitucion de cada caracter por letra del alfabeto

	for (int h = 0; h < longi; h++) {
		char buffer[50];
		strcpy_s(buffer, szPalabraLeida);
		for (int i = 0; i < 26; i++) {
			szPalabraLeida[h] = letras[i];
			strcpy_s(szPalabrasSugeridas[i + auxcont], szPalabraLeida);
			NumSugeridas++;
		}
		auxcont = NumSugeridas;
		strcpy_s(szPalabraLeida,50, buffer);
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
		for (int j = 0; j < 26; j++) {
			szPalabraLeida[h] = letras[j];
			strcpy_s(szPalabrasSugeridas[j + auxcont], szPalabraLeida);
			NumSugeridas++;
		}
		auxcont = NumSugeridas;
		p++;
		strcpy_s(szPalabraLeida,50, buffer);

	}
	*iNumSugeridas = NumSugeridas;


}


int main() {

	char PalabraLeida[50];
	char PalabrasSugeridas[2000][TAMTOKEN];
	int NumSugeridas = 0;

	fgets(PalabraLeida, 50, stdin);
	//Quitar salto de línea
	for (int i = 0; i < 50; i++)
		if (PalabraLeida[i] == '\n') {
			PalabraLeida[i] = '\0';
			i = 51;
		}


	ClonaPalabras(PalabraLeida, PalabrasSugeridas, &NumSugeridas);
	

	printf("%s\n", PalabraLeida);
	printf("%i\n", NumSugeridas);
	for (int i = 0; i < NumSugeridas; i++)
	printf("%s\n", PalabrasSugeridas[i]);
	




}