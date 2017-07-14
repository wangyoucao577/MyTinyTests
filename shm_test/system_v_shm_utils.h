

/**
* @file       system_v_shm_utils.h
* @brief      major interfaces: shmget, shmat, shmdt, shmctl
* @author     wangyoucao577@gmail.com
*
*/

#ifndef _MY_TINY_TEST_SHM_TEST_SYSTEM_V_SHM_UTILS_H_
#define _MY_TINY_TEST_SHM_TEST_SYSTEM_V_SHM_UTILS_H_

#include <sys/ipc.h>
#include <sys/shm.h>


#include "shm_utils_base.h"

namespace shm_test {

	class SystemVShm : public ShmBase {
	public:
		SystemVShm(int key_id, int bytes) : ShmBase(bytes), key_ (key_id) {}
		~SystemVShm();

	public:
		bool Link() override;
		void Unlink() override;
		void UnMap() override;

	private:
		key_t key_{ 1 };	//@todo: try use ftok generate the key

		int fd_{ INVALID_FILE_DESCRIPTOR };
	};
}
#endif
