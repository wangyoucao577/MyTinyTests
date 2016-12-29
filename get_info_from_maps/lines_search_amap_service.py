#!/usr/bin/python2
# coding=utf-8

"""
Description: 通过web service接口迭代抓取amap/baidumap的城市公交线路信息
           注：AMap和BaiduMap的后端REST接口都有调用次数限制, 一般日千次左右免费
Author:     wangyoucao577@gmail.com
Created Date:   2016-12-07
Version:        2016-12-07
"""

import urllib
import urllib2
import re
import sys
import json
import time
import datetime
import codecs

amap_place_search_url = 'http://restapi.amap.com/v3/place/text?key=ec001ba28cef4168991d5dc2063ea2d1&types=150700&extensions=all&children=1'
amap_nearby_search_url = 'http://restapi.amap.com/v3/place/around?key=ec001ba28cef4168991d5dc2063ea2d1&types=150700&extensions&children=1&radius=50000'

baidumap_place_search_url = 'http://api.map.baidu.com/place/v2/search?query=公交车站&tag=交通设施&page_size=20&page_num=0&scope=1&region=上海&output=json&ak=GvqrFr3Ns8eaHG4bMUPX4yN4R0jZ8oDq'


def print_list(list):
    for i in list:
        print i.encode('utf-8')
        
def rest_request(url):
    request_user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.106 Safari/537.36'
    request_headers = { 'User-Agent' : request_user_agent, 'Referer': url}
    try:
        request = urllib2.Request(url, headers=request_headers)
        response = urllib2.urlopen(request)
        content = response.read()#.decode('utf-8')
        #content = content.encode(sys.getfilesystemencoding())   #for windows default correctly print
        #print content
        #print "read bytes: " + str(len(content))
        return content

        #raw_input("Press any key to continue...")
    except urllib2.HTTPError, e:
        print "HTTPError Exception:"
        print e.code
        print e.reason
        
    except urllib2.URLError, e:
        print "URLError Exception:"
        if hasattr(e,"code"):
            print e.code
        if hasattr(e,"reason"):
            print e.reason
        
    return ""

def nearby_search_for_lines_via_location(base_reqest_url, city, location, in_out_stations, in_out_stations_location, in_out_lines):
    for page in range(1, 20):
        #print "request page: " + str(page)
        url = base_reqest_url + "&city=" + city + "&page=" + str(page) + "&location=" + location
        content = rest_request(url)
        if not content:
            print "rest request null, break"
            break
        json_content = json.loads(content)

        #print "result.status: " + str(json_content["status"]) + ", result.info: " + json_content["info"]
        if 0 == json_content["status"] or "OK" != json_content["info"]:
            print "result failed: " + json_content["info"]
            break

        #print "result count: " + str(json_content["count"])
        #print "pois len: " + str(len(json_content["pois"]))
        for a_pois in json_content["pois"]:
            if a_pois['name'] not in in_out_stations:
                in_out_stations.append(a_pois['name'])
            if a_pois['location'] not in in_out_stations_location:
                in_out_stations_location.append(a_pois['location'])
            this_pois_lines = a_pois['address'].replace('...', '').split(';')
            for line in this_pois_lines:
                if line not in in_out_lines:
                    in_out_lines.append(line)

        print "out_stations len: " + str(len(in_out_stations)) + ", out_stations_location len: " + str(len(in_out_stations_location)) + ", out_lines len: " + str(len(in_out_lines))

    return (in_out_stations, in_out_stations_location, in_out_lines)

def place_search_for_stations_lines(city, base_reqest_url):

    
    out_stations = []
    out_stations_location = []
    out_lines = []
    
    for page in range(1, 20):
        #print "request page: " + str(page)
        url = base_reqest_url + "&city=" + city + "&page=" + str(page)
        content = rest_request(url)
        if not content:
            print "rest request null, break"
            break
        json_content = json.loads(content)

        #print "result.status: " + str(json_content["status"]) + ", result.info: " + json_content["info"]
        if 0 == json_content["status"] or "OK" != json_content["info"]:
            print "result failed: " + json_content["info"]
            break
        
        #print "result count: " + str(json_content["count"])
        #print "pois len: " + str(len(json_content["pois"]))
        for a_pois in json_content["pois"]:
            #print a_pois
            if a_pois['name'] not in out_stations:
                out_stations.append(a_pois['name']);
            if a_pois['location'] not in out_stations_location:
                out_stations_location.append(a_pois['location'])

            this_pois_lines = a_pois['address'].replace('...', '').split(';')
            for line in this_pois_lines:
                if line not in out_lines:
                    out_lines.append(line)

        print "out_stations len: " + str(len(out_stations)) + ", out_stations_location len: " + str(len(out_stations_location)) + ", out_lines len: " + str(len(out_lines))
            
    return (out_stations, out_stations_location, out_lines)


def write_to_file(city, lines):
    target_file_name = city + "_Lines_" + datetime.datetime.now().strftime('%Y%m%d_%H%M%S') + ".txt"
    f = codecs.open(target_file_name,'w+','utf-8')
    f.write("count = " + str(len(lines)) + "\n")
    f.write("var city_lines = [")
    for l in lines:
        f.write("\'" + l + "\'")
        if l != lines[len(lines) - 1]:
            f.write(", ")
    f.write("]")
    f.close()


def main():
    city = '021'

    tick1 = time.time();
    print "tick1: " + str(tick1);

    (stations, stations_location, lines) = place_search_for_stations_lines(city, amap_place_search_url)
    #print_list(stations)
    #print_list(stations_location)
    #print_list(lines)
    print "len(stations): " + str(len(stations)) + "len(stations_location): " + str(len(stations_location)) + ", len(lines): " + str(len(lines))

    tick2 = time.time();
    print "tick2: " + str(tick2) + ", place_search cost seconds: " + str(tick2 - tick1) + "."

    print "ready to search nearby."

    #DeepCopy
    stations_location_copy = []
    for loc in stations_location:
        stations_location_copy.append(loc)

    nearby_count = 0
    for x in stations_location_copy:
        print "nearby search count: " + str(nearby_count) + ", total count: " + str(len(stations_location_copy))
        nearby_count += 1
        (stations, stations_location, lines) = nearby_search_for_lines_via_location(amap_nearby_search_url, city, x, stations, stations_location, lines)
    print "len(stations): " + str(len(stations)) + ", len(stations_location): " + str(len(stations_location)) + ", len(lines): " + str(len(lines))

    tick3 = time.time();
    print "tick3: " + str(tick3) + ", nearby search cost seconds: " + str(tick3 - tick2) + ", ready for nearby search again."

    #DeepCopy
    stations_location_copy_2 = []
    for loc in stations_location:
        if loc not in stations_location_copy:   #ignore the items which has been searched
            stations_location_copy_2.append(loc)
    for x in stations_location_copy_2:
        print "nearby search count: " + str(nearby_count) + ", total count: " + str(len(stations_location_copy_2))
        (stations, stations_location, lines) = nearby_search_for_lines_via_location(amap_nearby_search_url, city, x, stations, stations_location, lines)

    #print_list(lines)
    print "len(stations): " + str(len(stations)) + ", len(stations_location): " + str(len(stations_location)) + ", len(lines): " + str(len(lines))

    tick4 = time.time();
    print "tick4: " + str(tick4) + ", nearby search again cost seconds: " + str(tick4 - tick3) + ", app total cost seconds: " + str(tick4 - tick1)

    # format and then output to file
    #print_list(lines)
    write_to_file(city, lines)

if __name__ == '__main__':
    main()
    

            