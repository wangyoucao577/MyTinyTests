

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
		typedef TestType1* PointerOfTestType1;

		bool Construct(PointerOfTestType1& obj, const std::string& obj_name, uint32_t count = 1);
		bool Write(const TestType1& obj, const std::string& obj_name, uint32_t count = 1);
		bool Find(PointerOfTestType1& obj, uint32_t& count, const std::string& obj_name);

		bool Destory(const std::string& obj_name, const TestType1& obj);

	private:
		boost::interprocess::managed_shared_memory* shm_{ nullptr };

		std::string name_;
		const uint32_t bytes_per_growth_{ kDefaultBytesPerGrowth };

	public:
		static const uint32_t kDefaultBytesPerGrowth{ 1000000 };	// 1MB per growth in default
	};

}

#endif
