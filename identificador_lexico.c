#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETRA 101
#define DIGITO 102
#define FIM_DO_ARQUIVO 103
#define PONTO_E_VIRGULA 104

char proximoCaractere = '\0';
int classeCaractere = -1;
char lexema[] = "\0";

void acrescentaCaractere() { strncat(lexema, &proximoCaractere, 1); }

void obtemCaractere(FILE* arquivo) {
    proximoCaractere = fgetc(arquivo);
    if (proximoCaractere == ' ' || proximoCaractere == '\n') {
        classeCaractere = -1;
        return;
    } else if (proximoCaractere == EOF) {
        classeCaractere = FIM_DO_ARQUIVO;
    } else if (isdigit(proximoCaractere)) {
        classeCaractere = DIGITO;
        return;
    } else {
        classeCaractere = LETRA;
        return;
    }
}

int pesquisa(char lexema[]) {
    if (strcmp(lexema, "int") == 0) {
        printf("%s\t\t\t", lexema);
        printf("palavra_reservada\n");
    } else if (strcmp(lexema, "for") == 0) {
        printf("%s\t\t\t", lexema);
        printf("loop\n");
    } else if (strcmp(lexema, "+") == 0) {
        printf("%s\t\t\t", lexema);
        printf("op_soma\n");
    } else if (strcmp(lexema, "/") == 0) {
        printf("%s\t\t\t", lexema);
        printf("op_igua\n");
    } else if (strcmp(lexema, "-") == 0) {
        printf("%s\t\t\t", lexema);
        printf("op_subt\n");
    } else if (strcmp(lexema, "*") == 0) {
        printf("%s\t\t\t", lexema);
        printf("op_mult\n");
    } else if (strcmp(lexema, "=") == 0) {
        printf("%s\t\t\t", lexema);
        printf("sinal_igual\n");
    } else if (strcmp(lexema, ";") == 0) {
        printf("%s\t\t\t", lexema);
        printf("ponto_e_virgula\n");
    } else {
        printf("%s\t\t\t", lexema);
        printf("idetificador_desconhecido\n");
    }
    lexema[0] = '\0';
}

int lex() {
    FILE* arquivo;
    arquivo = fopen("entrada.txt", "r");

    printf("lexemas\t\t\ttokens\n");
    printf("========================================\n");

    while (classeCaractere != FIM_DO_ARQUIVO) {
        obtemCaractere(arquivo);
        switch (classeCaractere) {
            case LETRA:
                acrescentaCaractere();
                obtemCaractere(arquivo);
                while (classeCaractere == LETRA || classeCaractere == DIGITO) {
                    acrescentaCaractere();
                    obtemCaractere(arquivo);
                }
                pesquisa(lexema);
                break;
            case DIGITO:
                acrescentaCaractere();
                obtemCaractere(arquivo);
                while (classeCaractere == DIGITO) {
                    acrescentaCaractere();
                    obtemCaractere(arquivo);
                }
                printf("%s\t\t\t", lexema);
                printf("inteiro_literal\n");
                lexema[0] = '\0';
                break;
        }
    }
    fclose(arquivo);
}

int main() { lex(); }
