#!/usr/bin/python2
# vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! :

import re
import fileinput
import datetime
import time

from inquery_my_public_ip import Getmyip

newip_file_path = r'.'
newip_file_name = r'newip.md'

def read_newip_from_file(newip_file):
    last_line = None
    try:        
        #print last_line
        for line in fileinput.input(newip_file, mode="rb"):
            #print line
            last_line = line
    except:
        #print "read error"
        pass

    if last_line is None:
        pass    
    else:
        pattern = re.compile(r'.*\[(.*)\].*Update at (.*)\n', re.I)
        #print last_line
        match_result = re.match(pattern, last_line)
        if match_result:
            #print match_result.group(1)
            #print match_result.group(2)
            return (match_result.group(1), match_result.group(2))
    return (None, None)


def append_newip_to_file(newip_file, newip_str):
    with open(newip_file, 'ab+') as f:
        f.write("- " + newip_str+ '\n')

def refresh_new_ip(newip_file):
    (last_ip, last_update_time) = read_newip_from_file(newip_file)
    if last_ip is not None:
        print "Latest Public Ip " + last_ip

    getmyip = Getmyip()
    while (True):
        publicip = getmyip.getip()
        curr_time = datetime.datetime.now().strftime("%Y%m%d_%H:%M:%S")

        if publicip is not None:
            if publicip != last_ip:
                last_ip = publicip
                new_ip_outstr = "My new public Ip changed to [" + publicip + "], Update at " + curr_time
            else:
                new_ip_outstr = "My new public Ip [" + publicip + "], Update at " + curr_time
        else:
            new_ip_outstr = "Inquery public Ip failed at " + curr_time + ", try again later."
        print new_ip_outstr
        
        append_newip_to_file(newip_file, new_ip_outstr)

        time.sleep(30)

if __name__ == '__main__':
    newip_file = newip_file_path + "/" + newip_file_name
    print "File Location: " + newip_file
    refresh_new_ip(newip_file)

else:
    pass
