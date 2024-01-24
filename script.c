#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int petitFermat(int, int);
int fonctionEuler(int, int);
void genererCles();
int euclideEtendu(int, int);
int exposantChiffrement(int);
int exposantDechiffrement(int, int);
void chiffrerMessage();
void dechiffrerMessage();



int nombrePremierP, nombrePremierQ, produitN, fonctionEulerV, clesPubliques[91], clesPrivees[91], tableauMessage[91], tableauMessageChiffre[91], i, exposantChiffrementE, exposantDechiffrementD;
char messageSaisi[91];



int main()
{
    // Saisie des nombres premiers p et q
    printf("Bonjour, pour pouvoir utiliser ce programme, veuillez entrer deux nombres premiers (si possible >= 5): ");
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

    // Calcul de n et indicatrice Euler
    produitN = nombrePremierP * nombrePremierQ;
    fonctionEulerV = fonctionEuler(nombrePremierP, nombrePremierQ);

    genererCles();

    chiffrerMessage();
    dechiffrerMessage();

    return 0;
}



// Utilisation du petit théorème de Fermat pour tester si le nombre (p ou q) est premier
int petitFermat(int nombre, int iterations)
{
    if (nombre <= 1)
        return 0; 

    if (nombre <= 3)
        return 1;


    for (int i = 0; i < iterations; i++)
    {
        // Choisir un nombre aléatoire 'a' entre 2 et nombre-2
        int a = 2 + rand() % (nombre - 3);

        // La formule du petit théorème de Fermat est a^p-1 congruent à 1 modulo p. Cependant, nous utiliserons la méthode suivante a^(nombre-1) % nombre avec une boucle for. La raison de cette méthode est l'évitement des débordements d'entiers. Calculer directement a^n-1 peut entrîner des résultats extrêmement grands et peut dépasser la capacité maximale d'un entier (2^31 pour un int en C par exemple). En utilisant l'opération modulo à chaque étape on réduit continuellement la taille du résultat intermédiaire. Cela maintient le résultat dans une plage gérable, évitant ainsi les problèmes de débordement.  
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



// Fonction pour calculer l'exposant de chiffrement E
int exposantChiffrement(int phi)
{
    int e = 2; // Valeur arbitraire

    // Vérifie que l'exposant de chiffrement est premier avec phi
    while (e < phi)
    {
        if (euclideEtendu(e, phi) == 1)
            break;
        else
            e++;
    }

    return e;
}



int fonctionEuler(int p, int q)
{
    return (p - 1) * (q - 1);
}



// Fonction pour calculer l'exposant de déchiffrement D avec l'algorithme d'Euclide étendu (simplifié)
int euclideEtendu(int a, int b)
{
    int x0 = 1, x1 = 0, y0 = 0, y1 = 1, q, temp, quotient;

    while (b != 0)
    {
        quotient = a / b;

        temp = a;
        a = b;
        b = temp % b;

        temp = x0;
        x0 = x1;
        x1 = temp - quotient * x1;

        temp = y0;
        y0 = y1;
        y1 = temp - quotient * y1;
    }

    return x0;
}



int exposantDechiffrement(int e, int phi) // Utilisation de l'algorithme d'Euclide étendu pour calculer l'exposant de déchiffrement
{
    return euclideEtendu(e, phi);
}



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
            if ((clesPrivees[indiceCle] = euclideEtendu(clesPubliques[indiceCle], fonctionEulerV)) > 0)
            {
                indiceCle++;
            }
            if (indiceCle == 91 - 1)
                break;
        }
    }

    exposantChiffrementE = exposantChiffrement(fonctionEulerV);
    exposantDechiffrementD = exposantDechiffrement(exposantChiffrementE, fonctionEulerV);
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
            valeurChiffree = (valeurChiffree * valeurCaractere) % produitN;
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
