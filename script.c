#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int petitFermat(int, int);
int Phi(int, int);
void genererCles();
int euclideEtendu(int, int);
int exposantChiffrement(int);
int exposantDechiffrement(int, int);
void chiffrerMessage();
void dechiffrerMessage();


int nombrePremierP, nombrePremierQ, produitN, PhiN, clePubliqueE, clePriveeD;
char messageSaisi[91];



int main() {
    printf("Bonjour, pour pouvoir utiliser ce programme, veuillez entrer deux nombres premiers (si possible >= 5): ");
    scanf("%d %d", &nombrePremierP, &nombrePremierQ);

    if (!petitFermat(nombrePremierP, 5) || nombrePremierP == 1 ||
        !petitFermat(nombrePremierQ, 5) || nombrePremierQ == 1 ||
        nombrePremierP == nombrePremierQ) {
        printf("Entrée incorrecte, choisissez des nombres premiers\n");
        exit(1);
    }

    printf("Entrez ensuite le message à crypter : ");
    scanf(" %[^\n]s", messageSaisi);

    produitN = nombrePremierP * nombrePremierQ;
    PhiN = Phi(nombrePremierP, nombrePremierQ);

    genererCles();
    chiffrerMessage();
    dechiffrerMessage();

    return 0;
}



// Utilisation du petit théorème de Fermat pour tester si le nombre (p ou q) est premier
int petitFermat(int nombre, int iterations) {
    if (nombre <= 1)
        return 0;

    if (nombre <= 3)
        return 1;

    for (int i = 0; i < iterations; i++) {
        int a = 2 + rand() % (nombre - 3); 
        int result = 1;
        for (int j = 0; j < nombre - 1; j++) {
            result = (result * a) % nombre;  // La formule du petit théorème de Fermat est a^p-1 congruent à 1 modulo p. Cependant, nous utiliserons la méthode suivante a^(nombre-1) % nombre avec une boucle for. La raison de cette méthode est l'évitement des débordements d'entiers. Calculer directement a^n-1 peut entraîner des résultats extrêmement grands et peut dépasser la capacité maximale d'un entier (2^31 pour un int en C par exemple). En utilisant l'opération modulo à chaque étape on réduit continuellement la taille du résultat intermédiaire. 
        }

        if (result != 1)   // Si le résultat n'est pas 1, le nombre n'est pas premier
            return 0;
    }

    return 1;   // Le nombre est probablement premier
}



// Indicatrice d'Euler
int Phi(int p, int q) {
    return (p - 1) * (q - 1);
}



// E
int exposantChiffrement(int PhiN) {
    int e = 2; // Valeur arbitraire

    while (e < PhiN) {
        if (euclideEtendu(e, PhiN) == 1)
            break;
        else
            e++;
    }

    return e;
}



int euclideEtendu(int a, int b) {
    int x0 = 1, x1 = 0, y0 = 0, y1 = 1, q, temp, quotient;

    while (b != 0) {
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



// D
int exposantDechiffrement(int e, int PhiN) {
    return euclideEtendu(e, PhiN);
}



void genererCles() {
    clePubliqueE = exposantChiffrement(PhiN);
    clePriveeD = exposantDechiffrement(clePubliqueE, PhiN);
}



void chiffrerMessage() {
    printf("\nLe message chiffré est :\n");
    for (int i = 0; i < strlen(messageSaisi); i++) {
        int valeurCaractere = messageSaisi[i];
        int valeurChiffree = 1;

        for (int j = 0; j < clePubliqueE; j++) {
            valeurChiffree = (valeurChiffree * valeurCaractere) % produitN;
        }

        printf("\033[1;31m%c\033[0m", (char)valeurChiffree); // En rouge
    }
}



void dechiffrerMessage() {
    printf("\nLe message déchiffré est :\n");
    for (int i = 0; i < strlen(messageSaisi); i++) {
        int valeurChiffree = messageSaisi[i];
        int valeurDechiffree = 1;

        for (int j = 0; j < clePriveeD; j++) {
            valeurDechiffree = (valeurDechiffree * valeurChiffree) % produitN;
        }

        printf("\033[1;32m%c\033[0m", (char)valeurDechiffree); // En vert
    }
}
