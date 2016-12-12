
var local_search_global_bmap = {};


local_search_global_bmap.execute_local_search = function (all_done_callback, city, place, map_provider_name){

  //输出站点
  var city_lines = [];
  var city_stations = [];
  var city_stations_location = [];

  var poi_index = 0;

  var local = new BMap.LocalSearch(city, {      
      onSearchComplete: function (result) {
          //console.log(result);
          console.log("NumPages: " + result.getNumPages() + ", NumPois: " + result.getNumPois() 
            + ", CurrentNumPois: " + result.getCurrentNumPois() + ", PageIndex: " + result.getPageIndex());

          

          for (var i = 0; i < result.getCurrentNumPois(); ++i){
            var poi = result.getPoi(i);
            console.log("local poi result " + poi_index + ", title: " + poi.title  + ", type: " + poi.type + ", location: " + poi.point.lng + "," + poi.point.lat
              + ", address: " + poi.address);
            poi_index++;

            if (-1 == city_stations.indexOf(poi.title)){
              city_stations.push(poi.title);
            }
            if (-1 == city_stations_location.indexOf(poi.point)){
              city_stations_location.push(poi.point);
            }

            //TODO: BaiduMap返回的Address中有些并不是经过此站点的线路，而是真实的地址，应想办法过滤
            var this_lines = poi.address.split(';');
            for (var j in this_lines){
                if (-1 == city_lines.indexOf(this_lines[j])){
                    city_lines.push(this_lines[j]);
                }
            }

          }

          //后续还有结果页面, 应翻页
          if (result.getPageIndex() + 1 < result.getNumPages()){
            local.gotoPage(result.getPageIndex() + 1);
          }else{
            console.log("all pages completed.");
            all_done_callback(city_lines, city_stations, city_stations_location, map_provider_name);
          }

      },    
      pageCapacity:50
  });     
  local.search(place, {forceLocal:true});

}

