
/*
 * 针对BaiduMap的专用的工具函数
 *
 * */


var tools_bmap = {};

tools_bmap.location_array_to_string = function(location_array){
    var out_str = "[";
    for (var i in location_array){
        out_str += "\'" + location_array[i].lng + "," + location_array[i].lat + "\'" ;
        if (i < location_array.length - 1){
            out_str += ", ";
        }
    }
    out_str += "]";

    return out_str;
}

//from presentation format to BaiduMap format
tools_bmap.location_array_convert = function (location_arr) {
    var location_arr_bmap = [];

    //BaiduMap的location 需要用BMap的Point结构进行存储
    for (var i = 0; i < location_arr.length; ++i){
        var loc = location_arr[i].split(',');
        if (!(loc.length == 2)){
            console.log("loc length " + loc.length + " error, ignore this value: " + loc + "\n");
            continue;
        }
        location_arr_bmap.push(new BMap.Point(loc[0], loc[1]));
    }

    return location_arr_bmap;
}