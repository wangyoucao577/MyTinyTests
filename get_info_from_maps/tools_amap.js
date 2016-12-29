/**
 * @file 针对AMap的专用的工具函数
 * @author wangyoucao577(wangyoucao577@gmail.com)
 */


var tools_amap = {};

tools_amap.location_array_to_string = function(location_array){

    return array_to_string(location_array);
}

//from presentation format to AMap format
tools_amap.location_array_convert = function (location_array) {

    //NOTE: AMap的location存储方式为所见即所得, 不需要转换
    return location_array;
}