#!/usr/bin/python2
# -*- coding: utf-8 -*-
"""
CopyRight: 
Description:
    rescure copy compiled kernel modules 
Author:     zhangj
Created Date:   2016-02-25
Version:        2016-02-25
"""

from files_operation import *


def main():
    if (len(sys.argv) < 3):
        print "Usage: "
        print "      python ./copy_modules.py <dst_path> <src_path>"
        return
    print "Start Copy Kernel Modules---------------------------------------------"
    
    dst_folder_path = sys.argv[1]
    src_folder_path = sys.argv[2]
    
    if False == do_mkdir(dst_folder_path):
        print "Mkdir " + dst_folder_path + " Failed. Quit!\n\n"
        return
    
    scan_folder_to_copy_files(dst_folder_path, src_folder_path, ".ko")  
        
    print "Copy Kernel Modules Done!---------------------------------------------"

if __name__ == '__main__':
    main()



