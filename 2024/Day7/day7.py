import numpy as np
import re

in_data = open("input.txt", "r")
num = re.compile('[1-9][0-9]*')
count = 0
n_inputs = 3
for line in in_data:
    nums_in = num.findall(line)
    total = int(nums_in[0])
    eq_inputs = nums_in[1:]
    eq_len = len(eq_inputs)
    for i in range(eq_len):
        eq_inputs[i]=int(eq_inputs[i])
    for j in range(pow(n_inputs,eq_len)):
        eq_tot = eq_inputs[0]
        temp_j = j
        for k in range(1,eq_len):
            action = int(temp_j%pow(n_inputs,k+1))/(pow(n_inputs,k))
            if (action == 0):
                eq_tot = eq_tot + eq_inputs[k]
            elif (action == 1):
                eq_tot = int(str(eq_tot)+str(eq_inputs[k]))
            else:
                eq_tot = eq_tot * eq_inputs[k]
            temp_j = temp_j - action*pow(n_inputs,k)
        if (eq_tot == total):
            count = count + total
            break

print(count)
    