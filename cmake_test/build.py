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

# for autotools
kAutogen = "./autogen.sh"
kAutoclean = "./autoclean.sh" 


def clean_all():
    # cmake output
    if os.path.isdir(kBuildFolder):
        shutil.rmtree(kBuildFolder)
    if os.path.isfile(kCMakeGeneratedConfig):
        os.remove(kCMakeGeneratedConfig)

    if platform.system() != 'Windows':
        # autotools output
        if os.path.isfile(kAutoclean):
            #do_cmd(kAutoclean)
            subprocess.call(kAutoclean, shell=True)


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
    do_cmd("cmake --version")
    do_cmd("m4 --version")
    do_cmd("aclocal --version")
    do_cmd("autoconf --version")
    do_cmd("automake --version")
    
def cmake_build(build_type):

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

def autotools_build(build_type):

    # call autogen.sh
    if os.path.isfile(kAutogen):
        do_cmd(kAutogen)
    else:
        print "no valid " + kAutogen + " file."
        return False

    # prepare build folders 
    do_mkdir(kBuildFolder) 
    os.chdir(kBuildFolder)
    sub_dir_name = build_type
    do_mkdir(sub_dir_name)
    os.chdir(sub_dir_name)

    # configure and build
    do_cmd('../../configure')
    do_cmd('make -j')
    os.chdir("../../")

class BuildArgs:

    def __init__(self):
        self.__parser = argparse.ArgumentParser(description='Call cmake/autotools to build codes on indicated platform. Default build with cmake/release.')
        
        # version
        # not use normal version action here, because we hope to dump gcc version here actually
        self.__parser.add_argument('-v', '--version', action='store_true', help='display cmake/autotools version info')
        #self.__parser.add_argument('-v', '--version', action='version', help='display version info', version='%(prog)s 0.0.1')

        # clean
        self.__parser.add_argument('-c', '--clean', action='store_true', help='clean all output from cmake/autotools')

        # build_system
        self.__parser.add_argument('-B', '--build_system', help='build by cmake or GNU autotools, default cmake', \
            choices=['cmake', 'autotools'], default='cmake')

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
        clean_all()
        exit(0)
    build_type = kBuildTypes[args.build_type]   # set cmake build_type for compile
    
    if args.build_system == 'autotools':
        if platform.system() == 'Windows':
            print "[ERROR] Windows doesn't support Autotools."
        else:
            autotools_build(build_type)
    else:
        cmake_build(build_type)


if __name__ == '__main__':
    main()
else:
    pass


