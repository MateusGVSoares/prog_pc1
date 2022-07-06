#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Obtem o menor número
int get_lnumber(int *array, int size, int *ret_pointer)
{
    int i = 0,
        ret_pos = 0,
        ret_value = array[size - 1];

    // Varre o vetor procurando o menor valor
    for (; i < size - 1; i++)
    {
        if (array[i] < ret_value)
        {
            ret_value = array[i];
            ret_pos = i;
        }
    }

    // Retorna os valores
    *ret_pointer = ret_value;
    return ret_pos;
}

// Obtêm o maior número
int get_gnumber(int *array, int size)
{
    int ret_number = array[size - 1];
    for (int i = 0; i < size - 1; i++)
    {
        if (array[i] > ret_number)
            ret_number = array[i];
    }
    return ret_number;
}

int str_size(char *arr_s)
{
    int i = 0;
    for (; arr_s[i] != '\0'; i++)
        ;
    return i;
}

void to_lower(char *str)
{
    // Varre todo o vetor até o terminador de string
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] >= 0x41 && str[i] <= 0x5A)
            // Incrementa o valor para casar com o minusculo em ASCII
            str[i] += 0x20;
}

// Questão 4, pega os caracteres com mais ocorrência da string
void get_max_c(char *array)
{
    int *vet_letras = malloc(sizeof(int) * 26);
    memset(vet_letras, 0, 26);
    int max_val = 0;
    // Transforma a string em apenas letras minúsculas
    to_lower(array);
    // printf("%s \n", array);

    // Percorre todo o vetor contando as letras
    for (int i = 0; array[i] != '\0'; i++)
    {
        if (array[i] >= 0x61 && array[i] <= 0x7A)
            vet_letras[(int)(array[i]) - 0x61]++;
    }
    // print_vector("Vet_Letras", vet_letras, 26);

    // Pega o maior numero de ocorrências e printa as letras com essa ocorrência
    max_val = get_gnumber(vet_letras, 26);
    //  printf("Maior ocorrência : %d \n", max_val);
    for (int i = 0; i < 26; i++)
    {
        if (vet_letras[i] == max_val)
            printf("%c", (0x61 + i));
    }
    free(vet_letras);
}

char *get_code(char *target_str)
{
    // Ola Casa
    int vet_pos = 0;
    for (int i = 0; target_str[i] != '\0'; vet_pos++, i++)
    {
        // Get next letter
        while (target_str[i] == ' ')
            i++;

        // printf("Fct  : %c | Pos : %d | Vet_Pos : %d \n", target_str[i], i, vet_pos);
        target_str[vet_pos] = target_str[i];

        // Get next space
        while (target_str[i] != ' ' && target_str[i] != '\0')
            i++;
    }
    printf("%d \n", vet_pos);
    target_str[vet_pos] = '\0';
    return target_str;
}

// Função que obtêm o número de aliterações em uma sequência de palavras
int get_allit(char *target_str)
{
    // Numero para retornar a quantidade de aliterações
    int ret_allit = 0;

    // Cria um vetor para incrementar as respectivas letras
    int *vet_letras = malloc(sizeof(int) * 26);
    memset(vet_letras, 0, 26);

    // Transforma a string em caracteres minúsculos
    to_lower(target_str);

    for (int i = 0; target_str[i] != '\0'; i++)
    {
        if (target_str[i + 1] != ' ')
            vet_letras[target_str[i] - 0x61]++;
        while (target_str[i] != ' ' && target_str[i] != '\0')
            i++;
    }

    for (int i = 0; i < 26; i++)
        if (vet_letras[i] > 1)
        {
            ret_allit++;
        }

    // Libera a memória e retorna o valor
    free(vet_letras);
    return ret_allit;
}

void fill_vector(int *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = rand() % 30;
}

void print_vector(char *name, int *array, int size)
{
    printf("%s[%d] = {", name, size);

    for (int i = 0; i < size; i++)
    {
        printf("%d,", array[i]);
    }
    printf("};\n");
}

void print_ptr(char *name, int **array, int size)
{
    printf("%s[%d] = {", name, size);

    for (int i = 0; i < size; i++)
    {
        printf("%d,", *(array[i]));
    }
    printf("};\n");
}

int **create_ptr(int *array, int size)
{
    int **res_array = malloc(sizeof(int *) * size);
    int *aux_pointer = NULL;
    int cont = 1;

    // Copia os enderecos do array inicial para o vetor auxiliar
    for (int i = 0; i < size; i++)
        res_array[i] = &array[i];

    // Sort no vetor de ponteiros
    while (cont)
    {
        cont = 0;
        for (int pos = 0; pos < size - 1; pos++)
        {
            if (*(res_array[pos]) > *(res_array[pos + 1]))
            {
                aux_pointer = res_array[pos];
                res_array[pos] = res_array[pos + 1];
                res_array[pos + 1] = aux_pointer;
                cont++;
            }
        }
    }

    return res_array;
}

