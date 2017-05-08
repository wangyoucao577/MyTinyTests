#!/usr/bin/python2.7

import os
import sys
import shutil
import commands


# pre-set parameters
kCMakeGeneratedConfig = "cmake_config.h"
kBuildFolder = "./build/"
kBuildTypesDebug = "Debug"
kBuildTypeRelease = "Release"


# Quit
kQuit = "Quit"

def cmake_clean():
    do_cmd("rm -rf " + kBuildFolder)
    do_cmd("rm -f " + kCMakeGeneratedConfig)
    return kQuit

def initialize_debug_parameters():
    return kBuildTypesDebug

def initialize_release_parameters():
    return kBuildTypeRelease

def do_cmd(cmd):
    print cmd
    (exec_status, content) = commands.getstatusoutput(cmd)
    if 0 == exec_status:    #exit correctly
        print content
        return True
    else:
        print "execute cmd: '" + cmd + "'' failed, error msg: " + content
        return False

def do_mkdir(dir_path):
    if os.path.isdir(dir_path):
        #print "Dir Already Exist: " + dir_path
        pass
    else:
        try:
            os.mkdir(dir_path)
            print "Succeed mkdir: " + dir_path
        except os.error:
            print "[ERROR]Failed mkdir: " + dir_path
            return False
    return True

def dump_version():
    do_cmd("g++ --version")
    return kQuit

def build_help():
    print "Call cmake to build codes on indicated platform. Default build with release."
    print "Usage: "
    print "     python build.py [option]"
    print "Sample: "
    print "     python build.py"
    print "     python build.py debug"
    print "     python build.py release"
    print "     python build.py clean"
    print "     python build.py --help"
    print "     python build.py --version"
    print "Options: "
    print "     debug    :    compile with -g, -DDEBUG"
    print "     release  :    compile with -O2, -UDEBUG"
    print "     clean    :    clean all output from cmake"
    print "     --help   :    display help information"
    print "     --version:    display related versions, such as GCC version"
    return kQuit

def main():
    cmd_behavior_list = {'--help' : build_help, '--version' : dump_version,
                        'clean': cmake_clean, 
                        'debug' : initialize_debug_parameters, 'release' : initialize_release_parameters}

    build_type = kBuildTypeRelease

    # handle options from command
    if len(sys.argv) >= 2:
        if sys.argv[1] not in cmd_behavior_list:
            print "Error: Invalid options!"
            build_help()
            return      
        # handle options, may quit then  
        cmd_ret = cmd_behavior_list[sys.argv[1]]()
        if cmd_ret == kQuit:
            return
        elif cmd_ret == kBuildTypeRelease or cmd_ret == kBuildTypesDebug:
            build_type = cmd_ret
    
    # do cmake
    do_mkdir(kBuildFolder)
    os.chdir(kBuildFolder)
    do_cmd("cmake -DCMAKE_CONFIG_FILE=" + kCMakeGeneratedConfig + " -DCMAKE_BUILD_TYPE=" + build_type + " ..")
    do_cmd("make")
    os.chdir("..")

if __name__ == '__main__':
    main()
else:
    pass


