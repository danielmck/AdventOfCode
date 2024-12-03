import numpy as np
import re
import time

t0 = time.time()

t1 = time.time()

total = t1-t0
in_data = open("input.txt", "r")
list0=[]
list1=[]
mul_str = re.compile('mul\([1-9][0-9]*,[1-9][0-9]*\)')
num = re.compile('[1-9][0-9]*')
do = re.compile('do\(\)')
dont = re.compile('don\'t\(\)')
total=0
for line in in_data:
    while len(line) > 0:
        dont_match = dont.search(line)
        
        if dont_match is not None:
            # print(dont_match.group())
            ext_line = line[:dont_match.end()]
            line = line[dont_match.end():]
        else:
            ext_line = line;

        mul_in = mul_str.findall(ext_line)
        for seg in mul_in:
            nums_in= num.findall(seg)
            total = total + int(nums_in[0])*int(nums_in[1])
        do_match = do.search(line)

        if do_match is not None: 
            # print(do_match.group())
            line = line[do_match.end():]
        else:
            break
t1 = time.time()

print(t1-t0)
print(total)