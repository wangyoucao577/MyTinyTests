
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "posix_shm_utils.h"
#include "system_v_shm_utils.h"
#include "boost_posix_shm_utils.h"
#include "boost_shm.h"

using namespace std;
using namespace shm_test;

//#define COMPARE_POSIX_SYSTEMV_BOOSTNATIVE

#ifdef COMPARE_POSIX_SYSTEMV_BOOSTNATIVE

int main(int argc, char* argv[]){

	//ShmBase* sm = new PosixShm("jay_test_01", 1025);
	//ShmBase* sm = new SystemVShm(11, 1026);
	ShmBase* sm = new BoostPosixShm("jay_test_02", 1026);

	if (argc >= 2) {
		if (0 == strcmp(argv[1], "link")) {
			bool ret = sm->Link();
			assert(ret == true);

			if (argc >= 4 && 0 == strcmp(argv[2], "write")) {

				memcpy(sm->address(), argv[3], strlen(argv[3]));

			}else if (argc >= 3 && 0 == strcmp(argv[2], "read")) {
				sm->Dump();
			}
			
		}
		else if (0 == strcmp(argv[1], "unlink")) {
			sm->Unlink();
		}
	}
	
	delete sm;
    return 0;
}

#else

void print_usage() {
	shm_log("Usage:\n");
	shm_log("    ./shm <cmd>\n");
	shm_log("Sample:\n");
	shm_log("    ./shm write\n");
	shm_log("    ./shm read\n");
	shm_log("    ./shm destory_obj\n");
	shm_log("    ./shm unlink\n");
}

int main(int argc, char* argv[]) {

	BoostShm shm("jay_test_03", 10000);

	if (argc >= 2 && 0 == strcmp(argv[1], "write")) {
		bool ret = shm.Link();
		assert(ret == true);

		//POD
		TestType1* test1 = nullptr;
		int count = 1;
		if (shm.Construct<TestType1>(test1, VNAME(test1), count)) {
			for (size_t i = 0; i < count; i++)
			{
				test1->a = -11;
				test1->b = 12;
				test1++;
			}
		}

		//not POD
		TestType2* test2 = nullptr;
		count = 3;
		if (shm.Construct<TestType2>(test2, VNAME(test2), count)) {
			for (size_t i = 0; i < count; i++)
			{
				test2->a = -13;
				test2->b = 15.5f;
				test2++;
			}
		}
		
		//vector, not POD
		ShmVector<TestType3>* test3 = nullptr;
		if (shm.ConstructVector<TestType3>(test3, VNAME(test3))) {
			shm_log("shm get free memory %lld\n", shm.GetFreeMemory());
			test3->push_back(TestType3(3.1415926535f));
			test3->push_back(TestType3(3.1415926535f));
			test3->push_back(TestType3(3.1415926535f));
			shm_log("shm get free memory %lld\n", shm.GetFreeMemory());
		}
	}
	else if (argc >= 2 && 0 == strcmp(argv[1], "read")) {
		bool ret = shm.Link();
		assert(ret == true);

		TestType1* test1 = nullptr;
		uint32_t test1_count = 0;
		if (shm.Find<TestType1>(test1, test1_count, VNAME(test1))) {
			assert(test1);
			assert(test1_count > 0);

			for (int i = 0; i < test1_count; ++i, ++test1) {
				test1->dump();
			}
		}

		TestType2* test2 = nullptr;
		uint32_t test2_count = 0;
		if (shm.Find<TestType2>(test2, test2_count, VNAME(test2))) {
			assert(test2);
			assert(test2_count > 0);

			for (int i = 0; i < test2_count; ++i, ++test2) {
				test2->dump();
			}
		}

		ShmVector<TestType3>* test3 = nullptr;
		uint32_t test3_count = 0;
		if (shm.Find<ShmVector<TestType3>>(test3, test3_count, VNAME(test3))) {
			assert(test3);
			assert(test3_count > 0);

			for (size_t i = 0; i < test3_count; i++, test3++)
			{
				const ShmVector<TestType3>& test3_vec = *test3;
				for (const auto& val : test3_vec) {
					val.dump();
				}
			}
		}
		
	}
	else if (argc >= 2 && 0 == strcmp(argv[1], "destory_obj")) {
		bool ret = shm.Link();
		assert(ret == true);

		shm.Destory<TestType1>(VNAME(test1));
		shm.Destory<TestType2>(VNAME(test2));
		shm.Destory<ShmVector<TestType3>>(VNAME(test3));
	}
	else if (argc >= 2 && 0 == strcmp(argv[1], "unlink")) {
		shm.Unlink();
	}
	else {
		print_usage();
	}
	
	
	return 0;
}

#endif // COMPARE_POSIX_SYSTEMV_BOOSTNATIVE

