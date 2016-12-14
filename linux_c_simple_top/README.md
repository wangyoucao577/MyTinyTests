## simple_top.c  
  参考`top`源码实现的简单的`top`, 实现了`system`的详细`cpu`信息刷新，进程和线程的cpu、虚拟内存、实际内存等信息快照的获取. 若需要实现类似`top`的显示所有进程和线程的`cpu`和`memory`占用，则需要将快照进行计算、排序再显示(需要时可实现).  
  此源码基于`procps-ng-3.3.11`和`ncurses-5.9`版本测试, 编译和运行时时需依赖`libncurses.so.5.9`和`libprocps.so.5.0.0`(前述源码的`build`结果), 实现主要基于`libprocps.so`中的`readproc`, `openproc`等接口(使用时注意这几个接口的坑, 已通过注释的形式写在`simple_top.c`文件中).

#### 编译:
  <pre><code>//依赖procps-ng
gcc -lncurses -lprocps simple_top.c -o simple_top

//不依赖prcops-ng, 仅支持总的cpu统计和读取/proc/[pid]/stat计算的进程cpu统计
gcc -m32 -DWITHOUT_LIBPROCPS simple_top.c -o simple_top
</code></pre>

#### 在`arm linux`嵌入式平台上的交叉编译:
  <pre><code>//依赖procps-ng
arm-xilinx-linux-gnueabi-gcc -Llibs -Iinclude -lncurses -lprocps simple_top.c -o simple_top

//不依赖prcops-ng, 仅支持总的cpu统计和读取/proc/[pid]/stat计算的进程cpu统计
arm-none-linux-gnueabi-gcc -DWITHOUT_LIBPROCPS simple_top.c -o simple_top</code></pre>

#### 运行：
  <pre><code>
./simple_top
./simple_top -p pid
./simple_top p
./simple_top H
  </code></pre>

## Links
- http://stackoverflow.com/questions/17359517/how-can-i-properly-free-memory-when-using-libproc
- http://unix.stackexchange.com/questions/58539/top-and-ps-not-showing-the-same-cpu-result
- http://stackoverflow.com/questions/41134205/different-processs-cpu-output-via-top-from-busybox-and-procps-ng
- https://gitlab.com/procps-ng/procps/issues/48
- http://www.cnblogs.com/westfly/p/4230956.html
- http://www.blogjava.net/fjzag/articles/317773.html    
- http://man7.org/linux/man-pages/man1/top.1.html  
- http://www.linuxhowtos.org/manpages/5/proc.htm
- procps-ng-3.3.11源码
- busybox-1.3.2源码
