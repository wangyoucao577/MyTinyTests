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


## docker和host OS
- docker 和 host OS 之间的唯一联系即他们共享了 host OS 的`kernel`;     
  - 比如如果host OS是ubuntu, 而docker image的base OS是CentOS, 那么实际运行时, docker用的依然是ubuntu的`kernel`;    
  - 另外, 比如现在虽然能在windows上run任意docker, 但那实际是借助了windows的HyperV虚拟化技术;     
- 由于共享了`kernel`, 比虚拟机少掉了许多overhead, 从而性能方面也会好不少, 资源的开销也会更少.      



## 遇到的问题   
- docker服务器在国外, 在线安装docker或者download image经常会特别慢   
  - 可以使用国内厂商的mirror加速功能, 如[阿里云](https://cr.console.aliyun.com/)/DaoCloud等   

### Reference links  
- [Get started with Docker](https://docs.docker.com/get-started)   
- [Docker FAQ](https://docs.docker.com/engine/faq/)
- [阿里云docker控制台](https://cr.console.aliyun.com/)  
- [阿里云容器镜像服务 Docker镜像的基本使用](https://yq.aliyun.com/articles/70756)  
- [Docker - 从入门到实践 (yeasy)](https://www.gitbook.com/book/yeasy/docker_practice/details)  
- [How is Docker different from a virtual machine](https://stackoverflow.com/questions/16047306/how-is-docker-different-from-a-virtual-machine)
- [Docker Containers OS base image](https://www.ca.com/en/blog-developers/docker-containers-os-base-image.html)
- [Run different linux OS in docker container](https://stackoverflow.com/questions/33112137/run-different-linux-os-in-docker-container)
- [Understanding Docker "Container Host" vs. "Container OS" for Linux and Windows ContainersV](http://www.floydhilton.com/docker/2017/03/31/Docker-ContainerHost-vs-ContainerOS-Linux-Windows.html)
- [What is the relationship between the docker host OS and the container base image OS?](https://stackoverflow.com/questions/18786209/what-is-the-relationship-between-the-docker-host-os-and-the-container-base-image)