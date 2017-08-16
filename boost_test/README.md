# boost_test   
学习及尝试`boost`库, 熟悉其behavior及原理.  

## 编译运行
- `Windows`:  
TODO   

- `Linux`:   
		`CentOS7 64bit, Kernel 3.10.0-229.el7.x86_64, gcc 4.8.5 20150623`   

	- 编译运行代码   
	注: 大部分`boost`库的内容直接通过`.h`引用即可, 但有部分需要链接使用的, 需提前编译安装至`/usr/local/boost_1_64_0/lib/`中   
	```   
	mkdir build
	cd build
	mkdir linux  
	cd linux
	cmake ../../
	make
	./boost_test
	```   

## 代码说明   
- main.cc  
测试入口及代码.  


## Reference Link:  
- [Getting Started on Unix variants (e.g. Linux, MacOS)](http://www.boost.org/doc/libs/1_64_0/more/getting_started/unix-variants.html)  

### Contacts   
Author's Email: wangyoucao577@gmail.com.
