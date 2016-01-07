#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
Function:
【整理】如何在Windows下开发Python（如何运行Python脚本）
 
http://www.crifan.com/how_to_do_python_development_under_windows_environment
 
Author:     Crifan Li
Version:    2012-12-06
"""

import platform;

pythonVersion = platform.python_version();
uname = platform.uname();

print("Just for demo how to do python development under windows:");
print("Current python version info is ",pythonVersion);
print("uname=",uname);
