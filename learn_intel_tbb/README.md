# Learn Intel TBB
学习 [Intel - Threading Building Blocks (TBB)](https://software.intel.com/en-us/tbb-documentation) 的基本概念和使用. 其提供的通用算法可参考 [Tutorial: Generic Parallel Algorithms](https://www.threadingbuildingblocks.org/tutorial-intel-tbb-generic-parallel-algorithms), 思路非常的 **map&reduce**.       

## 实验环境
- `Linux`:    
    - `Ubuntu 18.04 LTS`(`WSL(Windows Subsystem for Linux) on Win10 1803-17134.228`)    
    - `cmake version 3.10.2`    
    - `gcc (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0`    
    - `GNU gdb (Ubuntu 8.1-0ubuntu3) 8.1.0.20180409-git`    
    - [Threading Building Blocks 2019 Update 2](https://github.com/01org/tbb/releases/tag/2019_U2)    

## 实验代码   
- 运行    
```bash
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ../            # or `cmake -DCMAKE_BUILD_TYPE=Debug ../`
$ cmake --build .
```

`$ ./parallel_for_test`    
or     
`$ ./parallel_reduce_test`    

## 原理理解及使用说明     
### Gereric Parallel Algorithms
The [Structured Parallel Programming](http://parallelbook.com/) book by McCool, Robison and Reinders describes a number of useful parallel patterns. Intel TBB algorithms maps to those patterns as follows:

- `parallel_for`: map
- `parallel_reduce`, `parallel_scan`: reduce, scan
- `parallel_do`: workpile
- `parallel_pipeline`: pipeline
- `parallel_invoke`, `task_group`: fork-join
- `flow_graph`: plumbing for reactive and streaming apps


#### `tbb::parallel_for`
- 设计上借鉴的即是 [MapReduce](https://en.wikipedia.org/wiki/MapReduce) 中的`Map`的概念. 基本思路即是输入一个可拆分的任务(通过`tbb::blocked_range<>`来描述任务范围以及是否可拆分), 函数内部自动进行拆分并通过不同的线程来运行, 从而达到并发的目的.      
- 基于`lambda`来实现`tbb::parallel_for`的调用, 可以简化掉仿函数, 简洁不少.    

#### `tbb::parallel_reduce`
- 设计上借鉴的即是 [MapReduce](https://en.wikipedia.org/wiki/MapReduce) 的概念. 基本思路即是输入一个可拆分的任务(通过`tbb::blocked_range<>`来描述任务范围以及是否可拆分), 函数内部自动进行拆分并通过不同的线程来运行, 从而达到并发的目的. 并发的子任务都运行完成后, 通过自定义的仿函数类中的`join()`函数来实现`reduce`的动作.       
- 基于`lambda`来实现`tbb::parallel_reduce`的调用, 可以简化掉仿函数, 简洁不少.    



## References 
- [Official Intel(R) Threading Building Blocks (Intel TBB) GitHub repository](https://github.com/01org/tbb)
- [Official Intel(R) Threading Building Blocks (Intel TBB) Main Page](https://www.threadingbuildingblocks.org/)
- [tbb2019_20181010oss](./modules/tbb2019_20181010oss/README.md)
- [Threading Building Blocks 2019 Update 2](https://github.com/01org/tbb/releases/tag/2019_U2)  
- [Intel - Threading Building Blocks (TBB)](https://software.intel.com/en-us/tbb-documentation) 
- [Tutorial: Generic Parallel Algorithms](https://www.threadingbuildingblocks.org/tutorial-intel-tbb-generic-parallel-algorithms)
- [MapReduce](https://en.wikipedia.org/wiki/MapReduce)