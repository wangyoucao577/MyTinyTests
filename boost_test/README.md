# boost_test   
学习及尝试`boost`库, 熟悉其behavior及原理.  

## 实验环境
- `Linux`:    
	- `Ubuntu 18.04 LTS`: `WSL(Windows Subsystem for Linux) on Win10 1803-17134.228`    
	- `cmake version 3.10.2`    
	- `gcc (Ubuntu 7.3.0-16ubuntu3) 7.3.0`    
	- `boost 1_65_1`(`sudo apt-get install libboost-all-dev`)    

### 编译运行
- `Linux`:    
注: 大部分`boost`库的内容直接通过`.h`引用即可, 少部分需要链接使用.    
	```   
	mkdir -p build/linux
	cd build/linux
	cmake ../../
	cmake --build . -- -j
	./boost_test
	```   

## 代码说明   
- main.cc  
测试入口及代码.  


## Reference Link:  
- [Getting Started on Unix variants (e.g. Linux, MacOS)](http://www.boost.org/doc/libs/1_64_0/more/getting_started/unix-variants.html)  

### Contacts   
Author's Email: wangyoucao577@gmail.com.
