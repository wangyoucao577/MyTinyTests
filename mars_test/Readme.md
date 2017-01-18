# [C++] Mars_test
学习并尝试试用Tencent刚刚开源的Mars库.  
Commit:
bb793a0bed547ed6be8c57cedc7121f51880da9b [bb793a0]
  

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
		Mars团队分析中...
		
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
		
	- xlog的不足
		- 不支持Linux
		- 全局日志, 不支持实例化
		- 不支持filter TAG过滤后输出
		- 不支持单条日志指定output target(如仅输出到FILE, or输出到FILE&CONSOLE)
		- 频繁调用时貌似CPU占用过高
		
		
- 其他杂项

## Mars源码记要

## Reference Links
- [Mars on Github](https://github.com/Tencent/mars)  
- [Mars Wiki](https://github.com/Tencent/mars/wiki)  
- [Mars iOS/OS X 接入指南](https://github.com/Tencent/mars/wiki/Mars-iOS%EF%BC%8FOS-X-%E6%8E%A5%E5%85%A5%E6%8C%87%E5%8D%97)  
- [Mars iOS/OS X 接口详细说明](https://github.com/Tencent/mars/wiki/Mars-iOS%EF%BC%8FOS-X-%E6%8E%A5%E5%8F%A3%E8%AF%A6%E7%BB%86%E8%AF%B4%E6%98%8E)  
- [xlog在iOS上测试频繁调用时cpu占用过高](https://github.com/Tencent/mars/issues/104)

### Contacts
Author's Email: wangyoucao577@gmail.com.
