#ifndef DATES__H
#define DATES__H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "TYPES.h"

#define OUTPUT_PRECISION 2
#define MAX_LEN_AUX 5

status_t print_diff_time(double diff_date,FILE * fo);
status_t get_diff_time(const time_t date_1,const time_t date_2,double * diff_date,unit_t unit);
status_t initialize_tm( struct tm* date_1, struct tm* date_2);
status_t parse_string_date(format_date_t * format,char * str_date, time_t * date);
status_t convert_string_to_date_ddmmyyyyhhmmss(const char * str_date,time_t * date);
status_t convert_string_to_date_ddmmyyyy(const char * str_date,time_t * date);
status_t convert_string_to_date_yyyymmdd(const char * str_date,time_t * date);
status_t convert_tm_to_time_t(struct tm * date,time_t * time);
status_t change_unit_time(double * diff_date,unit_t unit,time_t aux_date);

#endif
