

/**
* @file       boost_shm.h
* @brief      major interfaces: `boost::interprocess::managed_shared_memory`
*				
* @note	      share objects between multi-process 
*
* @author     wangyoucao577@gmail.com
*
*/

#ifndef _MY_TINY_TEST_SHM_TEST_BOOST_SHM_H_
#define _MY_TINY_TEST_SHM_TEST_BOOST_SHM_H_

#include <string>
#include <vector>

#include "boost/interprocess/managed_shared_memory.hpp"

#include "shm_utils_base.h"

#include "sample_structures.h"

namespace shm_test {

	class BoostShm : public ShmBase {
	public:
		BoostShm(std::string name, int bytes, int bytes_per_growth);
		BoostShm(std::string name, int bytes);
		~BoostShm();

	public:
		bool Link() override;
		void Unlink() override;
		void UnMap() override;
		void Dump() const override;

	public:
		bool Valid() const { return nullptr == shm_ ? false : true; }
		bool Grow(uint32_t grow_size);

	public:

		template <typename T>
		bool Construct(T*& obj, const std::string& obj_name, uint32_t count = 1);
		
		template <typename T>
		bool Find(T*& obj, uint32_t& count, const std::string& obj_name);
		
		template <typename T>
		bool Destory(const std::string& obj_name);

	private:
		boost::interprocess::managed_shared_memory* shm_{ nullptr };

		std::string name_;
		const uint32_t bytes_per_growth_{ kDefaultBytesPerGrowth };

	public:
		static const uint32_t kDefaultBytesPerGrowth{ 1000000 };	// 1MB per growth in default
	};

	// Implementation of template functions
	template <typename T>
	bool BoostShm::Construct(T*& obj, const std::string& obj_name, uint32_t count) {
		if (!Valid()) {
			return false;
		}

		assert(count > 0);

		int before_memory = shm_->get_free_memory();

		shm_log("try construct %s, type %s, is_pod %d, free_memory %d\n", 
			obj_name.c_str(), typeid(T).name(), std::is_pod<T>::value, before_memory);

		do {
			obj = shm_->find_or_construct<T>(obj_name.c_str(), std::nothrow)[count]();

			shm_log("find_or_construct %s %s, type %s, is_pod %d, address %p free_memory %d cost memory %d\n",
				obj_name.c_str(), obj ? "succeed" : "failed", typeid(T).name(), std::is_pod<T>::value,
				obj, shm_->get_free_memory(), before_memory - shm_->get_free_memory());

		} while (!obj && Grow(bytes_per_growth_));

		return obj ? true : false;
	}

	template <typename T>
	bool BoostShm::Find(T*& obj, uint32_t& count, const std::string& obj_name) {
		if (!Valid()) {
			return false;
		}

		std::pair<T*, uint32_t> find_result = shm_->find<T>(obj_name.c_str());
		shm_log("find %s result obj %p count %u, %s\n", obj_name.c_str(), find_result.first, find_result.second,
			find_result.first ? "succeed" : "failed");

		if (find_result.first) {
			obj = find_result.first;
			count = find_result.second;
			return true;
		}
		return false;
	}

	template <typename T>
	bool BoostShm::Destory(const std::string& obj_name) {

		if (!Valid()) {
			return false;
		}

		int before_memory = shm_->get_free_memory();

		bool ret = shm_->destroy<T>(obj_name.c_str());

		shm_log("destory %s %s free memory %d delta %d\n", VNAME(obj_name), ret ? "succeed" : "failed",
			shm_->get_free_memory(), before_memory - shm_->get_free_memory());

		return ret;

	}

}

#endif
