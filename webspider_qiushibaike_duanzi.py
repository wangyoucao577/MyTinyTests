#!/usr/bin/python2
# -*- coding: utf-8 -*-

"""
Description:
    A simple web spider for qiushibaike, ignore images.
    Reference: http://cuiqingcai.com/990.html    静觅 » Python爬虫实战一之爬取糗事百科段子
Author:     wangyoucao577@gmail.com
Created Date:   2016-07-15
Version:        2016-07-15
"""

import urllib
import urllib2
import re

qiushibaike_url = 'http://www.qiushibaike.com/'

def main():
    url = qiushibaike_url + 'hot/page/' + '2'
    request_user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.106 Safari/537.36'
    request_headers = { 'User-Agent' : request_user_agent, 'Referer': url}
    try:
        request = urllib2.Request(url, headers=request_headers)
        response = urllib2.urlopen(request)
        content = response.read().decode('utf-8')
        #print content
        pattern = re.compile('<div.*?author clearfix">.*?<a.*?<img.*?>(.*?)</a>.*?<a href.*?>.*?<h2>(.*?)</h2>.*?</a>.*?<div class="content">(.*?)</div>(.*?)<div class="stats">.*?</div>',re.S)
        items = re.findall(pattern, content)

        count = 0
        for item in items:
            if "thumb" not in item[3]:  # not have image
                print item[1], (item[2].replace('<br/>', '\r\n')).replace('&quot', '\"')
                raw_input("Press any key to continue...")
                count += 1
        print "Total done. Count :" + str(count)
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
    

            