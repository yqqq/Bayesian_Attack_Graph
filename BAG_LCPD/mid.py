#
#q:     yq json pointer
#fout:  pre_number.txt pointer
#f :     one_zero.txt pointer
#
import json

def tec(pre):
        c = 1
        for i in range(1,pre+1):
           c  *= 2
        return c

q = file('edge.json')

#yq json pointer

js = json.load(q)
fout=open("pre_number.txt","r")
#one_zero pointer

pre = fout.readline()
#pre -> number of pre in json

pre = int(pre)
double = tec(pre)
#print "tec(pre)",tec(pre)
#sdf =  'a'
p = js['a']['pre_node']
p = str(p)
p = p.strip('[{}]')

#delete{}

pout = open("pre_node.txt","w")
pout.write(p)
pout.close()

#pout = open("pre_node.txt","r+")
#print "read(3)",pout.read(10)
#print "read(3)",pout.read(10)
#pout.close()
#complex read
#q.close

fout.close
f = open("one_zero.txt","r")
total = tec(pre)

#print total 2^n

pout = open("pre_node.txt","r+")
#for loop in range (0,pre):
    #str = pout.read(10)
    #str.strip(',')
    #str = str.replace(',',"")
    #str = str.replace(' ',"")
    #str = str.replace('\'',"")
    #str = str.replace(':',"")
    #print "every_node",str
pout.close()
for n in range(0,double):
    #print one_zero
    x = f.readline()
    print x
    i = 0
    p = 1
    while i < pre :
        pout = open("pre_node.txt","r+")
        print "x[",i,"]",x[i],
        str = pout.read(10)
        str = str[5:8]
        str = float(str)
        print str
        if x[i] == '1':
                p *= (1-str)
                print 'p:',p
        else:
                print 'p:',p 
        #print 'p(final):',p        
        i = i+1
        pout.seek(0)
    print 'p(total):',1-p

