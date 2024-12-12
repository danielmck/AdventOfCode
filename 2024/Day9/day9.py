import numpy as np
import re

in_data = open("test.txt", "r")
num = re.compile('[0-9]')

count = 0
big_list = list()
line = next(in_data)
nums = num.findall(line)
len_input = len(nums)
for i in range(len_input):
    nums[i] = int(nums[i])
# print(nums)
for j in range(len_input):
    for k in range(nums[j]):
        if (j%2 == 0):
            big_list.append(j//2)
        else:
            big_list.append(-1)
# print(big_list)
# end_ind = len(big_list)-1
# start_ind = 0
# while start_ind < end_ind:
#     while big_list[end_ind] < 0:
#         end_ind = end_ind-1
#     while big_list[start_ind] >= 0:
#         start_ind = start_ind+1
#     big_list[start_ind] = big_list[end_ind]
#     big_list[end_ind] = -1
#     end_ind -= 1
#     start_ind+=1
# count = 0
# for i in range(len(big_list)):
#     if big_list[i]!=-1:
#         count += i*big_list[i]
# print(count)
print(big_list)
end_ind = len(big_list)-1
while end_ind >= 0:
    while big_list[end_ind] < 0:
        end_ind = end_ind-1
    end_in_end = max(end_ind+1,len(big_list)-1)
    curr_val = big_list[end_ind]
    while big_list[end_ind] == curr_val:
        end_ind = end_ind-1
        if (end_ind == 0):
            break
    end_in_st = end_ind+1
    data_len = end_in_end-end_in_st
    start_ind = 0
    print(end_in_st,end_in_end,len(big_list))
    while (start_ind < end_in_st):
        while big_list[start_ind] >= 0:
            start_ind = start_ind+1
        start_ind_st = start_ind
        st_curr_val = big_list[start_ind]
        while big_list[start_ind] == st_curr_val:
            start_ind += 1
            if start_ind == len(big_list):
                break
        start_ind_end = start_ind
        if (start_ind_end-start_ind_st) >= data_len:
            for i in range(data_len):
                big_list[start_ind_st+i] = big_list[end_in_st+i]
                big_list[end_in_st+i] = -1
    end_ind = end_ind-1
print(big_list)
    # big_list[start_ind] = big_list[end_ind]
    # big_list[end_ind] = -1
    # end_ind -= 1
    # start_ind+=1
count = 0
for i in range(len(big_list)):
    if big_list[i]!=-1:
        count += i*big_list[i]
print(count)