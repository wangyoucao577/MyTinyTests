
var local_search_global_bmap = {};


local_search_global_bmap.execute_local_search = function (all_done_callback, city, map_provider_name){


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

            if (poi.type == BMAP_POI_TYPE_BUSSTOP || poi.type == BMAP_POI_TYPE_SUBSTOP){
              //过滤掉normal一般位置点, 因为一般位置点的address不是经过站点的线路

              if (-1 == city_stations.indexOf(poi.title)){
                city_stations.push(poi.title);
              }
              if (-1 == city_stations_location.indexOf(poi.point)){
                city_stations_location.push(poi.point);
              }

              if (poi.address.length > 0 && poi.address !== 'null'){  //过滤掉空的address
                var this_lines = poi.address.split(';');
                for (var j in this_lines){
                  if (-1 == city_lines.indexOf(this_lines[j])){
                      city_lines.push(this_lines[j]);
                  }
                }
              }
            }


          }

          //后续还有结果页面, 应翻页
          if (result.getNumPages() !== undefined && result.getPageIndex() + 1 < result.getNumPages()){
            local.gotoPage(result.getPageIndex() + 1);
          }else{
            console.log("all pages completed.");
            all_done_callback(city_lines, city_stations, city_stations_location, map_provider_name);
          }

      },    
      pageCapacity:50
  });     
  local.search('公交车站', {forceLocal:true});

}

