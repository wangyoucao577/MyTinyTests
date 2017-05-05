
import os
import sys
import shutil
import commands

#parameters
kCMakeGeneratedConfig = "cmake_config.h"
kBuildFolder = "./build/"
kBuildType = "Release"

# Quit
kQuit = "Quit"

def cmake_clean():
    do_cmd("rm -rf " + kBuildFolder)
    do_cmd("rm -f " + kCMakeGeneratedConfig)
    return kQuit

def initialize_debug_parameters():
    print "TODO DEBUG"
    return

def initialize_release_parameters():
    print "TODO RELEASE"
    return

def do_cmd(cmd):
    (exec_status, content) = commands.getstatusoutput(cmd)
    if 0 == exec_status:    #exit correctly
        return True
    else:
        print "execute cmd: '" + cmd + "'' failed, error msg: " + content
        return False


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
    print "Options: "
    print "     debug    :    compile with -g, -DDEBUG"
    print "     release  :    compile with -O2, -UDEBUG"
    print "     clean    :    clean all output from cmake"
    print "     --help   :    display help information"
    return kQuit

def main():
    cmd_behavior_list = {'--help' : build_help, 'clean': cmake_clean, 
                        'debug' : initialize_debug_parameters, 'release' : initialize_release_parameters}

    if len(sys.argv) >= 2:
        if sys.argv[1] not in cmd_behavior_list:
            print "Error: Invalid options!"
            build_help()
            return      
        # handle options, may quit then  
        cmd_ret = cmd_behavior_list[sys.argv[1]]()
        if cmd_ret == kQuit:
            return

    # do cmake
    print "TODO cmake"

if __name__ == '__main__':
    main()
else:
    pass


