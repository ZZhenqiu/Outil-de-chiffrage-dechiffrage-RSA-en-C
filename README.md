# Outil basique Time-Base-One-Time-Password (TOTP) en C + rapport Pentest

Outil basique Time-Base-One-Time-Password (TOTP) en C + rapport Pentest

Bonjour, 

Disclaimer : 

Ce programme est hautement NON fonctionnel et ne prétend pas être autre chose qu’un simple exercice réalisé dans un but pédagogique. L’idée est principalement de s’entraîner sur le langage C et d’avoir une meilleure compréhension des vulnérabilités et attaques liées. 

Ce script permet la génération d’un TOTP puis sa vérification. Le but était de trouver certains vecteurs d’attaques possibles et ensuite de proposer des mesures de remédiation. Vous pouvez trouver un document plus détaillé à ce sujet ici, qui s’apparente à une forme de rapport de pentest : 

https://docs.google.com/document/d/1DekOahjO3trraw4UTMqll9W1dNavJVaQ904plXO7tRk/edit?usp=sharing


Pour lancer ce programme : 
-Créez un fichier par exemple « script.c ». 
-Compilez-le avec la commande « gcc -o test test.c -lcrypto »
-Lancez le script avec la commande ./test 1 ou ./test 2 

Voilà. 

Vous pouvez également utiliser MyCompiler si besoin. 


![c](https://github.com/user-attachments/assets/e2b5b373-ecf0-483f-8210-c24a0e4c2af5)




