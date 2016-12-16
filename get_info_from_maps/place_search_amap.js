
//文件内的全局变量
var place_search_global_amap = {};

//NOTE:城市对应的线路列表
place_search_global_amap.city_lines = [];
place_search_global_amap.city_stations = [];
place_search_global_amap.city_stations_location = [];

// 等待站点搜索结果, 并触发线路搜索
place_search_global_amap.expect_total_place_search_result_count = 0;
place_search_global_amap.total_place_search_result_count = 0;
function waitForPlaceSearchResult_Callback(){
    if (0 != place_search_global_amap.expect_total_place_search_result_count
        && place_search_global_amap.total_place_search_result_count == place_search_global_amap.expect_total_place_search_result_count){
        // 已完成公交站点的搜索, 并完成了city_lines的生成
        console.log("All place search succeed, city_lines.length: " + place_search_global_amap.city_lines.length 
            + ", city_stations.length: " + place_search_global_amap.city_stations.length + ", city_stations_location.length: " + place_search_global_amap.city_stations_location.length);
        //console.log(place_search_global_amap.city_lines);

        // 触发外部的callback
        place_search_global_amap.allDone_Callback(place_search_global_amap.city, place_search_global_amap.city_lines, place_search_global_amap.city_stations, place_search_global_amap.city_stations_location, place_search_global_amap.map_provider_name);

    }else{
        setTimeout(waitForPlaceSearchResult_Callback, 1000);
    }
}

function placeSearch_Callback(result)
{
    //console.log("placeSearch callback, count " + result.poiList.count + ", pageIndex " + result.poiList.pageIndex);

    if (0 == place_search_global_amap.expect_total_place_search_result_count){
        place_search_global_amap.expect_total_place_search_result_count = result.poiList.count;
    }
    
    var pois = result.poiList.pois;
    for (var i = 0; i < pois.length; i++) {

        if (-1 == place_search_global_amap.city_stations.indexOf(pois[i].name)){
            place_search_global_amap.city_stations.push(pois[i].name);
        }
        if (-1 == place_search_global_amap.city_stations_location.indexOf(pois[i].location)){
            place_search_global_amap.city_stations_location.push(pois[i].location);
        }

        var lines_address = pois[i].address;
        var this_lines = lines_address.replace('...', "").split(';');
        for (var j in this_lines){
            if (-1 == place_search_global_amap.city_lines.indexOf(this_lines[j])){
                place_search_global_amap.city_lines.push(this_lines[j]);
            }

        }
    }

    place_search_global_amap.total_place_search_result_count += pois.length;
    console.log("city_lines.length: " + place_search_global_amap.city_lines.length + ", city_stations.length: " + place_search_global_amap.city_stations.length + ", city_stations_location.length: " + place_search_global_amap.city_stations_location.length + ", total place search result count: " + place_search_global_amap.total_place_search_result_count);
}

place_search_global_amap.executePlaceSearchForCity = function (allPlaceSearchDone_Callback, city, map_provider_name){
    place_search_global_amap.allDone_Callback = allPlaceSearchDone_Callback;
    place_search_global_amap.map_provider_name = map_provider_name;
    place_search_global_amap.city = city;

    //先查询城市的公交站点
    AMap.service('AMap.PlaceSearch',function(){//回调函数

        for (var i = 1; i <= 100; i++){ //pageIndex range 1~100

            //实例化PlaceSearch
            var placeSearch = new AMap.PlaceSearch({ //构造地点查询类
                pageSize: 100,
                pageIndex: i,
                type:"公交车站",
                city: city, //城市
                extensions:'all'//返回全部信息
            });

            //使用placeSearch对象调用关键字搜索的功能

            //关键字查询
            placeSearch.search('', function(status, result) {
                //取回公交站点的查询结果
                if(status === 'complete' && result.info === 'OK'){
                    //取得了正确的公交站点结果

                    placeSearch_Callback(result);
                }else{
                    //无数据或者查询失败, 输出错误信息
                    //console.log("placeSearch failed, ignored.");
                }    
            });
        }
        setTimeout(waitForPlaceSearchResult_Callback, 1000);
    });

}
