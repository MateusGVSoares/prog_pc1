#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG

// Definição da estrutura de matriz
typedef struct
{
    int rows;     // Número de linhas
    int cols;     // Número de colunas
    int **matriz; // Ponteiro para a matriz

} Matrix;

int alloc_matrix(Matrix *target, int rows, int cols)
{
    target->cols = cols;
    target->rows = rows;

    // Aloca (rows) ponteiros para as linhas e verifica se a memória foi alocada com sucesso
    target->matriz = malloc(rows * sizeof(int *));
    if (target->matriz == NULL)
        return 1;

    // Aloca (cols) * sizeof(int) de memória para as colunas dentro das linhas e verifica se alocou com sucesso
    for (int i = 0; i < rows; i++)
    {
        target->matriz[i] = malloc(cols * sizeof(int));
        if (target->matriz[i] == NULL)
            return 1;
    }
    return 0;
}

// Free na memória alocada para a matriz
int free_matrix(Matrix *target)
{
    for (int m = 0; m < target->rows; m++)
    {
        // Deve liberar a memória de cada ponteiro da linha individualmente
        free(target->matriz[m]);
    }
    // Libera a memória alocada para os ponteiros de ponteiros
    free(target->matriz);
    target->matriz = NULL;
    return 0;
}

// Atribui um valor individual para uma entrada da matriz
int set_entry_matrix(Matrix *target_m, int value, int row, int col)
{
    if (target_m != NULL && target_m->matriz != NULL)
    {
        target_m->matriz[row][col] = value;
        return 0;
    }
    else
        return 1;
}

int set_matrix_row(Matrix *target_m, int *vector, int row)
{
    if (target_m != NULL && target_m->matriz != NULL)
    {
        for (int e = 0; e < target_m->cols; e++)
            target_m->matriz[row][e] = vector[e];
        return 0;
    }
    else
        return 1;
}

int sum_matrix(Matrix *matriz_a, Matrix *matriz_b, Matrix *result)
{
    // Verifica a alocação de memória
    if (matriz_a == NULL || matriz_b == NULL)
        return -1;

    // Se a soma não conseguir ser realizada, retorna 1
    if (matriz_a->cols != matriz_b->cols || matriz_a->rows != matriz_b->rows)
        return 1;

    for (int i_rows = 0; i_rows < matriz_a->rows; i_rows++)
    {
        for (int i_cols = 0; i_cols < matriz_a->cols; i_cols++)
        {
            result->matriz[i_rows][i_cols] = matriz_a->matriz[i_rows][i_cols] + matriz_b->matriz[i_rows][i_cols];
        }
    }
    return 0;
}

int mult_matrix(Matrix *matriz_a, Matrix *matriz_b, Matrix *result)
{
    if (matriz_a->cols != matriz_b->rows)
    {
        return 1;
    }

    if (alloc_matrix(result, matriz_a->rows, matriz_b->cols))
    {
        printf("DEU RUIM ! \n");
        return 0;
    }

    int mult_result = 0, it_cols = 0, it_cols_b;
    // Itera as linhas da matriz A
    for (int i_rows = 0; i_rows < matriz_a->rows; i_rows++)
    {
        // Itera as colunas de B
        for (int it_cols_b = 0; it_cols_b < matriz_b->cols; it_cols_b++)
        {
            // Itera as colunas da linha i_rows da matriz A
            for (it_cols = 0; it_cols < matriz_a->cols; it_cols++)
            {
                // Guarda numa variável a multiplicação dos elementos da linha i_rows A e da coluna it_cols_b B
                mult_result += (matriz_a->matriz[i_rows][it_cols]) * (matriz_b->matriz[it_cols][it_cols_b]);
            }
#ifdef DEBUG
            printf("Iterando na posição [%d][%d] (Resultado = %d) \n",
                   i_rows,
                   it_cols,
                   mult_result);
#endif
            result->matriz[i_rows][it_cols_b] = mult_result;
            mult_result = 0;
        }
    }
    return 0;
}

// Retorna o vetor com as médias de cada coluna
float *get_rows_avg(Matrix *target)
{
    // Cria um vetor para armazenar as médias
    float *avg_vet = malloc(sizeof(int) * target->rows);
    int avg = 0;

    for (int i = 0; i < target->rows; i++)
    {
        avg = 0;
        for (int j = 0; j < target->cols; j++)
            avg += target->matriz[i][j];
        avg_vet[i] = (float)avg / target->cols;
    }
    return avg_vet;
}

int find_max_val(float *avg_vet, int size, float *ret_value)
{
    float max_value = 0.0;
    int max_index = 0;

    for (int i = 0; i < size; i++)
    {
        if (avg_vet[i] > max_value)
        {
            max_value = avg_vet[i];
            max_index = i;
        }
    }
    *(ret_value) = max_value;
    return max_index;
}

float upper_matrix_op(Matrix *target, int op)
{
    float ret_val = 0;
    for (int i = 0; i < target->rows / 2; i++)
    {
        for (int j = i + 1; j < (target->cols - (i + 1)); j++)
        {
            ret_val += target->matriz[i][j];
        }
    }
    if (op)
        ret_val /= 30.0;
    return ret_val;
}

/* UTILIDADES */

// Gera uma matriz aleatória de acordo com range e offset
void rand_matrix(Matrix *target, int range)
{
    // Preenche a matriz de tamanho MxN com elementos randômicos
    for (int i = 0; i < target->rows; i++)
    {
        for (int j = 0; j < target->cols; j++)
            target->matriz[i][j] = (rand() % range);
    }
}

// Função para printar a matriz
void matrix_to_string(Matrix target)
{
    int *it_row = NULL;
    printf("{\n");

    for (int row_c = 0; row_c < target.rows; row_c++)
    {
        // Recebe o ponteiro para a respectiva linha
        it_row = target.matriz[row_c];

        for (int cols_c = 0; cols_c < target.cols; cols_c++)
        {
            // Printa o conteúdo da posição de coluna
            printf("[%d]", it_row[cols_c]);
        }
        printf("\n");
    }
    printf("}\n");
}

// Printa a string float
void print_vector(float *vector, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%0.4f, ", vector[i]);
    }
    printf("\n");
}

int main()
{
    Matrix *target_a = malloc(1 * sizeof(Matrix));

    if (alloc_matrix(target_a, 12, 12))
    {
        printf("DEU RUIM ! \n");
        return 0;
    }

    // srand(time(0));
    rand_matrix(target_a, 2);
    matrix_to_string(*target_a);
    printf("Resultado = %f \n", upper_matrix_op(target_a, 0));
}
