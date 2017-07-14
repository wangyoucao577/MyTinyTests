

#ifndef _MY_TINY_TEST_SHM_TEST_POSIX_SHM_UTILS_H_
#define _MY_TINY_TEST_SHM_TEST_POSIX_SHM_UTILS_H_

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#include "shm_utils_base.h"


namespace shm_test {


	class PosixShm : public ShmBase {
	public:
		PosixShm(std::string name, int bytes);
		~PosixShm();

	public:

		/**
		* @brief create new shm if it's not exist. link to shm if it's already exist.
		*/
		bool Link() override;

		/**
		* @brief delete shm object explicity, converse operation of shm_open
		*
		* @note don't need to call this function until you want to delete the shm object
		*/
		void Unlink() override;

		/**
		* @brief remove the reference of the shm object
		*/
		void UnMap() override;

	private:

		int fd_{ INVALID_FILE_DESCRIPTOR };

		int mode_{ S_IRWXU | S_IRWXG | S_IRWXO };
		char err_str_[256]{0};
	};
}


#endif

