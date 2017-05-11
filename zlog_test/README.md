# zlog_test  
`C`实现的轻量级日志库`zlog`的使用学习及尝试.   

## 使用简介     
- 编译`zlog`的输出  
  - zlog.h  
  - libzlog.a    
  - libzlog.so    
  - zlog-chk-conf  
    检查zlog配置文件是否正确的小工具  

- 使用  
  - `#include "zlog.h"`  
  - 链接时加上 ` -pthread -lzlog`  
  - 程序中调用`zlog_init/zlog_get_category/dzlog_init`等接口初始化后即可调用接口  
  - 可用接口包括`zlog_fatal/error/warn/notice/info/debug`及简化版(忽略Category)的`dzlog_fatal/...`接口   
  - 程序结束时调用 `zlog_fini`清理内存   

- 配置  
  - 通过`*.conf`文件来配置`zlog`的行为, 支持输出到`std/syslog/file/...`等, 支持定义格式等. 详见 [zlog使用手册](https://hardysimpson.github.io/zlog/UsersGuide-CN.html#htoc1)

## 编译运行   
`g++ main.cc -L. -pthread -lzlog`  
or   
`g++ dzlog_main.cc -L. -pthread -lzlog`   
`./a.out`

## 优劣势分析(个人观点)  
- 优势   
  - 纯`C`实现, 仅依赖`pthread`, 便于集成   
  - 轻量级, 使用简单, 功能强大  
  - 高性能(未测试), 在一些性能不足的平台/日志量特别大时上非常重要   

- 劣势  
  - 不支持以时间/大小的fsync(目前仅支持按日志行数), 比较不方便   
  - 不支持跨平台  
    - 目前原生为Linux(包括Unix系系统)   
    - 看到过有`Winzlog`的实现, 待尝试  
    - 貌似没看到有`iOS/Android`的支持   
    - 或者其实是`C`代码，只是差个跨平台的构建?   


### Reference Links  
- https://github.com/HardySimpson/zlog  
- [zlog使用手册](https://hardysimpson.github.io/zlog/UsersGuide-CN.html#htoc1)  
