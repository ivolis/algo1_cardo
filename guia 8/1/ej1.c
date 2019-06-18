// EJ 1 GUIA 8 (MEMORIA DINAMICA)


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MSJ_OK "OK"
#define MSJ_NULL_POINTER "Null pointer"
#define MSJ_STRING_EMPTY "Empty string"

typedef enum{
  OK,
  ERROR_NULL_POINTER,
} status_t;


//$$$$$$$$$$$$$$$$$$$$$$$$$$ PROTOTIPOS
status_t clone_string(char*,char**);


//$$$$$$$$$$$$$$$$$$$$$$$$$$ INVOCACIÓN
  int main(void)
{
  char* string="hola";
  char* clonedstring;

  status_t st;

  if(string[0]=='\0')
  {
    fprintf(stderr, "%s\n",MSJ_STRING_EMPTY );
    return 1;
  }

  st=clone_string(string,&clonedstring);
  printf("%s      %s\n",string,clonedstring);

  switch (st) {
    case(OK):
    fprintf(stdin, "%s\n",MSJ_OK );
    break;

    case(ERROR_NULL_POINTER):
    fprintf(stderr, "%s\n",MSJ_NULL_POINTER );
  }
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

status_t clone_string(char * string, char **clonedstring)
{
  size_t i;
  if(string==NULL || clonedstring==NULL)
    return ERROR_NULL_POINTER;

  if( ( *clonedstring = malloc(strlen((string)+1)*sizeof(char)) ) == NULL )
    return ERROR_NULL_POINTER;

  for(i=0;(*clonedstring)[i]=string[i];i++);

  return OK;

}
