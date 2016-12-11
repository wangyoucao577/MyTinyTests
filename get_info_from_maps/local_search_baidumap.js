
var local_search_global_bmap = {};

local_search_global_bmap.execute_local_search = function (city, place){

  var local = new BMap.LocalSearch(city, {      
      onSearchComplete: function (result) {
          //console.log(result);
          console.log("NumPages: " + result.getNumPages() + ", NumPois: " + result.getNumPois() 
            + ", CurrentNumPois: " + result.getCurrentNumPois() + ", PageIndex: " + result.getPageIndex());

          

          for (var i = 0; i < result.getCurrentNumPois(); ++i){
            var poi = result.getPoi(i);
            console.log("local poi result " + i + ", title: " + poi.title + ", location: " + poi.point.lng + "," + poi.point.lat
              + ", address: " + poi.address);
          }

          //后续还有结果页面, 应翻页
          if (result.getPageIndex() + 1 < result.getNumPages()){
            local.gotoPage(result.getPageIndex() + 1);
          }else{
            console.log("all pages completed");
          }

      },    
      pageCapacity:100
  });     
  local.search(place, {forceLocal:true});

}

