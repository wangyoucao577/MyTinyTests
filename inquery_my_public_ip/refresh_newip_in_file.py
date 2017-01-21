#!/usr/bin/python2
# vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! :

import fileinput
import datetime
import time

from inquery_my_public_ip import Getmyip

newip_file_path = r'.'
newip_file_name = r'newip.md'

def read_newip_from_file(newip_file):
    for line in fileinput.input(file_path, mode="rb"):
        print line

def append_newip_to_file(newip_file, newip_str):
    #print newip_file
    try:
        f = open(newip_file, "wb+")
        f.seek(0, 0)
        f.write("- " + newip_str + "  \n")
        f.close()
    except:
        print "append to file failed!"
    

def refresh_new_ip(newip_file):
    print newip_file
    getmyip = Getmyip()
    while (True):
        publicip = getmyip.getip()
        curr_time = datetime.datetime.now().strftime("%Y%m%d_%H:%M:%S")

        if publicip is not None:
            new_ip = "My new public Ip [" + publicip + "], Update at " + curr_time
        else:
            new_ip = "Inquery public Ip failed at " + curr_time + ", try again later."
        print new_ip
        append_newip_to_file(newip_file, new_ip)

        time.sleep(1)

if __name__ == '__main__':
    refresh_new_ip(newip_file_path + "/" + newip_file_name)
else:
    pass
