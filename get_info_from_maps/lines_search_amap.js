
//NOTE:输入参数, 目标城市, 及城市对应的线路列表
var expect_city = '深圳';
//var city_lines = ['1', '2', '3', '4', '5', '7', '8', '9', '10', '11', '12', '13', '14', '17', '18', '19', '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '32', '33', '34', '36', '37', '38', '40', '41', '42', '43', '44', '45', '46', '49', '50', '52', '54', '54区间', '57', '58', '59', '60', '61', '62', '63', '64', '65', '66', '67', '68', '69', '70', '71', '72', '73', '74', '75', '76区间', '79', '80', '81', '82', '83', '85', '90', '97', '101', '102', '103', '103B', '104', '107', '108', '111', '113', '121', '122', '123', '201', '202', '203', '204', '205', '207', '209', '211', '212', '213', '214', '215', '216', '218', '220', '222', '223', '225', '226', '229', '233', '234', '235', '236', '237', '239', '242', '245', '302', '302区间', '303', '306', '306区间', '307', '308', '309', '311', '312', '313', '316', '317', '317区间高峰', '320', '321', '322', '323', '324', '325', '325B', '326', '327', '328', '330B', '331', '332', '333', '334', '334区间', '336', '337', '338', '339', '351', '352', '357', '358', '362', '363', '365', '366', '369', '371', '372', '373', '374', '375', '376', '377', '379', '380A', '380B', '381', '382', '383', '385', '387', '390', '391', '392', '392区间', '393', '395', '398', '603', '605', '606', '610', '612', '613', '615', '620', '621', '624', '627', '629', '630', '631', '635', '639', '650', '651', '652', '653', '655', '656', '668', '704', '707', '718', '720', '723', '727', '759', '767', '769', '779', '780', '781', '782', '789', '790', '791', '794', '797', '802', '810', '811', '812', '818', '821B', '822', '833', '836', '839', '862', '862区间线', '866', '868', '868区间1线', '868区间2', '881', '882', '906', '907', '915', '923', '926', '929', '930', '932', '935', '937', '939', '941', '954', '956', '963', '964', '968B', '977', '978', '979', '980', '982', '982B', 'B604', 'B605', 'B607', 'B608', 'B609', 'B611', 'B613', 'B614', 'B615', 'B618', 'B619', 'B621', 'B622', 'B623', 'B624', 'B626', 'B629', 'B630', 'B631', 'B634', 'B637', 'B640', 'B641', 'B642', 'B643', 'B644', 'B645', 'B646', 'B648', 'B649', 'B650', 'B651', 'B652', 'B653', 'B654', 'B655', 'B656', 'B657', 'B658', 'B659', 'B660', 'B662', 'B663', 'B663区间线', 'B665', 'B666', 'B667', 'B668', 'B669', 'B670', 'B671', 'B673', 'B675', 'B678', 'B679', 'B682', 'B683', 'B685', 'B688', 'B689', 'B690', 'B691', 'B692', 'B693', 'B695', 'B696', 'B697', 'B698', 'B701', 'B706', 'B707', 'B708', 'B709', 'B710', 'B711', 'B713', 'B714', 'B715', 'B716', 'B718', 'B719', 'B720', 'B722', 'B723', 'B725', 'B726', 'B728', 'B729', 'B730', 'B731', 'B732', 'B733', 'B736', 'B737', 'B738', 'B739', 'B740', 'B741', 'B742', 'B742区间', 'B743', 'B744', 'B745', 'B746', 'B750', 'B751', 'B752', 'B753', 'B760', 'B761', 'B762', 'B764', 'B765', 'B766', 'B767', 'B768', 'B769', 'B774', 'B775', 'B776', 'B778', 'B780', 'B781', 'B784', 'B786', 'B788', 'B789', 'B790', 'B791', 'B792', 'B795', 'B796', 'B797', 'B798', 'B803', 'B804', 'B805', 'B810', 'B811', 'B812', 'B813', 'B815', 'B816', 'B817', 'B818', 'B820', 'B821', 'B826', 'B827', 'B828', 'B829', 'B830', 'B831', 'B837', 'B838', 'B839', 'B840', 'B842', 'B843', 'B847', 'B849', 'B850', 'B851', 'B852', 'B854', 'B855', 'B856', 'B858', 'B859', 'B861', 'B864', 'B867', 'B868', 'B870', 'B872', 'B873', 'B874', 'B875', 'B876', 'E1', 'E2', 'E3', 'E4', 'E5', 'E6', 'E7', 'E8', 'E9', 'E10', 'E11', 'E11区间线', 'E12', 'E15', 'E16', 'E18', 'E19', 'E20', 'E21', 'E22', 'E23', 'E24', 'E25', 'E26', 'E27', 'J1', 'K105', 'K113', 'K204', 'K318', 'K359', 'K384', 'K538沙井线', 'K538松岗线', 'K578福田线', 'K578南山线', 'M200', 'M201', 'M202', 'M203', 'M204', 'M206', 'M209', 'M210', 'M211', 'M212', 'M214', 'M215-M218环线', 'M216', 'M217', 'M219', 'M220', 'M221', 'M222', 'M223', 'M224', 'M225', 'M226', 'M227', 'M228', 'M229', 'M230', 'M231', 'M232', 'M233', 'M234', 'M235', 'M236', 'M237', 'M238', 'M240', 'M241', 'M242', 'M243', 'M244', 'M245', 'M246', 'M247', 'M248', 'M249', 'M250', 'M251', 'M252', 'M253', 'M254', 'M255', 'M256', 'M257', 'M258', 'M259', 'M260', 'M261', 'M262', 'M263', 'M264', 'M265', 'M266', 'M267', 'M268', 'M269', 'M270', 'M271', 'M272', 'M273', 'M274', 'M275', 'M276', 'M277', 'M278', 'M279', 'M280', 'M281', 'M282', 'M283', 'M284', 'M285', 'M286', 'M287', 'M288', 'M289', 'M290', 'M291', 'M292', 'M293', 'M294', 'M295', 'M296', 'M297', 'M299', 'M300', 'M301', 'M302', 'M303', 'M304', 'M305', 'M306', 'M307', 'M308', 'M309', 'M310', 'M311', 'M312', 'M313', 'M314', 'M315', 'M316', 'M317', 'M318', 'M319', 'M320', 'M321', 'M322', 'M324', 'M325', 'M326', 'M327', 'M330', 'M331', 'M332', 'M333', 'M334', 'M335', 'M336', 'M337', 'M338', 'M339', 'M340', 'M341', 'M342', 'M343', 'M344', 'M345', 'M346', 'M347', 'M348', 'M349', 'M350', 'M351', 'M352', 'M353', 'M354', 'M355', 'M357', 'M358', 'M359', 'M360', 'M361', 'M362', 'M363', 'M364', 'M365', 'M366', 'M367', 'M368', 'M369', 'M370', 'M371', 'M372', 'M373', 'M374', 'M375', 'M376', 'M377', 'M378', 'M379', 'M380', 'M381', 'M382', 'M383', 'M384', 'M385', 'M386', 'M388', 'M389', 'M390', 'M391', 'M392', 'M393', 'M394', 'M397', 'M399', 'M400', 'M401', 'M402', 'M403', 'M404', 'M405', 'M406', 'M407', 'M408', 'M409', 'M410', 'M411', 'M412', 'M413', 'M414', 'M415', 'M416', 'M418', 'M419', 'M420', 'M421', 'M422', 'M423', 'M424', 'M425', 'M426', 'M427', 'M429', 'M430', 'M431', 'M432', 'M433', 'M434', 'M435', 'M436', 'M437', 'M438', 'M439', 'M440', 'M441', 'M442', 'M443', 'M444', 'M445', 'M446', 'M447', 'M448', 'M449', 'M450', 'M451', 'M452', 'M453', 'M454', 'M455', 'M456', 'M457', 'M458', 'M459', 'M460', 'M461', 'M462', 'M463', 'M464', 'M465', 'M466', 'M467', 'M468', 'M469', 'M470', 'M471', 'M472', 'M473', 'M474', 'M475', 'M476', 'M477', 'M478', 'M479', 'M480', 'M481', 'M482', 'M483', 'M484', 'M485', 'M486', 'M487', 'M489', 'M490', 'M491', 'M492', 'M493', 'M494', 'M495', 'M496', 'M497', 'M498', 'M499', 'M500', 'M501', 'M502', 'N1（70）', 'N2（83）', 'N3（3）', 'N4（204）', 'N6（59）', 'N7（1）', 'N8（19）', 'N9（60）', 'N10（63）', 'N12（216）', 'N13（M369）', 'N14（220）', 'N16（8）', 'N17', 'N18（97）', 'N19（307）', 'N21（E12）', 'N24（72）', 'N25（9）', 'N26', 'N27', '高峰专线1', '高峰专线3', '高峰专线7', '高峰专线8', '高峰专线9', '高峰专线10', '高峰专线11', '高峰专线12', '高峰专线13', '高峰专线14', '高峰专线15', '高峰专线17', '高峰专线18', '高峰专线19', '高峰专线21', '高峰专线22', '高峰专线23', '高峰专线24', '高峰专线25', '高峰专线26', '高峰专线30', '高峰专线32', '高峰专线33', '高峰专线38', '高峰专线39', '高峰专线49', '高峰专线51', '高峰专线53', '高峰专线54', '高峰专线55', '高峰专线56', '高峰专线57', '高峰专线58', '高峰专线59', '高峰专线60', '高峰专线61', '高峰专线62', '高峰专线64', '高峰专线65', '高峰专线66', '高峰专线67', '高峰专线68', '高峰专线69', '高峰专线70', '高峰专线71', '高峰专线72', '高峰专线73', '高峰专线74', '高峰专线75', '高峰专线76', '高峰专线80', '高峰专线81', '高峰专线82', '高峰专线83', '高峰专线84', '高峰专线86', '高峰专线87', '高峰专线89', '高峰专线90', '高峰专线91', '高峰专线92', '高峰专线93', '高峰专线94', '高峰专线95', '高峰专线97', '高峰专线98', '高峰专线99', '高峰专线100', '高峰专线101', '高峰专线102', '高峰专线103', '高峰专线104', '高峰专线105', '高峰专线106', '高峰专线107', '高峰专线108', '高峰专线109', '高峰专线110', '高峰专线111', '高峰专线112', '高峰专线113', '高峰专线114', '高峰专线115', '高峰专线116', '高峰专线117', '高峰专线118', '高峰专线119', '高峰专线120', '高峰专线121', '高峰专线122', '高峰专线123', '高快巴士1', '高快巴士3', '高快巴士4', '高快巴士7', '高快巴士8', '高快巴士9', '高快巴士10', '高快巴士13', '高快巴士16', '机场1线', '机场2线', '机场4线', '机场5线', '机场5区间线', '机场6线', '机场7线', '机场8线', '机场9线', '机场10线', '观光线', '观光购物线', '口岸观光线', '海滨观光线', '大鹏金沙湾旅游专线', '海上田园旅游专线1', '海上田园旅游专线2', '欧洲城假日专线', '梧桐山假日专线1', '梧桐山假日专线2', '滨海休闲观光假日专线', '大梅沙假日专线1', '大梅沙假日专线2', '大梅沙假日专线3', '大鹏半岛假日专线1', '大鹏半岛假日专线2', '大鹏半岛假日专线3', '大鹏半岛假日专线4', '大鹏半岛假日专线5', '大鹏暑期周末专线1', '大鹏暑期周末专线2', '大鹏暑期周末专线3', '大鹏暑期周末专线4', '大鹏暑期周末专线5', 'T1', 'T2', 'T2A', '仙湖植物园穿梭巴士', '大运城邦-深圳湾口岸专线', '松岗汽车站-坪山汽车站专线', '第三人民医院高峰专线', '东部华侨城旅游专线', '东部假日专线', '凤凰山景区接驳公交专线', '福田保税区1号', '联通区间线', '深惠1线', '深惠2线', '深惠3线', '深惠3A线', '深惠3线海滨支线', '深莞1线', '深莞2线']
var city_lines = [];

