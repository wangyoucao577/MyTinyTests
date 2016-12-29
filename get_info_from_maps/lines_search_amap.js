/**
 * @file busline search function on AMap
 * @author wangyoucao577(wangyoucao577@gmail.com)
 */


//文件内的全局变量
var lines_search_global_amap = {};

//全局变量, temp result for line search callback
lines_search_global_amap.outStr = "";    //统一输出
lines_search_global_amap.searchSucceedCallbackCount = 0;
lines_search_global_amap.searchFailedCallbackCount = 0;


// 等待线路搜索结束, 并结果写入文件
lines_search_global_amap.last_remember_count = 0;
function waitForLineSearchResult_Callback(){
    console.log("time waked up, search succeed count: " + lines_search_global_amap.searchSucceedCallbackCount + ", search failed count: " + lines_search_global_amap.searchFailedCallbackCount 
        + ", last_remember_count: " + lines_search_global_amap.last_remember_count);
    if ((lines_search_global_amap.searchSucceedCallbackCount + lines_search_global_amap.searchFailedCallbackCount) == lines_search_global_amap.city_lines.length)
    {
        //all callback comes, write succeed to file
        console.log("All lineSearch callback executed, we'll write.");
        lines_search_global_amap.allDone_callback(lines_search_global_amap.expect_city, lines_search_global_amap.outStr, lines_search_global_amap.map_provider_name);
        //write_to_file();
    }
    else if (0 != lines_search_global_amap.last_remember_count && (lines_search_global_amap.searchSucceedCallbackCount + lines_search_global_amap.searchFailedCallbackCount) == lines_search_global_amap.last_remember_count)
    {
        console.log("Lost lineSearch callback count: " + (lines_search_global_amap.city_lines.length - lines_search_global_amap.last_remember_count) + ", we'll write.");
        lines_search_global_amap.allDone_callback(lines_search_global_amap.expect_city, lines_search_global_amap.outStr, lines_search_global_amap.map_provider_name);
        //write_to_file();
    }
    else
    {
        lines_search_global_amap.last_remember_count = lines_search_global_amap.searchSucceedCallbackCount + lines_search_global_amap.searchFailedCallbackCount;
        setTimeout(waitForLineSearchResult_Callback , 1000);
    }
}


//公交线路搜索的回调, 处理查询到的数据
function lineSearch_Callback(result)
{
    //document.getElementById("result").innerHTML = result.info;

    var stops_txt = "";
    var path_txt = "";
    
    var lineArr = result.lineInfo;
    for (var i = 0; i < lineArr.length; i++) {

        //deal with stops and path
        var pathArr = lineArr[i].path;
        var stops = lineArr[i].via_stops;
        //stops_txt += "stops: </br>";
        for (var j = 0; j < stops.length; j++) {
            stops_txt += (lines_search_global_amap.expect_city + "," + lineArr[i].name + "," + "stops" + "," + (j + 1) + "," +  stops[j].location + "," + stops[j].name + "</br>");
        }
        //stops_txt += "paths: </br>"
        for (var j = 0; j < pathArr.length; j++) {
            path_txt += (lines_search_global_amap.expect_city + "," + lineArr[i].name + "," + "path" + "," + (j + 1) + "," + pathArr[j].toString() + "</br>")
        }
    }

    //document.getElementById("stops").innerHTML = stops_txt
    //document.getElementById("path").innerHTML = path_txt

    //save them
    lines_search_global_amap.outStr += stops_txt;
    lines_search_global_amap.outStr += path_txt;
    ++lines_search_global_amap.searchSucceedCallbackCount;
    console.log("line search succeed count " + lines_search_global_amap.searchSucceedCallbackCount + ", Line:" + lineArr[0].name);
}

lines_search_global_amap.executeLineSearch = function (allLineSearchDone_Callback, city, city_lines, map_provider_name){
    lines_search_global_amap.allDone_callback = allLineSearchDone_Callback;
    lines_search_global_amap.city_lines = city_lines;
    lines_search_global_amap.expect_city = city;
    lines_search_global_amap.map_provider_name = map_provider_name;

    //加载公交路线查询服务
    //实例化公交线路查询类，只取回一条路线
    AMap.service(["AMap.LineSearch"], function search_line_in_city() {

        console.log("city:" + city + ", lines_count:" + city_lines.length);
        for (var n in city_lines)
        {
            var expect_line = city_lines[n];

            var linesearch = new AMap.LineSearch({
                pageIndex:1,
                city:city,
                pageSize:1,
                extensions:'all'//返回全部信息
            });
        
            //调用search方法
            //搜索 公交线路
            linesearch.search(expect_line, function(status, result){
                //取回公交路线查询结果
                if(status === 'complete' && result.info === 'OK'){
                    //取得了正确的公交路线结果
     
                    lineSearch_Callback(result);

                    //结果处理函数，demo中绘制了线路
     
                }else{
                    //无数据或者查询失败, 输出错误信息
                    //document.getElementById("result").innerHTML = status + " " + result.info;
                    ++lines_search_global_amap.searchFailedCallbackCount;
                    //console.log("line search failed count " + lines_search_global_amap.searchFailedCallbackCount + ", error info: "+ status + ", " + result.info);
                }
            });
        }

        //first wait
        setTimeout(waitForLineSearchResult_Callback , 1000);
    });
}

// 入口
//executePlaceSearchForCity();
//executeLineSearch();