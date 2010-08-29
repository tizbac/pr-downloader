


#define VERSION 0.1
#define USER_AGENT "unitsync-dev" + VERSION
#define SPRING_DIR "/home/matze/.spring"
#define TMP_FILE "/tmp/repos.gz"
#define TMP_FILE2 "/tmp/version.gz"


#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "md5.h"
#include "RapidDownloader.h"
#include "Util.h"
#include <string>


int main(int argc, char **argv){
	int i;
	if (argc==1){
		printf("Usage: %s tagtodownload|--list\n", argv[0]);
	}
	rapidDownloader->Initialize();
	for(i=1;i<argc;i++){
		std::string arg=argv[i];
		if(arg=="--list"){
			rapidDownloader->list_tag();
		}else{
			rapidDownloader->download_tag(arg);
		}
	}

	rapidDownloader->Shutdown();

    return 0;
}

