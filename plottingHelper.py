import numpy
import pylab

file = open("max_eps(h).txt");

map = {}
for line in file.readlines():
	(key,val) = line.split('\t')
	map[float(key)] = float(val)

pylab.plot(map.keys(),map.values())
pylab.show()

#print map.values()
#raw_input()	