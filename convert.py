import sys

fname = sys.argv[1]
f = open(fname, "r")
s = f.read().rstrip()
f.close()
f = open(fname+".old", "w")
f.write(s)
f.close()
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
s = ",\n".join([",".join(nl[x]) for x in range(len(nl))])
print s

f = open(fname, "w")
f.write(s)
f.close()
