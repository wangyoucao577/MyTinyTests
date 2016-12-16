
//定义一个自己的全局变量, 串联执行流程
var search_global = {};



//统计
search_global.searched_count = 0;

//动态函数调用
search_global.functions = {

    //三个搜索入口
    local_search: notImplementFunction,
    nearby_search: notImplementFunction,
    lines_search: notImplementFunction,

    //工具函数
    location_array_convert: notImplementFunction
}

//根据map_provider绑定不同的函数 及 参数
if (search_config.options.map_provider === search_config.MapProvider.AMap){

    search_global.functions.local_search = place_search_global_amap.executePlaceSearchForCity;
    search_global.functions.nearby_search = nearby_search_global_amap.executePlaceSearchNearbyForCity;
    search_global.functions.lines_search = lines_search_global_amap.executeLineSearch;

    search_global.functions.location_array_convert = tools_amap.location_array_convert;

}else if (search_config.options.map_provider === search_config.MapProvider.BaiduMap){

    search_global.functions.local_search = local_search_global_bmap.execute_local_search;
    search_global.functions.nearby_search = nearby_search_global_bmap.execute_local_nearby_search;
    search_global.functions.lines_search = busline_search_global_bmap.execute_buslines_search;

    search_global.functions.location_array_convert = tools_bmap.location_array_convert;

}else if (search_config.options.map_provider === search_config.MapProvider.GoogleMap){

    //TODO: for GoogleMap
    search_global.functions.local_search = place_search_global_gmap.execute_nearby_search;

}else{
    //Unknown map provider
}

//Search的返回city_lines, city_stations, city_stations_lcation写入文件的工具函数, 以便用于后续的迭代搜索
search_global.write_city_lines_stations_locations_to_file = function(city, type, map_provider_name, city_lines, city_stations, city_stations_location)
{
    var out_str = "";

    //显示下三个返回数据的长度, 仅用于人看以了解
    out_str += "// city_lines_count = " + city_lines.length + "\n";
    out_str += "// city_stations_count = " + city_stations.length + "\n";
    out_str += "// city_stations_location_count = " + city_stations_location.length + "\n";
    out_str += "\n";

    out_str += "var expect_city = " + city;
    out_str += "\n\n";

    out_str += "var city_lines = ";
    out_str += array_to_string(city_lines);
    out_str += "\n\n";

    out_str += "var city_stations = ";
    out_str += array_to_string(city_stations);
    out_str += "\n\n";

    out_str += "var city_stations_location = ";
    if (map_provider_name === search_config.MapProvider.AMap){
        out_str += tools_amap.location_array_to_string(city_stations_location);
    }else if(map_provider_name === search_config.MapProvider.BaiduMap){
        out_str += tools_bmap.location_array_to_string(city_stations_location);
    }
    out_str += "\n";


    //把结果写入文件
    write_to_file(city, type + "_" + map_provider_name, out_str, true);

}

/************************** 三种Search动作的分别的回调 *******************************/

