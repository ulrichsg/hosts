#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hosts_file.h"

HostsFile *createHostsFile(const char *path) {
	HostsFile *hostsFile = (HostsFile*)malloc(sizeof(HostsFile));
	if (hostsFile == NULL) {
		fputs("Memory problem encountered", stderr);
		exit(EXIT_FAILURE);
	}
	
	hostsFile->path = path;
	hostsFile->entries = (HostsFileEntry*)malloc(10*sizeof(HostsFileEntry));
	if (hostsFile->entries == NULL) {
		fputs("Memory problem encountered", stderr);
		exit(EXIT_FAILURE);
	}
	hostsFile->numEntries = 0;
	
	return hostsFile;
}

void addHostsFileEntry(HostsFile *hostsFile, const char *ip, const char *hostname) {
	int maxEntries = sizeof(hostsFile->entries) / sizeof(hostsFile->entries[0]);
	if (maxEntries == hostsFile->numEntries) {
		hostsFile->entries = (HostsFileEntry*)realloc(hostsFile->entries, (maxEntries+10)*sizeof(HostsFileEntry));
		if (hostsFile->entries == NULL) {
			fputs("Memory problem encountered", stderr);
			exit(EXIT_FAILURE);
		}
	}
	
	int ipLength = strlen(ip);
	hostsFile->entries[hostsFile->numEntries].ip = (char*)malloc(ipLength + 1);
	if (hostsFile->entries[hostsFile->numEntries].ip == NULL) {
		fputs("Memory problem encountered", stderr);
		exit(EXIT_FAILURE);
	}
	strncpy(hostsFile->entries[hostsFile->numEntries].ip, ip, ipLength);
	hostsFile->entries[hostsFile->numEntries].ip[ipLength] = 0;
	
	int hostnameLength = strlen(hostname);
	hostsFile->entries[hostsFile->numEntries].hostname = (char*)malloc(hostnameLength + 1);
	if (hostsFile->entries[hostsFile->numEntries].hostname == NULL) {
		fputs("Memory problem encountered", stderr);
		exit(EXIT_FAILURE);
	}
	strncpy(hostsFile->entries[hostsFile->numEntries].hostname, hostname, hostnameLength);
	hostsFile->entries[hostsFile->numEntries].hostname[hostnameLength] = 0;
	
	hostsFile->numEntries = hostsFile->numEntries + 1;
}

int removeHostsFileEntry(HostsFile *hostsFile, const char *hostname) {
	for (int i = 0; i < hostsFile->numEntries; ++i) {
		if (strcmp(hostsFile->entries[i].hostname, hostname) == 0) {
			for (int j = i; j < hostsFile->numEntries - 1; ++j) {
				hostsFile->entries[j] = hostsFile->entries[j+1];
			}
			--hostsFile->numEntries;
			return 0;
		}
	}
	return -1;
}
