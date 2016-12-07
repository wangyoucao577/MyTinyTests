#!/usr/bin/python2
# -*- coding: utf-8 -*-

"""
Description:
Author:     wangyoucao577@gmail.com
Created Date:   2016-12-07
Version:        2016-12-07
"""

import urllib
import urllib2
import re
import sys
import json

amap_place_search_url = 'http://restapi.amap.com/v3/place/text?key=ec001ba28cef4168991d5dc2063ea2d1&types=150700&extensions=all&children=1'
baidumap_place_search_url = 'http://api.map.baidu.com/place/v2/search?query=公交车站&tag=交通设施&page_size=20&page_num=0&scope=1&region=上海&output=json&ak=GvqrFr3Ns8eaHG4bMUPX4yN4R0jZ8oDq'

def print_list(list):
    for i in list:
        print i.encode('utf-8')

def nearby_search_for_lines_via_station(city, station, in_out_lines):
    for page in range(1, 100):
        pass

def place_search_for_stations_lines(city, base_reqest_url):

    request_user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.106 Safari/537.36'
    
    out_stations = []
    out_lines = []
    
    for page in range(1, 100):
        print "request page: " + str(page)
        url = base_reqest_url + "&city=" + city + "&page=" + str(page)
        request_headers = { 'User-Agent' : request_user_agent, 'Referer': url}
        try:
            request = urllib2.Request(url, headers=request_headers)
            response = urllib2.urlopen(request)
            content = response.read()#.decode('utf-8')
            #content = content.encode(sys.getfilesystemencoding())   #for windows default correctly print
            #print content
            print "read bytes: " + str(len(content))
            json_content = json.loads(content)

            print "result.status: " + str(json_content["status"]) + ", result.info: " + json_content["info"]
            if (0 == json_content["status"] || "OK" != json_content["info"]):
                print "result failed: " + json_content["info"]
                break
            
            print "result count: " + str(json_content["count"])
            print "pois len: " + str(len(json_content["pois"]))
            for a_pois in json_content["pois"]:
                #print a_pois
                if a_pois['name'] not in out_stations:
                    out_stations.append(a_pois['name']);
                this_pois_lines = a_pois['address'].replace('...', '').split(';')
                for line in this_pois_lines:
                    if line not in out_lines:
                        out_lines.append(line)
            print "out_stations len: " + str(len(out_stations)) + ", out_lines len: " + str(len(out_lines))

            
            #raw_input("Press any key to continue...")
        except urllib2.HTTPError, e:
            print "HTTPError Exception:"
            print e.code
            print e.reason
            break
        except urllib2.URLError, e:
            print "URLError Exception:"
            if hasattr(e,"code"):
                print e.code
            if hasattr(e,"reason"):
                print e.reason
            break
            
    return (out_stations, out_lines)

def main():
    (stations, lines) = place_search_for_stations_lines('上海', amap_place_search_url)
    print_list(stations)
    print_list(lines)

if __name__ == '__main__':
    main()
    

            