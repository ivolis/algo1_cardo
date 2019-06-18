#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dates.h"


status_t get_diff_time(const time_t date_1,const time_t date_2,double * diff_date,unit_t unit)
{
    time_t aux_date;
    status_t st;

    if(diff_date==NULL)
        return ERROR_NULL_POINTER;

    aux_date=difftime(date_1,date_2);

    if((st=change_unit_time(diff_date,unit,aux_date))!=OK)
      return st;

    return OK;
}

status_t change_unit_time(double * diff_date,unit_t unit,time_t aux_date)
{
  if(diff_date==NULL)
    return ERROR_NULL_POINTER;

  switch(unit)
  {
    case UNIT_SECONDS:
      *diff_date=(double)aux_date;
      break;

    case UNIT_MINUTES:
      *diff_date=(double)aux_date/60;
      break;

    case UNIT_HOUR:
      *diff_date=(double)aux_date/3600;
      break;

    case UNIT_DAYS:
      *diff_date=(double)aux_date/86400;
      break;
  }

  return OK;
  
}

status_t print_diff_time(double diff_date,FILE * fo)
{
  if(fo==NULL)
    return ERROR_NULL_POINTER;

  fprintf(fo, "%.*f\n",OUTPUT_PRECISION,diff_date);
  return OK;
}

status_t parse_string_date(format_date_t * format,char * str_date, time_t * date)
{
	status_t st;

	if(format==NULL || str_date==NULL || date==NULL)
		return ERROR_NULL_POINTER;

	switch(*format)
	{
			case FORMAT_DATE_DDMMYYYYHHMMSS:
					if((st=convert_string_to_date_ddmmyyyyhhmmss(str_date,date))!=OK)
						return st;

					break;

			case FORMAT_DATE_DDMMYYYY:
					if((st=convert_string_to_date_ddmmyyyy(str_date,date))!=OK)
						return st;

					break;

			case FORMAT_DATE_YYYYMMDD:
					if((st=convert_string_to_date_yyyymmdd(str_date,date))!=OK)
						return st;

					break;
	}

	return OK;
}


status_t convert_string_to_date_ddmmyyyyhhmmss(const char * str_date,time_t * date)
{
	char  aux[MAX_LEN_AUX];
	char * tmp;
	struct tm date_tm;
	status_t st;

	if(str_date==NULL)
		return ERROR_NULL_POINTER;


	/*$$$$$ MON $$$$$*/
	memcpy(aux,str_date+2,2);
	aux[2]='\0';
	date_tm.tm_mon=(int)strtoul(aux,&tmp,10)-1;

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;

	/*$$$$$ YEAR $$$$$*/
	memcpy(aux,str_date+4,4);
	aux[4]='\0';
	date_tm.tm_year=(int)strtoul(aux,&tmp,10)-1900;

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;

	/*$$$$$ HOUR $$$$$*/
	memcpy(aux,str_date+8,2);
	aux[2]='\0';
	date_tm.tm_hour=(int)strtoul(aux,&tmp,10);

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;

	/*$$$$$ MIN $$$$$*/
	memcpy(aux,str_date+10,2);
	aux[2]='\0';
	date_tm.tm_min=(int)strtoul(aux,&tmp,10);

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;

	/*$$$$$ SEC $$$$$*/
	memcpy(aux,str_date+12,2);
	aux[2]='\0';
	date_tm.tm_sec=(int)strtoul(aux,&tmp,10);

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;

	/*$$$$$ DAY $$$$$*/
	memcpy(aux,str_date,2);
	aux[2]='\0';
	date_tm.tm_mday=(int)strtoul(aux,&tmp,10);

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;

	/*$$$$$$$$$$$$*/

	if((st=convert_tm_to_time_t(&date_tm,date))!=OK)
		return st;

	return OK;
}

status_t convert_string_to_date_ddmmyyyy(const char * str_date,time_t *date)
{
	char  aux[MAX_LEN_AUX];
	char * tmp;
	struct tm date_tm;
	status_t st;

	if(str_date==NULL)
		return ERROR_NULL_POINTER;

	/*$$$$$ DAY $$$$$*/
	memcpy(aux,str_date,2);
	aux[2]='\0';
	date_tm.tm_mday=(int)strtoul(aux,&tmp,10);

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;

	/*$$$$$ MON $$$$$*/
	memcpy(aux,str_date+2,2);
	aux[2]='\0';
	date_tm.tm_mon=(int)strtoul(aux,&tmp,10)-1;

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;

	/*$$$$$ YEAR $$$$$*/
	memcpy(aux,str_date+4,4);
	aux[4]='\0';
	date_tm.tm_year=(int)strtoul(aux,&tmp,10)-1900;

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;


	if((st=convert_tm_to_time_t(&date_tm,date))!=OK)
		return st;

	return OK;
}

status_t convert_string_to_date_yyyymmdd(const char * str_date,time_t *date)
{
	char  aux[MAX_LEN_AUX];
	char * tmp;
	struct tm date_tm;
	status_t st;

	if(str_date==NULL)
		return ERROR_NULL_POINTER;

/*$$$$$ YEAR $$$$$*/
	memcpy(aux,str_date,4);
	aux[4]='\0';
	date_tm.tm_year=(int)strtoul(aux,&tmp,10)-1900;

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;


/*$$$$$ MON $$$$$*/
	memcpy(aux,str_date+4,2);
	aux[2]='\0';
	date_tm.tm_mon=(int)strtoul(aux,&tmp,10)-1;

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;

 /*$$$$$ DAY $$$$$*/
	memcpy(aux,str_date+6,2);
	aux[2]='\0';
	date_tm.tm_mday=(int)strtoul(aux,&tmp,10);

	if(*tmp)
		return ERROR_PROGRAM_INVOCATION;


	if((st=convert_tm_to_time_t(&date_tm,date))!=OK)
		return st;

	return OK;
}

status_t convert_tm_to_time_t(struct tm * tm_date,time_t * t_date)
{
	struct tm * tm_aux;

	if(tm_date==NULL || t_date==NULL)
		return ERROR_NULL_POINTER;

  if((*t_date=mktime(tm_date))==-1)
    return ERROR_TIME_CONVERSION;

  tm_aux=localtime(t_date);

  if(tm_aux->tm_sec!=tm_date->tm_sec)
    return ERROR_DATE_INPUT;

  if(tm_aux->tm_min!=tm_date->tm_min)
    return ERROR_DATE_INPUT;

  if(tm_aux->tm_hour!=tm_date->tm_hour)
    return ERROR_DATE_INPUT;

  if(tm_aux->tm_mday!=tm_date->tm_mday)
    return ERROR_DATE_INPUT;

  if(tm_aux->tm_mon!=tm_date->tm_mon)
    return ERROR_DATE_INPUT;

  if(tm_aux->tm_year!=tm_date->tm_year)
    return ERROR_DATE_INPUT;


  return OK;

}
