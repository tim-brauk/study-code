/* Notenverwaltung fuer Studenten */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // viel zu viele includes, die nicht gebraucht werden
#include <ctype.h>

int anzahl = 0;
char namen[10][20];
float noten[10];
int i, j;
float summe;
int x;

void studentHinzufuegen(char *name, float note)
{
    strcpy(namen[anzahl], name);   
    noten[anzahl] = note;          
    anzahl++;                     
}

void ausgabe()
{
    for (i = 0; i < anzahl; i++)
    {
        printf("%d. %s: %.1f\n", i + 1, namen[i], noten[i]);
    }
}

float durchschnitt()
{
    summe = 0;
    for (i = 0; i < anzahl; i++)
        summe = summe + noten[i];
    return summe / anzahl;
}

int bestanden(float note)
{
    if (note <= 4.0)
        return 1;
    else
        return 0;
}

char *bewertung(float note)
{
    char *text = (char *)malloc(20);
    if (note == 1.0)
        strcpy(text, "sehr gut");
    else if (note <= 2.5)
        strcpy(text, "gut");
    else if (note <= 3.5)
        strcpy(text, "befriedigend");
    else if (note <= 4.0)
        strcpy(text, "ausreichend");
    else
        strcpy(text, "nicht bestanden");
    return text;
}

void sortieren()
{
    float tmp;
    char tmpName[20];
    for (i = 0; i < anzahl; i++)
    {
        for (j = 0; j < anzahl - 1; j++)
        {
            if (noten[j] > noten[j + 1])
            {
                tmp = noten[j];
                noten[j] = noten[j + 1];
                noten[j + 1] = tmp;
                strcpy(tmpName, namen[j]);
                strcpy(namen[j], namen[j + 1]);
                strcpy(namen[j + 1], tmpName);
            }
        }
    }
}

void grossschreiben(char *s)
{
    for (int k = 0; k < strlen(s); k++)
    {
        s[k] = toupper(s[k]);
    }
}

int main()
{
    studentHinzufuegen("Anna", 1.0);
    studentHinzufuegen("Ben", 2.3);
    studentHinzufuegen("Clara", 3.7);
    studentHinzufuegen("David", 4.7);
    studentHinzufuegen("Emma", 1.7);
    studentHinzufuegen("Felix", 2.0);

    printf("=== Alle Studenten ===\n");
    ausgabe();

    printf("\nDurchschnitt: %.2f\n", durchschnitt());

    // beste note suchen
    float beste = 6.0;
    int besterIndex = 0;
    for (i = 0; i < anzahl; i++)
    {
        if (noten[i] < beste)
        {
            beste = noten[i];
            besterIndex = i;
        }
    }
    printf("Beste Note: %s mit %.1f\n", namen[besterIndex], beste);

    // schlechteste note suchen
    float schlechteste = 0.0;
    int schlechtesterIndex = 0;
    for (i = 0; i < anzahl; i++)
    {
        if (noten[i] > schlechteste)
        {
            schlechteste = noten[i];
            schlechtesterIndex = i;
        }
    }
    printf("Schlechteste Note: %s mit %.1f\n", namen[schlechtesterIndex], schlechteste);

    int anzahlBestanden = 0;
    for (i = 0; i < anzahl; i++)
        if (bestanden(noten[i]) == 1)
            anzahlBestanden = anzahlBestanden + 1;
    printf("Bestanden: %d von %d\n", anzahlBestanden, anzahl);

    printf("\n=== Bewertungen ===\n");
    for (int k = 0; k < anzahl; k++)
    {
        printf("%-6s -> %s\n", namen[k], bewertung(noten[k]));
    }

    sortieren();
    printf("\n=== Sortiert ===\n");
    ausgabe();

    int *verteilung = (int *)malloc(6 * sizeof(int));
    for (int k = 0; k < 6; k++)
        verteilung[k] = 0;
    for (int k = 0; k < anzahl; k++)
        verteilung[(int)noten[k] - 1]++;
    printf("\n=== Notenverteilung ===\n");
    for (int k = 0; k < 6; k++)
        printf("Note %d: %d\n", k + 1, verteilung[k]);

    FILE *f = fopen("noten.txt", "w");
    for (int k = 0; k < anzahl; k++)
        fprintf(f, "%s;%.1f\n", namen[k], noten[k]);
    printf("\nDaten in noten.txt gespeichert.\n");

    char gruss[50] = "Viel Erfolg, ";
    strcat(gruss, namen[0]);
    grossschreiben(gruss);
    printf("%s!\n", gruss);

    return 0;
}