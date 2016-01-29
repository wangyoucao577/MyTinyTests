#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import random

grammar = {'<start>':[['This', '<object>', 'is here']], 
'<object>':[['computer'], ['car'], ['assignment']]}

print(grammar)

def expand(symbol, grammar) :
	if symbol.startswith('<'):
		definations = grammar[symbol]
		expansion = random.choice(definations)
		#map(expand, expansion)	#map迭代
		
		#方式二：lambda表达式
		map(lambda item : expand(item, grammar), expansion)
	else :
		sys.stdout.write(symbol + '\n')
	
print("Let do the expend")
random.seed()	
expand('<start>', grammar)