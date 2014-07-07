import sys

fname = sys.argv[1]
f = open(fname, "r")
s = f.read()
f.close()
f = open(fname+".old", "w")
f.write(s)
f.close()
s = s.rstrip()
a = s.split(",\n")
l = []
for x in range(len(a)):
	tmp = a[x].split(",")
	l.append(tmp)

nl = []
for x in range(len(l[0])):
	tmp = []
	for y in range(len(l)):
		tmp.append(l[y][x])
	nl.append(tmp)

s = ""
data = ""
s = ",\n".join([",".join(nl[x]) for x in range(len(nl))])
data = "\n".join([" ".join(nl[x]) for x in range(len(nl))])
print data

f = open(fname+"_str.data", "w")
f.write(s)
f.close()
f = open(fname, "w")
f.write(s)
f.close()
