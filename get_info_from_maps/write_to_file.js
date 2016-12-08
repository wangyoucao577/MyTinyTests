

//申请空间, 线路的搜索结果写入文件
function write_to_file(city, out_str)
{
    var new_file = city + "_" + (new Date()).toString() + ".txt";

    //申请空间, save to File
    window.webkitRequestFileSystem(window.TEMPORARY, 100*1024*1024, function onInitFs(fs) {
      //console.log('Opened file system: ' + fs.name);

      fs.root.getFile(new_file, {create: true}, function(fileEntry) {
            fileEntry.createWriter(function(writer) {
                writer.onerror = errorHandler;
                writer.onwriteend = function(e) {
                    console.log('write complete, file:' + new_file);
                };
                writer.write(new Blob([out_str.replace(/<\/br>/g, "\n")], {type: 'text/plain'}));
            });
      }, errorHandler);
    }, errorHandler);
}

