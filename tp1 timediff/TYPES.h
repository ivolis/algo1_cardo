#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lang.h"

typedef enum{
	FORMAT_DATE_DDMMYYYYHHMMSS=0,
	FORMAT_DATE_DDMMYYYY=1,
	FORMAT_DATE_YYYYMMDD=2
}format_date_t;

typedef enum{
	UNIT_SECONDS=0,
	UNIT_MINUTES=1,
	UNIT_HOUR=2,
	UNIT_DAYS=3
}unit_t;

typedef enum{
	OK=0,
	ERROR_NULL_POINTER=1,
	ERROR_PROGRAM_INVOCATION=2,
	ERROR_DATE_FORMAT=3,
	ERROR_DATE_INPUT=4,
	ERROR_TIME_CONVERSION=5,
	ERROR_OUTPUT_UNIT=6
} status_t;

typedef struct{
    format_date_t format_date_1;
    time_t date_1;
    format_date_t format_date_2;
    time_t date_2;
    unit_t output_unit;
} setup_t;

#endif