int get_number(int *array, int a_size, int n_pos)
{
    int ret_number = 0, // Número para retornar
        aux_lower = 0,  // Variável que contêm o menor valor
        atual_cont = 0; // Varíavel de contagem dos ciclos

    // Obtêm o maior valor e salva em ret_number
    ret_number = get_gnumber(array, a_size);
    get_lnumber(array, a_size, &aux_lower);
    printf("Maior número = [%d] | Menor número = [%d] \n", ret_number, aux_lower);

    // Repete a varredura do vetor enquanto nao obter o n maior elemento ou percorer a_size elementos
    for (int atual_pos = 1, atual_lower = aux_lower; (atual_pos < n_pos) && (atual_cont < a_size); atual_cont++)
    {
        atual_lower = aux_lower;
        // Varre o vetor
        for (int i = 0; i < a_size; i++)
        {
            // Procura pelo n maior elemento
            if (array[i] > atual_lower && array[i] < ret_number)
            {
                atual_lower = array[i];
            }
        }

        if (atual_lower >= aux_lower) //  Verifica se o número é maior que o menor
        {
            // ret_number vira agora o n-1 maior
            ret_number = atual_lower;
            atual_pos++;
            // printf("%d_maior = [%d] | N+1 maior = [%d] \n", atual_pos, aux_lower, ret_number);
        }
    }
    printf("%d \n", atual_cont);
    if (atual_cont >= a_size)
        return -1;
    return ret_number;
}

int check_repeat(int *array, int size, int value, int ig_pos)
{
    for (int i = 0; i < size; i++)
    {
        if (i != ig_pos && array[i] == value)
            return 1;
    }
    return 0;
}

void gen_norepeat(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        while (check_repeat(array, size, array[i], i))
            array[i] = rand() % 50;
    }
}

void bubble_sort(int *array, int size)
{
    int operations = 1;
    while (operations)
    {
        operations = 0;
        for (int i = 0; i < size - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                operations = array[i];
                array[i] = array[i + 1];
                array[i + 1] = operations;
            }
        }
    }
}

int get_number_o(int *array, int size, int number)
{
    int occur = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] == number)
            occur += 1;
    }
    return occur;
}

void get_vet_o(int *array, int size)
{
    // Aloca um vetor auxiliar dinamicamente
    int *aux_vet = malloc(sizeof(int) * size);
    memset(aux_vet, 0, size);
    int aux_pos = 0;
    // Varre o vetor em busca de elementos nao repetidos
    for (int i = 0; i < size; i++)
    {
        if (!check_repeat(aux_vet, size, array[i], -1))
        {
            aux_vet[aux_pos] = array[i];
            aux_pos++;
        }
    }
    print_vector("Aux", aux_vet, aux_pos);

    bubble_sort(aux_vet, aux_pos);

    print_vector("Aux", aux_vet, aux_pos);
    for (int i = 0; i < aux_pos; i++)
        printf("%d aparece %d vez(es)\n",
               aux_vet[i],
               get_number_o(array, size, aux_vet[i]));
    free(aux_vet);
}

void str_cpy(char *dest, char *src)
{
    int i = 0;
    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
}

void remove_occur(char *str, char ch)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        while (str[i] == ch)
            str_cpy(&str[i], &str[i + 1]);
    }
}

int str_srch(char *str, char ch)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == ch)
            return i;
    return 0;
}

void remove_all_rep(char *str)
{
    int rep_pos = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        // Verifica se o caractere é diferente de espaço
        if (str[i] != ' ')
        {
            // Verifica se há alguma repetição no vetor
            while ((rep_pos = str_srch(&str[i + 1], str[i])))
            {
                rep_pos += i + 1;
                printf("%c | %d | %d \n", str[i], i, rep_pos);
                remove_occur(&str[rep_pos], str[i]);
            }
        }
    }
}

int str_n_comp(char *dest, char *src, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (dest[i] != src[i])
            return 0;
    }
    return 1;
}

int check_palin(char *dest)
{
    int j = 0;

    for( ; dest[j+1] != '\0'; j++);

    for(int i = 0; dest[i] != '\0';i++, j--)
    {
        if(dest[i] != dest[j])
            return 0;
    }

    return 1;
}


int main()
{
    char *main_str = malloc(sizeof(char) * 300);
    printf("Digite: ");
    gets(main_str);    

    int result = check_palin(main_str);

    printf("Resultado = %d \n", result);

    free(main_str);
    return 0;
}
