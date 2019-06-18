#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"

char *errors[MAX_ERRORS]={
	STR_OK,
	STR_ERROR_NULL_POINTER,
	STR_ERROR_PROGRAM_INVOCATION,
	STR_ERROR_DATE_FORMAT,
	STR_ERROR_DATE_INPUT,
	STR_ERROR_TIME_CONVERSION,
	STR_ERROR_OUTPUT_UNIT
};

status_t print_error(status_t st)
{
	fprintf(stderr, "%s\n\n",errors[st]);
	return OK;
}
