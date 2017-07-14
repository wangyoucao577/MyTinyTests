
#include "posix_shm_utils.h"

#include <assert.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>


namespace shm_test {

	PosixShm::PosixShm(std::string name, int bytes) : ShmBase(name, bytes)
	{
	}

	PosixShm::~PosixShm() {
		if (fd_ != INVALID_FILE_DESCRIPTOR) {
			close(fd_);
			fd_ = INVALID_FILE_DESCRIPTOR;
		}

		UnMap();
	}

	void PosixShm::Unlink() {
		
		UnMap();
		int ret = shm_unlink(name_.c_str());
		if (ret != 0) {
			shm_log("shm_unlink %s failed, errno %d %s\n", name_.c_str(), errno, strerror_r(errno, err_str_, sizeof(err_str_)));
			return;
		}
		shm_log("unlink succeed, name %s, bytes %d\n", name_.c_str(), bytes_);
	}

	void PosixShm::UnMap() {
		if (nullptr == address_) {
			return;
		}

		int ret = munmap(address_, bytes_);
		if (ret != 0) {
			shm_log("munmap failed, address_ %p, bytes %d\n", address_, bytes_);
			return;
		}
		shm_log("unmap succeed, address_ %p, bytes %d\n", address_, bytes_);

		address_ = nullptr;
	}

	bool PosixShm::Link()
	{
		int flags{ O_RDWR };

		while (fd_ == INVALID_FILE_DESCRIPTOR) {
			fd_ = shm_open(name_.c_str(), flags, mode_);
			if (fd_ >= 0) {
				break;
			}

			shm_log("shm_open %s failed via flag %d, errno %d %s\n", name_.c_str(), flags, \
				errno, strerror_r(errno, err_str_, sizeof(err_str_)));

			if (ENOENT == errno && (0 == (flags & O_CREAT))) {
				shm_log("since errno is ENOENT, try create new one with one more flag O_CREAT\n");
				flags |= O_CREAT;
			}
			else {
				return false;
			}
		}

		shm_log("opened %s as fd %d\n", name_.c_str(), fd_);

		if (flags & O_CREAT) {	// new created
			int ret = ftruncate(fd_, bytes_);
			if (0 != ret) {
				shm_log("ftruncate for fd %d failed, size %d errno %d %s\n", fd_, bytes_, errno, strerror_r(errno, err_str_, sizeof(err_str_)));
				Unlink();
				return false;
			}
			shm_log("ftruncate %s fd %d bytes to %d succeed\n", name_.c_str(), fd_, bytes_);
		}

		address_ = mmap(NULL, bytes_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
		if (address_ == MAP_FAILED) {
			shm_log("mmap fd %d failed, errno %d %s", fd_, errno, strerror_r(errno, err_str_, sizeof(err_str_)));
			return false;
		}
		shm_log("mmap fd %d to address %p succeed\n", fd_, address_);
		
		return true;
	}

}