//全局变量, temp result for line search callback
var outStr = "";    //统一输出
var searchSucceedCallbackCount = 0;
var searchFailedCallbackCount = 0;


//通用的error handler
function errorHandler(e) {

  console.log(e.name + ": " + e.message);
}

//申请空间, 线路的搜索结果写入文件
function write_to_file()
{
    var new_file = expect_city + "_" + (new Date()).toString() + ".txt";

    //申请空间, save to File
    window.webkitRequestFileSystem(window.TEMPORARY, 100*1024*1024, function onInitFs(fs) {
      //console.log('Opened file system: ' + fs.name);

      fs.root.getFile(new_file, {create: true}, function(fileEntry) {
            fileEntry.createWriter(function(writer) {
                writer.onerror = errorHandler;
                writer.onwriteend = function(e) {
                    console.log('write complete, ' + new_file + ', total search succeed count ' + searchSucceedCallbackCount + ", failed count " + searchFailedCallbackCount);
                };
                writer.write(new Blob([outStr.replace(/<\/br>/g, "\n")], {type: 'text/plain'}));
            });
      }, errorHandler);
    }, errorHandler);
}

// 等待线路搜索结束, 并结果写入文件
var last_remember_count = 0;
function waitForLineSearchResult_Callback(){
    console.log("time waked up, search succeed count: " + searchSucceedCallbackCount + ", search failed count: " + searchFailedCallbackCount 
        + ", last_remember_count: " + last_remember_count);
    if ((searchSucceedCallbackCount + searchFailedCallbackCount) == city_lines.length)
    {
        //all callback comes, write succeed to file
        console.log("All callback executed, we'll write.");
        write_to_file();
    }
    else if (0 != last_remember_count && (searchSucceedCallbackCount + searchFailedCallbackCount) == last_remember_count)
    {
        console.log("Lost search callback count: " + (city_lines.length - last_remember_count) + ", we'll write.");
        write_to_file();
    }
    else
    {
        last_remember_count = searchSucceedCallbackCount + searchFailedCallbackCount;
        setTimeout(waitForLineSearchResult_Callback , 1000);
    }
}

