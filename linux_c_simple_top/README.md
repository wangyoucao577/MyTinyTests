simple_top.c  
  参考`top`源码实现的简单的`top`, 实现了`system`的详细`cpu`信息刷新，进程和线程的cpu、虚拟内存、实际内存等信息快照的获取. 若需要实现类似`top`的显示所有进程和线程的`cpu`和`memory`占用，则需要将快照进行计算、排序再显示(需要时可实现).  
  此源码基于`procps-ng-3.3.11`和`ncurses-5.9`版本测试, 编译和运行时时需依赖`libncurses.so.5.9`和`libprocps.so.5.0.0`(前述源码的`build`结果), 实现主要基于`libprocps.so`中的`readproc`, `openproc`等接口(使用时注意这几个接口的坑, 已通过注释的形式写在`simple_top.c`文件中).

  编译:
  <pre><code>gcc -lncurses -lprocps simple_top.c -o simple_top</code></pre>

  在`arm linux`嵌入式平台上的交叉编译:
  <pre><code>arm-xilinx-linux-gnueabi-gcc -Llibs -Iinclude -lncurses -lprocps simple_top.c -o simple_top</code></pre>

  运行：
  <pre><code>
./simple_top
./simple_top p
./simple_top H
  </code></pre>

  主要参考:  
  http://www.blogjava.net/fjzag/articles/317773.html  
  http://man7.org/linux/man-pages/man1/top.1.html  
  procps-ng-3.3.11源码
