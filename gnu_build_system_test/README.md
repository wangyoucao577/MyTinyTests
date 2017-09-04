# [Autotools/C++] gnu_build_system_test  
学习使用 The GNU Build System 并理解其原理. 即使用 `Autotools`相关工具, 以生成跨平台的编译系统. 工具包括`autoconf/autoheader/automake/autoreconf/aclocal/...`等.   


# 实验运行
- 实验平台  
  - `Linux`: `CentOS7 64bit`, `Kernel 3.10.0-229.el7.x86_64`, `gcc 4.8.5 20150623`  

  - `configure`,`Makefile`, `config.h`生成过程  

<pre><code>  
\# 根据 configure.ac 中的宏需求, 生成相关的 m4 依赖  
aclocal

\# configure.ac --> configure  
autoconf

\# 生成 config.h.in  
autoheader

\# Makefile.am --> Makefile.in  
automake -i

mkdir _build/
</code></pre>  
或者
<pre><code>
./autogen.sh
</code></pre>
  - 编译运行  
  <pre><code>
  cd _build/

  \# 检测配置编译环境的同时, config.h.in --> config.h, Makefile.in --> Makefile
  ../configure


  make
  ./hello
  </code></pre>


### Reference links   
  - [Very Good Tutorial for beginners](http://markuskimius.wikidot.com/programming:tut:autotools)  
  - http://autotoolset.sourceforge.net/tutorial.html  
  - https://www.gnu.org/software/autoconf/manual/autoconf.html  

### Contacts
  Author's Email: wangyoucao577@gmail.com.
