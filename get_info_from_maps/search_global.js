
//定义一个自己的全局变量
var search_global = {};

//输入参数, 目标城市
//TODO: 挪到search_param_in.js中去
search_global.expect_city = '上海';

//地图提供商的枚举
search_global.MapProvider = {
    AMap: "AMap",
    BaiduMap: "BaiduMap",
    GoogleMap: "GoogleMap"
}
//启动步骤的枚举
search_global.Step = {
    LocalSearch: "local search",
    NearbySearch: "nearby search",
    BusLineSearch: "busline search"
}

//NOTE: options
search_global.options = {
    map_provider: search_global.MapProvider.AMap,			//选择地图提供商
    start_step: search_global.Step.NearbySearch,               //选择此次任务的起始步骤

    is_write_city_lines_to_file_after_place_search: true,		//选择基于城市的初步 PlaceSearch后的结果city_lines是否写入文件
    is_write_city_lines_to_file_after_nearby_search: true,		//选择迭代的 PlaceNearbySearch 后的结果city_lines是否写入文件

    nearby_iterate_count: 1   //nearby迭代搜索的次数
}

//统计
search_global.searched_count = 0;

//动态函数调用
search_global.functions = {

    //三个搜索入口
    local_search: place_search_global_amap.executePlaceSearchForCity,
    nearby_search: nearby_search_global_amap.executePlaceSearchNearbyForCity,
    lines_search: lines_search_global_amap.executeLineSearch,

    location_array_convert: tools_amap.location_array_convert
}

//根据map_provider绑定不同的函数 及 参数
if (search_global.options.map_provider === search_global.MapProvider.AMap){
    //default values, nothing to change

}else if (search_global.options.map_provider === search_global.MapProvider.BaiduMap){

    search_global.functions.local_search = local_search_global_bmap.execute_local_search;
    search_global.functions.nearby_search = nearby_search_global_bmap.execute_local_nearby_search;
    search_global.functions.lines_search = busline_search_global_bmap.execute_buslines_search;

    search_global.functions.location_array_convert = tools_bmap.location_array_convert;

}else if (search_global.options.map_provider === search_global.MapProvider.GoogleMap){
    //TODO:
    search_global.functions.local_search = place_search_global_gmap.execute_nearby_search;
}else{
    //Unknown map provider
}

//Search的返回city_lines, city_stations, city_stations_lcation写入文件的工具函数, 以便用于后续的迭代搜索
search_global.write_city_lines_stations_locations_to_file = function(city, type, map_provider_name, city_lines, city_stations, city_stations_location)
{
    var out_str = "";

    //显示下三个返回数据的长度, 仅用于人看以了解
    out_str += "city_lines_count = " + city_lines.length + "\n";
    out_str += "city_stations_count = " + city_stations.length + "\n";
    out_str += "city_stations_location_count = " + city_stations_location.length + "\n";
    out_str += "\n";

    out_str += "search_global.city_lines = ";
    out_str += array_to_string(city_lines);
    out_str += "\n\n";

    out_str += "search_global.city_stations = ";
    out_str += array_to_string(city_stations);
    out_str += "\n\n";

    out_str += "search_global.city_stations_location = ";
    if (map_provider_name === search_global.MapProvider.AMap){
        out_str += tools_amap.location_array_to_string(city_stations_location);
    }else if(map_provider_name === search_global.MapProvider.BaiduMap){
        out_str += tools_bmap.location_array_to_string(city_stations_location);
    }
    out_str += "\n";


    //把结果写入文件
    write_to_file(city, type + "_" + map_provider_name, out_str, true);

}

/************************** 三种Search动作的分别的回调 *******************************/

