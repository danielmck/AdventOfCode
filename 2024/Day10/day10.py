import numpy as np
import re

class trail_map:
    def __init__(self,list_in):
        self.map = list_in
        self.height = len(self.map)
        self.width = len(self.map[0])
        self.zeros = self.find_zeros()
        self.x_step = [1,0,-1,0]
        self.y_step = [0,1,0,-1]


    def find_zeros(self):
        trailhead_list = list()
        for j in range(self.height):
            for k in range(self.width):
                if (map[j][k] == 0):
                    trailhead_list.append((k,j))
        return(trailhead_list)
        

    def next_step(self,curr, path_dict):
        for pts in path_dict[curr]:
            xval = pts[0]
            yval= pts[1]
            for j in range(4):
                new_x = xval+self.x_step[j]
                new_y = yval+self.y_step[j]
                if min(new_x,new_y) > -1 and new_x < self.width and new_y<self.height:
                    if map[new_y][new_x] == curr+1:
                        path_dict[curr+1].add((new_x,new_y))
        return(path_dict)
    
    def next_step_paths(self,curr, path_dict):
        for pts in path_dict[curr]:
            xval = pts[0]
            yval= pts[1]
            for j in range(4):
                new_x = xval+self.x_step[j]
                new_y = yval+self.y_step[j]
                if min(new_x,new_y) > -1 and new_x < self.width and new_y<self.height:
                    if map[new_y][new_x] == curr+1:
                        path_dict[curr+1].append((new_x,new_y))
        return(path_dict)


in_data = open("input.txt", "r")
num = re.compile('[0-9]')

count = 0
map = list()
for line in in_data:
    nums = num.findall(line)
    for i in range(len(nums)):
        nums[i] = int(nums[i])
    map.append(nums)

map_object = trail_map(map)

for start in map_object.zeros:
    path_dict = {}
    for i in range(10):
        path_dict[i] = set()
    path_dict[0].add(start)
    for step in range(9):
        path_dict=map_object.next_step(step,path_dict)
    count += len(path_dict[9])

print(count)
count_paths = 0
for start in map_object.zeros:
    all_paths_dict = {}
    for i in range(10):
        all_paths_dict[i] = list()
    all_paths_dict[0].append(start)
    for step in range(9):
        all_paths_dict=map_object.next_step_paths(step,all_paths_dict)
    count_paths += len(all_paths_dict[9])
print(count_paths)