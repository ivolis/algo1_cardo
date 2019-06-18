#include <stdio.h>
#include <stdlib.h>

#define MAX_COMPANY_NAME 100
#define INPUT_FILE_BINARY "customers_base.bin"
#define OUTPUT_FILE_TEXT "customers_base.csv"


typedef struct
{
  char company_name[MAX_COMPANY_NAME+1];
  size_t id;
  double amount;
}bill_t;

typedef enum{
  OK=0,
  ERROR_CORRUPT_FILE=1,
  ERROR_CLOSING_FILE=2
}status_t;


int main(void)
{
	FILE* fo;
	FILE* fi;
  bill_t bill;
  char delimiter=',';

    if((fi=fopen(INPUT_FILE_BINARY,"rb"))==NULL)
      return CORRUPT_FILE;

    if((fo=fopen(OUTPUT_FILE_TEXT,"wt"))==NULL)
      return CORRUPT_FILE;


    while(fread(&bill, sizeof(bill_t), 1, fi))
    {
      fprintf(fo, "%s%c%zu%c%f\n", bill.company_name, delimiter, bill.id, delimiter, bill.amount);
    }

    fclose(fi);
    if(fclose(fo)==EOF)
      return ERROR_CLOSING_FILE;

	return 0;
}