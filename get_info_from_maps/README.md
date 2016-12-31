# [JavaScript/Python2] get_info_from_maps
通过各地图提供商(`AMap`, `BaiduMap`, `Googlemap`, etc)提供的`JavaScript API`抓取信息并制定信息并写入文件至`Chrome file system`. 

### 名词解释
- MapProvider: 地图提供商
- city_lines: 城市中的公交线路列表  
- city_stations: 城市中的公交站点列表  
- city_stations_location: 城市中的公交站点的经纬度位置列表  
- line_details: 某条公交线路的详细信息, 包含经过的所有站点的经纬度坐标和地图上描绘路线(Path)所需要的所有点的经纬度坐标  


### 主要功能
获取指定`city`的`city_lines`和`line_details`并写入文件. 文件可供`ArcGis`导入使用.  

1. 初步获取指定城市的公交线路列表  
指定`city`进行`Place/Local Search`(`AMap`, `BaiduMap`), 将搜索结果中的`city_lines`, `city_stations`, `city_stations_location`输出至文件  

2. 迭代完善指定城市的公交线路列表  
指定`city`, 以已知的`city_lines`, `city_stations`, `city_stations_location`为基础数据发起`NearbySearch`(`AMap`, `BaiduMap`), 搜索结果仍主要为`city_lines`, `city_stations`, `city_stations_location`, 输出至文件. 
  - 可支持多次迭代, 以获取更加准确的结果.  
  - 各`MapProvider`都会限制`JavaScript API`的调用频度, 可能经常会报一些错误, 甚至错误卡死, 需要手动取出过程中输出的文件以作为结果    


3. 获取指定线路列表中每条线路的详细信息  
指定`city`, 以`city_lines`为基础数据发起`LineSearch`(`AMap`, `BaiduMap`), 将搜索结果中的`line_details`输出至文件  

### 主要文件说明

### 使用方法

### 各`MapProvider`的`JavaScript API`的异同

### 杂项

### Links

### Contacts
Author's Email: wangyoucao577@gmail.com