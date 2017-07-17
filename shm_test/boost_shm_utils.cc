
#include "boost_shm_utils.h"

namespace shm_test {

	BoostShm::BoostShm(std::string name, int bytes)
		: ShmBase(bytes),
		name_(name)
	{

	}

	BoostShm::~BoostShm() {

	}

	bool BoostShm::Link() {

		return true;
	}
	void BoostShm::Unlink() {

	}
	void BoostShm::UnMap() {

	}

}