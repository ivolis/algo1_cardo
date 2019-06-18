#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSJ_FDIV "The FDIV is"
#define FDIV_MASK_BITS 0x3E
#define FDIV_OFFSET_SYNTHESIZER 1

typedef unsigned char uchar;  // tipo de dato

typedef enum{
	FDIV_1=1,
	FDIV_2=2,
	FDIV_3=3,
	FDIV_4=4,
	FDIV_5=5,
	FDIV_6=6,
	FDIV_7=7,
	FDIV_8=8,
	FDIV_9=9,
	FDIV_10=10,
	FDIV_11=11,
	FDIV_12=12,
	FDIV_13=13,
	FDIV_14=14,
	FDIV_15=15,
	FDIV_16=16,
	FDIV_17=17,
	FDIV_18=18,
	FDIV_19=19,
	FDIV_20=20,
	FDIV_21=21,
	FDIV_22=22,
	FDIV_23=23,
	FDIV_24=24,
	FDIV_25=25,
	FDIV_26=26,
	FDIV_27=27,
	FDIV_28=28,
	FDIV_29=29,
	FDIV_30=30,
	FDIV_31=31,
	FDIV_32=32
}FDIVnumber_t;

FDIVnumber_t get_synthesizer_divider(uchar); // prototipo

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

int main(void){

uchar bit_register=0xFF; // 0 0 0 0 0 son los bites EDCBA
uchar FDIV;	// 

FDIV = get_synthesizer_divider(bit_register);

printf("%s %u\n", MSJ_FDIV, FDIV);

    return 0;
}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

FDIVnumber_t get_synthesizer_divider(uchar reg)
{

return (((reg&FDIV_MASK_BITS)>>FDIV_OFFSET_SYNTHESIZER)+1);

}