from math import *
from fileinput import *
from random import *
from copy import *

input_v = []

# of edges
m = 0

# Put input into an array
def to_int(x): return int(x)

for line in input():
	input = str(line).split()
	input =	map(to_int, input)
	# First index identifies true index of vertex
	input[0] = [input[0]]
	# Add # of edges (ignore first)
	m += len(input) - 1 
	input_v.append(input)

# There should be 1/2 the # of edges (since 1 edge = 2 vertices)
m /= 2

#Find # of vertices
n = len(input_v)
max_iters = int(n*n)

#Init smallest # of cross edges found
c_edges = n-1;

vertices = []

# Perform Karger's n^2ln(n) times to ensure p > 1-1/n
for i in range(0, max_iters):
	print "iter: " + str(i)

	vertices = deepcopy(input_v)

	#Contract edges n-2 times to find A and B
	for j in range(0, n - 2):

		# length of current array
		len_arr = n - j

		#rand_vn => random index within current array
		#i_vn => true index of vertex from orig array

		# Randomly select 1st vertex (v1) to contract
		rand_v1 = randint(1, len_arr) - 1
		i_v1 = vertices[rand_v1][0][0]
		
		# Randomly select 2nd vertex (v2) connected to v1
		i_in_v1 = randint(1,len(vertices[rand_v1]) - 1)
		i_v2 = vertices[rand_v1][i_in_v1]

		for k in range(0, len_arr):
			if i_v2 in vertices[k][0]:
				rand_v2 = k

		for y in vertices[rand_v2][1:]:
			if y not in vertices[rand_v1]:
				vertices[rand_v1].append(y);

		# Remove each other's indices from list of edges
		for q in vertices[rand_v2][0]:
			if q in vertices[rand_v1]:
				vertices[rand_v1].remove(q)
			# Add indices from v2 to v1 (supernode)
			vertices[rand_v1][0].append(q)

		for r in vertices[rand_v1][0]:
			if r in vertices[rand_v1]:
				vertices[rand_v1].remove(r)

		vertices.pop(rand_v2)

		# print vertices

	min_cut_edges = max(len(vertices[0]), len(vertices[1])) - 1

	if min_cut_edges < c_edges:
		c_edges = min_cut_edges

print c_edges

