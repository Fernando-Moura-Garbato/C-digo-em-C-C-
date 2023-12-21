

#include <stdio.h>

double pegarCdb() {
    printf("Qual o percentual de CDI que o CDB oferece?\n");
    double cdb;
    scanf("%lf", &cdb);
    while (cdb <= 0) {
        printf("A taxa do CDB não pode ser igual ou abaixo de zero.");
        pegarCdb();
    }
    return cdb/100;
}

int pegarMeses(int *ptr) {
    int meses;
    do {
        printf("Qual sera a quantidade de meses em que o dinheiro sera investido?\n");
        scanf("%i", &meses);
        *ptr = meses;
        return meses;
    } while (meses < 1);
}

double pegarLci() {
    printf("Qual o percentual de CDI que o LCI oferece?\n");
    double lci;
    scanf("%lf", &lci);
    if (lci < 0) {
        printf("A porcentagem de CDI nao pode ser negativa.\n");
        pegarLci();
    }
    else return lci/100;
}

double pegarInvestido() {
    printf("Qual sera a quantidade a ser investida?\n");
    double capital;
    scanf("%lf", &capital);
    if (capital < 0) {
        printf("Nao ha como investir um valor negativo. Insira o valor correto.\n");
        pegarInvestido();
    }
    else return capital;
}

double pegarSelic() {
    printf("Qual a taxa Selic anual, em porcentagem?\n");
    double selic;
    scanf("%lf", &selic);
    if (selic < 0.10) {
        printf("O valor esta errado.\n");
        pegarSelic();
    }
    else return selic;
    }

double calculoInvestimentosLCI(double lci, double investido, double taxaSelic, int tempo, double* vetorL) {
    double ganhos = (((taxaSelic - 0.10) / 12) / 100);
    double ganhosProcessados = (ganhos * lci) + 1;

    double monte = investido;
    for (int i = 0; i < tempo; i++) {
        monte = monte * ganhosProcessados;
        vetorL[i] = monte;
    }

    return(monte);

}

double calcularImposto(int meses) {
    double impostoRenda;
    if (meses <= 6) {
        impostoRenda = 0.22;
    }
    else if (meses <= 12) {
        impostoRenda = 0.20;
    }
    else if (meses <= 24) {
        impostoRenda = 0.175;
    }
    else{
        impostoRenda = 0.15;
        }
    return impostoRenda;
}



double calculoInvestimentosCDB(double cdb, double investido, double taxaSelic, int tempo, double* vetorC) {
    double ganhos = (((taxaSelic - 0.10) / 12) / 100);
    double ganhosProcessados = (ganhos * cdb) + 1;
    double imposto = calcularImposto(tempo);

    double monte = investido;
    for (int i = 0; i < tempo; i++) {
        double lucro = monte * ganhosProcessados;
        double lucroIsolado = lucro - monte;
        double lucroComImposto = lucroIsolado * imposto;
        monte = monte + (lucroIsolado - lucroComImposto);
        vetorC[i] = monte;
    }

    return (monte);
}

double calculoInvestimentos(double lci, double cdb, double investido, double taxaSelic, int tempo, double* vetorL, double* vetorC) {
    calculoInvestimentosLCI(lci, investido, taxaSelic, tempo, vetorL);
    calculoInvestimentosCDB(cdb, investido, taxaSelic, tempo, vetorC);
    return(0);
}


void apresentacaoDeResultados(int tempo, double *vetorC, double *vetorL) {
    for (int i = 0; i < tempo; i++) {
        printf("No mes %i, o investimento em CDB esta com %lf, e o em LCI esta com %lf", i + 1, vetorC[i], vetorL[i]);
        if (vetorC[i] > vetorL[i]) {
            printf(", portanto, o CDB lucrou mais.\n");
        }
        else {
            printf(", portanto, o LCI lucrou mais.\n");
        }
    }
}


    int main(){
    printf("Bem vindo. Para calcular o resultado do seu investimento, por favor informe:\n");

    int meses;
    int *ptrMeses = &meses;
    pegarMeses(ptrMeses);
    double* vetorCdb = (double*)malloc(meses * sizeof(double));
    double* vetorLci = (double*)malloc(meses * sizeof(double));
    
    calculoInvestimentos(pegarLci(), pegarCdb(), pegarInvestido(), pegarSelic(), meses, vetorLci, vetorCdb);
    apresentacaoDeResultados(meses, vetorCdb, vetorLci);
    double valorFinalC = vetorCdb[meses-1];
    double valorFinalL = vetorLci[meses-1];

    printf("\nEm %i meses, o valor resultante do investimento em CDB seria %lf, e o valor resultante do LCI seria %lf.\n", meses, valorFinalC, valorFinalL);
    if (valorFinalC > valorFinalL) {
        printf(" Assim, o investimento melhor nessas condições será em CDB.");
    }
    else {
        printf(" Assim, o investimento melhor nessas condicoes sera em LCI.");
    }
     return(0);
}