import numpy as np
import re

class GuardMap:
    def __init__(self,map,xpos,ypos,dir):
        self.map = map
        self.size_x = len(map[0])
        self.size_y = len(map)
        
        self.xpos = xpos
        self.ypos = ypos
        self.dir = dir
        self.del_x = [1,0,-1,0]
        self.del_y = [0,1,0,-1]
        self.path_x = [xpos]
        self.path_y = [ypos]

        self.map_x()
        self.loop_map = self.map

    def map_x(self):
        if (min(self.xpos,self.ypos) >= 0) and (self.xpos < self.size_x) and (self.ypos < self.size_y):
            self.map[self.ypos] = self.map[self.ypos][0:self.xpos]+'X'+self.map[self.ypos][self.xpos+1:]

    def move_guard(self):
        can_move = False
        in_domain = True
        while not can_move:
            new_x = self.xpos + self.del_x[self.dir]
            new_y = self.ypos + self.del_y[self.dir]
            if (new_x > self.size_x-1) or (new_x < 0):
                can_move = True
                in_domain = False
            elif (new_y > self.size_y-1) or (new_y < 0):
                can_move = True
                in_domain = False
            else:
                if self.map[new_y][new_x] == '#':
                    print(new_x,new_y,self.map[new_y][new_x])
                    can_move = False
                    self.dir = (self.dir+1)%4
                else:
                    can_move = True
        self.xpos = new_x
        self.ypos = new_y
        if in_domain:
            self.path_x.append(new_x)
            self.path_y.append(new_y)
        self.map_x()
        return(in_domain)
    
    def count_distinct(self):
        count = 0
        for i in range(self.size_y):
            curr_line = self.map[i]
            for j in range(self.size_x):
                if curr_line[j] == 'X':
                    count = count+1
        return(count)
    
in_data = open("input.txt", "r")
arr = re.compile('v|\\^|\\<|\\>')
map_in = []
dict_dir = {'>':0,'v': 1,'<':2,'^':3}
line_num = 0
for line in in_data:
    if line[-1:] == '\n':
        line = line[:-1]
    map_in.append(line)
    found = arr.search(line)
    if found is not None:
        x_in = found.start()
        y_in = line_num
        dir_in = dict_dir[found.group()]
    line_num +=1
guard = GuardMap(map_in,x_in,y_in,dir_in)
in_domain = True
steps = 0
while in_domain and steps<100000:
    in_domain=guard.move_guard()
    steps+=1
print(guard.count_distinct())
