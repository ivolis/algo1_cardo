#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "main.h"

char * str_format_date[MAX_FORMAT_TYPES]={
	"DDMMYYYYhhmmss",
	"DDMMYYYY",
	"YYYYMMDD"
};

char * str_unit_output[MAX_UNIT_TYPES]={
	"s",
	"m",
	"h",
	"d"
};



/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ INVOCATION $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

int main(int argc, char *argv[])
{

	double diff_date;
	status_t st;


	if((st=validate_arguments(argc,argv,&setup))!=OK)
	{
		print_error(st);
		return st;
	}

	if((st=get_diff_time(setup.date_1,setup.date_2,&diff_date,setup.output_unit))!=OK)
	{
		print_error(st);
		return st;
	}

	if((st=print_diff_time(diff_date,stdout))!=OK)
	{
		print_error(st);
		return st;
	}

	return OK;
}

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ MAIN-CLA VALIDATION FUNCTION $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

status_t validate_arguments(int argc, char* argv[],setup_t* setup)
{
	size_t i;
	status_t st;

	if(argv==NULL || setup==NULL)
		return ERROR_NULL_POINTER;

	if(argc!=MAX_ARGS)
		return ERROR_PROGRAM_INVOCATION;

	if(strcmp(argv[CMD_ARG_POS_FORMAT_DATE_1_TOKEN],CMD_ARG_FORMAT_DATE_1_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	for(i=0; i<MAX_FORMAT_TYPES; i++)
	{
		if(!(strcmp(argv[CMD_ARG_POS_FORMAT_DATE_1_TOKEN+1], str_format_date[i])))
		{
			setup->format_date_1=i;
			break;
		}
	}

	if(i==MAX_FORMAT_TYPES)
	{
		return ERROR_DATE_FORMAT;
	}


	if(strcmp(argv[CMD_ARG_POS_DATE_1_TOKEN],CMD_ARG_DATE_1_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	if(strlen(argv[CMD_ARG_POS_DATE_1_TOKEN+1])+1>MAX_LEN_DATE)
		return ERROR_PROGRAM_INVOCATION;


	if(strcmp(argv[CMD_ARG_POS_FORMAT_DATE_2_TOKEN],CMD_ARG_FORMAT_DATE_2_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	for(i=0; i<MAX_FORMAT_TYPES ; i++)
	{
		if(!(strcmp(argv[CMD_ARG_POS_FORMAT_DATE_2_TOKEN+1], str_format_date[i])))
		{
			setup->format_date_2=i;
			break;
		}
	}

	if(i==MAX_FORMAT_TYPES)
	{
		return ERROR_DATE_FORMAT;
	}


	if(strcmp(argv[CMD_ARG_POS_DATE_2_TOKEN],CMD_ARG_DATE_2_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	if(strlen(argv[CMD_ARG_POS_DATE_2_TOKEN+1])+1>MAX_LEN_DATE)
		return ERROR_PROGRAM_INVOCATION;


	if(strcmp(argv[CMD_ARG_POS_OUTPUT_UNIT_TOKEN],CMD_ARG_OUTPUT_UNIT_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	for(i=0;i<MAX_UNIT_TYPES;i++)
	{
		if(!(strcmp(argv[CMD_ARG_POS_OUTPUT_UNIT_TOKEN+1],str_unit_output[i])))
		{
			setup->output_unit=i;
			break;
		}
	}

	if(i==MAX_UNIT_TYPES)
	{
		return ERROR_OUTPUT_UNIT;
	}


/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	if((st=parse_string_date(&(setup->format_date_1),argv[CMD_ARG_POS_DATE_1_TOKEN+1],&(setup->date_1)))!=OK)
		return st;

	if((st=parse_string_date(&(setup->format_date_2),argv[CMD_ARG_POS_DATE_2_TOKEN+1],&(setup->date_2)))!=OK)
		return st;

	return OK;
}
