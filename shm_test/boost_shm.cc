

#include "boost_shm.h"

namespace shm_test {

	BoostShm::BoostShm(std::string name, int bytes, int bytes_per_growth) :
		name_(name),
		bytes_per_growth_(bytes_per_growth),
		ShmBase(bytes)
	{

	}

	BoostShm::BoostShm(std::string name, int bytes) 
		: BoostShm(name, bytes, kDefaultBytesPerGrowth)
	{
	}

	BoostShm::~BoostShm() {
		UnMap();
	}

	bool BoostShm::Link() {

		assert(nullptr == shm_);

		try
		{
			shm_ = new boost::interprocess::managed_shared_memory(boost::interprocess::open_or_create, name_.c_str(), bytes_, 
				nullptr, boost::interprocess::permissions(0600));
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
	void BoostShm::Unlink() {

		UnMap();

		if (!boost::interprocess::shared_memory_object::remove(name_.c_str())) {
			shm_log("unlink %s failed\n", name_.c_str());
			return;
		}
		shm_log("unlink %s succeed\n", name_.c_str());
	}
	void BoostShm::UnMap() {

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

		//TODO:
	}

	bool BoostShm::Grow(uint32_t grow_size) {
		if (!Valid()) {
			return false;
		}

		int before_memory = shm_->get_free_memory();
		shm_log("before grow, free memory %d grow_size %d\n", before_memory, grow_size);

		bool ret = shm_->grow(name_.c_str(), grow_size);

		shm_log("after  grow, free memory %d grow_size %d delta %d\n", shm_->get_free_memory(), grow_size, shm_->get_free_memory() - before_memory);
	
		return ret;
	}

	uint64_t BoostShm::GetFreeMemory() const {
		if (!Valid()) {
			return 0LL;
		}

		return shm_->get_free_memory();
	}

}