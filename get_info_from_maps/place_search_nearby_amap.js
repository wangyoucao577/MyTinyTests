
//文件内的全局变量
var nearby_search_global_amap = {};


// 等待站点搜索结果, 并触发线路搜索
nearby_search_global_amap.total_nearby_search_succeed_callback_count = 0;
nearby_search_global_amap.total_nearby_search_failed_callback_count = 0;
nearby_search_global_amap.last_remember_succeed_callback_count = 0;
function waitForPlaceSearchNearbyResult_Callback(){
    if (0 != nearby_search_global_amap.last_remember_succeed_callback_count
        && nearby_search_global_amap.last_remember_succeed_callback_count == nearby_search_global_amap.total_nearby_search_succeed_callback_count){

        //一段时间没有更新
        console.log("All nearby search done. total_nearby_search_succeed_callback_count: " + nearby_search_global_amap.total_nearby_search_succeed_callback_count
            + ", total_nearby_search_failed_callback_count: " + nearby_search_global_amap.total_nearby_search_failed_callback_count);

        // 触发外部的callback
        nearby_search_global_amap.allDone_Callback(nearby_search_global_amap.city_lines, nearby_search_global_amap.city_stations, nearby_search_global_amap.city_stations_location, nearby_search_global_amap.wait_for_nearby_search_locations);

    }else{
        nearby_search_global_amap.last_remember_succeed_callback_count = nearby_search_global_amap.total_nearby_search_succeed_callback_count;
        setTimeout(waitForPlaceSearchNearbyResult_Callback, 1000);
    }
}

function placeSearchNearby_Callback(result)
{
    //console.log("placeSearchNearby_Callback, pois count " + result.poiList.count + ", pageIndex " + result.poiList.pageIndex);
    
    var pois = result.poiList.pois;
    for (var i = 0; i < pois.length; i++) {

        if (-1 == nearby_search_global_amap.city_stations.indexOf(pois[i].name)){
            nearby_search_global_amap.city_stations.push(pois[i].name);
        }
        if (-1 == nearby_search_global_amap.city_stations_location.indexOf(pois[i].location)){
            nearby_search_global_amap.city_stations_location.push(pois[i].location);
        }

        var lines_address = pois[i].address;
        var this_lines = lines_address.replace('...', "").split(';');
        for (var j in this_lines){
            if (-1 == nearby_search_global_amap.city_lines.indexOf(this_lines[j])){
                nearby_search_global_amap.city_lines.push(this_lines[j]);
            }

        }
    }

    ++nearby_search_global_amap.total_nearby_search_succeed_callback_count;
    console.log("city_lines.length: " + nearby_search_global_amap.city_lines.length 
        + ", city_stations.length: " + nearby_search_global_amap.city_stations.length 
        + ", city_stations_location.length: " + nearby_search_global_amap.city_stations_location.length 
        + ", total_nearby_search_succeed_callback_count: " + nearby_search_global_amap.total_nearby_search_succeed_callback_count);
}

nearby_search_global_amap.executePlaceSearchNearbyForCity = function (allPlaceSearchNearbyDone_Callback, city_lines, city_stations, city_stations_location, city, loc, wait_for_nearby_search_locations){

    console.log("executePlaceSearchNearbyForCity, location: " + loc);

    nearby_search_global_amap.allDone_Callback = allPlaceSearchNearbyDone_Callback;
    nearby_search_global_amap.city_lines = city_lines;
    nearby_search_global_amap.city_stations = city_stations;
    nearby_search_global_amap.city_stations_location = city_stations_location;
    nearby_search_global_amap.city = city;
    nearby_search_global_amap.location = loc;
    nearby_search_global_amap.wait_for_nearby_search_locations = wait_for_nearby_search_locations;

    //clear before this search
    nearby_search_global_amap.total_nearby_search_succeed_callback_count = 0;
    nearby_search_global_amap.total_nearby_search_failed_callback_count = 0;
    nearby_search_global_amap.last_remember_succeed_callback_count = 0;

    //先查询城市的公交站点
    AMap.service('AMap.PlaceSearch',function(){//回调函数


        for (var i = 1; i <= 20; i++){ //pageIndex range 1~100

            //实例化PlaceSearch
            var placeSearch = new AMap.PlaceSearch({ //构造地点查询类
                pageSize: 100,
                pageIndex: i,
                type: '公交车站',
                city: city, //城市
                citylimit: true,
                extensions:'all'//返回全部信息
            });

            //使用placeSearch对象调用关键字搜索的功能

            //关键字查询
            placeSearch.searchNearBy('', loc, 50000, function(status, result) {
                //取回公交站点的查询结果
                if(status === 'complete' && result.info === 'OK'){
                    //取得了正确的公交站点结果

                    placeSearchNearby_Callback(result);
                }else{
                    //无数据或者查询失败, 输出错误信息
                    ++nearby_search_global_amap.total_nearby_search_failed_callback_count;
                    //console.log("placeSearch nearby failed count: " + nearby_search_global_amap.total_nearby_search_failed_callback_count + ", " + status + ": " + result.info + ", ignored.");
                }    
            });
        }    

        setTimeout(waitForPlaceSearchNearbyResult_Callback, 1000);

    });

}
