# [JavaScript/Python2] get_info_from_maps
通过各地图提供商(`AMap`, `BaiduMap`, `Googlemap`, etc)提供的`JavaScript API`抓取信息并制定信息并写入文件至`Chrome file system`. 

## 名词解释
- MapProvider: 地图提供商
- city_lines: 城市中的公交线路列表  
- city_stations: 城市中的公交站点列表  
- city_stations_location: 城市中的公交站点的经纬度位置列表  
- line_details: 某条公交线路的详细信息, 包含经过的所有站点的经纬度坐标和地图上描绘路线(Path)所需要的所有点的经纬度坐标  


## 主要功能
当前已实现的主要功能为获取指定`city`的`city_lines`和`line_details`并写入文件. 文件可供`ArcGis`导入使用.  

1. 初步获取指定城市的公交线路列表  
指定`city`进行`Place/Local Search`(`AMap`, `BaiduMap`), 将搜索结果中的`city_lines`, `city_stations`, `city_stations_location`输出至文件  

2. 迭代完善指定城市的公交线路列表  
指定`city`, 以已知的`city_lines`, `city_stations`, `city_stations_location`为基础数据发起`NearbySearch`(`AMap`, `BaiduMap`), 搜索结果仍主要为`city_lines`, `city_stations`, `city_stations_location`, 输出至文件. 
  - 可支持多次迭代, 以获取更加准确的结果.  
  - 各`MapProvider`都会限制`JavaScript API`的调用频度, 可能经常会报一些错误, 甚至错误卡死. 故迭代过程中每隔一段时间会输出一次`temp`结果, 可根据卡死情况选择性使用.      


3. 获取指定线路列表中每条线路的详细信息  
指定`city`, 以`city_lines`为基础数据发起`LineSearch`(`AMap`, `BaiduMap`), 将搜索结果中的`line_details`输出至文件  

## 主要文件说明
- search.html  
程序入口页面, `Chrome`中打开此页面从而触发`JavaScript`代码的功能.  

- search_configs.js  
程序运行的统一配置, 可用于调整运行哪几个`Search`, 分别用哪个`MapProvder`的`API`, `Nearby Search`时迭代几次, 过程中是否写文件等等.  

- search_global.js  
  - 定义`Search`功能的入口`main`   
  - 定义`Place/Local Search`, `Nearby Search` 和 `Line Search`三个主要功能的统一`callback`，从而统一处理结果内容    
  - 根据`search_configs.js`中定义的参数, 实现不同的行为(如用`AMap` or `BaiduMap`? 从`Place/Local Search`or `Nearby Search` or `Line Search`启动程序? etc), 串联多个步骤流程  

- search_param_in.js  
提供预定义的`expect_city`, `city_lines`, `city_stations` 和 `city_stations_location`. 此文件可手动填入, 或由`generate_search_param_in.py`合并几次搜搜结果文件而自动生成.  

- generate_search_param_in.py  
合并各次(`AMap`/`BaiduMap`的`Place/Local Search`/`Nearby Search`等)输出的文件, 生成定义的`search_param_in.js`文件, 供后续搜索使用.  

- place_search_amap.js, local_search_baidumap.js, place_search_googlemap.js  
提供`AMap`, `BaiduMap`, `GoogleMap`的`Place/Local Search`功能.  

- place_search_nearby_amap.js, local_nearby_search_baidumap.js  
提供`AMap`, `BaiduMap` 的`Nearby Search`功能.   

- lines_search_amap.js, busline_search_baidumap.js  
提供`AMap`, `BaiduMap` 的`Line Search`功能.  

- tools_amap.js, tools_baidumap.js, tools_googlemap.js  
提供`AMap`, `BaiduMap`, `GoogleMap` 各自不通用的一些工具函数.  

- my_base_tools.js   
一些较通用的`JavaScript`功能封装.  

- write_to_file.js  
输出文件的功能封装.  

- [deprecated] lines_search_amap_service.py  
通过`AMap`的`Web Service`接口进行`Place Search`和`Nearby Search`. 但由于`Web Service`接口一般日访问量都很少, 故不太实用, 除非花钱买. 废弃之.  

- [deprecated] webspider_wiki_citylines.py  
爬一下中文`wiki`上城市的公交线路页面, 以抓取`city_lines`. 但由于每个城市的公交线路页面格式都有所不同(试过上海, 广州和深圳, 都不同), 正则需要case by case, 有点麻烦. 且有些城市干脆没有这个页面(如北京). 总体就是不够通用. 废弃之. 


## 使用方法

## 各`MapProvider`的`JavaScript API`的异同

## 杂项

## Links

### Contacts
Author's Email: wangyoucao577@gmail.com