//AMap, BaiduMap的PlaceSearch完成时的回调, 触发NearbySearch
search_global.placeSearchDone_Callback = function (city_lines_result, city_stations_result, city_stations_location_result, map_provider_name)
{
    //console.log(city_lines_result);
    console.log("placeSearchDone_Callback, city_lines_result.length: " + city_lines_result.length + ", city_stations_result.length: "
        + city_stations_result.length + ", city_stations_location_result.length: " + city_stations_location_result.length);
    ++search_global.searched_count;

    if (search_global.options.is_write_city_lines_to_file_after_place_search){
        //把city_lines写入文件
        //write_city_lines_to_file(search_global.expect_city, "CityLines_" + map_provider_name, city_lines_result);
        search_global.write_city_lines_stations_locations_to_file(search_global.expect_city, "Lines_Stations_Locations",  map_provider_name, city_lines_result, city_stations_result, city_stations_location_result);
    }

    if (city_stations_location_result.length > 0){

        //deep copy
        var wait_for_nearby_search_locations = [];
        for (var i in city_stations_location_result){

            wait_for_nearby_search_locations.push(city_stations_location_result[i]);
        }
        var loc = wait_for_nearby_search_locations.pop();

        // 触发nearby搜索, AMap
        search_global.functions.nearby_search(search_global.placeNearbySearchDone_Callback, city_lines_result, city_stations_result, city_stations_location_result, search_global.expect_city, loc, wait_for_nearby_search_locations, map_provider_name);
    }

}
search_global.placeNearbySearchDone_Callback = function (city_lines_result, city_stations_result, city_stations_location_result, wait_for_nearby_search_locations_result, map_provider_name)
{
    console.log("placeNearbySearchDone_Callback, city_lines_result.length: " + city_lines_result.length
        + ", city_stations_result.length: " + city_stations_result.length
        + ", city_stations_location_result.length: " + city_stations_location_result.length
        + ", wait_for_nearby_search_locations_result.length: " + wait_for_nearby_search_locations_result.length);
    document.getElementById('result').innerHTML = wait_for_nearby_search_locations_result.length;

    ++search_global.searched_count;
    if (search_global.searched_count % 50 == 0){
        //NOTE: 过程中也把city_lines写入文件, 以免由于高德的拖动认证问题导致成果作废...
        //write_city_lines_to_file(search_global.expect_city, "CityLines_temp_"
        //   + search_global.searched_count + "_" + map_provider_name, city_lines_result);
        search_global.write_city_lines_stations_locations_to_file(search_global.expect_city, "Lines_Stations_Locations_temp",  map_provider_name, city_lines_result, city_stations_result, city_stations_location_result);

    }

    if (0 == wait_for_nearby_search_locations_result.length){

        if (search_global.options.is_write_city_lines_to_file_after_nearby_search){
            //Nearby搜索完成, 把city_lines写入文件
            //write_city_lines_to_file(search_global.expect_city, "CityLines_whole_" + map_provider_name, city_lines_result);
            search_global.write_city_lines_stations_locations_to_file(search_global.expect_city, "Lines_Stations_Locations_whole",  map_provider_name, city_lines_result, city_stations_result, city_stations_location_result);

        }


        search_global.options.nearby_iterate_count--;
        if (search_global.options.nearby_iterate_count == 0){

            // Nearby搜索完成, 触发Line搜索
            search_global.functions.lines_search(search_global.lineSearchDone_Callback, search_global.expect_city, city_lines_result, map_provider_name);
        }else{
            // 进行下一次Nearby迭代
            console.log("ready to next nearby iterate. remain count: " + search_global.options.nearby_iterate_count);

            var wait_for_nearby_search_locations = [];
            for (var i in city_stations_location_result){

                wait_for_nearby_search_locations.push(city_stations_location_result[i]);
            }
            var loc = wait_for_nearby_search_locations.pop();

            // 触发nearby搜索
            search_global.functions.nearby_search(search_global.placeNearbySearchDone_Callback, city_lines_result, city_stations_result, city_stations_location_result, search_global.expect_city, loc, wait_for_nearby_search_locations, map_provider_name);

        }


    }else{
        var loc = wait_for_nearby_search_locations_result.pop();

        // 触发nearby搜索
        search_global.functions.nearby_search(search_global.placeNearbySearchDone_Callback, city_lines_result, city_stations_result, city_stations_location_result, search_global.expect_city, loc, wait_for_nearby_search_locations_result, map_provider_name);
    }

}

//AMap, BaiduMap的通用busline搜索完成时的回调，以触发写入文件
search_global.lineSearchDone_Callback = function (out_str_result, map_provider_name)
{
    //console.log(out_str_result);
    console.log("out_str_result len: " + out_str_result.length);

    // 触发文件写入
    write_to_file(search_global.expect_city, "LinesDetails_" + map_provider_name,
        out_str_result.replace(/<\/br>/g, "\n"), false);
}

/************************** 三种Search动作的分别的回调 *******************************/


//入口函数
search_global.my_main = function() {
    console.log("start with " + search_global.options.start_step);
    if (search_global.options.start_step === search_global.Step.BusLineSearch){

        //已有线路list, 直接搜索线路详细
        search_global.functions.lines_search(search_global.lineSearchDone_Callback,
            search_global.expect_city, search_param_in.city_lines,
            search_global.options.map_provider);
    }else if (search_global.options.start_step === search_global.Step.NearbySearch){
        //TODO: 已有初步的 city_lines, city_stations, city_stations_location, 直接启动Nearby迭代以期更多的结果

        console.log("start with NearbySearch, city_lines.length: " + search_param_in.city_lines.length + ", city_stations.length: " + search_param_in.city_stations.length + ", city_stations_location.length: " + search_param_in.city_stations_location.length);

        //location的格式AMap和BaiduMap表示方式各不同相同, 需先转换为其能识别的格式
        var city_stations_location = search_global.functions.location_array_convert(search_param_in.city_stations_location);

        //迭代array
        var wait_for_nearby_search_locations = [];
        for (var i in city_stations_location){

            wait_for_nearby_search_locations.push(city_stations_location[i]);
        }
        var loc = wait_for_nearby_search_locations.pop();

        search_global.functions.nearby_search(search_global.placeNearbySearchDone_Callback,
            search_param_in.city_lines, search_param_in.city_stations, city_stations_location,
            search_global.expect_city, loc, wait_for_nearby_search_locations, search_global.options.map_provider);

    }
    else{
        //默认从Local/Place Search开始, 先取得初步的信息, 再进入Nearby迭代
        search_global.functions.local_search(search_global.placeSearchDone_Callback,
            search_global.expect_city, search_global.options.map_provider);
    }

}


//入口
search_global.my_main();