// 等待站点搜索结果, 并触发线路搜索
var expect_total_place_search_result_count = 0;
var total_place_search_result_count = 0;
function waitForPlaceSearchResult_Callback(){
    if (0 != expect_total_place_search_result_count
        && total_place_search_result_count == expect_total_place_search_result_count){
        // 已完成公交站点的搜索, 并完成了city_lines的生成
        console.log("All place search succeed, city_lines.length: " + city_lines.length);
        console.log(city_lines);

        // 触发线路搜索
        executeLineSearch();
    }else{
        setTimeout(waitForPlaceSearchResult_Callback, 1000);
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
            stops_txt += (expect_city + "," + lineArr[i].name + "," + "stops" + "," + (j + 1) + "," +  stops[j].location + "," + stops[j].name + "</br>");
        }
        //stops_txt += "paths: </br>"
        for (var j = 0; j < pathArr.length; j++) {
            path_txt += (expect_city + "," + lineArr[i].name + "," + "path" + "," + (j + 1) + "," + pathArr[j].toString() + "</br>")
        }
    }

    //document.getElementById("stops").innerHTML = stops_txt
    //document.getElementById("path").innerHTML = path_txt

    //save them
    outStr += stops_txt;
    outStr += path_txt;
    ++searchSucceedCallbackCount;
    console.log("line search succeed count " + searchSucceedCallbackCount + ", Line:" + lineArr[0].name);
}

