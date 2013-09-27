#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "hosts_file.h"

static FILE *openFile(const char *path, const char *mode) {
	FILE *file = fopen(path, mode);
	if (file == NULL) {
		char *errstr;
		switch (errno) {
			case EACCES:
				errstr = "Permission denied";
				break;
			case ENOENT:
				errstr = "File not found";
				break;
			case EISDIR:
				errstr = "Is a directory";
				break;
			default:
				errstr = "Unknown error";
		}
		fprintf(stderr, "Error opening %s: %s\n", path, errstr);
		exit(EXIT_FAILURE);
	}
	return file;
}

static void processLine(char *line, HostsFile *hostsFile) {
	char *ip = strtok(line, " \t\n");
	char *hostname;
	if (ip != NULL) {
		while ((hostname = strtok(NULL, " \t\n")) != NULL) {
			addHostsFileEntry(hostsFile, ip, hostname);
		}
	}
}

static void readHostsFileEntries(FILE *file, HostsFile *hostsFile) {
	char line[256];
	while (!feof(file)) {
		if (fgets(line, 256, file) == NULL) {
			break;
		}
		if (strlen(line) > 255) {
			fputs("Error: Line too long (max. 255 characters)", stderr);
			exit(EXIT_FAILURE);
		}
		if (line[0] == '#') {
			continue;
		}
		processLine(line, hostsFile);
	}
}

HostsFile *readHostsFile(const char *path) {
	FILE *file = openFile(path, "r");
	HostsFile *hostsFile = createHostsFile(path);
	readHostsFileEntries(file, hostsFile);
	fclose(file);
	return hostsFile;
}

void writeHostsFile(HostsFile *hostsFile) {
	FILE *file = openFile(hostsFile->path, "w");
	for (int i = 0; i < hostsFile->numEntries; ++i) {
		fprintf(file, "%s\t\t%s\n", hostsFile->entries[i].ip, hostsFile->entries[i].hostname);
	}
	fclose(file);
}
