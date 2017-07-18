
#ifndef _MY_TINY_TEST_SHM_TEST_SAMPLE_STRUCTURES_H_
#define _MY_TINY_TEST_SHM_TEST_SAMPLE_STRUCTURES_H_

#include <string>

#include "shm_utils_base.h"

namespace shm_test{

	struct TestType1 {
		int a;
		int b;

		void dump() {
			shm_log("type %s %s=%d %s=%d\n", VNAME(TestType1), VNAME(a), a, VNAME(b), b);
		}
	};

	struct TestType2 {

		TestType2(){}	// make it not POD

		int a;
		float b;

		void dump() {
			shm_log("type %s %s=%d %s=%f\n", VNAME(TestType2), VNAME(a), a, VNAME(b), b);
		}
	};

	struct TestType3 {
		char a[16];

		void dump() {
			shm_log("type %s %s=%s\n", VNAME(TestType3), VNAME(a), a);
		}
	};

}

#endif
