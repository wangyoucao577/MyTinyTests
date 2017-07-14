
#include "system_v_shm_utils.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>


namespace shm_test {

	SystemVShm::~SystemVShm() {
		if (fd_ != INVALID_FILE_DESCRIPTOR) {
			close(fd_);
			fd_ = INVALID_FILE_DESCRIPTOR;
		}

		UnMap();
	}

	bool SystemVShm::Link() {

		int flags{ mode_ };

		while (fd_ == INVALID_FILE_DESCRIPTOR) {
			fd_ = shmget(key_, bytes_, flags);
			if (fd_ >= 0) {
				break;
			}

			shm_log("shmget key %d failed via flag %d, errno %d %s\n", key_, flags, \
				errno, strerror_r(errno, err_str_, sizeof(err_str_)));

			if (ENOENT == errno && (0 == (flags & IPC_CREAT))) {
				shm_log("since errno is ENOENT, try create new one with one more flag IPC_CREAT\n");
				flags |= IPC_CREAT;
			}
			else {
				return false;
			}
		}

		shm_log("opened key %d as fd %d, bytes %d\n", key_, fd_, bytes_);

		address_ = shmat(fd_, NULL, 0);
		if (address_ == (void*)(-1)) {
			shm_log("map fd %d failed, errno %d %s\n", fd_, errno, strerror_r(errno, err_str_, sizeof(err_str_)));
			Unlink();
			return false;
		}

		shm_log("mmap fd %d to address %p succeed\n", fd_, address_);
		return true;
	}

	void SystemVShm::Unlink() {
		UnMap();

		if (fd_ == INVALID_FILE_DESCRIPTOR) {
			int flags{ mode_ };
			fd_ = shmget(key_, bytes_, flags);
			if (fd_ < 0) {
				shm_log("shmget key %d failed via flag %d, errno %d %s\n", key_, flags, \
					errno, strerror_r(errno, err_str_, sizeof(err_str_)));
				if (ENOENT == errno) {
					shm_log("shm key %d does't exist, do nothing for unlink\n", key_);
				}
				return;
			}
		}

		//delete 
		int ret = shmctl(fd_, IPC_RMID, 0);
		if (ret != 0) {
			shm_log("shmctl unlink key %d fd %d failed, errno %d %s\n", key_, fd_, errno, strerror_r(errno, err_str_, sizeof(err_str_)));
			return;
		}
		shm_log("unlink succeed, key %d, bytes %d\n", key_, bytes_);
	}

	void SystemVShm::UnMap() {
		if (nullptr == address_) {
			return;
		}

		int ret = shmdt(address_);
		if (0 != ret) {
			shm_log("munmap failed, address_ %p, bytes %d, errno %d %s\n", address_, bytes_, 
				errno, strerror_r(errno, err_str_, sizeof(err_str_)));
			return;
		}
		shm_log("unmap succeed, address_ %p, bytes %d\n", address_, bytes_);

		address_ = nullptr;
	}
}