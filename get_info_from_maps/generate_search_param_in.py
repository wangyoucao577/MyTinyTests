#!/usr/bin/python2
# -*- coding: utf-8 -*-

"""
Description: 合并各个渠道(AMap/BaiduMap PlaceSearch迭代, wiki城市公交列表等)输出的文件, 生成定义的search_param_in.js文件, 供后续搜索使用
Author:     wangyoucao577@gmail.com
Created Date:   2016-12-30
Version:        2016-12-30
"""

import sys
sys.path.append(sys.path[0] + r'\..')   #上级目录中加入搜寻列表, 以便于导入上级目录中的py模块
from files_operation import *

def main():
    if (len(sys.argv) < 3):
        print "Usage: "
        print "      python generate_search_param_in.py <out_file_name> <in_file_path[,in_file_path,...]>" 
        print "Sample: "
        print "      python generate_search_param_in.py out_search_param_in.js D:\Lines_Stations_Locations_temp_AMap_20161230_163140.txt"
        return

    in_files_list = sys.argv[2].split(',')
    out_file_path = sys.path[0] + "\\" + sys.argv[1]
    #print in_files_list
    #print out_file_path

    # 组织out_file的所有内容, 一次性写入文件
    out_file_all_str = ""

            
if __name__ == '__main__':
    main()
    

            