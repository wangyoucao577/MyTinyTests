#!/usr/bin/python2

import re
import urllib2

class Getmyip:
    def getip(self):
        try:
            myip = self.visit("http://www.ip138.com/ip2city.asp")
        except:
            try:
                myip = self.visit("http://www.whereismyip.com/")
            except:
                myip = "So sorry!!!"
        return myip
    def visit(self,url):
        opener = urllib2.urlopen(url)
        if url == opener.geturl():
            str = opener.read()
            #print str + "\n\n"
            
        return re.search('\d+\.\d+\.\d+\.\d+',str).group(0)
        
if __name__ == '__main__':
    getmyip = Getmyip()
    publicip = getmyip.getip()
    print "My Public IP:" + publicip
