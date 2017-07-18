

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

	bool BoostShm::Construct(PointerOfTestType1& obj, const std::string& obj_name, uint32_t count){
		if (!Valid()) {
			return false;
		}

		assert(count > 0);

		int before_memory = shm_->get_free_memory();

		shm_log("try construct %s, type %s, is_pod %d, free_memory %d\n", obj_name.c_str(), VNAME(TestType1), std::is_pod<TestType1>::value, before_memory);

		do {
			obj = shm_->find_or_construct<TestType1>(obj_name.c_str(), std::nothrow)[count]();

			shm_log("find_or_construct %s %s, type %s, is_pod %d, address %p free_memory %d cost memory %d\n",
				obj_name.c_str(), obj ? "succeed" : "failed", VNAME(TestType1), std::is_pod<TestType1>::value,
				obj, shm_->get_free_memory(), before_memory - shm_->get_free_memory());

		} while (!obj && Grow(bytes_per_growth_));

		return obj ? true : false;
	}

	bool BoostShm::Write(const TestType1& obj, const std::string& obj_name, uint32_t count) {

		TestType1* obj_on_shm = nullptr;
		if (!Construct(obj_on_shm, obj_name, count)) {
			return false;
		}

		for (int i = 0; i < count; ++i, ++obj_on_shm)
		{
			obj_on_shm->a = obj.a;
			obj_on_shm->b = obj.b;
		}

		return true;
	}

	bool BoostShm::Find(PointerOfTestType1& obj, uint32_t& count, const std::string& obj_name) {
		if (!Valid()) {
			return false;
		}

		std::pair<TestType1*, uint32_t> find_result = shm_->find<TestType1>(obj_name.c_str());
		shm_log("find %s result obj %p count %u, %s\n", obj_name.c_str(), find_result.first, find_result.second, 
			find_result.first ? "succeed" : "failed");

		if (find_result.first) {
			obj = find_result.first;
			count = find_result.second;
			return true;
		}
		return false;
	}

	bool BoostShm::Destory(const std::string& obj_name, const TestType1& obj) {
		if (!Valid()) {
			return false;
		}

		int before_memory = shm_->get_free_memory();

		bool ret = shm_->destroy<TestType1>(obj_name.c_str());

		shm_log("destory %s %s free memory %d delta %d\n", VNAME(obj_name), ret ? "succeed" : "failed", 
			shm_->get_free_memory(), before_memory - shm_->get_free_memory());

		return ret;
	}
}