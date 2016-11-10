#!/usr/bin/python
# -*- coding: utf-8 -*-

"""
Description:
Author:     wangyoucao577@gmail.com
Created Date:   2016-11-11
Version:        2016-11-10
"""

import sys
    
def main():
    if (len(sys.argv) < 2):
        print "Usage: "
        print "      python cdeclare.py <'c declare string'>" 
        print "Sample: "
        print "      python cdeclare.py 'char * const *(*next)()'"
        return
        
    declare_str = sys.argv[1]
    print "Going to analyse--->" + declare_str

if __name__ == '__main__':
    main()
    