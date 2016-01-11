#!/usr/bin/python2
# -*- coding: utf-8 -*-
"""
Description:
    compare versions and copy files in publishing
Author:     wangyoucao577@gmail.com
Version:    2016-01-11
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

#TODO:
"""
    return True if files the same
    return False if something different
"""
def do_file_compare(dst_file_path, src_file_path):
    return False

def main():
    if (len(sys.argv) <= 5):
        print "Usage: "
        print "      python ./publish.py <dst_path> <src_path> <new_version> <old_version> <platform_list>"
        return
    print "Start publish.py---------------------------------------------"
    
    dst_folder_path = sys.argv[1]
    src_folder_path = sys.argv[2]
    new_version = sys.argv[3]
    old_version = sys.argv[4]
    platform_list = []
    
    #analyse platform values
    argv_index = 0;
    for argv_value in sys.argv:
        if argv_index >= 5:
            platform_list.append(argv_value)
        argv_index += 1; 
    
    print "platform list :"
    print platform_list
    
    #check version
    if new_version == old_version:
        print "You haven't changed version_config! Publish failed!"
        sys.exit(1)
    
    #check "ReleaseNote.txt", make sure it's been changed
    src_release_note_path = src_folder_path + "/ReleaseNote.txt"
    dst_release_note_path = dst_folder_path + "/headers/" + old_version + "/ReleaseNote.txt"
    if do_file_compare(dst_release_note_path, src_release_note_path):
        print "ReleaseNote.txt have been changed!"
    else:
        print "Please modify the ReleaseNote.txt before publish!"
        sys.exit(1)
        
    #TODO:mkdir and copy files
        
    print "publish.py Done!---------------------------------------------"

if __name__ == '__main__':
    main()



