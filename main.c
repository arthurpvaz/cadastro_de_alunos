#include <stdio.h>
#include <stdlib.h>

struct ALUNOS {
    int matricula;
    double g1, g2, media;
};

void calcularMedia(struct ALUNOS *aluno) {
    aluno -> media = (aluno -> g1 + aluno -> g2) / 2.0;
}

int encontraMaiorMedia(struct ALUNOS *alunos, int tamanho) {
    int indiceMaior = 0;
    int i;

    for (i = 0; i < tamanho; i++) {
        if (alunos[i].media > alunos[indiceMaior].media) {
            indiceMaior = i;
        }
    }

    return indiceMaior;
}

int compararMedias(const void *a, const void *b) {
    struct ALUNOS *alunoA = (struct ALUNOS *)a;
    struct ALUNOS *alunoB = (struct ALUNOS *)b;

    if (alunoA -> media < alunoB -> media) return 1;
    if (alunoA -> media > alunoB -> media) return -1;
    return 0;
}

int main() {
    int quantidade;
    int i;

    printf("Quantos alunos serao cadastrados? ");
    scanf("%d", &quantidade);

    struct ALUNOS *alunos = (struct ALUNOS *)malloc(quantidade * sizeof(struct ALUNOS));

    if (alunos == NULL) {
        printf("Erro ao alocar memoria!\n");
        return (1);
    }

    for (i = 0; i < quantidade; i++) {
        printf("\nAluno %d:\n", i + 1);
        printf("Matricula: ");
        scanf("%d", &alunos[i].matricula);

        printf("Nota G1: ");
        scanf("%lf", &alunos[i].g1);
        printf("Nota G2: ");
        scanf("%lf", &alunos[i].g2);
    }

    for (i = 0; i < quantidade; i++) {
        calcularMedia(&alunos[i]);
    }

    int indiceMaior = encontraMaiorMedia(alunos, quantidade);

    printf("\nAluno com maior media\n");
    printf("Matricula: %d - G1: %.2lf - G2: %.2lf - Media: %.2lf", alunos[indiceMaior].matricula, alunos[indiceMaior].g1, alunos[indiceMaior].g2, alunos[indiceMaior].media);

    qsort(alunos, quantidade, sizeof(struct ALUNOS), compararMedias);

    printf("\nAlunos ordenados por media (decrescente):\n");
    
    for (i = 0; i < quantidade; i++) {
        printf("Matricula: %d - Media: %.2lf\n", alunos[i].matricula, alunos[i].media);
    }

    printf("\nAlunos que precisam realizar substituicao de grau:");
    int temSubstituicao = 0;
    for (i = 0; i < quantidade; i++) {
        if (alunos[i].media < 6.0) {
            printf("\nMatricula: %d - G1: %.2lf - G2: %.2lf - Media: %.2lf", alunos[i].matricula, alunos[i].g1, alunos[i].g2, alunos[i].media);
            temSubstituicao = 1;
        }
    }

    if (!temSubstituicao) {
        printf("\nNenhum aluno precisa de substituicao de grau!");
    }

    free(alunos);

    return 0;
}