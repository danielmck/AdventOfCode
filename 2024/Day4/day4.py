import numpy as np
import re
import time

in_data = open("input.txt", "r")
all_lines=[]
for line in in_data:
    if line[-1:] == '\n':
        line = line[:-1]
    all_lines.append(line)

line_len = len(all_lines[0])
text_len = len(all_lines)
# del_x = [1,0,-1,0,1,1,-1,-1]
# del_y = [0,-1,0,1,1,-1,-1,1]
del_x = [1,1]
del_y = [1,-1]

find_str={'MAS','SAM'}
count = 0
for y in range(text_len):
    for x in range(line_len):
        
        # for i in range(8):
        if all_lines[y][x] == 'A':
            poss_x = True
            for i in range(2):
                four_str = ''
                # for j in range(1,len(find_str)):
                for j in range(-1,2):
                    x_in = x+del_x[i]*j
                    y_in = y+del_y[i]*j
                    if (x_in < 0) or (x_in > line_len-1):
                        break
                    if (y_in < 0) or (y_in > text_len-1):
                        break
                    four_str=four_str+all_lines[y_in][x_in]
                if four_str not in find_str:
                    poss_x = False
                    break
            if poss_x:
                count = count+1
                # print(x,y,i,four_str)
                

print(count)
