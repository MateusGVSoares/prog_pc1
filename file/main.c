#include <stdio.h>
#include <stdlib.h>



int str_len(char * dest)
{
  int i =0;
  for(; dest[i] != '\0'; i++);
  return i;
}

int str_ncmp(char * dest, char * src, int _n)
{
  int i = 0;
  for(; i < _n ; i++)
    if(dest[i] != src[i])
      return 0;
  return i;
}

void str_cpy(char * dest, char * src)
{
  int i = 0;
  for(; src[i] != '\0'; i++)
    dest[i] = src[i];
  dest[i] = '\0';
}

void remove_w(char * dest,char * src)
{

  int dest_len = str_len(dest), src_len = str_len(src);

  for(int i = 0; dest[i] != '\0' && (i + src_len <= dest_len); i++)
  {
    // Verifica se a palavra está nessa posicao
    if(str_ncmp(&dest[i],src,src_len))
        // remove essa ocorrência
        str_cpy(&dest[i],&dest[i +src_len]);
  }
}

int main()
{
  FILE * file = NULL;
  char * text_buffer = malloc(sizeof(char)* 300);
  char * target_word = malloc(sizeof(char) * 300);
  char * out_buffer = NULL;
  char file_size = 0;
  
  
  file = fopen("text_1.txt","w+");
  printf("File pointer : %p \n",file);
  
  printf("Text to write : ");
  fgets(text_buffer,300,stdin);
  for(int i = 0; text_buffer[i] != '\0'; i++)
  {
    if(text_buffer[i+1] == '\0')
      text_buffer[i] = text_buffer[i+1];
  }
  printf("Word to remove : ");
  gets(target_word);
  
  fwrite(text_buffer,sizeof(char),str_len(text_buffer),file);
  file_size = ftell(file);
  printf("Tamanho do arquivo : %d \n",file_size);
  
  out_buffer = malloc(sizeof(char) * file_size + 1);
  
  fseek(file,SEEK_SET,0);
  // Reads the file
  fread(out_buffer,sizeof(char),file_size,file);
  out_buffer[file_size] = '\0';
  
  printf("Result : %s \n",out_buffer);
  
  remove_w(out_buffer,target_word);
  printf("Sem palavra : %s \n",out_buffer);
  printf(" Str_len : %d \n",str_len(out_buffer));
  fseek(file,SEEK_SET,0);
  printf("%ld \n",ftell(file));
  printf("Bytes Written : %ld",fwrite(out_buffer,sizeof(char),file_size,file));
  
  fclose(file);

  return 0;
}
