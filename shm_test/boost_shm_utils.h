

/**
* @file       boost_shm_utils.h
* @brief      major interfaces: 
* @author     wangyoucao577@gmail.com
*
*/

#ifndef _MY_TINY_TEST_SHM_TEST_BOOST_SHM_UTILS_H_
#define _MY_TINY_TEST_SHM_TEST_BOOST_SHM_UTILS_H_

#include "boost/interprocess/managed_shared_memory.hpp"

#include "shm_utils_base.h"

namespace shm_test {

    class BoostShm : public ShmBase {
	public:
		BoostShm(std::string name, int bytes);
		~BoostShm();

	public:
		bool Link() override;
		void Unlink() override;
		void UnMap() override;
        
	private:
		std::string name_;
    }

}

#endif
