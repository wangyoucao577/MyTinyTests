
#include <assert.h>

#include <iostream>

#include "boost_posix_shm_utils.h"

namespace shm_test {

	BoostPosixShm::BoostPosixShm(std::string name, int bytes)
		: ShmBase(bytes),
		name_(name)
	{
		
	}

	BoostPosixShm::~BoostPosixShm() {
		UnMap();
	}

	bool BoostPosixShm::LinkShmObject() {

		assert(nullptr == shm_);

		try
		{
			shm_ = new boost::interprocess::shared_memory_object(boost::interprocess::open_or_create, 
				name_.c_str(), boost::interprocess::read_write);
		}
		catch (const boost::interprocess::interprocess_exception& ex)
		{
			shm_log("try open_or_create shm failed, err %d(%d) %s\n", ex.get_error_code(), ex.get_native_error(), ex.what());
			return false;
		}

		shm_log("link managed_shared_memory succeed, name %s bytes %d\n", name_.c_str(), bytes_);

		return true;
	}

	bool BoostPosixShm::Link() {
		
		if (!LinkShmObject()) {
			return false;
		}
		assert(Valid());

		shm_->truncate(bytes_);

		map_region_ = new boost::interprocess::mapped_region(*shm_, boost::interprocess::read_write);

		address_ = map_region_->get_address();

		return true;
	}

	void BoostPosixShm::Unlink() {

		UnMap();

		if (!boost::interprocess::shared_memory_object::remove(name_.c_str())) {
			shm_log("unlink %s failed\n", name_.c_str());
			return;
		}
		shm_log("unlink %s succeed\n", name_.c_str());
		
	}
	void BoostPosixShm::UnMap() {

		address_ = nullptr;

		if (map_region_) {
			delete map_region_;
			map_region_ = nullptr;
		}

		if (shm_) {
			delete shm_;
			shm_ = nullptr;

			shm_log("unmap shm object %s succeed\n", name_.c_str());
		}
	}

	void BoostPosixShm::Dump() const {
		if (!Valid()) {
			return;
		}

		if (nullptr == address_) {
			return;
		}

		assert(map_region_);
		shm_log("address %p, size %d\n", address_, map_region_->get_size());
		shm_log("%s\n", (char*)address_);
	}

}