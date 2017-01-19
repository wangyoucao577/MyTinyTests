# [C++] Mars_test
学习并尝试试用Tencent刚刚开源的Mars库.  
Commit:
1198080f4cc0809299a9494418a1dfcab0765bb9 [1198080]
  

## xlog_test
- 关注点
	- xlog的接口如何使用
	- xlog的性能如何, 是否能够支撑非常频繁的调试日志打印  
	- xlog输出的日志是否能够方便的被分析
	- xlog是否可以支持全平台
	
- 核心文件  
	- xlog_test.cc/h  
	简单封装下`xlog`初始化和反初始化的接口, 及一些test case, 便于统一调用.  
	
	- test project  
		- iOS: `xlog_test.xcodeproj`  
		
		
- 目前遇到的问题
	- [vs2105编译不过](https://github.com/Tencent/mars/issues/47)  
		Mars团队解决中...
		
	- [xlog在iOS上测试频繁调用时cpu占用过高](https://github.com/Tencent/mars/issues/104)  
		已解决. 研究下来发现主要问题出在`NSLog`的消耗太高. 将`NSLog`改为`fprintf(stdout...)`则CPU占用率明显下降.  
		
	- [不支持linux](https://github.com/Tencent/mars/issues/54)  
		Mars团队Won't Fix!!! What the fuck!  
		
- 优劣势分析(个人观点)
	- xlog的优势
		- 经过微信考验的成熟日志方案, 且开源
		- 接口简单, 使用方便
		- 支持压缩
		- 支持加密
		- 支持时间范围外的日志清理, 便于作为基本的运行日志
		- 支持iOS、Android、Windows、MacOSX
		- 加TAG方便, 工程中定义XLOGGER_TAG宏即可
		- 支持Sync/Async输出
		- 支持方便的修改输出字符串的格式(修改formater.cc的实现)
		- 牛逼的调用方式
			- 类型安全检测方式：%s %d 。例如：xinfo(“%s %d”, “test”, 1)
			- 序号匹配的方式：%0 %1 。例如：xinfo(TSF”%0 %1 %0”, “test”, 1)
			- 智能匹配的懒人模式：%_  。例如：xinfo(TSF”%_ %_”, “test”, 1)

		
	- xlog的不足
		- 不支持Linux
		- 全局日志, 不支持实例化
		- 不支持filter TAG过滤后输出
		- 不支持单条日志指定output target(如仅输出到FILE, or输出到FILE&CONSOLE)
		
		
- 其他杂项

## 读Mars源码
### xlog 
- 核心文件
	- appender.h/cc  
		初始化/析构日志需要调用的接口, 同时包含了xlog文件创建/删除/超时清理/写Console/写File等逻辑。  
		
		- `appender_set_console_log`  
			是否打开Console日志的开关.
			
		- `appender_open`, `appender_close`  
			xlog初始化/析构.
		
		- `xlogger_appender`  
			每次调用`xverbose2/xdebug2...`接口写日志时, 将要调用的具体实现(在`xloggebase.c`文件的`__xlogger_Write_impl`中调用). 在此函数中调用写Console/File.  
			
		- `__async_log_thread`  
			日志异步写文件的线程, 等待通知(出现FATAL错误or攒了50KB) or 超时(Default: 15min)写一次文件.  
			
	- xlogger.h  
		该文件包含打印日志最常调用的接口。  
		`xverbose2/xdebug2/xinfo2/xwarn2/xerror2/xfatal2...`  
		通过一堆Macro把这堆开放的接口最终映射到`xloggerbase.h/c`文件中的`xlogger_Write`接口.   
		NOTE: 据说用到了`meta programming`, 看的不是很明白.暂不再深入. 

	- xloggerbase.h/c  
		提供xlog设置LogLevel的接口, 及内部的`xlogger_Write`等实现(实际最终还是调用到`appender.cc`文件中的`xlogger_appender`).   
		
	- formater.cc
		输出日志字符串的格式化. 若需要修改为自定义格式以适应日志分析, 可在此处修改.  
		
	- log_buffer.h/cc  
		日志缓存的buffer结构, 在其`Write`接口中调用了压缩(调用`zlib`)、加密(调用`log_crypt.h/cc`中的接口)等功能
		
	- log_crypt.h/cc  
		提供加密功能的代码. 使用者可覆盖此`log_crypt.cc`文件的实现以实现自己的加密方式. 目前的版本默认是无加密的.  


## Reference Links
- [Mars on Github](https://github.com/Tencent/mars)  
- [Mars Wiki](https://github.com/Tencent/mars/wiki)  
- [Mars iOS/OS X 接入指南](https://github.com/Tencent/mars/wiki/Mars-iOS%EF%BC%8FOS-X-%E6%8E%A5%E5%85%A5%E6%8C%87%E5%8D%97)  
- [Mars iOS/OS X 接口详细说明](https://github.com/Tencent/mars/wiki/Mars-iOS%EF%BC%8FOS-X-%E6%8E%A5%E5%8F%A3%E8%AF%A6%E7%BB%86%E8%AF%B4%E6%98%8E)  
- [xlog在iOS上测试频繁调用时cpu占用过高](https://github.com/Tencent/mars/issues/104)
- [NSLog效率低下的原因及尝试lldb断点打印Log](http://blog.sunnyxx.com/2014/04/22/objc_dig_nslog)
- [不支持linux](https://github.com/Tencent/mars/issues/54)
- [vs2105编译不过](https://github.com/Tencent/mars/issues/47)
- [微信终端跨平台组件 mars 系列（一） - 高性能日志模块xlog](http://mp.weixin.qq.com/s/cnhuEodJGIbdodh0IxNeXQ)  

### Contacts
Author's Email: wangyoucao577@gmail.com.
