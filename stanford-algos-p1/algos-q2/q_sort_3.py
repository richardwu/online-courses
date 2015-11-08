import math
import fileinput

n_comps = 0

def quick_sort(arr):
	global n_comps
	n_comps += len(arr) - 1

	first = arr[0]
	middle = arr[ int(math.ceil(len(arr) / 2.0)) - 1]
	last = arr[len(arr) - 1]

	pot_pivots = [first, middle, last]
	
	pot_pivots.sort()

	pivot = pot_pivots[1]

	if middle == pivot:
		arr[0], arr[int(math.ceil(len(arr) / 2.0)) - 1] = middle, first
	elif last == pivot:
		arr[0], arr[len(arr) - 1] = last, first

	i = 0
	j = 1
	
	while j < len(arr):
		if (arr[j] < pivot):
			i += 1
			if (j > i):
				arr[j], arr[i] = arr[i], arr[j]
		j += 1
	
	arr[0], arr[i] = arr[i], arr[0]
	
	if i > 0:
		left = quick_sort(arr[:i])
	else:
		left = []
	
	if i < len(arr) - 1:
		right = quick_sort(arr[i+1:len(arr)])
	else:
		right = []
	
	return left + [pivot] + right

arr = []

for line in fileinput.input():
	arr.append(int(line))

sorted_arr = quick_sort(arr)

print n_comps
