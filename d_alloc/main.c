#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person
{
  char * nome;
  char * birth;
  char * cpf;
} person_t;

int element_check(int * vec,int size,int element)
{
  if(size)
  {
    for(int i = 0; i <size;i++)
    {
      if(vec[i] == element)
          return 1;
    }
  }
  return 0;
}

int get_intersection(int * array_1, int size_1, int * array_2, int size_2,int ** res_array)
{
  int res_size = 0;
  *res_array = malloc(sizeof(int) * 1);
  
  for(int i = 0; i < size_1; i++)
  {
    for(int j =0; j< size_2; j++)
    {
      if((array_1[i] == array_2[j]) && !(element_check(*res_array,res_size,array_2[j])))
      {
          printf("Passou aqui \n");
          
          // Incrementa o tamanho do vetor e realoca dentro da heap
          res_size++;
          *res_array = realloc(*res_array,sizeof(int)*res_size);
          
          // Atribui ao vetor resposta na posicão res_size - 1 o elemento e incrementa o contador do vetor 1
          (*res_array)[res_size-1] = array_1[i];
          break;
      }
        
    }
  }

  if(!res_size)
  {
    free(*res_array);
    *res_array = NULL;
  }
  // Retorna o tamanho do vetor 
  return res_size;
}

void fill_vector(int * array,int size)
{
  for(int i = 0; i < size; i++)
    array[i] = rand()%30;
}

void print_vector(char * name,int * array, int size)
{
  printf("%s[%d] = ",name,size);

  for(int i = 0; i < size; i++)
  {
    printf("%d ",array[i]);
  }
  printf(";\n");
}

void print_ptr(person_t * pessoa)
{ 
  printf("\nNOME : %s\n",pessoa->nome);
  printf("NASCIMENTO: %s\n",pessoa->birth);
  printf("CPF : %s\n",pessoa->cpf);
}

void fill_person(person_t * d_pessoa)
{
  d_pessoa->nome = malloc(sizeof(char) * 300);
  d_pessoa->cpf = malloc(sizeof(char) * 15);
  d_pessoa->birth = malloc(sizeof(char)*9);

  printf("Digite o nome da pessoa: ");
  fgets(d_pessoa->nome,300,stdin);
  
  // 01/02/03
  printf("Digite a data de nascimento da pessoa: ");
  fgets(d_pessoa->birth,12,stdin);
  
  printf("Digite o CPF da pessoa: ");
  fgets(d_pessoa->cpf,15,stdin);
}

void free_person(person_t * pessoa)
{
  if(pessoa != NULL)
  {
    if(pessoa->nome != NULL)
      free(pessoa->nome);
    if(pessoa->cpf != NULL)
      free(pessoa->cpf);
    if(pessoa->birth != NULL)
      free(pessoa->birth);
  }
}
int main()
{
  
  person_t * d_pessoa = malloc(sizeof(person_t)*1);  
  
  fill_person(d_pessoa);
  print_ptr(d_pessoa);
    
  free_person(d_pessoa);
  return 0;
}
