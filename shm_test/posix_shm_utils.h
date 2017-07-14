/**
* @file       posix_shm_utils.h
* @brief      major interfaces: shm_open, shm_unlink, ftruncate, mmap, munmap
* @author     wangyoucao577@gmail.com
*
*/


#ifndef _MY_TINY_TEST_SHM_TEST_POSIX_SHM_UTILS_H_
#define _MY_TINY_TEST_SHM_TEST_POSIX_SHM_UTILS_H_

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#include <string>
#include "shm_utils_base.h"


namespace shm_test {


	class PosixShm : public ShmBase {
	public:
		PosixShm(std::string name, int bytes);
		~PosixShm();

	public:
		bool Link() override;
		void Unlink() override;
		void UnMap() override;

	private:
		std::string name_;

		int fd_{ INVALID_FILE_DESCRIPTOR };
	};
}


#endif

