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
- `Place/Local Search`  
	- `AMap`  
		限定城市和`type:公交车站`以进行关键字搜索, 返回结果`poi array`, 即搜索得出城市内的公交站点. 其中的`address`文本化显示了经过此位置的公交线路信息, `name`为公交站点名, `location`为公交站点的经纬度   
	- `BaiduMap`    
		限定城市以进行关键字(`公交车站`)搜索, 返回结果`poi array`, 即搜索得出城市内的公交站点(由于无`type`限定, 需要在结果中过滤非`type`的`poi`). 其中的`address`文本化显示了经过此位置的公交线路信息, `title`为公交站点名, `point`为公交站点的经纬度(`BaiduMap`定义的`point`对象, 若需与`AMap`混用, 需进行互相转换)   
	- `GoogleMap`  
		对应`Places库`中的`textSearch`接口. `GoogleMap`的`API`不支持直接的`city`限定, 故需按照其要求先将`city`转换为`bounds`进行范围的限定, 然后发起文本搜索. 另外, `GoogleMap`的`textSearch`结构仅会输出`placeId`及粗略的信息. 要获取此位置的详细信息, 还需以`placeId`在发起一次`getDetails`以获得.  `GoogleMap`搜索的结果中并没有经过此站点的公交线路信息，故无法提供所期望的功能.  
  
- `Nearby Search`  
 	- `AMap`  
 	限定城市和`type`, 以`location`为中心进行附近搜索. 输出结果细节同`Place/Local Search`->`AMap`中所述.  
	- `BaiduMap`  
	限定城市, 以`point`为中心进行附近搜索. 输出结果细节同`Place/Local Search`->`BaiduMap`中所述.  
	- `GoogleMap`  
	对应`Places库`中的`nearbySearch` or `radarSearch`接口. 细节同`Place/Local Search`->`GoogleMap`中所述.  
	
- `BusLine Search`  
 	- `AMap`  
 	限定城市, 以`公交线路名`发起`Line Search`, 返回此线路所经过的所有`stop`的位置和绘制其线路所需要的所有位置的坐标.  
	- `BaiduMap`  
	限定城市，以`公交线路名`发起`BusList Search`, 返回`BaiduMap`匹配的对应线路的信息`object`. 再需以此`object`发起`BusLine Search`, 返回此线路所经过的所有`stop`的位置和绘制其线路所需要的所有位置的坐标.  
	- `GoogleMap`: 未提供此接口.  

## 杂项
- `Chrome`的`filesystem`本地调试, 需要启动时加上`--allow-file-access-from-files`选项，才能在页面的`JavaScript`代码中调用`fileystem API`写文件    

	参考:  
	https://developers.google.com/web/updates/2011/08/Debugging-the-Filesystem-API  
    
  	注: 刚刚开始做这个功能时, 可以在`chrome`中输入`filesystem:file:///temporary/`以查看写入的文件列表, 但某天突然不能用了, 也未查到资料说明为什么. 只能手动去`Windows`的缓存目录中自己去找了然后重命名, 一般缓存路径为`C:\Users\USERNAME\AppData\Local\Google\Chrome\User Data\Default\File System\`  
  	参考:  
	- http://stackoverflow.com/questions/41011441/the-filesystemfile-temporary-has-no-response-in-chrome  
	- http://stackoverflow.com/questions/11676584/where-does-persistent-file-system-storage-store-with-chrome  

- `API`调用限制  
	- 三家的`JavaScript API`写的都是不限制调用次数. 但实际使用中, `BaiduMap`相对限制最少, 可连续调用; `AMap`连续频繁调用后, 需要拖动验证, 一般第二次拖动验证总是过不了, 就只能停掉了; `GoogleMap`貌似是认为限制不能频繁调用, 否则很容易报`OVER_QUERY_LIMIT`, 官方解释就是需要过会再调用.   
	- 三家的`WebService API`写的免费调用次数都不多, 大约日均免费都在1000次左右. 实际试了下`AMap`, 发现一直用都没问题, 只是`API控制台`中会提示警告. 另外两家没有尝试.  

## Links
- http://lbs.amap.com/api/javascript-api/guide/map-data/busroutes/  
- http://lbs.amap.com/api/javascript-api/reference/core/  
- http://lbsyun.baidu.com/index.php?title=jspopular/guide/service  
- http://lbsyun.baidu.com/cms/jsapi/reference/jsapi_reference.html  
- https://developers.google.com/maps/documentation/javascript/tutorial  
- https://developers.google.com/maps/documentation/javascript/reference#PlacesService  
- https://developers.google.com/web/updates/2011/08/Debugging-the-Filesystem-API  
- http://stackoverflow.com/questions/41011441/the-filesystemfile-temporary-has-no-response-in-chrome  
- http://stackoverflow.com/questions/11676584/where-does-persistent-file-system-storage-store-with-chrome  


### Contacts
Author's Email: wangyoucao577@gmail.com