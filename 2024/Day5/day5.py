import numpy as np
import re

def visit(new, L, temp, perm):
    if new in perm:
        return(L, temp, perm)
    elif new in temp:
        raise Exception("It's a loop de loop")
    temp.add(new)
    if new in graph_dict:
        # print(new,line_set.intersection(graph_dict[new]))
        for baby in line_set.intersection(graph_dict[new]):
            L, temp, perm = visit(baby,L,temp,perm)
    temp.remove(new)
    perm.add(new)
    L = [new]+L
    # print(L)
    return(L,temp,perm)

in_data = open("input.txt", "r")
num = re.compile('[1-9][0-9]*')
pipe = re.compile('\\|')

first = []
second = []

line = next(in_data)
is_pipe = pipe
graph_dict = dict()
while is_pipe is not None:
    nums = num.findall(line)
    first.append(int(nums[0]))
    second.append(int(nums[1]))
    if int(nums[0]) not in graph_dict:
        graph_dict[int(nums[0])] = {int(nums[1])}
    else:
        graph_dict[int(nums[0])].add(int(nums[1]))
    line = next(in_data)
    is_pipe = pipe.search(line)

count = 0
for line in in_data:
    nums = num.findall(line)
    valid = True
    for i in range(len(nums)):
        nums[i]=int(nums[i])
    for j in range(len(first)):
        try:
            f_ind = nums.index(first[j])
        except ValueError:
            f_ind = None
        try:
            s_ind = nums.index(second[j])
        except ValueError:
            s_ind = None
        if (f_ind is not None) and (s_ind is not None):
            if s_ind < f_ind:
                valid = False
                break
    if not valid:
        line_set = set(nums)
        temp_set = set()
        perm_set = set()
        new_nums = list()
        for new in nums:
            new_nums, temp_set, perm_set = visit(new,new_nums,temp_set,perm_set)
        # print(new_nums)
        count = count + new_nums[len(new_nums)//2]
print(count)

