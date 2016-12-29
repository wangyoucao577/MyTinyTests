/**
 * @file place search function on Google map
 * @author wangyoucao577(wangyoucao577@gmail.com)
 */


//NOTE: 与BaiduMap和AMap不同, GoogleMap的JavaScript API貌似并未提供通过公交站点的公交线路.
//      代码先留着, 有时需要测试用. 几种placeSearch调用方式都差不多.

//参考
//https://developers.google.com/maps/documentation/javascript/places#place_search_requests
//https://developers.google.com/maps/documentation/javascript/reference#PlaceResult

var place_search_global_gmap = {};

place_search_global_gmap.execute_get_details = function (service, place_id) {
    service.getDetails({
        placeId: place_id
    }, 
    function (result, status) {
        if (status == google.maps.places.PlacesServiceStatus.OK) {
            console.log("name: " + result.name + ", place_id: " + result.place_id + ", vicinity: " + result.vicinity + "\n");
        }else{
            console.log("getDetails failed, status: " + status);
        }
    });
}


place_search_global_gmap.execute_nearby_search = function (all_done_callback, city, map_provider_name){

    //TODO: could transfer city to location
    var pyrmont = new google.maps.LatLng(31.1770572,121.4232641);

    var map = new google.maps.Map(document.createElement('map'), {
        center: pyrmont,
        zoom: 15
    });

    var service = new google.maps.places.PlacesService(map);
    service.textSearch({
            //keyword: '公交',
            query: '地铁站',
            location: pyrmont,
            radius: '50000',
            //type: 'bus_station'
        },
        function (results, status){
              console.log(status);
              if (status == google.maps.places.PlacesServiceStatus.OK){
                  for (var i = 0; i < results.length; ++i) {
                      console.log("index: " + i + ", name: " + results[i].name + ", place_id: " + results[i].place_id + ", vicinity: " +  results[i].vicinity + "\n");
                      //TODO: for GoogleMap

                      place_search_global_gmap.execute_get_details(service, results[i].place_id);
                  }
              }
        }
    );

}

