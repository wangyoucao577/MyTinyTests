
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <string>

#define shm_log(...) printf(__VA_ARGS__)
#define INVALID_FILE_DESCRIPTOR (-1)

namespace shm_test {


	class PosixShm {
	public:
		PosixShm(std::string name, int bytes);
		~PosixShm();

	public:

		/**
		* @brief create new shm if it's not exist. link to shm if it's already exist.
		*/
		bool Link();

		/**
		* @brief delete shm object explicity, converse operation of shm_open
		*
		* @note don't need to call this function until you want to delete the shm object
		*/
		void Unlink();

		/**
		* @brief remove the reference of the shm object
		*/
		void UnMap();

	public:
		/**
		* @brief get the shared memory address
		*/
		void* address() { return address_; }

	public:
		void dump() const;

	private:
		void* address_{ nullptr };
		
		int bytes_{ 0 };
		std::string name_;

		int fd_{ INVALID_FILE_DESCRIPTOR };

		int mode_{ S_IRWXU | S_IRWXG | S_IRWXO };
		char err_str_[256]{0};
	};
}
