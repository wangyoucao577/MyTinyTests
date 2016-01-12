#!/usr/bin/python2
# -*- coding: utf-8 -*-
"""
Description:
    public files operation
Author:     wangyoucao577@gmail.com
Version:    2016-01-11
"""

import os
import sys
import shutil
import filecmp
import commands

def scan_folder_to_get_indicated_file_list(folder_path, wildcard):
    file_list = []
    print "Start Scan " + folder_path
    for root, dirs, files in os.walk(folder_path):
        for name in files:
            if wildcard in name:
                print(name)
                file_list.append(name)
          
    print "End Scan " + folder_path + "\n\n"
    return file_list

def do_file_copy(dst_file_path, src_file_path):
    try:
        shutil.copyfile(src_file_path, dst_file_path)
    except IOError:
        print dst_file_path + "can not write."
        return False
    return True

#For svn operation, also could use pysvn 3rd lib to implement, more powerful
def do_svn_add(file_path):
    (exec_status, content) = commands.getstatusoutput("svn add " + file_path)
    #print exec_status
    #print content
    if 0 == exec_status:	#exit correctly
        return True
    else:
        print "svn add return:" + content
        return False
    
def do_svn_delete(file_path):
    (exec_status, content) = commands.getstatusoutput("svn delete " + file_path)
    #print exec_status
    #print content
    if 0 == exec_status:	#exit correctly
        return True
    else:
        print "svn delete return:" + content
        return False
        
def do_files_copy(dst_path, src_path, files_to_copy, mode):
    retval = True
    for file_name in files_to_copy:
        src_file_path = src_path + "/" + file_name
        dst_file_path = dst_path + "/" + file_name
        
        if do_file_copy(dst_file_path, src_file_path):
            print "Succeed " + mode + ": " + src_file_path + " -> " + dst_file_path
        else:
            print "[ERROR]Failed "  + mode + ": " + src_file_path + " -> " + dst_file_path
            retval = False
            
        if "Svn Add" in mode:
            if do_svn_add(dst_file_path):
                print "Succeed " + mode + ": " + dst_file_path
            else:
                print "[ERROR]Failed " + mode + ": " + dst_file_path
                retval = False

    return retval
                
"""
    return True if files the same
    return False if something different
"""
def do_file_compare(dst_file_path, src_file_path):
    return filecmp.cmp(dst_file_path, src_file_path)

def do_mkdir(dir_path):
    if os.path.isdir(dir_path):
        print "Dir Already Exist: " + dir_path
    else:
        try:
            os.mkdir(dir_path)
            print "Succeed mkdir: " + dir_path
        except os.error:
            print "[ERROR]Failed mkdir: " + dir_path
            return False
    return True
    
def main():
    print "Execute files_operation."

if __name__ == '__main__':
    main()



