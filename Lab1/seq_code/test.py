with open('inner_p_measure.txt') as f:
    lines = f.readlines()

file1 = open("step1.txt","w")
file2 = open("step2.txt","w")
file4 = open("step4.txt","w")
file8 = open("step8.txt","w")
file16 = open("step16.txt","w")

step1 = lines[0]
step2 = lines[1]
step4 = lines[2]
step8 = lines[3]
step16 = lines[4]

file1.write('\n' + step1)
file2.write('\n' + step2)
file4.write('\n' + step4)
file8.write('\n' + step8)
file16.write('\n' + step16)