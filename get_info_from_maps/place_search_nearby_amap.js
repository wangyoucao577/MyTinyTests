
//文件内的全局变量
var place_search_nearby_global = {};


// 等待站点搜索结果, 并触发线路搜索
place_search_nearby_global.total_nearby_search_succeed_callback_count = 0;
place_search_nearby_global.total_nearby_search_failed_callback_count = 0;
place_search_nearby_global.last_remember_succeed_callback_count = 0;
function waitForPlaceSearchNearbyResult_Callback(){
    if (0 != place_search_nearby_global.last_remember_succeed_callback_count
        && place_search_nearby_global.last_remember_succeed_callback_count == place_search_nearby_global.total_nearby_search_succeed_callback_count){

        //一段时间没有更新
        console.log("All nearby search done. total_nearby_search_succeed_callback_count: " + place_search_nearby_global.total_nearby_search_succeed_callback_count
            + ", total_nearby_search_failed_callback_count: " + place_search_nearby_global.total_nearby_search_failed_callback_count);

        // 触发外部的callback
        place_search_nearby_global.allDone_Callback(place_search_global.city_lines, place_search_global.city_stations, place_search_global.city_stations_location);

    }else{
        place_search_nearby_global.last_remember_succeed_callback_count = place_search_nearby_global.total_nearby_search_succeed_callback_count;
        setTimeout(waitForPlaceSearchNearbyResult_Callback, 10000);
    }
}

function placeSearchNearby_Callback(result)
{
    //console.log("placeSearchNearby_Callback, pois count " + result.poiList.count + ", pageIndex " + result.poiList.pageIndex);
    
    var pois = result.poiList.pois;
    for (var i = 0; i < pois.length; i++) {

        if (-1 == place_search_nearby_global.city_stations.indexOf(pois[i].name)){
            place_search_nearby_global.city_stations.push(pois[i].name);
        }
        if (-1 == place_search_nearby_global.city_stations_location.indexOf(pois[i].location)){
            place_search_nearby_global.city_stations_location.push(pois[i].location);
        }

        var lines_address = pois[i].address;
        var this_lines = lines_address.replace('...', "").split(';');
        for (var j in this_lines){
            if (-1 == place_search_nearby_global.city_lines.indexOf(this_lines[j])){
                place_search_nearby_global.city_lines.push(this_lines[j]);
            }

        }
    }

    ++place_search_nearby_global.total_nearby_search_succeed_callback_count;
    console.log("city_lines.length: " + place_search_nearby_global.city_lines.length 
        + ", city_stations.length: " + place_search_nearby_global.city_stations.length 
        + ", city_stations_location.length: " + place_search_nearby_global.city_stations_location.length 
        + ", total_nearby_search_succeed_callback_count: " + place_search_nearby_global.total_nearby_search_succeed_callback_count);
}

function executePlaceSearchNearbyForCity(allPlaceSearchNearbyDone_Callback, city_lines, city_stations, city_stations_location, city){
    place_search_nearby_global.allDone_Callback = allPlaceSearchNearbyDone_Callback;
    place_search_nearby_global.city_lines = city_lines;
    place_search_nearby_global.city_stations = city_stations;
    place_search_nearby_global.city_stations_location = city_stations_location;
    place_search_nearby_global.city = city;

    //先查询城市的公交站点
    AMap.service('AMap.PlaceSearch',function(){//回调函数

        for (var location_index in city_stations_location){

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
                placeSearch.searchNearBy('', city_stations_location[location_index], 50000, function(status, result) {
                    //取回公交站点的查询结果
                    if(status === 'complete' && result.info === 'OK'){
                        //取得了正确的公交站点结果

                        placeSearchNearby_Callback(result);
                    }else{
                        //无数据或者查询失败, 输出错误信息
                        ++place_search_nearby_global.total_nearby_search_failed_callback_count;
                        //console.log("placeSearch nearby failed count: " + place_search_nearby_global.total_nearby_search_failed_callback_count + ", " + status + ": " + result.info + ", ignored.");
                    }    
                });
            }    
            sleep(2000);    //execute next query after 1000 ms
        }
        setTimeout(waitForPlaceSearchNearbyResult_Callback, 10000);

    });

}
