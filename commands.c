#include <stdio.h>
#include <string.h>
#include "arguments.h"
#include "hosts_file.h"

int cmd_list(HostsFile *hostsFile, Arguments arguments) {
	if (hostsFile->numEntries == 0) {	
		fprintf(stderr, "No hosts entries in file %s\n", hostsFile->path);
	}
	for (int i = 0; i < hostsFile->numEntries; ++i) {
		printf("%s -> %s\n", hostsFile->entries[i].ip, hostsFile->entries[i].hostname);
	}
	return 0;
}

int cmd_add(HostsFile *hostsFile, Arguments arguments) {
	const char *hostname = arguments.values[0];
	const char *ip = arguments.values[1];

	for (int i = 0; i < hostsFile->numEntries; ++i) {
		char *entryName = hostsFile->entries[i].hostname;
		if (strcmp(entryName, hostname) == 0) {
			fprintf(stderr, "Host already defined: %s -> %s\n", entryName, hostsFile->entries[i].ip);
			return 1;
		}
	}

	addHostsFileEntry(hostsFile, ip, hostname);
	writeHostsFile(hostsFile);
	return 0;
}

int cmd_rm(HostsFile *hostsFile, Arguments arguments) {
	int removedHostnames = 0;
	for (int i = 0; i < arguments.size; ++i) {
		const char *hostname = arguments.values[i];
		if (removeHostsFileEntry(hostsFile, hostname) == 0) {
			++removedHostnames;
		} else {
			fprintf(stderr, "Hostname not found: %s\n", hostname);
		}
	}
	if (removedHostnames > 0) {
		writeHostsFile(hostsFile);
		return 0;
	}
	return 1;
}
