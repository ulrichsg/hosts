typedef struct hosts_entry_struct {
	char *ip;
	char *hostname;
} HostsFileEntry;

typedef struct hosts_file_struct {
	const char *path;
	HostsFileEntry *entries;
	int numEntries;
} HostsFile;

HostsFile *readHostsFile(const char *path);
void writeHostsFile(HostsFile *hostsFile);

HostsFile *createHostsFile(const char *path);
void addHostsFileEntry(HostsFile *hostsFile, const char *ip, const char *hostname);
int removeHostsFileEntry (HostsFile *hostsFile, const char *hostname);
