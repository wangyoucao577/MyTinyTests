
#include <assert.h>

#include <iostream>

#include "boost_shm_utils.h"

namespace shm_test {

	BoostShm::BoostShm(std::string name, int bytes)
		: ShmBase(bytes),
		name_(name)
	{
		
	}

	BoostShm::~BoostShm() {
		UnMap();
	}

	bool BoostShm::LinkShmObject() {

		assert(nullptr == shm_);

		try
		{
			shm_ = new boost::interprocess::managed_shared_memory(boost::interprocess::open_or_create, name_.c_str(), bytes_);
		}
		catch (const boost::interprocess::interprocess_exception& ex)
		{
			shm_log("try open_or_create shm failed, err %d(%d) %s\n", ex.get_error_code(), ex.get_native_error(), ex.what());
			return false;
		}

		shm_log("link managed_shared_memory succeed, name %s bytes %d actual_size %d free_memory %d\n", 
			name_.c_str(), bytes_, shm_->get_size(), shm_->get_free_memory());

		return true;
	}

	bool BoostShm::Link() {
		
		if (!LinkShmObject()) {
			return false;
		}
		assert(Valid());

		// we cost all valid bytes in this mode
		// todo: find the reason why can not allocate all free_memory, `80` is just a guess
		int addr_size = shm_->get_free_memory() - 80;
		shm_log("free memory before shm allocate: %d\n", shm_->get_free_memory());
		//address_ = shm_->allocate(100);	
		address_ = shm_->find_or_construct<char>("address")[addr_size] (0);
		shm_log("free memory after  shm allocate: %d\n", shm_->get_free_memory());

		return true;
	}

	void BoostShm::Unlink() {

		UnMap();

		if (!boost::interprocess::shared_memory_object::remove(name_.c_str())) {
			shm_log("unlink %s failed\n", name_.c_str());
			return;
		}
		shm_log("unlink %s succeed\n", name_.c_str());
		
	}
	void BoostShm::UnMap() {

		address_ = nullptr;

		if (shm_) {
			delete shm_;
			shm_ = nullptr;

			shm_log("unmap shm object %s succeed\n", name_.c_str());
		}
	}

	void BoostShm::Dump() const {
		if (!Valid()) {
			return;
		}

		shm_log("free bytes %d\n", shm_->get_free_memory());

		if (nullptr == address_) {
			return;
		}

		shm_log("address %p, size %d\n", address_, bytes_);
		shm_log("%s\n", (char*)address_);
	}

}