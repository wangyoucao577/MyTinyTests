
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "posix_shm_utils.h"

using namespace std;
using namespace shm_test;

int main(int argc, char* argv[]){

	PosixShm sm("jay_test_01", 1025);

	if (argc >= 2) {
		if (0 == strcmp(argv[1], "link")) {
			bool ret = sm.Link();
			assert(ret == true);

			if (argc >= 4 && 0 == strcmp(argv[2], "write")) {

				memcpy(sm.address(), argv[3], strlen(argv[3]));

			}else if (argc >= 3 && 0 == strcmp(argv[2], "read")) {
				sm.dump();
			}
			
		}
		else if (0 == strcmp(argv[1], "unlink")) {
			sm.Unlink();
		}
	}
	

    return 0;
}