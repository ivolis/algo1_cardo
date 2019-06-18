#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPANY_NAME 100
#define MAX_ERRORS 
#define INPUT_FILE "unsubscribers.bin"
#define OUTPUT_FILE "customers_base.bin"
#define CURRENT_CUSTOMERS_FILE "current_customers_base.bin"

#define MSG_OK "Ok"
#define MSG_ERROR_NULL_POINTER "Error. Null pointer."
#define MSG_ERROR_INPUT_FILE "Error with the input file."
#define MSG_ERROR_OUTPUT_FILE "Error with the output file."
#define MSG_ERROR_BASE_FILE "Error with base file."
#define MSG_ERROR_CLOSING_FILE "Error closing the file."


typedef struct
{
  char company_name[MAX_COMPANY_NAME+1];
  size_t id;
  double amount;
}bill_t;

char* errors[MAX_ERRORS]=
{
	MSG_OK,
	MSG_ERROR_NULL_POINTER,
	MSG_ERROR_INPUT_FILE,
	MSG_ERROR_OUTPUT_FILE,
	MSG_ERROR_BASE_FILE,
	MSG_ERROR_CLOSING_FILE
};

typedef enum{
	OK=0, 
	ERROR_NULL_POINTER=1,
	ERROR_INPUT_FILE=2,
	ERROR_OUTPUT_FILE=3,
	ERROR_BASE_FILE=4,
	ERROR_CLOSING_FILE=5
	UNSUBSCRIBER=6;
}status_t;

status_t cmp_customers_id(const bill_t* unsubscribers_struct,const bill_t* current_customers_struct);
status_t unsubscribe(FILE *actual_customers, FILE *fi, FILE *fo);



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ INVOCACION $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

int main(void)
{
    FILE *fi,*fo,*current_customers;
    status_t st;

/* NEW SUBSCRIBERS */

    if((fi=fopen(INPUT_FILE,"rb"))==NULL)
    {
      fprintf(stderr, "%s\n", MSG_ERROR_INPUT_FILE);
      return ERROR_INPUT_FILE;
    }

/* "OLD" SUBSCRIBERS */

    if((current_customers=fopen(CURRENT_CUSTOMERS_FILE,"rb"))==NULL) 
    {
    	fprintf(stderr, "%s\n", MSG_ERROR_BASE_FILE);
    	fclose(fi);
    	return ERROR_BASE_FILE;
    }

/* NEW BASE WITH NEW SUBSCRIBERS + OLD SUBSCRIBERS */

    if((fo=fopen(OUTPUT_FILE,"wb"))==NULL)
    {
    	fprintf(stderr, "%s\n", MSG_ERROR_OUTPUT_FILE);
    	fclose(fi);
    	fclose(current_customers);
		return ERROR_OUTPUT_FILE;
    }


/* SUBSCRIBING */

    if(st=unsubscribe(current_customers, fo, fi)!= OK)
    {
      fprintf(stderr, "%s\n", errors[st]);
      remove(OUTPUT_FILE);
      fclose(fi)
      fclose(current_customers);
      if(fclose(fo)==EOF)
      	return ERROR_CLOSING_FILE;

      return st;
    }

/* CLOSING FILES */

    fclose(current_customers);
    fclose(fi);
    if(fclose(fo)==EOF)
    	return ERROR_CLOSING_FILE;

    return OK;

}


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  FUNCIONES  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */


/* COMPARISON */
size_t cmp_customers_id(const bill_t* unsubscribers_struct,const bill_t* current_customers_struct)
{
	return (unsubscribers_struct->id - current_customers_struct->id);
}


/* SUBSCRIBE */
status_t unsubscribe(FILE *current_customers, FILE *fi, FILE *fo)
{

	if(current_customers==NULL || fi==NULL || fo==NULL)
		return ERROR_NULL_POINTER;

	bill_t unsubscribers_struct;
	bill_t current_customers_struct;
	size_t read_current_customers, read_unsubscribers;

  read_current_customers=fread(&current_customers_struct, sizeof(bill_t), 1, current_customers);
  read_unsubscribers=fread(&unsubscribers_struct, sizeof(bill_t), 1,fi);


	while(read_unsubscribers && read_current_customers)
	{
		if( cmp_customers_id(&unsubscribers_struct, &current_customers_struct) == 0)
		{
			read_current_customers=fread(&current_customers_struct, sizeof(bill_t), 1, current_customers);
			return UNSUBSCRIBER;
		}
	    
	    if (cmp_customers_id(&unsubscribers_struct, &current_customers_struct) > 0)
	    {
			fwrite(&current_customers_struct, sizeof(bill_t), 1, fo);	/* OLD SUBSCRIBER */
	  		read_current_customers=fread(&current_customers_struct, sizeof(bill_t), 1, current_customers);
	    }

	}

	while(read_current_customers)
	{
		fwrite(&current_customers_struct,sizeof(bill_t),1,fo);
		read_current_customers=fread(&current_customers_struct,sizeof(bill_t),1,current_customers);
	}
	while(read_unsubscribers)
	{
		fwrite(&unsubscribers_struct,sizeof(bill_t),1,fo);
		read_unsubscribers=fread(&unsubscribers_struct,sizeof(bill_t),1,fi);
	}


	  return OK;
}