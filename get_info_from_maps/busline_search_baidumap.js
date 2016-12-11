
var busline_search_global_bmap = {};

//输出
busline_search_global_bmap.outStr = "";

//统计
busline_search_global_bmap.onGetBusListCompleteCount = 0;
busline_search_global_bmap.onGetBusLineCompleteCount = 0;
busline_search_global_bmap.getBusListCount = 0;
busline_search_global_bmap.getBusLineCount = 0;
busline_search_global_bmap.last_remember_count = 0;

busline_search_global_bmap.execute_buslines_search = function (allLineSearchDone_Callback, city, city_lines, map_provider_name){
  busline_search_global_bmap.allDone_callback = allLineSearchDone_Callback;

  var busline = new BMap.BusLineSearch(city,{
      onGetBusListComplete: function(result){
         if(result) {

            var busItemCount = result.getNumBusList();
            for (var i = 0; i < busItemCount; i++){

                // 触发线路详细的搜索
                var fstLine = result.getBusListItem(i);
                busline.getBusLine(fstLine);
                ++busline_search_global_bmap.getBusLineCount;
            }
            ++busline_search_global_bmap.onGetBusListCompleteCount;

            console.log("baidu map buslist search succeed count " + busline_search_global_bmap.onGetBusListCompleteCount);

         }else{
            console.log("onGetBusListComplete failed.");
         }
      },
      onGetBusLineComplete: function(result){
          if(result) {

              var stops_txt = "";
              var path_txt = "";

              var busStopsCount = result.getNumBusStations();
              for (var i = 0; i < busStopsCount; i++){
                stops_txt += (city + "," + result.name + "," + "stops" + "," + (i + 1) + "," 
                  +  result.getBusStation(i).position.lng + "," + result.getBusStation(i).position.lat + "," + result.getBusStation(i).name + "</br>");
              }

              var pathArr = result.getPath();
              for (var j = 0; j < pathArr.length; j++) {
                path_txt += (city + "," + result.name + "," + "path" + "," + (j + 1) + "," + pathArr[j].lng + "," + pathArr[j].lat + "</br>");
              }

              //save them
              busline_search_global_bmap.outStr += stops_txt;
              busline_search_global_bmap.outStr += path_txt;
              ++busline_search_global_bmap.onGetBusLineCompleteCount;
              console.log("baidu map busline search succeed count " + busline_search_global_bmap.onGetBusLineCompleteCount + ", Line:" + result.name);


          } else {
              console.log("onGetBusLineComplete failed.");
          }

      }
  });

  for (var i in city_lines){

    //先根据已知线路名, 作为关键词搜索getBusLine详细信息所需要的busListItem
    //每个getBusList调用应对应一次onGetBusListComplete返回
    busline.getBusList(city_lines[i]);
    busline_search_global_bmap.getBusListCount++;
  }

  waitForAllBusLineResult_Callback = function(){
    console.log("time waked up, getBusList count: " + busline_search_global_bmap.getBusListCount
          + ", getBusList complete count: " + busline_search_global_bmap.onGetBusListCompleteCount
          + ", getBusLine count: " + busline_search_global_bmap.getBusLineCount
          + ", getBusLine complete count: " + busline_search_global_bmap.onGetBusLineCompleteCount
          + ", last_remember_count: " + busline_search_global_bmap.last_remember_count);


    if (0 != busline_search_global_bmap.last_remember_count && (busline_search_global_bmap.onGetBusListCompleteCount + busline_search_global_bmap.onGetBusLineCompleteCount) == busline_search_global_bmap.last_remember_count)
    {
        //NOTE: 结果不再变化, 触发外部的下一步动作 
        console.log("bus list/line search result has no change" 
          + ", getBusList count: " + busline_search_global_bmap.getBusListCount
          + ", getBusList complete count: " + busline_search_global_bmap.onGetBusListCompleteCount
          + ", getBusLine count: " + busline_search_global_bmap.getBusLineCount
          + ", getBusLine complete count: " + busline_search_global_bmap.onGetBusLineCompleteCount
          + ", we'll write.");
        busline_search_global_bmap.allDone_callback(busline_search_global_bmap.outStr, map_provider_name);
    }
    else
    {
        busline_search_global_bmap.last_remember_count = busline_search_global_bmap.onGetBusListCompleteCount + busline_search_global_bmap.onGetBusLineCompleteCount;
        setTimeout(waitForAllBusLineResult_Callback , 1000);
    }

}


  setTimeout(waitForAllBusLineResult_Callback , 1000);
}

