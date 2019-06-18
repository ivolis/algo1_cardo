#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPANY_NAME 100
#define MAX_ERRORS 8
#define INPUT_FILE "new_subscribers.bin"
#define OUTPUT_FILE "customers_base.bin"
#define CURRENT_CLIENTS_FILE "current_customers_base.bin"

#define MSG_OK "Ok"
#define MSG_ERROR_NULL_POINTER "Error. Null pointer."
#define MSG_ERROR_INPUT_FILE "Error with the input file."
#define MSG_ERROR_OUTPUT_FILE "Error with the output file."
#define MSG_ERROR_BASE_INVENTORY "Error with the base file."
#define MSG_ERROR_DUPLICATE_KEY "Duplicated ID."
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
	MSG_ERROR_BASE_INVENTORY,
	MSG_ERROR_CLOSING_FILE,
	MSG_ERROR_DUPLICATE_KEY
};

typedef enum{
	OK=0, 
	ERROR_NULL_POINTER=1,
	ERROR_INPUT_FILE=2,
	ERROR_OUTPUT_FILE=3,
	ERROR_BASE_INVENTORY=4,
	ERROR_CLOSING_FILE=5,
	ERROR_DUPLICATE=6
}status_t;

status_t cmp_customers_id(const bill_t* subscribers_struct,const bill_t* current_customers_struct);
status_t register_subscribers(FILE *actual_customers, FILE *fi, FILE *fo);
status_t visor(FILE *fo, FILE *fi);



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

    if((current_customers=fopen(CURRENT_CLIENTS_FILE,"rb"))==NULL) 
    {
    	fprintf(stderr, "%s\n", MSG_ERROR_BASE_INVENTORY);
    	fclose(fi);
    	return ERROR_BASE_INVENTORY;

    }

/* NEW BASE WITH NEW SUBSCRIBERS + OLD SUBSCRIBERS */

    if((fo=fopen(OUTPUT_FILE,"wb"))==NULL)
    {
    	fprintf(stderr, "%s\n", MSG_ERROR_OUTPUT_FILE);   
    	fclose(fi);
    	fclose(current_customers);

      return ERROR_OUTPUT_FILE;
    }

/* REGISTER */

    if(st=register_subscribers(current_customers, fo, fi)!= OK)
    {
      fprintf(stderr, "%s\n", errors[st]);
      remove(OUTPUT_FILE);
      fclose(fi);
      fclose(current_customers);
      if(fclose(fo)==EOF)
      	return ERROR_CLOSING_FILE;
      
      return st;
    }

/* CLOSING STREAMS */

    fclose(current_customers);
    fclose(fi);
    if(fclose(fo)==EOF)
    	return ERROR_CLOSING_FILE;

    return OK;

}


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  FUNCIONES  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */


/* COMPARISON */
size_t cmp_customers_id(const bill_t* subscribers_struct,const bill_t* current_customers_struct)
{
	return (subscribers_struct->id - current_customers_struct->id);
}


/* REGISTER */
status_t register_subscribers(FILE *current_customers, FILE *fi, FILE *fo)
{

	if(current_customers==NULL || fi==NULL || fo==NULL)
		return ERROR_NULL_POINTER;

	bill_t subscribers_struct;
	bill_t current_customers_struct;
	size_t read_current_customers, read_subscribers;

  read_current_customers=fread(&current_customers_struct, sizeof(bill_t), 1, current_customers);
  read_subscribers=fread(&subscribers_struct, sizeof(bill_t), 1,fi);


	while(read_subscribers && read_current_customers)
	{
		if( cmp_customers_id(&subscribers_struct, &current_customers_struct) == 0)
			return ERROR_DUPLICATE;
	    
	    if (cmp_customers_id(&subscribers_struct, &current_customers_struct) < 0) /* NEW SUBSCRIBER */
	    {
	    		fwrite(&subscribers_struct, sizeof(bill_t),1, fo);
	    		read_subscribers=fread(&subscribers_struct, sizeof(bill_t), 1,fi);
	    }
	        
	    else
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
	while(read_subscribers)
	{
		fwrite(&subscribers_struct,sizeof(bill_t),1,fo);
		read_subscribers=fread(&subscribers_struct,sizeof(bill_t),1,fi);
	}


	  return OK;
}