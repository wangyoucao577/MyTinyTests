#!/usr/bin/python2.7

import os
import sys
import shutil
import subprocess
import platform
import argparse

# pre-set parameters
kCMakeGeneratedConfig = "cmake_config.h"
kBuildFolder = "./_build/"
kBuildTypesDebug = "Debug"
kBuildTypeRelease = "Release"
kBuildTypes = {'debug' : kBuildTypesDebug, 'release' : kBuildTypeRelease}


def cmake_clean():
    if os.path.isdir(kBuildFolder):
        shutil.rmtree(kBuildFolder)
    if os.path.isfile(kCMakeGeneratedConfig):
        os.remove(kCMakeGeneratedConfig)

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
    


class BuildArgs:

    def __init__(self):
        self.__parser = argparse.ArgumentParser(description='Call cmake to build codes on indicated platform. Default build with release.')
        
        # version
        # not use normal version action here, because we hope to dump gcc version here actually
        self.__parser.add_argument('-v', '--version', action='store_true', help='display version info')
        #self.__parser.add_argument('-v', '--version', action='version', help='display version info', version='%(prog)s 0.0.1')

        # clean
        self.__parser.add_argument('-c', '--clean', action='store_true', help='clean all output from cmake')

        # build_type
        self.__parser.add_argument('-b', '--build_type', help='build as debug(-g -DDEBUG) or release(-O2 -UDEBUG), default release', \
            choices=['debug', 'release'], default='release')

        # parse
        self.__args = self.__parser.parse_args()

    def get_args(self):
        return self.__args

def main():

    args = BuildArgs().get_args()
    if args.version:
        dump_version()
        exit(0)
    if args.clean:
        cmake_clean()
        exit(0)
    build_type = kBuildTypes[args.build_type]   # set cmake build_type for compile
    
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
        cmake_build_cmd = "make -j"
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


