# [C/C++] shm_test     
学习使用共享内存在`Linux`上的使用, `shm`即`shared memroy`. 含`Posix Shared Memory`, `System V Shared Memory`, `Boost Shared Memory`等多种接口/使用方式.     


## 目标
- 熟悉`Linux Shared Memory`的原理  
- 熟悉`Posix Shared Memory`, `System V Shared Memory`, `Boost Shared Memory`的常用接口及基本使用  

## 几种方法的主要接口  
- `Posix Shared Memory`  
  - `shm_open`: 创建一个新的共享内存块, 创建后在`tmpfs`的挂载目录中可见且可当做文件操作(创建时传入的name即在`tmpfs`中看到的文件名)       
  - `shm_unlink`: 删除共享内存块     
  - `ftruncate`: 创建后需要用此接口调整`size`      
  - `mmap`: 将`shm_open`创建后的共享内存块映射到进程的虚拟内存地址中. 此接口其实也可以直接映射一个`open`打开的文件到内存中, 从而不需要`read/write`.  
  - `munmap`: 取消映射(不影响共享内存块的存在与否, 仅仅让进程看不到映射而已)     
- `System V Shared Memory`   
  - `shmget`: 创建一个新的共享内存块, 在`tmpfs`的挂载目录中不可见. 以`key`为索引.    
  - `shmat`: 映射`shmget`打开的内存块到进程的虚拟内存地址空间     
  - `shmdt`: 取消映射     
  - `shmctl`: 删除共享内存块, 也可以进行一些其他操作        
- `Boost Shared Memory`    
  - TODO:  

## 编译运行  
- 实验平台
    - `CentOS7 64bit, 3.10.0-229.el7.x86_64`
- compile  
```
cd build/linux/
cmake ../../
make
```
- run  
```
./shm link
./shm unlink
./shm link read
./shm link write 12345
```
- 生成vs工程方便coding(On windows)
```
cd build/win32/  
cmake ../../  
```  

## 原理及比较    
- `Linux`较新版本上现在默认会创建`tmpfs`并挂载到`/dev/shm`(不同发行版可能不同, 本实验中是这个), 由名字即可看出, 相当于用内存做了一个临时的高速磁盘/文件系统, 操作这上面的文件即操作内存中的文件, 方便提升速度  
- `Posix`接口相对`SystemV`的接口较新一些, 而由于其创建的共享内存块在`/dev/shm`直接可见, 也更方便调试/分析; 反之`SystemV`创建的共享内存块更类似于匿名的.  
- `Posix`接口中`name`是共享内存块的唯一标识, `SystemV`接口中唯一标识则是一个`key_t`的结构.      

## 应用  
- ramdisk  
    - 进程中需要处理一些大文件或者频繁读写时, 读写磁盘的效率会比较低, 且一直需要`read/write`. 需要提升性能时, 可以把文件拷贝到`tmpfs`(默认即`/dev/shm`目录下), 然后直接把文件通过`mmap`映射到进程的虚拟内存地址空间中, 进程只当做操作内存即可.  
- 进程间通信  
    - 共享内存也是进程间通信的一种典型方式, 可以由任意进程之间共享数据  
    - 共享内存用作进程间通信时, 没有同步机制, 需要开发者自行实现这块内存的读写同步, 逻辑上相对会比较复杂, 容易出问题   

### Reference links   
- [shm_overview - overview of POSIX shared memory](http://man7.org/linux/man-pages/man7/shm_overview.7.html)    
- [svipc - System V interprocess communication mechanisms](http://man7.org/linux/man-pages/man7/svipc.7.html)  
- [boost - Sharing memory between processes](http://www.boost.org/doc/libs/1_55_0/doc/html/interprocess/sharedmemorybetweenprocesses.html#interprocess.sharedmemorybetweenprocesses.sharedmemory.shared_memory_mapping_shared_memory_segments)  
- [两种Linux共享内存](http://blog.jqian.net/post/linux-shm.html)  
- [浅析Linux的共享内存与tmpfs文件系统](http://hustcat.github.io/shared-memory-tmpfs/)  
- [Boost IPC共享内存的使用总结](https://my.oschina.net/lday/blog/724458)

## TODO:  
- `boost shared memory`    
