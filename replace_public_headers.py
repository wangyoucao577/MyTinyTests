#!/usr/bin/python2
# -*- coding: utf-8 -*-
"""
Description:
    Help for replace headers for libraries while update to the indicate version.
Author:     wangyoucao577@gmail.com
Version:    2016-01-08
"""

import os
import sys
import shutil
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
            
def compare_files_in_folder(dst_folder_path, src_folder_path, file_name_wildcard):
    
    dst_curr_file_list = scan_folder_to_get_indicated_file_list(dst_folder_path, file_name_wildcard)  
    src_curr_file_list = scan_folder_to_get_indicated_file_list(src_folder_path, file_name_wildcard)  
    
    files_to_replace = []
    files_to_add = []
    files_to_delete = []
    
    for file_name in src_curr_file_list:
        if file_name in dst_curr_file_list:
            files_to_replace.append(file_name)
        else:
            files_to_add.append(file_name)
            
    for file_name in dst_curr_file_list:
        if file_name not in src_curr_file_list:
            files_to_delete.append(file_name)

    print "compare folders result"
    print "To add files: "
    print files_to_add
    print "\n\n"
    print "To replace files: "
    print files_to_replace
    print "\n\n"
    print "To delete files: "
    print files_to_delete
    print "\n\n"
    
    return (files_to_add, files_to_replace, files_to_delete)

def my_file_copy(dst_file_path, src_file_path):
    try:
        shutil.copyfile(src_file_path, dst_file_path)
    except IOError:
        print dst_file_path + "can not write."
        return False
    return True

def do_files_copy(dst_path, src_path, files_to_add, mode):
    for file_name in files_to_add:
        src_file_path = src_path + "/" + file_name
        dst_file_path = dst_path + "/" + file_name
        
        if my_file_copy(dst_file_path, src_file_path):
            print "Succeed " + mode + ": " + src_file_path + " -> " + dst_file_path
        else:
            print "[ERROR]Failed "  + mode + ": " + src_file_path + " -> " + dst_file_path
            
        if "Add" in mode:
            if do_svn_add(dst_file_path):
                print "Succeed svn " + mode + ": " + dst_file_path
            else:
                print "[ERROR]Failed svn " + mode + ": " + dst_file_path
    
def do_files_delete(dst_path, files_to_delete):
    for file_name in files_to_delete:
        dst_file_path = dst_path + "/" +file_name
        if do_svn_delete(dst_file_path):
            print "Succeed svn Delete: " + dst_file_path
        else:
            print "[ERROR]Failed svn Delete: " + dst_file_path

#For svn operation, also could use pysvn 3rd lib to implement, more powerful
#TODO: debugging
def do_svn_add(file_path):
    (exec_status, content) = commands.getstatusoutput("svn add " + file_path)
    print exec_status
    print content
    return exec_status
    
#TODO: debugging
def do_svn_delete(file_path):
    (exec_status, content) = commands.getstatusoutput("svn delete " + file_path)
    print exec_status
    print content
    return exec_status

def main():
    if (len(sys.argv) < 3):
        print "Usage: "
        print "      python ./replace_public_headers.py <dst_path> <src_path>"
        return
    print "Start Replace---------------------------------------------"
    
    dst_folder_path = sys.argv[1]
    src_folder_path = sys.argv[2]
    (files_to_add, files_to_replace, files_to_delete) = compare_files_in_folder(dst_folder_path, src_folder_path, ".h")

    do_files_copy(dst_folder_path, src_folder_path, files_to_add, "Add")
    do_files_copy(dst_folder_path, src_folder_path, files_to_replace, "Replace")
    do_files_delete(dst_folder_path, files_to_delete)
    
    print "Replace Done!---------------------------------------------"

if __name__ == '__main__':
    main()



