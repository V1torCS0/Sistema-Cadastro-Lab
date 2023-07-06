/* Desenvolva um sistema de Cadastro utilizando a linguagem C. Para isso a aplicação deve os seguintes requisitos:
- A aplicação deve ter um menu com no mínimo as opções de adicionar, deletar e editar elementos do cadastro, além de fechar o programa.
- O programa de cadastro deve utilizar arquivos para armazenar os dados no computador.
- A escolha do tipo de Aplicação para Cadastro é exclusivo da equipe.
- Não é obrigatório o uso de interface gráfica, pode uitlizar apenas o console. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILENAME "queriesDB.txt"

int showMenu (void);
int pickUp (void);
void insertData (FILE *);
void deleteData (FILE *);
void updateData (FILE *);
void closeSystem (FILE *);

int main (void) {

    int choice;

    do {
        choice = showMenu ();
        printf ("\n");
    } while (!choice);

    switch (choice) {

        case 1:
            //insertData ();
            break;
        case 2:
            //deleteData ();
            break;
        case 3:
            //updateData ();
            break;
        case 4:
            //closeSystem ();
            break;
    
        default:
            printf ("Falha ao executar.\n");
            break;
    }
    
    return 0;
}

int showMenu (void) {

    printf ("===Menu do Sistema===\n");
    printf ("1. Adicionar Elemento;\n"); printf ("2. Deletar Elemento;\n");
    printf ("3. Editar Elemento;\n"); printf ("4. Fechar Arquivo.\n");
    
    printf ("Input: ");
    int inputValue = pickUp ();
    
    if (inputValue <= 4 && inputValue >= 1)
        return inputValue;
    else {
        printf ("Tente novamente...\n");
        return 0;
    }
}

int pickUp (void) {

    int aux; scanf ("%d", &aux);
    return aux;
}

void insertData (FILE * masterFile) {

}

void deleteData (FILE * masterFile) {

}

void updateData (FILE * masterFile) {

}

void closeSystem (FILE * masterFile) {

}