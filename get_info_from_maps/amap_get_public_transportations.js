
//目标城市
var expect_city = '深圳';

//TODO: 抓取所有的线路
var city_lines = ['高快巴士10', '高峰专线13','M416'];



//初始化文件系统失败的错误处理
function errorHandler(e) {

  console.log(e.name + ": " + e.message);
}

//temp result for search callback
var outStr = "";    //统一输出
var searchCallbackCount = 0;

//公交线路搜索的回调, 处理查询到的数据
function lineSearch_Callback(result)
{
    document.getElementById("result").innerHTML = result.info;

    var stops_txt = "";
    var path_txt = "";
    
    var lineArr = result.lineInfo;
    for (var i = 0; i < lineArr.length; i++) {

        //deal with stops and path
        var pathArr = lineArr[i].path;
        var stops = lineArr[i].via_stops;
        //stops_txt += "stops: </br>";
        for (var j = 0; j < stops.length; j++) {
            stops_txt += (expect_city + "," + lineArr[i].name + "," + "stops" + "," + (j + 1) + "," +  stops[j].location + "," + stops[j].name + "</br>");
        }
        //stops_txt += "paths: </br>"
        for (var j = 0; j < pathArr.length; j++) {
            path_txt += (expect_city + "," + lineArr[i].name + "," + "path" + "," + (j + 1) + "," + pathArr[j].toString() + "</br>")
        }
    }

    document.getElementById("stops").innerHTML = stops_txt
    document.getElementById("path").innerHTML = path_txt

    //save them
    outStr += stops_txt;
    outStr += path_txt;
    ++searchCallbackCount;

    if (searchCallbackCount === city_lines.length)
    {
        //申请空间, save to File
        window.webkitRequestFileSystem(window.TEMPORARY, 5*1024*1024, function onInitFs(fs) {
          console.log('Opened file system: ' + fs.name);

          fs.root.getFile(expect_city + "_" + (new Date()).toString(), {create: true}, function(fileEntry) {
                fileEntry.createWriter(function(writer) {
                    writer.onerror = errorHandler;
                    writer.onwriteend = function(e) {
                        console.log('write complete');
                    };
                    writer.write(new Blob([outStr.replace(/<\/br>/g, "\n")], {type: 'text/plain'}));
                });
          }, errorHandler);
        }, errorHandler);
    }
}


//加载公交路线查询服务
//实例化公交线路查询类，只取回一条路线
AMap.service(["AMap.LineSearch"], function search_line_in_city() {

    for (var n in city_lines)
    {
        var expect_line = city_lines[n];

        var linesearch = new AMap.LineSearch({
        pageIndex:1,
        city:expect_city,
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
            document.getElementById("result").innerHTML = status + " " + result.info;
            console.log(result);
        }});
    }
});
