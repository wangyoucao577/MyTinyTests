

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
		bool PassVector(const std::string& obj_name, const std::vector<std::string>& value);
		bool PassVector(const std::string& obj_name, const std::vector<float>& value);

	private:
		boost::interprocess::managed_shared_memory* shm_{ nullptr };

		std::string name_;
		const uint32_t bytes_per_growth_{ kDefaultBytesPerGrowth };

	public:
		static const uint32_t kDefaultBytesPerGrowth{ 1000000 };	// 1MB per growth in default
	};

}

#endif
