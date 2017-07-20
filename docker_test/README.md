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

### webservice_sample   
- build and run  
```
cd ./webservice_sample
docker build -t my_webservice_sample .
docker run -p <public port>:80 my_webservice_sample
```
- test   
Open the link `http://<your ip address>:<public port>` in a browser, then you'll see the output from the docker container.   
    [参考官网的链接截图](https://docs.docker.com/get-started/part2/#run-the-app)   


## 遇到的问题   
- docker服务器在国外, 在线安装docker或者download image经常会特别慢   
  - 可以使用国内厂商的mirror加速功能, 如[阿里云](https://cr.console.aliyun.com/)/DaoCloud等   

### Reference links  
- [Get started with Docker](https://docs.docker.com/get-started)   
