
#ifndef _MY_TINY_TEST_SHM_TEST_SHM_UTILS_BASE_H_
#define _MY_TINY_TEST_SHM_TEST_SHM_UTILS_BASE_H_

#include <string>

#define shm_log(...) printf(__VA_ARGS__)
#define INVALID_FILE_DESCRIPTOR (-1)


namespace shm_test{
	class ShmBase {
	public:
		ShmBase(std::string name, int bytes) : name_(name), bytes_(bytes){}
		virtual ~ShmBase() {}

		/**
		* @brief create new shm if it's not exist. link to shm if it's already exist.
		*/
		virtual bool Link() = 0;

		/**
		* @brief delete shm object explicity, converse operation of shm_open
		*
		* @note don't need to call this function until you want to delete the shm object
		*/
		virtual void Unlink() = 0;

		/**
		* @brief remove the reference of the shm object
		*/
		virtual void UnMap() = 0;

		/**
		* @brief dump basic info/content of the shm object
		*/
		virtual void Dump() const {
			if (nullptr == address_) {
				return;
			}

			shm_log("address %p, size %d\n", address_, bytes_);
			shm_log("%s\n", (char*)address_);
		}
	
	public:
		/**
		* @brief get the shared memory address for user operation
		*/
		void* address() { return address_; }

	protected:
		void* address_{ nullptr };

		int bytes_{ 0 };
		std::string name_;

	};
}

#endif
