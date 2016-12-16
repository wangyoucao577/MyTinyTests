
/*
* 搜索的配置项
* */

var search_config = {};

//地图提供商的枚举
search_config.MapProvider = {
    AMap: "AMap",
    BaiduMap: "BaiduMap",
    GoogleMap: "GoogleMap"
}
//启动步骤的枚举
search_config.Step = {
    LocalSearch: "local search",
    NearbySearch: "nearby search",
    BusLineSearch: "busline search"
}

//NOTE: 在这里修改配置, 调整期望执行的功能
search_config.options = {
    map_provider: search_config.MapProvider.AMap,			//选择地图提供商
    start_step: search_config.Step.BusLineSearch,               //选择此次任务的起始步骤

    is_write_city_lines_to_file_after_place_search: true,		//选择基于城市的初步 PlaceSearch后的结果city_lines是否写入文件
    is_write_city_lines_to_file_after_nearby_search: true,		//选择迭代的 PlaceNearbySearch 后的结果city_lines是否写入文件

    nearby_iterate_count: 1   //nearby迭代搜索的次数
}