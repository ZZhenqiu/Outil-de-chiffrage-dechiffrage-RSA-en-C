#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Prototypes
int petitFermat(int, int);
int fonctionEuler(int, int);
void genererCles();
int inverseMultiplicatif(int);
void chiffrerMessage();
void dechiffrerMessage();

// Variables
int nombrePremierP, nombrePremierQ, produitN, fonctionEulerV, clesPubliques[91], clesPrivees[91], tableauMessage[91], tableauMessageChiffre[91], i;
char messageSaisi[91];


int main()
{
    // Saisie des nombres premiers p et q
    printf("Bonjour, pour pouvoir utiliser ce programme, veuillez entrer deux nombres premiers : ");
    scanf("%d %d", &nombrePremierP, &nombrePremierQ);
    if (!petitFermat(nombrePremierP, 5) || nombrePremierP == 1 ||
        !petitFermat(nombrePremierQ, 5) || nombrePremierQ == 1 ||
        nombrePremierP == nombrePremierQ)
    {
        printf("Entrée incorrecte, choisissez des nombres premiers\n");
        exit(1);
    }

    printf("Entrez ensuite le message à crypter : ");
    scanf(" %[^\n]s", messageSaisi);
    for (i = 0; i < strlen(messageSaisi); i++)
        tableauMessage[i] = messageSaisi[i];

    // Calcul de n et fonction Euler
    produitN = nombrePremierP * nombrePremierQ;
    fonctionEulerV = fonctionEuler(nombrePremierP, nombrePremierQ);


    genererCles();

    chiffrerMessage();
    dechiffrerMessage();

    return 0;
}



// Utilisation du petit théorème de Fermat pour tester si un nombre est probablement premier
int petitFermat(int nombre, int iterations)
{
    if (nombre <= 1)
        return 0; // Les nombres <= 1 ne sont pas premiers

    if (nombre <= 3)
        return 1; // 2 et 3 sont premiers

    // Effectuer des tests avec le petit théorème de Fermat
    for (int i = 0; i < iterations; i++)
    {
        // Choisir un nombre aléatoire 'a' entre 2 et nombre-2
        int a = 2 + rand() % (nombre - 3);

        // Calculer a^(nombre-1) % nombre
        int result = 1;
        for (int j = 0; j < nombre - 1; j++)
        {
            result = (result * a) % nombre;
        }

        // Si le résultat n'est pas 1, le nombre n'est pas premier
        if (result != 1)
            return 0;
    }

// Le nombre est probablement premier
    return 1; 
}



//Calcul de la fonction d'Euler
int fonctionEuler(int p, int q)
{
    return (p - 1) * (q - 1);
}



// Fonction utilisant les résultats précédents pour générer les clés
void genererCles()
{
    int indiceCle;
    indiceCle = 0;

    for (i = 2; i < fonctionEulerV; i++)
    {
        if (fonctionEulerV % i == 0)
            continue;
        if (petitFermat(i, 5) && i != nombrePremierP && i != nombrePremierQ)
        {
            clesPubliques[indiceCle] = i;
            if ((clesPrivees[indiceCle] = inverseMultiplicatif(clesPubliques[indiceCle])) > 0)
            {
                indiceCle++;
            }
            if (indiceCle == 91 - 1)
                break;
        }
    }
}



int inverseMultiplicatif(int x)
{
    int k = 1;

    while (1)
    {
        k = k + fonctionEulerV;
        if (k % x == 0)
            return (k / x);
    }
}



void chiffrerMessage()
{
    int valeurCaractere, valeurChiffree, cleActuelle, longueurMessage;
    i = 0;
    longueurMessage = strlen(messageSaisi);

    while (i < longueurMessage)
    {
        valeurCaractere = tableauMessage[i];
        valeurCaractere = valeurCaractere - 96;
        valeurChiffree = 1;
        cleActuelle = clesPubliques[0];

        for (int j = 0; j < cleActuelle; j++)
        {
            valeurChiffree = valeurChiffree * valeurCaractere;
            valeurChiffree = valeurChiffree % produitN;
        }

        tableauMessageChiffre[i] = valeurChiffree + 96;
        i++;
    }
    tableauMessageChiffre[i] = -1;
    printf("\nLe message chiffré est :\n");
    for (i = 0; tableauMessageChiffre[i] != -1; i++)
        printf("\033[1;31m%c\033[0m", (char)tableauMessageChiffre[i]); // En rouge
}


void dechiffrerMessage()
{
    int valeurCaractere, valeurDechiffree, cleActuelle;
    i = 0;

    while (tableauMessageChiffre[i] != -1)
    {
        valeurCaractere = tableauMessageChiffre[i] - 96;
        valeurDechiffree = 1;
        cleActuelle = clesPrivees[0];

        for (int j = 0; j < cleActuelle; j++)
        {
            valeurDechiffree = valeurDechiffree * valeurCaractere;
            valeurDechiffree = valeurDechiffree % produitN;
        }

        tableauMessage[i] = valeurDechiffree + 96;
        i++;
    }
    tableauMessage[i] = -1;
    printf("\nLe message déchiffré est :\n");
    for (i = 0; tableauMessage[i] != -1; i++)
        printf("\033[1;32m%c\033[0m", (char)tableauMessage[i]); // En vert
}
