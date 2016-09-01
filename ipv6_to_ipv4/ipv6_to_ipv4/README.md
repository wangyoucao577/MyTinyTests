### [C] ipv6_to_ipv4

核心文件为ipv6_to_ipv4_interface.c, 其中封装了`easy_getaddrinfo`, `ip_str_family`, `inet_ntop_ipv4_ipv6_compatible` 三个典型接口(support Windows, Linux, iOS and Android), 同时实现了`iOS`上获取本地网卡ip地址的`get_local_net`(support Linux, iOS and Android)函数, 可供实际业务中需要时参考.
由于`iOS`上架Apple Store必须要支持`IPv6 only`, 故研究了下`ipv4`和`ipv6`兼容的实现方法, 其核心即为`getaddrinfo`函数. 此函数个人认为非常复杂，难以理解. 同时也由于测试环境的限制(仅有普通的`IPv4 only`环境和`mac OSX`模拟的支持`NAT64`的`IPv6 only`环境), 故也无法测试所有的条件以明确此函数的行为. 在有限的条件下, 封装了相对简单的`easy_getaddrinfo`接口供使用. 

