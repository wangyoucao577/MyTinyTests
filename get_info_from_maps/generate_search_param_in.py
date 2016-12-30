#!/usr/bin/python2
# -*- coding: utf-8 -*-

"""
Description: 合并各个渠道(AMap/BaiduMap PlaceSearch迭代, wiki城市公交列表等)输出的文件, 生成定义的search_param_in.js文件, 供后续搜索使用
Author:     wangyoucao577@gmail.com
Created Date:   2016-12-30
Version:        2016-12-30
"""

import sys
import datetime
import fileinput
import re
#sys.path.append(sys.path[0] + r'\..')   #上级目录中加入搜寻列表, 以便于导入上级目录中的py模块
#from files_operation import *

def print_list(list):
    for i in list:
        #print i.encode('utf-8')
        print i.decode('utf-8')

def read_lines_stations_locations_from_file(file_path):
    comments = ""
    expect_city = ""
    city_lines = []

    expect_city_pattern = re.compile("expect_city *=+ *(.+)", re.I) #TODO: 应加上 \'\'
    city_lines_pattern = re.compile("city_lines *=+ *\[(.*)\]", re.I)

    for line in fileinput.input(file_path, mode="rb"):
        if "//" in line:
            comments += (line)
            continue
        
        # 匹配expect_city
        match_result = re.search(expect_city_pattern, line)
        if match_result:
            expect_city = match_result.group(1)
            #print expect_city
            continue

        # 匹配 city_lines
        match_result = re.search(city_lines_pattern, line)
        if match_result:
            city_lines = match_result.group(1).replace(' ', '').replace('\'', '').split(',')
            #print_list(city_lines)
            continue
        
        # TODO: 匹配 city_stations
        # TODO: 匹配 city_stations_location

    return (comments, expect_city, city_lines, None, None)

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
    out_file_all_str = "Generated on " + str(datetime.datetime.now()) + ", From: \n\n"
    out_file_all_str += "###################################\n\n"

    # 内容
    out_expect_city = None
    out_city_lines = []

    for f in in_files_list:
        (comments, expect_city, city_lines, city_stations, city_stations_location) = read_lines_stations_locations_from_file(f)
        out_file_all_str += (comments + "\n\n")

        # expect_city check
        if out_expect_city == None:
            out_expect_city = expect_city
        elif out_expect_city != expect_city:
            print "Error: new expect_city: " + expect_city + ", from " + f + ", can not match with last expect_city: " + out_expect_city
            return

        # city_lines check
        for l in city_lines:
            if l not in out_city_lines:
                out_city_lines.append(l)
        print "after file: " + f + ", len(out_city_lines): " + str(len(out_city_lines))

    #拼接输出
    out_file_all_str += "var search_param_in = {};\n\n"
    out_file_all_str += ("search_param_in.expect_city = " + out_expect_city + ";\n\n")
    #TODO: 拼接city_lines, city_stations, city_stations_location

    out_file_all_str += "###################################\n\n"
    print out_file_all_str
            
    #TODO: 写入文件

if __name__ == '__main__':
    main()
    

            