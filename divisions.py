#!/usr/bin/python
# -*- coding: utf-8 -*-

def gatherDivision(number):
	divisions = []
	for div in range(1, number + 1):
		if number % div == 0:
			divisions.append(div)
		
	return divisions
	
'''
print(gatherDivision(24))
'''