

#include <stdio.h>
#include <math.h>


double pegarMeses() {
    printf("Qual sera a quantidade de meses em que o dinheiro sera investido?\n");
    double meses;
    scanf("%lf", &meses);
    while (meses < 1) {
        printf("Insira um valor apropriado de meses.\n");
        pegarMeses();
    }
    return meses;
}

double pegarCdi() {
    printf("Qual a porcentagem do CDI a ser investido?\n");
    double cdi;
    scanf("%lf", &cdi);
    if (cdi < 0) {
        printf("A porcentagem de CDI nao pode ser negativa.\n");
        pegarCdi();
    }
    else return cdi/100;
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
    if (selic < 0) {
        printf("O valor esta errado.\n");
        pegarSelic();
    }
    else return selic;
    }

void apresentacaoDeResultados(double tempo, double investido, double lucroFinal) {
    printf("Em %.0lf meses, com %.2lf investido, voce teria um lucro final de R$%.2lf reais, totalizando R$%.2lf reais.", tempo, investido, lucroFinal, lucroFinal + investido);
}


double calculoInvestimentosLCI(double cdi, double investido, double taxaSelic, double tempo) {
    double ganhos = (((taxaSelic - 0.10) / 12) / 100);
    if (ganhos<0) {
        printf("Um erro ocorreu. Insira a taxa selic novamente.");
        pegarSelic();
    }
    double ganhosUm = ganhos + 1;
    double porc = pow(ganhosUm, tempo);
    double ganhoMensal = (investido * ganhosUm) - investido;
    double lucroInicial = (investido * porc) - investido;
    double lucroFinal = cdi * lucroInicial;

    apresentacaoDeResultados(tempo, investido, lucroFinal);

    return lucroFinal+investido;
}


    int main(){
    printf("Bem vindo. Para calcular o resultado do seu investimento, por favor informe:\n");

    calculoInvestimentosLCI(pegarCdi(), pegarInvestido(), pegarSelic(), pegarMeses());

     return(0);
}