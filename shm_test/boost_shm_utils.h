

/**
* @file       boost_shm_utils.h
* @brief      major interfaces: `boost::interprocess::managed_shared_memory`
*				actually if prefer raw memory address link native Posix/SystemV shm interfaces, 
*					use `boost::interprocess::managed_xsi_shared_memory` instead. 
*				
* @author     wangyoucao577@gmail.com
*
*/

#ifndef _MY_TINY_TEST_SHM_TEST_BOOST_SHM_UTILS_H_
#define _MY_TINY_TEST_SHM_TEST_BOOST_SHM_UTILS_H_

#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"

#include "shm_utils_base.h"

namespace shm_test {

    class BoostShm : public ShmBase {
	public:
		BoostShm(std::string name, int bytes);
		~BoostShm();

	public:
		/**
		* @brief These 3 interfaces have the same behavior come from ShmBase. 
		*      But for boost::interprocess features, we'll have some other interfaces.
		*/
		bool Link() override;
		void Unlink() override;
		void UnMap() override;

		void Dump() const override;

		/**
		* @brief Only link boost managed_shared_memory object, but won't get raw pointer. 
		*	   So that we could map some structures/classes on this memory.
		*/
		bool LinkShmObject();

		/**
		* @brief Check whether shm object valid.
		* @return true if valid, false if invalid
		*/
		bool Valid() const { return nullptr == shm_ ? false : true; }

	private:
		std::string name_;
	
		boost::interprocess::shared_memory_object* shm_{ nullptr };
		boost::interprocess::mapped_region*	map_region_{ nullptr };
	};

}

#endif
