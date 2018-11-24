# Learn Intel TBB
学习 [Intel - Threading Building Blocks (TBB)](https://software.intel.com/en-us/tbb-documentation) 的基本概念和使用.     

## 实验环境
- `Linux`:    
    - `Ubuntu 18.04 LTS`(`WSL(Windows Subsystem for Linux) on Win10 1803-17134.228`)    
    - `cmake version 3.10.2`    
    - `gcc (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0`    
    - `GNU gdb (Ubuntu 8.1-0ubuntu3) 8.1.0.20180409-git`    
    - [Threading Building Blocks 2019 Update 2](https://github.com/01org/tbb/releases/tag/2019_U2)    

## 实验代码   
- 运行    
```
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ../            # or `cmake -DCMAKE_BUILD_TYPE=Debug ../`
$ cmake --build .
$ ./learn_intel_tbb
```