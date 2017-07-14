# [C/C++] shm_test     
学习使用共享内存在`Linux`上的使用, `shm`即`shared memroy`. 含`Posix Shared Memory`, `System V Shared Memory`, `Boost Shared Memory`等多种接口/使用方式.     


## 目标
- 熟悉`Linux Shared Memory`的原理  
- 熟悉`Posix Shared Memory`, `System V Shared Memory`, `Boost Shared Memory`的常用接口及基本使用  

## 几种方法的主要接口  
- `Posix Shared Memory`  
  - `shm_open`: 创建一个新的共享内存块, 创建后在`tmpfs`中可见且可当做文件操作(创建时传入的name即在`tmpfs`中看到的文件名)       
  - `shm_unlink`: 删除共享内存块     
  - `ftruncate`: 创建后需要用此接口调整`size`      
  - `mmap`: 将`shm_open`创建后的共享内存块映射到进程的虚拟内存地址中. 此接口其实也可以直接映射一个`open`打开的文件到内存中, 从而不需要`read/write`.  
  - `munmap`: 取消映射(不影响共享内存块的存在与否, 仅仅让进程看不到映射而已)     
- `System V Shared Memory`   
  - `shmget`: 创建一个新的共享内存块, 在`tmpfs`中不可见. 以`key`为索引.    
  - `shmat`: 映射`shmget`打开的内存块到进程的虚拟内存地址空间     
  - `shmdt`: 取消映射     
  - `shmctl`: 删除共享内存块, 也可以进行一些其他操作        
- `Boost Shared Memory`    
  - TODO:  


### Reference links   
- [shm_overview - overview of POSIX shared memory](http://man7.org/linux/man-pages/man7/shm_overview.7.html)    
- [svipc - System V interprocess communication mechanisms](http://man7.org/linux/man-pages/man7/svipc.7.html)  
- [boost - Sharing memory between processes](http://www.boost.org/doc/libs/1_55_0/doc/html/interprocess/sharedmemorybetweenprocesses.html#interprocess.sharedmemorybetweenprocesses.sharedmemory.shared_memory_mapping_shared_memory_segments)  
- [两种Linux共享内存](http://blog.jqian.net/post/linux-shm.html)  
- [浅析Linux的共享内存与tmpfs文件系统](http://hustcat.github.io/shared-memory-tmpfs/)  

## TODO:  
- `boost shared memory`    
