#include <stdio.h>
#include <stdlib.h>


typedef struct
	{
  char company_name[50];
  size_t id;
  double amount;
	}bill_t;

int main(int argc, char const *argv[])
{

FILE* fi;
size_t i;

char ivan[]="Ivan";
char martin[]="Martin";

bill_t ivann;
bill_t martinn;

for(i=0; i<8 ; i++){

ivann.company_name[i]=ivan[i];

martinn.company_name[i]=martin[i];
}



ivann.id=35;
ivann.amount=234.2;
martinn.id=101;
martinn.amount=234.2;

fi=fopen("new_subscribers.bin", "wb");

fwrite(&ivann, sizeof(bill_t),1, fi);
fwrite(&martinn, sizeof(bill_t),1, fi);



	return 0;
}