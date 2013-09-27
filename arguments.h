#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

typedef struct arguments_struct {
	const char *filename;
	const char **values;
	int size;
} Arguments;

#endif
