#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TYPES.h"
#include "errors.h"
#include "dates.h"

#define MAX_ARGS 11
#define CMD_ARG_POS_FORMAT_DATE_1_TOKEN 1
#define CMD_ARG_FORMAT_DATE_1_TOKEN "-fmt1"
#define CMD_ARG_POS_DATE_1_TOKEN 3
#define CMD_ARG_DATE_1_TOKEN "-f1"
#define CMD_ARG_POS_FORMAT_DATE_2_TOKEN 5
#define CMD_ARG_FORMAT_DATE_2_TOKEN "-fmt2"
#define CMD_ARG_POS_DATE_2_TOKEN 7
#define CMD_ARG_DATE_2_TOKEN "-f2"
#define CMD_ARG_POS_OUTPUT_UNIT_TOKEN 9
#define CMD_ARG_OUTPUT_UNIT_TOKEN "-u"

#define MAX_LEN_DATE 15
#define MIN_LEN_DATE 9
#define MAX_FORMAT_TYPES 3
#define MAX_UNIT_TYPES 4

status_t validate_arguments(int argc, char* argv[],setup_t* setup);

setup_t setup;

#endif
