#!/usr/bin/python2
# -*- coding: utf-8 -*-
"""
Description:
    public files operation
Author:     wangyoucao577@gmail.com
Created Date:   2016-01-11
Version:        2016-02-25
"""

import os
import sys
import shutil
import filecmp
import commands


    
def do_file_copy(dst_file_path, src_file_path):
    try:
        shutil.copyfile(src_file_path, dst_file_path)
    except IOError:
        print dst_file_path + " can not write."
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

"""
    This functions is for single path
"""
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

"""
    return file name and file path list
"""
def scan_folder_to_get_indicated_files(folder_path, wildcard):
    file_name_list = []
    file_path_list = []
    print "Start Scan " + folder_path
    for root, dirs, files in os.walk(folder_path):
        for name in files:
            #if wildcard in name:
            name_suffix = "." + name.split('.')[-1]
            if name_suffix == wildcard:
                print(name)
                file_name_list.append(name)
                file_path_list.append(os.path.join(root,file_name))
          
    print "End Scan " + folder_path + "\n\n"
    return (file_name_list, file_path_list)

"""
    only return file name list
"""
def scan_folder_to_get_indicated_file_list(folder_path, wildcard):
    (file_name_list, file_path_list) = scan_folder_to_get_indicated_files(folder_path, wildcard)
    return file_name_list

def scan_folder_to_copy_files(dst_folder_path, src_folder_path, wildcard):
    print "Start Scan " + src_folder_path
    for root, dirs, files in os.walk(src_folder_path):
        for file_name in files:
            #if wildcard in name:
            name_suffix = "." + file_name.split('.')[-1]
            if name_suffix == wildcard:
                
                src_file_path = os.path.join(root,file_name)
                dst_file_path = dst_folder_path + "/" + file_name
                #print src_file_path
                if os.path.isfile(dst_file_path):
                    print "[ WARN] File Exist: " + dst_file_path + " Src File: " + src_file_path
                elif do_file_copy(dst_file_path, src_file_path): 
                    print "Succeed Copy: " + src_file_path + " -> " + dst_file_path
                else:
                    print "[ERROR]Failed Copy: " + src_file_path + " -> " + dst_file_path
                    exit(1)
    print "End Scan " + src_folder_path
    
def main():
    print "Execute files_operation."

if __name__ == '__main__':
    main()
else:
    print "Module Loaded: files_operation."


