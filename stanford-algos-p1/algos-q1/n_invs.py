import math
import fileinput

def merge_sort(list, t_length):
	if len(list) == 1:
		return [list, 0]
	else:
		middle = int(math.ceil(len(list)/2.0))
		inv_count = 0
		left = merge_sort(list[0:middle], t_length)
		# print "left: ", left
		left_list = left[0]
		inv_count += left[1]
		right = merge_sort(list[middle:len(list)], t_length)
		# print "right: ", right
		right_list = right[0]
		inv_count += right[1]

		counter = 0
		i = 0
		j = 0
		max = len(left_list)+len(right_list)
		combined = []
		
		while counter < max:
			if j >= len(right_list):
				combined.append(left_list[i])
				i+=1
			elif i>= len(left_list):
				combined.append(right_list[j])
				j+=1
			elif left_list[i] <= right_list[j]:
				combined.append(left_list[i])
				i+=1
			else:
				combined.append(right_list[j])
				j+=1
				inv_count += len(left_list)-i

			counter+=1

		return [combined, inv_count]

array = []

for line in fileinput.input():
	array.append(int(line))

print(merge_sort(array, len(array))[1])

