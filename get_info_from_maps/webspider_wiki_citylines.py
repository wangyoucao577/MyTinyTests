#!/usr/bin/python2
# -*- coding: utf-8 -*-

"""
Description:
Author:     wangyoucao577@gmail.com
Created Date:   2016-12-05
Version:        2016-12-05
"""

import urllib
import urllib2
import re
import sys

wiki_url = 'https://zh.wikipedia.org/wiki/%E6%B7%B1%E5%9C%B3%E5%85%AC%E4%BA%A4%E5%B7%B4%E5%A3%AB%E7%BA%BF%E8%B7%AF%E8%A1%A8#.E9.AB.98.E5.B3.B0.E4.B8.93.E7.BA.BF'

def main():
    url = wiki_url
    request_user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.106 Safari/537.36'
    request_headers = { 'User-Agent' : request_user_agent, 'Referer': url}
    try:
        request = urllib2.Request(url, headers=request_headers)
        response = urllib2.urlopen(request)
        #content = response.read().decode('utf-8')
        content = response.read().decode('utf-8')
        content = content.encode(sys.getfilesystemencoding())   #for correctly print
        #print content
        #print len(content)

        #split to small strings, easy to Regex search
        str_items = content.split('</tr>')
        #print len(str_items)

        pattern = re.compile(r'<td style=".+?"><b><a href=".+?".+?title=".+?">(.+?)</a></b></td>', re.S)

        matched_items = []
        for i in str_items:
            #print i
            #raw_input("Press any key to continue...")
            items = re.findall(pattern, i)
            #print items
            for item in items:
                #print item
                matched_items.append(item)
        
        print "Total done. Count :" + str(len(matched_items))

        # format as my JavaScript want
        out_str = 'var city_lines = ['
        for i in range(0, len(matched_items)):
            #sys.stdout.write(i + ', ');
            out_str += ('\'' + matched_items[i] + '\'')
            if i != len(matched_items) - 1:
                out_str += ', '
        #sys.stdout.write(']');
        out_str += ']'
        print out_str
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
            
if __name__ == '__main__':
    main()
    

            