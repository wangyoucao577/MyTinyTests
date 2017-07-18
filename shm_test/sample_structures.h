
#ifndef _MY_TINY_TEST_SHM_TEST_SAMPLE_STRUCTURES_H_
#define _MY_TINY_TEST_SHM_TEST_SAMPLE_STRUCTURES_H_

#include <string>

#include "shm_utils_base.h"

namespace shm_test{

	struct TestType1 {
		int a;
		int b;

		void dump() const {
			shm_log("type %s %s=%d %s=%d\n", VNAME(TestType1), VNAME(a), a, VNAME(b), b);
		}
	};

	struct TestType2 {

		TestType2(){}	// make it not POD

		int a;
		float b;

		void dump() const {
			shm_log("type %s %s=%d %s=%f\n", VNAME(TestType2), VNAME(a), a, VNAME(b), b);
		}
	};

	struct TestType3 {

		TestType3(double val) : dd(val) {}

		double dd;

		void dump() const {
			shm_log("type %s %s=%lf\n", VNAME(TestType3), VNAME(dd), dd);
		}
	};

}

#endif
