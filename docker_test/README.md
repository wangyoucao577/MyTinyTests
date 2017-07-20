# docker_test
学习docker的基本原理及使用    

## Samples  
### my_hello_world  
- build and run   
```  
cd ./my_hello_world  
docker build -t my_hello_world .
docker run my_hello_world
```  
- list or delete   
```
docker images
docker image rm -r my_hello_world
```

## 遇到的问题   
- docker服务器在国外, 在线安装docker或者download image经常会特别慢   
  - 可以使用国内厂商的mirror加速功能, 如阿里云/DaoCloud等   

### Reference links  
- [Get started with Docker](https://docs.docker.com/get-started)   
