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

- 推送到 [Docker Registry Cloud](https://cloud.docker.com/)    
由于上面官网链接的速度太慢, 实际使用阿里云做的实验   
  - 到 [阿里云docker控制台](https://cr.console.aliyun.com/) 注册账号   
  - 在 [阿里云docker控制台](https://cr.console.aliyun.com/) 创建一个 registry(如果没有namespace需要先新建namespace)   
  - 本地push   
  ```
  docker login registry.cn-hangzhou.aliyuncs.com/<your namespace>/<your registry name>  
  (input username/password)  
  docker tag <ImageId> registry.cn-hangzhou.aliyuncs.com/<your namespace>/<your registry name>:<镜像版本号>  
  docker push registry.cn-hangzhou.aliyuncs.com/<your namespace>/<your registry name>:<镜像版本号>  
  ```
  - 远端pull  
  ```
  docker pull registry.cn-hangzhou.aliyuncs.com/<your namespace>/<your registry name>:<镜像版本号>  
  ```
  - 注: push时需要登录才有权限, 但pull时由于选择的是公开image, 所以不需要登录即可拉取.    



## 遇到的问题   
- docker服务器在国外, 在线安装docker或者download image经常会特别慢   
  - 可以使用国内厂商的mirror加速功能, 如[阿里云](https://cr.console.aliyun.com/)/DaoCloud等   

### Reference links  
- [Get started with Docker](https://docs.docker.com/get-started)   
- [阿里云docker控制台](https://cr.console.aliyun.com/)  
- [阿里云容器镜像服务 Docker镜像的基本使用](https://yq.aliyun.com/articles/70756)  
- [Docker - 从入门到实践 (yeasy)](https://www.gitbook.com/book/yeasy/docker_practice/details)  
