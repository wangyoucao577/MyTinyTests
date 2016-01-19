#!/usr/bin/python2
# -*- coding: utf-8 -*-
"""
Description:
    compare versions and copy files in publishing
Author:     wangyoucao577@gmail.com
Version:    2016-01-11
"""

from files_operation import *

def publish_library(platform_list, new_version, dst_folder_path, src_folder_path, sdk_name):
    for platform_name in platform_list:
        print "Publish at %s platform onto target place..." %(platform_name)
        
        #mkdir first
        platform_path = dst_folder_path + "/" + platform_name + "/"
        if not do_mkdir(platform_path):
            return False
        new_version_dir_path = platform_path + new_version + "/";
        if not do_mkdir(new_version_dir_path):
            return False
        target_debug_dir_path = new_version_dir_path + "debug/"
        if not do_mkdir(target_debug_dir_path):
            return False
        target_release_dir_path = new_version_dir_path + "release/"
        if not do_mkdir(target_release_dir_path):
            return False

        #copy files
        src_debug_file_path = src_folder_path + "/build/" + platform_name + "/debug/" + sdk_name
        src_release_file_path = src_folder_path + "/build/" + platform_name + "/release/" + sdk_name
        if do_file_copy(target_debug_dir_path + sdk_name, src_debug_file_path):
            print "Succeed Copy: " + src_debug_file_path + " -> " + target_debug_dir_path + sdk_name
        else:
            print "[Error]Failed Copy: " + src_debug_file_path + " -> " + target_debug_dir_path + sdk_name
            return False
            
        if do_file_copy(target_release_dir_path + sdk_name, src_release_file_path):
            print "Succeed Copy: " + src_release_file_path + " -> " + target_release_dir_path + sdk_name
        else:
            print "[Error]Failed Copy: " + src_release_file_path + " -> " + target_release_dir_path + sdk_name
            return False
    
    return True

def publish_headers(new_version, dst_folder_path, src_folder_path):
    print "Publish header files..."
    
    #scan ".h"
    src_headers_dir_path = src_folder_path + "/include/"
    file_list = scan_folder_to_get_indicated_file_list(src_headers_dir_path, ".h")
    print file_list
    
    #mkdir
    new_version_dir_path = dst_folder_path + "/headers/" + new_version + "/";
    if not do_mkdir(new_version_dir_path):
        return False
    target_headers_dir_path = new_version_dir_path + "include/"
    if not do_mkdir(target_headers_dir_path):
        return False
            
    #copy headers
    if not do_files_copy(target_headers_dir_path, src_headers_dir_path, file_list, "Copy"):
        return False
    
    #copy ReleaseNote.txt
    src_release_note_file_path = src_folder_path + "/ReleaseNote.txt"
    dst_release_note_file_path = new_version_dir_path + "/ReleaseNote.txt"
    if do_file_copy(dst_release_note_file_path, src_release_note_file_path):
        print "Succeed Copy: " + src_release_note_file_path + " -> " + dst_release_note_file_path
    else:
        print "[Error]Failed Copy: " + src_release_note_file_path + " -> " + dst_release_note_file_path
        return False 
    
    return True
    
def main():
    if (len(sys.argv) <= 6):
        print "Usage: "
        print "      python ./publish.py <sdk_name> <dst_path> <src_path> <new_version> <old_version> <platform_list>"
        return
    print "Start publish.py---------------------------------------------"
    
    sdk_name = sys.argv[1]
    dst_folder_path = sys.argv[2]
    src_folder_path = sys.argv[3]
    new_version = sys.argv[4]
    old_version = sys.argv[5]
    platform_list = []
    
    #analyse platform values
    argv_index = 0;
    for argv_value in sys.argv:
        if argv_index >= 6:
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
    if not do_file_compare(dst_release_note_path, src_release_note_path):
        print "ReleaseNote.txt have been changed!"
    else:
        print "Please modify the ReleaseNote.txt before publish!"
        sys.exit(1)
        
    #publish library
    if publish_library(platform_list, new_version, dst_folder_path, src_folder_path, sdk_name):
        print "publish_library Succeed!"
    else:
        print "publish_library Failed!"
        sys.exit(1)
    
    #publish headers
    if publish_headers(new_version, dst_folder_path, src_folder_path):
        print "publish_headers Succeed!"
    else:
        print "publish_headers Failed!"
        sys.exit(1)
        
    print "publish.py Done!---------------------------------------------"

if __name__ == '__main__':
    main()



