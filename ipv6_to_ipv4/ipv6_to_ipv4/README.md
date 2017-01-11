# [C] ipv6_to_ipv4

由于`iOS`上架Apple Store必须要支持`IPv6 only`, 故研究了下在`iOS`上标准`C`调用底层`socket`实现网络通信时`ipv4`和`ipv6`兼容的实现方法, 同时为保证移植性, 在`Linux`, `Windows` 和`Android`上也都相应进行了实验.

## 核心文件
- ipv6_to_ipv4_interface.c

## 全平台支持的几个典型接口

tested on iOS, Android, Linux and Windows

- `easy_getaddrinfo`  

此接口核心为`getaddrinfo`函数, Apple推荐使用底层`socket`的开发者使用此`getaddrinfo`函数来实现`ipv4`和`ipv6`的全面兼容. 但个人认为此函数过于复杂，难以理解. 而测试其行为又需要各种环境. 故由于测试环境的限制(仅有普通的`IPv4 only`环境和`mac OSX`模拟的支持`NAT64`的`IPv6 only`环境), 在有限的条件下, 测试其行为并封装了相对简单的`easy_getaddrinfo`接口以供更方便地使用.

- `ip_str_family`

根据`IP Address String`分析其为`AF_INET` or `AF_INET6`.

- `inet_ntop_ipv4_ipv6_compatible`   

## 获取本地网卡ip地址的接口

- `get_local_net`    
`get_local_net`依赖于系统函数`getifaddrs`实现.   
Tested on iOS, Linux and Android (Unavailable on Windows).   
详情见如下"`getifaddrs`支持情况不同"节.   

## test project
#### Linux
`gcc ipv6_to_ipv4_interface.c`  
`./a.out`

#### Windows
- 如果你有`Visual Studio 2015`  
打开`ipv6_to_ipv4.sln`，编译运行即可

- 如果你仅有其他版本的`Visual Studio`  
新建空的Win32控制台项目，添加`ipv6_to_ipv4_interface.c`和`ipv6_to_ipv4_interface.h`两个文件即可，同时项目配置中新增`Ws2_32.lib`链接库，enjoy yourself!

#### iOS
打开`ipv6_to_ipv4_ios.xcodeproj`, `Run`即可(接好你的`iOS`设备)

#### Android
//TODO:

## 各平台上的不同
#### AF_INET6值的定义
- iOS:     
#define AF_INET6 30  
- Linux, Android:   
#define AF_INET6 10  
- Windows:  
#define AF_INET6 23

#### ipv4->ipv6 map的行为不同
- iOS:  
在ipv4地址前追加了` 64:ff9b::`   (RFC 6146 、RFC 6147)  

- Linux, Windows:  
都是在ipv4地址前追加了 ` ::ffff:`,  所以即使连接上mac的NAT64, 也无法通过其访问外网 (RFC 4291)

正因为此，相当于mac OSX share出来的NAT64，仅Apple自己的设备可用...

#### getaddrinfo行为不同
这个接口在各个平台上都有些不同的参数、行为，本身功能设计也很复杂，应仔细弄清楚其行为再使用.

- iOS, Linux:   
在Local ipv6(NAT64) 时，输入为ipv4时可自动map成ipv6的地址输出，以供connect调用.  

- Windows:  
貌似不支持AI_V4MAPPED参数. 虽然MSDN online上有写此参数, 但实验结果却未进行转换. 也可能因为测试代码依赖、宏等定义问题，从而没生效. 不明白为何如此，甚至在C#中也没找到对应的可自动map的接口. (也不排除在windows上的使用还有些问题...)

#### getifaddrs支持情况不同
`get_local_net`依赖于此`getifaddrs`系统函数实现. 
  
- iOS, Linux:   
  可原生支持此接口, 以遍历获取系统上的`addrs`信息.    
  
- Android:   
  底层未提供此`C`接口, 需要自己实现. 网上有一些实现(`github`上可以搜到一些`ifaddrs`的`android`实现, 以及`webrtc`中有一份`ifaddrs-android.h/cc`的`c++`实现), 需要时可参考尝试.(个人仅做了非常简单的尝试, 试了`github`上的几个和`webrtc`的`getifaddrs`实现, 都还有些问题, 暂未深入下去. 有机会再深入尝试下.)  
  NOTE: `Android API`中也有提供上层的`NetworkInterface`相关, 可实现此功能. 故也不一定需要使用底层`API`上来实现. 用上层`Java API`也不失为一个选择.  
   
- Windows:  
  //TODO:   

## 补充
- 测试UDP时发现TTL的值IPV6没有，参考 http://www.jianshu.com/p/a6bab07c4062 应适应如下  
`setsockopt(send_sock, IPPROTO_IPV6, IPV6_UNICAST_HOPS, &ttl, sizeof(ttl))`  
`setsockopt(send_sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl))`

- find_ipv6_incompatible.sh  
搜索代码中是否存在`ipv6`不兼容的接口的一个脚本, 默认搜索当前目录的`trunk`路径下的代码.

- 

## Reference Links
- https://en.wikipedia.org/wiki/IPv6#Address_representation  
- https://developer.apple.com/library/ios/documentation/NetworkingInternetWeb/Conceptual/NetworkingOverview/UnderstandingandPreparingfortheIPv6Transition/UnderstandingandPreparingfortheIPv6Transition.html  
- https://github.com/WeMobileDev/article/blob/master/IPv6%20socket%E7%BC%96%E7%A8%8B.md  
- https://msdn.microsoft.com/en-us/library/system.net.ipaddress.maptoipv4(v=vs.110).aspx  
- http://stackoverflow.com/questions/37386161/service-port-is-missed-when-using-getaddrinfo-to-convert-ipv4-addr-to-ipv6-addr  
- http://stackoverflow.com/questions/17833765/detect-temporary-ipv6-address-crossplatform  
- http://www.jianshu.com/p/a6bab07c4062

### Contacts
Author's Email: wangyoucao577@gmail.com.
