#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char * strsrch(char * pointer, char ch)
{
  char * ret_pointer = NULL;
  for(int i = 0; (pointer[i] != '\0'); i++)
  { 
    if(pointer[i] == ch)
      ret_pointer= &pointer[i]; 
  }
    return ret_pointer;
}

char * f_strsrch(char * pointer, char ch)
{
  char * ret_pointer = NULL;
  for(int i = 0; (pointer[i] != '\0'); i++)
  { 
    if(pointer[i] == ch)
    {
      ret_pointer= &pointer[i];
      break;
    }
  }
    return ret_pointer;
}

int ** create_ptr(int * array,int size)
{
  int ** res_array = malloc(sizeof(int *) * size);
  int * aux_pointer = NULL;
  int  cont = 1;

  // Copia os enderecos do array inicial para o vetor auxiliar
  for(int i = 0; i < size; i++)
    res_array[i] = &array[i];

  // Sort no vetor de ponteiros
  while(cont)
  {
    cont = 0;
    for(int pos = 0; pos < size - 1; pos++)
    {
      if(*(res_array[pos]) > *(res_array[pos + 1]))
      {
        aux_pointer = res_array[pos];
        res_array[pos] = res_array[pos + 1];
        res_array[pos+1] = aux_pointer; 
        cont++;
      }
    }
  }

  return res_array;
}

void fill_vector(int * array,int size)
{
  for(int i = 0; i < size; i++)
    array[i] = rand()%30;
}

void print_vector(char * name,int * array, int size)
{
  printf("%s[%d] = {",name,size);

  for(int i = 0; i < size; i++)
  {
    printf("%d,",array[i]);
  }
  printf("};\n");
}

void print_ptr(char * name,int ** array,int size)
{ 
  printf("%s[%d] = {",name,size);

  for(int i = 0; i < size; i++)
  {
    printf("%d,",*(array[i]));
  }
  printf("};\n");
}

#define _SIZE 10

int main()
{
  srand(time(0));
  int * input_vec = malloc(sizeof(int) * _SIZE);
  int ** ret_vet = NULL;
  
  fill_vector(input_vec,_SIZE);
  print_vector("INPUT",input_vec,_SIZE);  
  ret_vet = create_ptr(input_vec, _SIZE);
  print_ptr("RESULT",ret_vet,_SIZE);
  return 0;
}
