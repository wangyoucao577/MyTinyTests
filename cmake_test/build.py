#!/usr/bin/python2.7

import os
import sys
import shutil
import subprocess
import platform

# pre-set parameters
kCMakeGeneratedConfig = "cmake_config.h"
kBuildFolder = "./_build/"
kBuildTypesDebug = "Debug"
kBuildTypeRelease = "Release"


# Quit
kQuit = "Quit"

def cmake_clean():
    if os.path.isdir(kBuildFolder):
        shutil.rmtree(kBuildFolder)
    if os.path.isfile(kCMakeGeneratedConfig):
        os.remove(kCMakeGeneratedConfig)
    return kQuit

def initialize_debug_parameters():
    return kBuildTypesDebug

def initialize_release_parameters():
    return kBuildTypeRelease

def do_cmd(cmd):
    print cmd
    
    args = cmd.split(' ')
    p = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    while True:
        line = p.stdout.readline()
        if line != '':    
            print line.rstrip() 
        else:   # done
            break

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
    
    # prepare build folders 
    do_mkdir(kBuildFolder) 
    os.chdir(kBuildFolder)
 
    # prepare cmake commands
    sub_dir_name = ""
    cmake_cmd = "cmake -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_CONFIG_FILE=" + kCMakeGeneratedConfig
    cmake_build_cmd = ""
    if platform.system() == 'Windows':
        sub_dir_name = platform.system()
        cmake_cmd += " -A x64"  # default use x64
        cmake_build_cmd = "cmake --build . -- /p:Configuration=" + build_type # also could use msbuild/devenv instead 
    elif platform.system() == 'Linux':
        sub_dir_name = build_type
        cmake_cmd += " -DCMAKE_BUILD_TYPE=" + build_type
        cmake_build_cmd = "make"
    else:
        print "Unknown platform: " + platform.system()
        exit(-1)
    cmake_cmd += " ../.."

    # do make
    do_mkdir(sub_dir_name)
    os.chdir(sub_dir_name)
    do_cmd(cmake_cmd)
    do_cmd(cmake_build_cmd)
    os.chdir("../../")

if __name__ == '__main__':
    main()
else:
    pass


