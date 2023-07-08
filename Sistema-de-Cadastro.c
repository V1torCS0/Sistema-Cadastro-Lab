/* Desenvolva um sistema de Cadastro utilizando a linguagem C. Para isso a aplicação deve os seguintes requisitos:
- A aplicação deve ter um menu com no mínimo as opções de adicionar, deletar e editar elementos do cadastro, além de fechar o programa.
- O programa de cadastro deve utilizar arquivos para armazenar os dados no computador.
- A escolha do tipo de Aplicação para Cadastro é exclusivo da equipe.
- Não é obrigatório o uso de interface gráfica, pode uitlizar apenas o console. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//arquivo padrão para execução do sistema
#define FILE_NAME "queriesDB.txt"
#define MAX_LEN 100
#define INS 1
#define DEL 2
#define UPD 3
#define CLS 4

typedef struct {
    
    char studentName[MAX_LEN];
    int studentAge;
    int registration;
    int schoolSemester;
    float evaluationScore;
} Data;


int showMenu (void);
int pickUp (void);
void insertData (FILE *);
void deleteData (FILE *);
void updateData (FILE *);
void closeSystem (FILE *);

int main (void) {

    FILE * cursor;
    int choice;

    do {

        cursor = fopen (FILE_NAME, "r");
        choice = showMenu ();

        switch (choice) {

            case INS:
                insertData (cursor);
                break;
            case DEL:
                deleteData (cursor);
                break;
            case UPD:
                //updateData (cursor);
                break;
            case CLS:
                closeSystem (cursor);
                break;
    
            default:
                printf ("Falha ao executar.\n");
                break;
        }
    } while (choice != CLS);
    
    return 0;
}

int showMenu (void) {

    printf ("===Menu do Sistema===\n");
    printf ("1. Adicionar Cadastro;\n"); printf ("2. Deletar Cadastro;\n");
    printf ("3. Editar Cadastro;\n"); printf ("4. Fechar Arquivo.\n");
    
    printf ("Input: ");
    int inputValue = pickUp ();
    
    if (inputValue <= CLS && inputValue >= INS)
        return inputValue;
    else {
        printf ("Tente novamente...\n");
        return showMenu ();
    }
}

int pickUp (void) {

    int aux; scanf ("%d", &aux);
    return aux;
}

void insertData (FILE * masterFile) {

    if (masterFile == NULL)
        masterFile = fopen (FILE_NAME, "w");
    else
        masterFile = fopen (FILE_NAME, "a");

    Data student;

    printf ("Insira os dados do aluno (um aluno por vez):");

    printf ("\nNome: "); scanf ("%s", student.studentName);
    printf ("\nIdade: "); scanf ("%d", &student.studentAge);
    printf ("\nMatricula: "); scanf ("%d", &student.registration);
    printf ("\nSemestre: "); scanf ("%d", &student.schoolSemester);
    printf ("\nNota do Exame: "); scanf ("%f", &student.evaluationScore);

    fprintf (masterFile, "Nome: %s | Idade: %d | Matricula: %d | Semestre: %d | Nota do Exame: %.2f\n",
    student.studentName, student.studentAge, student.registration, student.schoolSemester, student.evaluationScore);
    
    rewind (masterFile);
}

void deleteData (FILE * masterFile) {

    if (masterFile == NULL) {

        printf ("Falha ao abrir arquivo.\n");
        return;
    }

    char line[MAX_LEN];
    char registrationRemoved[7]; int registrationScanned; //padrão de matrícula com 6 dígitos
    int registrationFound = 0;

    printf ("Digite a matricula do aluno a ser removido: ");
    scanf ("%d", &registrationScanned); sprintf (registrationRemoved, "%d", registrationScanned);

    FILE * copyAndPaste = fopen ("temp.txt", "w");

    if (copyAndPaste == NULL) {

        printf ("Falha ao criar arquivo auxiliar.\n");
        return;
    }

    while (fgets (line, sizeof (line), masterFile) != NULL) {
        
        if (strstr(line, registrationRemoved) == NULL)
            fputs (line, copyAndPaste);
        else
            registrationFound++;
    }

    if (registrationFound)
        printf ("Removido com sucesso.\n");
    else
        printf ("Matricula nao foi cadastrada.\n");

    fclose (masterFile);
    fclose (copyAndPaste);

    remove (FILE_NAME);
    rename ("temp.txt", FILE_NAME);
}

void updateData (FILE * masterFile) {

    if (masterFile == NULL) {

        printf ("Falha ao abrir arquivo.\n");
        return;
    }
}

void closeSystem (FILE * masterFile) {

    printf ("Finalizando...\n");
    fclose(masterFile);
}