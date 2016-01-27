#!/usr/bin/python3

import re
import urllib.request

public_ip_inquery_url = ("http://www.whereismyip.com/",
"http://ifconfig.me/ip", 
"http://www.ip138.com/ip2city.asp")

class Getmyip:
    def getip(self):
        for url in public_ip_inquery_url:
            try:
                myip = self.visit(url)
                return myip
            except Exception as err:
                print(err)
                continue
        return "So sorry!!!"
    def visit(self, url):
        print("Try to inquery my public ip from :" + url)
        opener = urllib.request.urlopen(url)
        if url == opener.geturl():
            str = opener.read().decode('utf-8')
            #print(str + "\n\n")
            
        return re.search('\d+\.\d+\.\d+\.\d+',str).group(0)
        
if __name__ == '__main__':
    getmyip = Getmyip()
    publicip = getmyip.getip()
    print("My Public IP:" + publicip)
