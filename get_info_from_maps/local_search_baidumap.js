
var local_search_global_bmap = {};

local_search_global_bmap.localSearch_Callback = function (result) {
    
  console.log(result);
  // if (local.getStatus() == BMAP_STATUS_SUCCESS){      
  //       // 判断状态是否正确      
  //       // var s = [];      
  //       // for (var i = 0; i < results.getCurrentNumPois(); i ++){      
  //       //     s.push(results.getPoi(i).title + ", " + results.getPoi(i).address);      
  //       // }      
  // } else {
    
  // }     
}

//入口


local_search_global_bmap.execute_local_search = function (city, place){

  var options = {      
      onSearchComplete: local_search_global_bmap.localSearch_Callback,    
      pageCapacity:100
  };      

  var local = new BMap.LocalSearch(city, options);     
  local.search(place);

}