//AMap, BaiduMap的PlaceSearch完成时的回调, 触发NearbySearch
search_global.placeSearchDone_Callback = function (city, city_lines_result, city_stations_result, city_stations_location_result, map_provider_name)
{
    //console.log(city_lines_result);
    console.log("placeSearchDone_Callback, city_lines_result.length: " + city_lines_result.length + ", city_stations_result.length: "
        + city_stations_result.length + ", city_stations_location_result.length: " + city_stations_location_result.length);
    ++search_global.searched_count;

    if (search_config.options.is_write_city_lines_to_file_after_place_search){
        //把city_lines写入文件
        //write_city_lines_to_file(search_global.expect_city, "CityLines_" + map_provider_name, city_lines_result);
        search_global.write_city_lines_stations_locations_to_file(city, "Lines_Stations_Locations",  map_provider_name, city_lines_result, city_stations_result, city_stations_location_result);
    }

    if (city_stations_location_result.length > 0){

        //deep copy
        var wait_for_nearby_search_locations = [];
        for (var i in city_stations_location_result){

            wait_for_nearby_search_locations.push(city_stations_location_result[i]);
        }
        var loc = wait_for_nearby_search_locations.pop();

        // 触发nearby搜索, AMap
        search_global.functions.nearby_search(search_global.placeNearbySearchDone_Callback, city_lines_result, city_stations_result, city_stations_location_result, city, loc, wait_for_nearby_search_locations, map_provider_name);
    }

}
search_global.placeNearbySearchDone_Callback = function (city, city_lines_result, city_stations_result, city_stations_location_result, wait_for_nearby_search_locations_result, map_provider_name)
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
        search_global.write_city_lines_stations_locations_to_file(city, "Lines_Stations_Locations_temp",  map_provider_name, city_lines_result, city_stations_result, city_stations_location_result);

    }

    if (0 == wait_for_nearby_search_locations_result.length){

        if (search_config.options.is_write_city_lines_to_file_after_nearby_search){
            //Nearby搜索完成, 把city_lines写入文件
            //write_city_lines_to_file(search_global.expect_city, "CityLines_whole_" + map_provider_name, city_lines_result);
            search_global.write_city_lines_stations_locations_to_file(city, "Lines_Stations_Locations_whole",  map_provider_name, city_lines_result, city_stations_result, city_stations_location_result);

        }


        search_config.options.nearby_iterate_count--;
        if (search_config.options.nearby_iterate_count == 0){

            // Nearby搜索完成, 触发Line搜索
            search_global.functions.lines_search(search_global.lineSearchDone_Callback, city, city_lines_result, map_provider_name);
        }else{
            // 进行下一次Nearby迭代
            console.log("ready to next nearby iterate. remain count: " + search_config.options.nearby_iterate_count);

            var wait_for_nearby_search_locations = [];
            for (var i in city_stations_location_result){

                wait_for_nearby_search_locations.push(city_stations_location_result[i]);
            }
            var loc = wait_for_nearby_search_locations.pop();

            // 触发nearby搜索
            search_global.functions.nearby_search(search_global.placeNearbySearchDone_Callback, city_lines_result, city_stations_result, city_stations_location_result, city, loc, wait_for_nearby_search_locations, map_provider_name);

        }


    }else{
        var loc = wait_for_nearby_search_locations_result.pop();

        // 触发nearby搜索
        search_global.functions.nearby_search(search_global.placeNearbySearchDone_Callback, city_lines_result, city_stations_result, city_stations_location_result, city, loc, wait_for_nearby_search_locations_result, map_provider_name);
    }

}

//AMap, BaiduMap的通用busline搜索完成时的回调，以触发写入文件
search_global.lineSearchDone_Callback = function (city, out_str_result, map_provider_name)
{
    //console.log(out_str_result);
    console.log("out_str_result len: " + out_str_result.length);

    // 触发文件写入
    write_to_file(city, "LinesDetails_" + map_provider_name,
        out_str_result.replace(/<\/br>/g, "\n"), false);
}

/************************** 三种Search动作的分别的回调 *******************************/


//入口函数
search_global.my_main = function(param_in) {
    console.log("start with " + search_config.options.start_step);
    if (search_config.options.start_step === search_config.Step.BusLineSearch){

        //已有线路list, 直接搜索线路详细
        search_global.functions.lines_search(search_global.lineSearchDone_Callback,
            param_in.expect_city, param_in.city_lines,
            search_config.options.map_provider);
    }else if (search_config.options.start_step === search_config.Step.NearbySearch){
        // 已有初步的 city_lines, city_stations, city_stations_location, 直接启动Nearby迭代以期更多的结果

        console.log("start with NearbySearch, city_lines.length: " + param_in.city_lines.length + ", city_stations.length: " + param_in.city_stations.length + ", city_stations_location.length: " + param_in.city_stations_location.length);

        //location的格式AMap和BaiduMap表示方式各不同相同, 需先转换为其能识别的格式
        var city_stations_location = search_global.functions.location_array_convert(param_in.city_stations_location);

        //迭代array
        var wait_for_nearby_search_locations = [];
        for (var i in city_stations_location){

            wait_for_nearby_search_locations.push(city_stations_location[i]);
        }
        var loc = wait_for_nearby_search_locations.pop();

        search_global.functions.nearby_search(search_global.placeNearbySearchDone_Callback,
            param_in.city_lines, param_in.city_stations, city_stations_location,
            param_in.expect_city, loc, wait_for_nearby_search_locations, search_config.options.map_provider);

    }
    else{
        //默认从Local/Place Search开始, 先取得初步的信息, 再进入Nearby迭代
        search_global.functions.local_search(search_global.placeSearchDone_Callback,
            param_in.expect_city, search_config.options.map_provider);
    }

}


//入口
search_global.my_main(search_param_in);