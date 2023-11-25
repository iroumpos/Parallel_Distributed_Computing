import sys



def csvAppendToRow(csv,row,element):
    csv = open(csv,"r+")
    lines = csv.readlines()
    line = lines[row]
    line.replace('\n','')
    line = line + element + ','
    # line.strip()
    # print(lines)
    lines[row] = line
    # print("After:")
    # print(lines)
    csv.seek(0)
    csv.write("".join(lines))
    return

with open('measurements.txt') as f:
    lines = f.readlines()

step1 = lines[1]
step2 = lines[2]
step4 = lines[3]
step8 = lines[4]
step16 = lines[5]

# c= open("cpu.csv","r+") 
# clines = c.readlines()
# print(clines)
# g= open("gpu.csv")
# glines = g.readlines()


csvAppendToRow("cpu.csv",int(sys.argv[1]),cputime)
csvAppendToRow("gpu.csv",int(sys.argv[1]),gputime)
# print(int(sys.argv[1]))
# line = clines[int(sys.argv[1])]
# line.replace('\n',' ')
# line = line + cputime + ","
# # print(clines)
# clines[int(sys.argv[1])] = line
# # print(clines)
# c.seek(0)
# print(" ".join(clines))
# c.write(" ".join(clines))



# print(cputime)
# print(gputime)