function placeSearch_Callback(result)
{
    console.log("placeSearch callback, count " + result.poiList.count + ", pageIndex " + result.poiList.pageIndex);

    if (0 == expect_total_place_search_result_count){
        expect_total_place_search_result_count = result.poiList.count;
    }
    
    var pois = result.poiList.pois;
    for (var i = 0; i < pois.length; i++) {
        var lines_address = pois[i].address;
        var this_lines = lines_address.replace('...', "").split(';');
        for (var j in this_lines){
            if (-1 == city_lines.indexOf(this_lines[j])){
                city_lines.push(this_lines[j]);
            }
        }
    }

    total_place_search_result_count += pois.length;
    console.log("city_lines.length: " + city_lines.length + ", total place search result count: " + total_place_search_result_count);
}

function executePlaceSearchForCity(){
    //先查询城市的公交站点
    AMap.service('AMap.PlaceSearch',function(){//回调函数

        for (var i = 1; i <= 100; i++){ //pageIndex range 1~100

            //实例化PlaceSearch
            var placeSearch = new AMap.PlaceSearch({ //构造地点查询类
                pageSize: 100,
                pageIndex: i,
                type:"公交车站",
                city: expect_city, //城市
                extensions:'all'//返回全部信息
            });

            //使用placeSearch对象调用关键字搜索的功能

            //关键字查询
            placeSearch.search('', function(status, result) {
                //取回公交站点的查询结果
                if(status === 'complete' && result.info === 'OK'){
                    //取得了正确的公交站点结果

                    placeSearch_Callback(result);
                }else{
                    //无数据或者查询失败, 输出错误信息
                    //console.log("placeSearch failed, ignored.");
                }    
            });
        }
        setTimeout(waitForPlaceSearchResult_Callback, 1000);
    });

}

function executeLineSearch(){
    //加载公交路线查询服务
    //实例化公交线路查询类，只取回一条路线
    AMap.service(["AMap.LineSearch"], function search_line_in_city() {

        console.log("city:" + expect_city + ", lines_count:" + city_lines.length);
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
                    //document.getElementById("result").innerHTML = status + " " + result.info;
                    ++searchFailedCallbackCount;
                    console.log("line search failed count " + searchFailedCallbackCount + ", error info: "+ status + ", " + result.info);
                }
            });
        }

        //first wait
        setTimeout(waitForLineSearchResult_Callback , 1000);
    });
}

// 入口
executePlaceSearchForCity();
//executeLineSearch();