#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAMTOKEN 50
#define MAXPAL 50000

int esDelimitador(char c) {
    return c == ' ' || c == '\t' || c == '\n' ||
        c == ',' || c == ';' || c == '.' ||
        c == '(' || c == ')' || c == '\r';
}

// Busca una palabra en el diccionario, devuelve índice o -1
int buscaPalabra(char palabra[][TAMTOKEN], int num, char* pal) {
    for (int i = 0; i < num; i++) {
        if (strcmp(palabra[i], pal) == 0)
            return i;
    }
    return -1;
}

// Implementación de Diccionario()
void Diccionario(char* szNombre,
    char szPalabras[][TAMTOKEN],
    int iEstadisticas[],
    int& iNumElementos)
{
    FILE* archivo;
    archivo = fopen(szNombre, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo: %s\n", szNombre);
        return;
    }

    char c;
    char palabra[TAMTOKEN];
    int pos = 0;
    iNumElementos = 0;

    while ((c = fgetc(archivo)) != EOF) {
        if (!esDelimitador(c)) {
            if (pos < TAMTOKEN - 1) {
                palabra[pos++] = c;
            }
        }
        else if (pos > 0) {
            palabra[pos] = '\0';
            

            // Buscar si ya existe
            int indice = buscaPalabra(szPalabras, iNumElementos, palabra);
            if (indice >= 0) {
                iEstadisticas[indice]++;
            }
            else {
                strcpy(szPalabras[iNumElementos], palabra);
                iEstadisticas[iNumElementos] = 1;
                iNumElementos++;
            }
            pos = 0;
        }
    }

    // Última palabra 
    if (pos > 0) {
        palabra[pos] = '\0';
        
        int indice = buscaPalabra(szPalabras, iNumElementos, palabra);
        if (indice >= 0) {
            iEstadisticas[indice]++;
        }
        else {
            strcpy(szPalabras[iNumElementos], palabra);
            iEstadisticas[iNumElementos] = 1;
            iNumElementos++;
        }
    }

    
}

int main() {
    char palabras[MAXPAL][TAMTOKEN];
    int frecuencias[MAXPAL];
    int num = 0;

    Diccionario("texto.txt", palabras, frecuencias, num);

    printf("\nPalabras detectadas: %d\n", num);
    for (int i = 0; i < num && i < 20; i++) // mostramos las primeras 20
        printf("%s: %d\n", palabras[i], frecuencias[i]);

    return 0;
}
// \(0 ~ 0)/ inicia burbujazo
int main_burbuja()
{
bNoOrdenado = 1; // true
for (pasada = 0; pasada < contaPalDiccionario - 1 && bNoOrdenado; pasada++)
{
    bNoOrdenado = 0; // false
    for (i = 0; i < contaPalDiccionario - 1; i++)
    {
        if (strcmp(palabras[i], palabras[i + 1]) > 0)
        {
            strcpy(auxPal, palabras[i]);
            strcpy(palabras[i], palabras[i + 1]);
            strcpy(palabras[i + 1], auxPal);
            bNoOrdenado = 1;
        }
    }

    printf("\nPasada %i:\n", pasada + 1);
    for (i = 0; i < contaPalDiccionario; i++)
        printf("%s\t", palabras[i]);
    printf("\n");
}

// Resultado final
printf("\nPalabras ordenadas alfabeticamente:\n");
for (i = 0; i < contaPalDiccionario; i++)
    printf("%s\n", palabras[i]);

return 0;
}
// ~('u')~ 