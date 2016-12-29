/**
 * @file 针对GoogleMap的专用的工具函数
 * @author wangyoucao577(wangyoucao577@gmail.com)
 */


var tools_gmap = {};

tools_gmap.convert_city_to_bounds = function (city) {

    var geo_promise = new Promise(function (resolve, reject) {
        var geo = new google.maps.Geocoder();
        geo.geocode({address: city}, function (results, status) {
            if (status == google.maps.places.PlacesServiceStatus.OK){
                console.log("convert " + city + " to location ok, use the first one.\n");
                for (var i = 0; i < results.length; ++i) {
                    console.log("index: " + i + ", " + results[i].geometry.bounds + "\n");
                }

                //choose the first result for use
                resolve(results[0].geometry.bounds);
            }
            else {
                console.log("convert " + city + " to location failed, status " + status + "\n");
            }
        });
    });
    return geo_promise;

}