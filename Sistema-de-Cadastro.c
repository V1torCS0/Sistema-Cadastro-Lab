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
#define TRUE 1
#define FALSE 0

typedef struct {
    
    char studentName[MAX_LEN];
    int studentAge;
    int registration;
    int schoolSemester;
    float evaluationScore;
} Data;


int showMenu (void);
int pickUp (void);
int fileLineExist (FILE *);
int fileLineSearch (FILE *, int);
int registrationExist (FILE *, int);
void insertData (FILE *);
void deleteData (FILE *);
void updateData (FILE *);
void closeSystem (FILE *);

int main (void) {

    int choice;

    do {

        FILE * cursor = fopen (FILE_NAME, "r");
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

int fileLineExist (FILE * masterFile) {

    char readLines[MAX_LEN];

    rewind (masterFile);

    if (fgets(readLines, sizeof(readLines), masterFile) != NULL)
        return TRUE;
    return FALSE;
}

int fileLineSearch (FILE * masterFile, int registration) {

    char readLines[MAX_LEN], registrationParseString[10];
    sprintf (registrationParseString, "%d", registration);
    int line = 0;

    rewind (masterFile);

    while (fgets(readLines, sizeof(readLines), masterFile) != NULL)
        if (strstr(readLines, registrationParseString) == NULL)
            line++;

    return line;
}

int registrationExist(FILE * masterFile, int registration) {

    char readLine[MAX_LEN];
    char registrationParseString[10]; // padrão de matrícula com 6 dígitos

    sprintf(registrationParseString, "%d", registration);

    rewind (masterFile); // Voltar para o início do arquivo

    while (fgets(readLine, sizeof(readLine), masterFile) != NULL)
        if (strstr(readLine, registrationParseString) != NULL)
            return TRUE;

    return FALSE;
}

void insertData (FILE * masterFile) {

    if (masterFile == NULL)
        masterFile = fopen (FILE_NAME, "w");
    else
        masterFile = fopen (FILE_NAME, "a");

    Data student;

    printf ("Insira os dados do aluno (um aluno por vez):");
    printf ("\nMatricula: "); scanf ("%d", &student.registration);

    if (registrationExist (masterFile, student.registration)) {

        printf ("Essa matricula ja existe, tente novamente...\n");
        return;
    }

    printf ("\nNome: "); scanf ("%s", student.studentName);
    printf ("\nIdade: "); scanf ("%d", &student.studentAge);
    printf ("\nSemestre: "); scanf ("%d", &student.schoolSemester);
    printf ("\nNota do Exame: "); scanf ("%f", &student.evaluationScore);

    fprintf (masterFile, "Matricula: %d | Nome: %s | Idade: %d | Semestre: %d | Nota do Exame: %.2f\n",
    student.registration, student.studentName, student.studentAge, student.schoolSemester, student.evaluationScore);
        
    rewind (masterFile);
    fclose (masterFile);
}

void deleteData(FILE * masterFile) {

    if (masterFile == NULL) {

        printf("Falha ao abrir arquivo ou arquivo nao foi criado.\n");
        return;
    }

    if (fileLineExist (masterFile)) {

        printf("Digite a matricula do aluno a ser removido: ");
        int registrationScanned; scanf("%d", &registrationScanned);

        if (!registrationExist(masterFile, registrationScanned)) {

            printf("A matricula inserida nao consta, tente novamente...\n");
            return;
        }

        char lineFile[MAX_LEN], registrationRemoved[10]; // padrão de matrícula com 6 dígitos

        sprintf(registrationRemoved, "%d", registrationScanned);

        FILE * copyAndPaste = fopen("temp.txt", "w");

        if (copyAndPaste == NULL) {

            printf("Falha ao criar arquivo auxiliar.\n");
            return;
        }

        rewind (masterFile); // Voltar para o início do arquivo

        while (fgets(lineFile, sizeof(lineFile), masterFile) != NULL)
            if (strstr(lineFile, registrationRemoved) == NULL)
                fputs(lineFile, copyAndPaste);

        fclose(masterFile);
        fclose(copyAndPaste);

        printf("Removido com sucesso.\n");

        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
    } else
        printf ("Arquivo sem cadastros...\n");
}

void updateData (FILE * masterFile) {

    if (masterFile == NULL) {

        printf("Falha ao abrir arquivo ou arquivo nao foi criado.\n");
        return;
    } else
        masterFile = fopen (FILE_NAME, "r+");

    if (fileLineExist (masterFile)) {

        printf ("Digite a matricula do aluno a ser atualizado: ");
        int registrationScanned; scanf ("%d", &registrationScanned);

        if (!registrationExist (masterFile, registrationScanned)) {

            printf ("A matricula inserida nao consta, tente novamente...\n");
            return;
        }

        fseek (masterFile, fileLineSearch (masterFile, registrationScanned), SEEK_SET);
        //continuar a partir daqui
    } else
        printf ("Arquivo sem cadastros...\n");
}

void closeSystem (FILE * masterFile) {

    printf ("Finalizando...\n");
    fclose(masterFile);
}