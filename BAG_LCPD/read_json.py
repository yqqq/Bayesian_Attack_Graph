#
#import pre in json to c program
#
import json
f = file('edge.json')
js = json.load(f)
fout=open("pre_number.txt","w")
print >>fout,js['a']['pre']
f.close
fout.close
