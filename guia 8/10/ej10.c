#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum{
  OK,
  ERROR_MEMORY,
  ERROR_NULL_POINTER,
  ERROR_MATRIX,
  ERROR
}status_t;


status_t create_matrix(double ***, size_t);
status_t destroy_matrix(double ***, size_t);


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$> MAIN <$$$$$$$$$$$$$$$$$$$$$$$$$$

int main(void){

  double **matrix;
  size_t len, i,j ;
  status_t st;

  len=10;

  if( (st=create_matrix(&matrix, len)) != OK )
  {
      destroy_matrix(&matrix, len);
      return ERROR;
  }

// imprimo matrix

  for(i=0; i<len ;i++)
      {
        for(j=0; j<len ;j++)
        {
          printf("(%.1lf) ", matrix[i][j] );
        }
        putchar('\n');
      }

// imprimo error

      switch(st){
        case(OK):
        fprintf(stdin,"OK\n");
        break;

        case(ERROR_MEMORY):
        fprintf(stderr,"pelotudo1\n");
        break;

        case(ERROR_NULL_POINTER):
        fprintf(stderr,"pelotudo2\n");
        break;

        case(ERROR_MATRIX):
        fprintf(stderr,"pelotudo3\n");
        break;

        default:
        fprintf(stderr,"cardo\n");
        break;
      }

  return 0;
}

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$>FUNCIONES<$$$$$$$$$$$$$$

status_t create_matrix(double ***pm, size_t dim)
{

    size_t i,j;

  if(pm==NULL)
    return ERROR_NULL_POINTER;

    if ( (*pm=(double **) malloc (dim * sizeof(double *))) == NULL )
      return ERROR_MEMORY;

    for (i=0 ; i<dim ; i++)
    {
        if( ((*pm)[i]=(double*) malloc(dim * sizeof(double))) == NULL )
        {
          destroy_matrix(pm,i);
          return ERROR_MATRIX;
        }
    }

  for (i=0; i<dim; i++){
    for(j=0; j<dim; j++){
        (*pm)[i][j]=(i==j)?1:0;
    }
  }
  return OK;
}

status_t destroy_matrix(double ***pm, size_t dim)
{

    size_t i;

  if(pm==NULL)
    return ERROR_NULL_POINTER;

  for (i=0; i<dim ; i++){
    free( (*pm)[i] );
    (*pm)[i]=NULL;
  }

  free(*pm);
  *pm=NULL;
  return OK;
}
