
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