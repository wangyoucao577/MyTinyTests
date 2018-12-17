# Test shared_ptr
学习`shared_ptr`的使用和注意事项, 以及比较`std::shared_ptr<T>`, `boost::shared_ptr<T>`在不同场景下的表现.        

## 实验环境
- `Linux`:    
    - `Ubuntu 18.04 LTS`(`WSL(Windows Subsystem for Linux) on Win10 1803-17134.228`)    
    - `cmake version 3.10.2`    
    - `gcc (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0`    
    - `GNU gdb (Ubuntu 8.1-0ubuntu3) 8.1.0.20180409-git`    
    - `Boost version: 1.65.1`

## 实验过程   

### `Release`编译, 并关闭编译器优化(`-O0`)   
```bash
$ mkdir build
$ cd build
$ cmake ../            
$ cmake --build .
$
$ ./test_std_shared_ptr 
test_case_pass_shared_ptr ---> 0.633972 seconds, 0.353455 seconds, 0.62363 seconds.
test_case_access_value ---> 0.0417496 seconds, 0.11343 seconds
$
$ ./test_boost_shared_ptr 
test_case_pass_shared_ptr ---> 0.412738 seconds, 0.227477 seconds, 0.430141 seconds.
test_case_access_value ---> 0.0414274 seconds, 0.0603911 seconds
$
```

- 数据解释    
```bash
test_case_pass_shared_ptr ---> {(a) 传值方式传递shared_ptr} seconds, 
                               {(b) 传引用方式传递shared_ptr} seconds, 
                               {(c) 传引用方式传递shared_ptr, 但其指向的类型由 T 传递给了 const T } seconds.
test_case_access_value ---> {(d) 通过原生指针直接访问对象内容} seconds, {(e) 通过shared_ptr访问对象内容} seconds
```

- test_case_pass_shared_ptr    
    - 对于这个test case来说, 不论是`std::shared_ptr`还是`boost::shared_ptr`, 表现出的趋势都是(a)和(c)的值相对很接近, (b)的值约为一半的值. 如下分析:      
      - (a)中每次循环存在两次`shared_ptr`的拷贝, 一次是`pass by value`给构造函数, 一次是构造函数中通过函数参数去构造对象中的成员变量`shared_ptr`;    
      - (b)中传递`const shared_ptr<T> &`不需要额外的一次`shared_ptr`拷贝. 所以这里仅一次`shared_ptr`的拷贝, 即在构造函数中通过函数参数构造对象中的成员变量`shared_ptr`时;    
      - (c)中传递`const shared_ptr<const T> &`, 虽然是引用传递, 但由于外部调用时原来的`shared_ptr`类型为`shared_ptr<T>`, 其并不能赋值给`shared_ptr<const T>`, 所以这里先要存在一次`shared_ptr`的拷贝构造(可参考 [Difference between `const shared_ptr<T>` and `shared_ptr<const T>`?
](https://stackoverflow.com/questions/17793333/difference-between-const-shared-ptrt-and-shared-ptrconst-t) ); 然后另一次同上也是在构造函数中通过函数参数构造成员变量`shared_ptr`时; 共2次拷贝.    
      - 所以, 会出现测试数据中的约`2:1:2`的结果.     
    - 对于为什么`shared_ptr`的拷贝开销这么大的问题    
      - 首先, `shared_ptr`并不仅仅是一个简单的4字节或8字节的指针, 而是一个`object`;    
      - 既然是`object`, 那么拷贝就涉及到构造和析构的开销. 更主要的应当是`shared_ptr`内部的引用计数的维护开销(原子操作), 在频繁操作时会显得很大. 而通过`const shared_ptr<T> &`来传递, 即显式地不用去触发引用计数的维护, 从而能够明显地降低开销.     

- test_case_access_value    
    - 理论上来讲, 通过`shared_ptr`来访问对象的内容和通过原生指针来访问对象的内容, 并没有什么不同. 最多也就是前者多了一步函数调用, 在`shared_ptr`的`operator->()`中先调用内部函数获得原生指针, 不应当有如此大的差距.    

### `Release`编译, 并打开编译器优化(`-O3`)    
```bash
$ # 首先修改 CMakeLists.txt 中的 -O0 ==> -O3 
$
$ mkdir build
$ cd build
$ cmake ../            
$ cmake --build .
$
$ ./test_std_shared_ptr 
test_case_pass_shared_ptr ---> 0.0133012 seconds, 0.002437 seconds, 0.0129323 seconds.
test_case_access_value ---> 8e-07 seconds, 5e-07 seconds
$
$ ./test_boost_shared_ptr 
test_case_pass_shared_ptr ---> 0.166111 seconds, 0.0827962 seconds, 0.164819 seconds.
test_case_access_value ---> 8e-07 seconds, 0.0022888 seconds
$
```

- test_case_pass_shared_ptr
  - 即使打开了编译器优化之后, 约`2:1:2`的趋势仍然比较明显, 尤其是`boost::shared_ptr`.    
  - `std::shared_ptr`优化后的拷贝开销明显比`boost::shared_ptr`少了一个数量级;    
  - `std::shared_ptr`的`pass by reference`优化后的效率也明显很高;    
  - 从绝对值上来看, 编译器优化的作用还是非常明显的, 尤其是针对`std::shared_ptr`, 开销直接降低了1~2个数量级.    

- test_case_access_value
  - 经过编译器优化之后, 这个测试数据基本上可以忽略不计了.    

### 结论
- 在需要频繁传递的场景下, `shared_ptr`还是会存在比较明显的性能问题. 在性能资源比较紧张时需要重视. 
  - 发现这个问题是在`QNX 6.5.0`平台下, 因为一处`shared_ptr`频繁拷贝传递导致了整体系统的性能下降约10%.      
- 在我的测试环境下, 编译器优化的作用非常明显, 并且`std::shared_ptr`的性能也明显好于`boost::shared_ptr`.    
- 不同平台/系统的表现可能不同, 必要时应实际平台上测试后再得出对应的结论.    


## References 
- https://zh.cppreference.com/w/cpp/memory/shared_ptr
- https://zh.cppreference.com/w/cpp/memory/shared_ptr/make_shared
- [Difference between `const shared_ptr<T>` and `shared_ptr<const T>`?
](https://stackoverflow.com/questions/17793333/difference-between-const-shared-ptrt-and-shared-ptrconst-t)
- [Passing const shared_ptr<T>& versus just shared_ptr<T> as parameter](https://stackoverflow.com/questions/37610494/passing-const-shared-ptrt-versus-just-shared-ptrt-as-parameter)
- [GotW #91 Solution: Smart Pointer Parameters](https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/)
- [Wow: shared_ptr is very slow, is there an alternative?](https://www.reddit.com/r/cpp/comments/r5phm/wow_shared_ptr_is_very_slow_is_there_an/)
- [shared_ptr: horrible speed](https://stackoverflow.com/questions/3628081/shared-ptr-horrible-speed)
- [Const reference as class member](https://stackoverflow.com/questions/15513734/const-reference-as-class-member)


