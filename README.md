# MyTinyTests
Just use to store my tiny test src files and solutions, may contains python, c#, c/c++ or something else.

# 说明

### CheckGateway

基于C#的Console, 检查本机Gateway设置. 网络初学者经常会出现误设置多个网关导致一些网络异常的情况，此小工具可检查本机Gateway设置是否仅为一条，若为一条则认为设置正确，否则提示设置错误.


### CProgrammingLanguage

回顾《C Programming Language》时敲的一些小sample.

- bit_fields.c  
  C语言中按bit定义变量的用法. 多年前该是为了节约内存设计的, 现在应该早已不需要了. 不过由于C语言中没有bool类型, 其实也可以用这个用法自定义1个bit的bool, 赋值在0和1以外则会报warning, 有助于防止误写. 

- minprintf.c, va_param_in_macro.c  
  C语言中变长参数 `...` 的用法及其在 `macro` 中的传递方法. 

- simple_cat.c  
  `cat` 的一个简单实现. `stdin/out/err` 都是文件描述符, 故可以以文件形式操作. `cat` 的标准行为即读取文件并输出到`stdout`中. 

- dcl  
  TODO: 补齐说明


### webspider_qiushibaike_duanzi.py

学习Python爬虫，参考"静觅 » Python爬虫实战一之爬取糗事百科段子"实现的抓取糗事百科文字段子的小爬虫.


### TODO: 补齐其他说明...
