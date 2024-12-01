import numpy as np
import re

in_data = open("input.txt", "r")
list0=[]
list1=[]
num = re.compile('[1-9][0-9]*')
for line in in_data:
    nums_in = num.findall(line)
    list0.append(int(nums_in[0]))
    list1.append(int(nums_in[1]))

list0.sort()
list1.sort()

total = 0
for i in range(len(list0)):
    # total = total + abs(list0[i]-list1[i])
    total = total + list0[i]*list1.count(list0[i])

print(total)

