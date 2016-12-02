function lineSearch_Callback(result)
{
    var txt = result.info + "</br>";
    txt += (result.lineInfo.length + "</br>");

    var lineArr = result.lineInfo;

    for (var i = 0; i < lineArr.length; i++) {
        var pathArr = lineArr[i].path;
        var stops = lineArr[i].via_stops;
        txt += "stops: </br>";
        for (var j = 0; j < stops.length; j++) {
            txt += (stops[j].location + "," + stops[j].name + "</br>");
        }
        txt += "paths: </br>"
        for (var j = 0; j < pathArr.length; j++) {
            txt += (pathArr[j].toString() + "</br>")
        }
    }
    // var lineArr = data.lineInfo;
    // var lineNum = data.lineInfo.length;
    //     if (lineNum == 0) {
    //     } else {
    //         for (var i = 0; i < lineNum; i++) {
    //             var pathArr = lineArr[i].path;
    //             var stops = lineArr[i].via_stops;
    //             var startPot = stops[0].location;
    //             var endPot = stops[stops.length - 1].location;

    //             if (i == 0) drawbusLine(startPot, endPot, pathArr);
    //         }
    //     }
    document.getElementById("id1").innerHTML = txt

}
	
//加载公交路线查询服务
//实例化公交线路查询类，只取回一条路线
AMap.service(["AMap.LineSearch"], function() {
    var linesearch = new AMap.LineSearch({
    pageIndex:1,
    city:'深圳',
    pageSize:1,
    extensions:'all'//返回全部信息
    });
    //TODO:调用search方法

    //搜索“536”相关公交线路
linesearch.search('高快巴士10', function(status, result){
    //取回公交路线查询结果
    if(status === 'complete' && result.info === 'OK'){
                //取得了正确的公交路线结果
 
        lineSearch_Callback(result);
                //结果处理函数，demo中绘制了线路
 
    }else{
        //无数据或者查询失败
 
    }
});
});
