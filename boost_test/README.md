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
- `main.cc`     
测试入口及代码.  

- `heaps_tests.h/cc`    
	- 尝试下`std::priority_queue`和`boost::heap::d_ary_heap`的使用.     
	- `std::priority_queue`与`boost::heap::d_ary_heap`同样都是基于`heap`实现. `std::priority_queue`是二叉堆, 仅提供了`push()/top()/pop()`这三个常用接口, 其内部是基于`std::make_heap/push_heap/pop_heap`来实现.     
	- 与之区别的是, `boost::heap::d_ary_heap`可支持`d-ary`堆, 其中`d`设为`2`时得到的即是二叉堆. 并且`boost::heap::d_ary_heap`除了`push()/top()/pop()`这三个基本接口外, 还提供了`increase()/update()/decrease()/erase()`这几个修改`key`的接口, 可满足更多的应用场景.    
	- 另外需要注意的是, `std::priority_queue`与`boost::heap::d_ary_heap`在处理重复的`key`时行为刚好相反. 两者都可以支持重复`key`的插入, 但在弹出时会是相反的顺序弹出. 在直接替换时需要注意下, 理论上不应该影响使用者.     


## Reference Link:  
- [Getting Started on Unix variants (e.g. Linux, MacOS)](http://www.boost.org/doc/libs/1_64_0/more/getting_started/unix-variants.html)    
- https://www.boost.org/doc/libs/1_63_0/doc/html/heap.html
- https://www.boost.org/doc/libs/1_63_0/doc/html/heap/data_structures.html    
- https://www.boost.org/doc/libs/1_63_0/doc/html/heap/concepts.html
- https://www.boost.org/doc/libs/1_63_0/doc/html/boost/heap/d_ary_heap.html
- https://www.boost.org/doc/libs/1_63_0/doc/html/boost/heap/fibonacci_heap.html
- http://www.cplusplus.com/reference/queue/priority_queue/

### Contacts   
Author's Email: wangyoucao577@gmail.com.
