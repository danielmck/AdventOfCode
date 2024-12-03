import numpy as np
import re

def fake_sign(x,y):
    if x > y:
        sgn = -1
    elif x < y:
        sgn = 1
    else:
        sgn = 0
    return(sgn)

def rec_manager(nums_in,index,lev_lim, level):
    works = False
    if level < lev_lim:
        if index < 2:
            works = works or check_valid(nums_in[1:],lev_lim,level+1)
        lost_i = nums_in[0:index]+nums_in[index+1:]
        lost_i1 = nums_in[0:index+1]+nums_in[index+1:len(lost_i)]
        works = works or check_valid(lost_i,lev_lim,level+1)
        works = works or check_valid(lost_i1,lev_lim,level+1)
    return(works)
    
def check_valid(nums_in, lev_lim = 0, level = 0):
    dir_sgn = fake_sign(int(nums_in[0]),int(nums_in[1]))
    for i in range(len(nums_in)-1):
        diff = int(nums_in[i+1])-int(nums_in[i])
        if (diff*dir_sgn < 1) or (diff*dir_sgn > 3):
            if lev_lim > level:
                # print(nums_in,i,diff,dir_sgn)
                works = rec_manager(nums_in,i,lev_lim,level)
                return(works)
            else:
                return(False)
            # else:
            #     removed = i
            #     lev_lim=0
            # break
            
        if i==len(nums_in)-2:
            return(True)


in_data = open("input.txt", "r")
num = re.compile('[1-9][0-9]*')
count=0
for line in in_data:
    nums_in = num.findall(line)
    if check_valid(nums_in,0):
        count = count+1
    else:
        valid = False
        for j in range(len(nums_in)):
            valid = valid or check_valid(nums_in[0:j]+nums_in[j+1:],0)
        if valid:
            count = count+1


print(count)