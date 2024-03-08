#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Criar structs para Placa e Marmorista
typedef struct St_Placa {
  char nome[20];
  float tamanho;
  float preco;
  struct St_Placa *Prox;
} Placa;

typedef struct St_Marmorista {
  char nome[20];
  int id;
  struct St_Marmorista *PrimeiraP;
  struct St_Marmorista *Prox;
} Marmorista;

Marmorista *PrimeiroM = NULL;

// Fun��o para adicionar marmoristas
void IncluirMarmorista(Marmorista *Novo) {
  Marmorista *Aux = PrimeiroM;

  if (PrimeiroM == NULL) {
    PrimeiroM = Novo;
    return;
  }

  while (Aux->Prox != NULL) {
    Aux = Aux->Prox;
  }
  Aux->Prox = Novo;
}

// Fun��o para incluir placa no servi�o dos marmoristas
void IncluirPlaca(Marmorista *Marmo, Placa *Nova) {
  Nova->Prox = Marmo->PrimeiraP;
  Marmo->PrimeiraP = Nova;
}

// Fun��o para liberar marmoristas
Marmorista *LiberarMarmorista() {

  if (PrimeiroM == NULL) {
    printf("\n----------\n");
    printf("  VAZIO!!");
    printf("\n----------\n");
    return NULL;
  }

  Marmorista *LiberarMarmorista = PrimeiroM;
  PrimeiroM = PrimeiroM->Prox;
  return LiberarMarmorista;
}

// Fun��o para exibir as placas liberadas
float LiberarPlacas(Marmorista *Marmor) {
  Placa *Aux = Marmor->PrimeiraP, *temp;
  float total = 0;

  while (Aux != NULL) {
    printf("\nPlaca: %s \t Tamanho: %.2f \t Pre�o: %.2f\n", Aux->nome,
           Aux->tamanho, Aux->preco);
    total = (Aux->preco * Aux->tamanho) + total;
    temp = Aux;
    Aux = Aux->Prox;
    free(temp);
  }
  Marmor->PrimeiraP = NULL;
  return total;
}

int main(void) {
  setlocale(LC_ALL, "portuguese");
  int i = 0;
  int j = 0;
  Marmorista *M1;
  Placa *P1;
  printf("=====================================================\n");
  printf("------------------TELA DE CADASTRO-------------------\n");
  printf("\nCadastrar Marmorista? (1 - CADASTRAR \t 2 - PULAR)\n");
  printf("\n");
  scanf("%d", &i);
  printf("-----------------------------------------------------\n");
  printf("=====================================================\n");

  if (i == 2) {
    printf("-----------------------------------------------------\n");
    printf("\nProcedimento encerrado. Tenha um bom dia!\n");
    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("=====================================================\n");
    return 0;
  }
  while (i != 3) {
    printf("\n\n");
    printf("=====================================================\n");
    printf("-----------------PERFIL MARMORISTA-------------------\n");
    printf("\n1 - Incluir \t 2 - Liberar \t 3 - Sair\n");
    scanf("%d", &i);
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");

    switch (i) {
    case 1:
      M1 = (Marmorista *)malloc(sizeof(Marmorista));
      M1->Prox = NULL;

      printf("\n\n");
      printf("=====================================================\n");
      printf("---------------------CADASTRAR-----------------------\n");
      printf("\nNome: ");
      scanf("%s", M1->nome);
      printf("\nC�digo: ");
      scanf("%d", &M1->id);
      IncluirMarmorista(M1);
      printf("\nInserir placa? \n(1 - Sim \t 2 - N�o) \n");
      scanf("%d", &j);
      printf("\n-----------------------------------------------------\n");
      printf("=====================================================\n");

      while (j == 1) {
        P1 = (Placa *)malloc(sizeof(Placa));
        P1->Prox = NULL;

        printf("\n\n");
        printf("=====================================================\n");
        printf("----------------------PLACAS-------------------------\n");
        printf("\nNome da placa: ");
        scanf("%s", P1->nome);
        printf("\nTamanho da placa: ");
        scanf("%f", &P1->tamanho);
        printf("\nPre�o da placa: ");
        scanf("%f", &P1->preco);
        IncluirPlaca(M1, P1);
        printf("\nInserir mais placas? \n (1- Sim \t 2- N�o)\n");
        scanf("%d", &j);
        printf("\n-----------------------------------------------------\n");
        printf("=====================================================\n");
      }
      break;
    case 2:
      M1 = LiberarMarmorista();

      if (M1 != NULL) {

        printf("\n\n");
        printf("=====================================================\n");
        printf("------------------TELA DE LIBERA��O------------------\n");
        printf("\nMarmorista Liberado: %s\t|| C�digo : %d\n", M1->nome, M1->id);
        printf("\n*****************************************************\n");

        if (P1 != NULL) {
          printf("\nTotal: %.2f\n", LiberarPlacas(M1));
          printf("\n*****************************************************\n");
          printf("\n-----------------------------------------------------\n");
          printf("=====================================================\n");
        }
        free(M1);
      }
      break;
    }
  }
  return 0;
}
