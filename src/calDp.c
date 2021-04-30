#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void help();
void run();
void create_csv(double*, int, int);
double calculate(double*, int, int, int);


int main(int argc, char* argv[])
{
    if (argc == 1)
        run();

    if (argc == 2)
    {
        if (strcmp(argv[1],"-h") == 0)
            help();
    }

    return 0;
}


void help()
{
    printf("\n1- Este programa serve para o calculo de desvio padrão de amostra\n");
    printf("2- Os numeros devem ser digitados separados por espaço ou com quebra de linha\n");
    printf("3- O label ID no arquivo csv se refere ao conjunto de dados digitados\n");

}

void run()
{
    int append_file = 0;
    int id = 0;
    int running = 1;
    while(running){
        // alocating the memory
        int number_of_values;
        double *values;
        printf("Digite o número de valores a serem digitados: ");
        scanf ("%d", &number_of_values);

        if(number_of_values >= 1)
        {
            values = malloc(number_of_values * sizeof(double));
            printf("Digite os valores:\n");
            double val;
            for (int i = 0; i < number_of_values; i++)
            {
                scanf("%lf", &val);
                values[i] = val;
            }
            calculate(values, number_of_values, append_file, id);
            free(values);
        }

        else
        {
            printf("\nERROR\n");
            exit(1);
        }

        char resp[1];
        printf("Deseja utilizar novos valores(s/n)? ");
        scanf("%s", &resp);

        if(strcmp(resp, "s") == 0)
        {
            append_file = 1;
            id += 1;
            continue;
        }
        else if (strcmp(resp, "n") == 0)
        {
            running = 0;
        }

        else
        {
            printf("\nERROR\n");
            exit(1);
        }
        
    }
    exit(0);
}


void create_csv(double values[], int append_file, int file_ID)
{  
    FILE* fp;
    if(!append_file)
    {
        fp = fopen("./csv/sample.csv", "w");
        fprintf(fp, "ID,Tamanho_da_amostra(N),Soma_dos_numeros,Media,Desvio_padrão(σ),Variação_da_população(σ²),Desvio_padrão_da_amostra(s),Variação_da_amostra(s²)\n");
    }

    else
    {
        fp = fopen("./csv/sample.csv", "a");
    }

    fprintf(fp, "%d,", file_ID);
    
    for(int i = 0; i < 7; i++)
    {
        fprintf(fp, "%lf,", values[i]);
    }
    fputc('\n', fp);
    fflush(fp);
    fclose(fp);
}


double calculate(double values[], int N, int append_file, int file_ID)
{
    double sum = 0;
    double std_dev, std_dev_sample, medium_value, average, population_variation, sample_population_variation;
    
    for(int i = 0; i < N; i++)
    {
        sum += values[i];
    }

    medium_value = sum/2;
    average = sum/N;

    printf("\nTamanho da amostra(N): %d\n", N);
    printf("Soma dos numeros: %lf\n", sum);
    printf("Media: %lf\n", average);


    // calculate the standard deviation 
    double sum_value_average = 0;
    double sub_value_average_pow;
    for(int i = 0; i < N; i++)
    {
        sub_value_average_pow = pow(values[i] - average, 2);
        sum_value_average += sub_value_average_pow;
    }

    std_dev = sqrt(sum_value_average/N);
    population_variation = pow(std_dev, 2);
    printf("Desvio padrão(σ): %lf\n", std_dev);
    printf("Variação da população(σ²): %lf\n", population_variation);

    // sample standard deviation
    sum_value_average = 0;
    sum_value_average = 0;
    for(int i = 0; i < N; i++)
    {
        sub_value_average_pow = pow(values[i] - medium_value, 2);
        sum_value_average += sub_value_average_pow;
    }

    std_dev_sample = sqrt(sum_value_average/(N-1));
    sample_population_variation = pow(std_dev_sample, 2);
    printf("Desvio padrão da amostra(s): %lf\n", std_dev_sample);
    printf("Variação da amostra(s²): %lf\n", sample_population_variation);

    // storing all of the calculated values
    double stored_values[7] = {N, sum, average, std_dev, population_variation, std_dev_sample, sample_population_variation};

    printf("\nDados salvos no arquivo sample.csv\n");
    create_csv(stored_values, append_file, file_ID);    
}
