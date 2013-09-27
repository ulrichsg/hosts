#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arguments.h"
#include "hosts_file.h"
#include "commands.h"

static int MAX_ARGS = 10;
static const char* DEFAULT_FILENAME = "/etc/hosts";

typedef struct command_struct {
	const char *name;
	int (*function)(HostsFile*, Arguments);
	int numArgs;
} Command;

static void printVersion() {
	printf("hosts v1.0.0 (c) 2013 Ulrich Schmidt-Goertz\n");
}

static void printUsage() {
	printVersion();

	printf("\nUsage: hosts [command] [-f <filename> | -h | -v] [arguments]\n\n");

	printf("Available commands:\n");
	printf("	list	Print the list of entries in the hosts file\n");
	printf("	add		Adds an entry to the hosts file. Arguments: [hostname] [ip-address]\n");
	printf("	rm		Removes one or more entries from the hosts file. Arguments: [hostname]...\n\n");

	printf("Available options:\n");
	printf("	-f <filename>	Chooses the file to operate on (default: /etc/hosts)\n");
	printf("	-h				Prints this help text\n");
	printf("	-v				Prints version information\n");
}

static int handleCommand(const char *command, Arguments arguments) {
	static Command commands[] = {
		{ "list", cmd_list, 0 },
		{ "add", cmd_add, 2 },
		{ "rm", cmd_rm, 1 }
	};
	HostsFile *hostsFile = readHostsFile(arguments.filename);
	for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); ++i) {
		if (strcmp(command, commands[i].name) == 0) {
			if (arguments.size < commands[i].numArgs) {
				fprintf(stderr, "Error: command %s needs %d argument(s)\n", commands[i].name, commands[i].numArgs);
				exit(EXIT_FAILURE);
			}
			return commands[i].function(hostsFile, arguments);
		}
	}
	printUsage();
	return 1;
}

int main(int argc, const char **argv) {
	if (argc < 2) {
		printUsage();
		return 1;
	}

	Arguments arguments;
	arguments.filename = DEFAULT_FILENAME;
	arguments.values = (const char**)malloc(MAX_ARGS*sizeof(char*));

	int nonopt = 0;
	const char *command = "";

	for (int i = 1; i < argc; ++i) {
		const char *argument = argv[i];
		if (argument[0] == '-') {
			switch (argument[1]) {
				case 'h':
					printUsage();
					exit(EXIT_SUCCESS);
				case 'v':
					printVersion();
					exit(EXIT_SUCCESS);
				case 'f':
					arguments.filename = argv[++i];
					break;
				default:
					printUsage();
					exit(EXIT_FAILURE);
			}
		} else {
			if (i == 1) {
				command = argument;
			} else {
				if (nonopt >= MAX_ARGS-1) {
					fputs("Error: Too many arguments", stderr);
					exit(EXIT_FAILURE);
				}
				arguments.values[nonopt++] = argument;
			}
		}
	}
	arguments.size = nonopt;

	return handleCommand(command, arguments);
}
