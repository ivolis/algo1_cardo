/*EJERCICIO 4 GUIA 8
FRANCISCO PERCZYK
PADRON: 99631
email: fperczyk@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_OK "OK"
#define MSG_NULL_POINTER "Null pointer"
#define MSG_ERROR_MEMORY "Not enough memory"

typedef enum{
  OK,
  ERROR_NULL_POINTER,
  ERROR_MEMORY
}status_t;
           /*PROTOTIPOS*/
status_t full_trim(const char *,char **);
/*************************************/

int main(int argc, char const *argv[])
{
  char * string="    esta cadena tiene espacios   ";
  char * clean_string;
  status_t st;

  st=full_trim(string,&clean_string);

  printf("%s\n",clean_string);

  switch (st) {

    case (OK):
    printf("%s\n",MSG_OK);
    break;

    case(ERROR_NULL_POINTER):
    printf("%s\n",MSG_NULL_POINTER);
    break;

    case(ERROR_MEMORY):
    printf("%s\n",MSG_ERROR_MEMORY);
    break;
  }
  return 0;
}

status_t full_trim(const char * string,char ** clean_string)
{
  size_t i=0,j=strlen(string),len_of_string_clean,k;

  if(string==NULL || clean_string==NULL)
  {
    return ERROR_NULL_POINTER;
  }
  /*Cuento la cantidad de espacios a la izquierda de la cadena original*/
  while(*(string+i)==' ') i++;
  /*Cuento la cantidad de espacios a la derecha de la cadena original*/
  while(*(string+j)==' ') j--;
  /*Pido memoria para la cadena limpia*/
  if((*clean_string=malloc((strlen((string)+1))*sizeof(char)))==NULL)
     return ERROR_MEMORY;

  len_of_string_clean=strlen(string)-i-j+1;

  /*Armo la cadena limpia*/
  for(k=0;i<j;k++,i++)
  {
    (*clean_string)[k]=string[i];
  }
  return OK;
}
