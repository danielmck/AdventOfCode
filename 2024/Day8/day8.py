import numpy as np
import re

in_data = open("input.txt", "r")
num = re.compile('[a-z]|[A-Z]|[0-9]')
count = 0
type_dict = dict()
line_num = 0 
for line in in_data:
    width = len(line)
    line_ind = 0
    find = num.search(line)
    while find is not None:
        if find.group() in type_dict:
            type_dict[find.group()].append(np.array((line_ind+find.start(),line_num)))
        else:
            type_dict[find.group()] = [np.array((line_ind+find.start(),line_num))]
        # print(find.start(),find.end())
        line = line[find.end():]
        find = num.search(line)   
    line_num += 1
poles = np.zeros((width,line_num))
print(type_dict.keys())
for points in type_dict:
    nodes = type_dict[points]
    while (len(nodes)>1):
        curr = nodes[0]
        nodes = nodes[1:]
        for pair in nodes:
            diff = curr-pair
            pt1 = curr + diff
            if np.min(pt1) > -1 and pt1[0]<width and pt1[1]<line_num:
                poles[pt1[0],pt1[1]] = 1
            pt2 = pair - diff
            if np.min(pt2) > -1 and pt2[0]<width and pt2[1]<line_num:
                poles[pt2[0],pt2[1]] = 1
            if (diff[0]%3 == 0) & (diff[1]%3 == 0):
                pt3 = pair + diff/3
                pt4 = pair + 2*diff/3
                poles[int(pt3[0]),int(pt3[1])] = 1
                poles[int(pt4[0]),int(pt4[1])] = 1
print(np.shape(poles))
print(np.sum(poles))