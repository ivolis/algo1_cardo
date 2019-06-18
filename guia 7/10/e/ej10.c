#include <stdio.h>
#include <stdlib.h>

#define MASK_BAND 0x40

typedef unsigned char uchar;
typedef enum{BAND_AM, BAND_FM}band_t;
typedef enum{OK, ERROR_NULL_POINTER}status_t;

status_t set_band(band_t, uchar*);

int main(void){

band_t band= BAND_FM;         // 1 == AM / 0 == FM
uchar control_register= 0x00;

set_band(band, &control_register);


return 0;

}


status_t set_band(band_t band, uchar*reg)
{
  if(reg == NULL)
      return ERROR_NULL_POINTER;

    if(band==BAND_AM){
      *reg = *reg | MASK_BAND;
      return OK;
    }

    *reg = *reg&(~MASK_BAND);
    return OK;
}
