def sum_binary_tree(tree):
	if len(tree) == 0:
		return 0
	return datum(tree) + sum_binary_tree(left_child(tree)) + sum_binary_tree(right_child(tree))

tree = [1,[2,[3,[],[]],[4,[],[]]],[5,[6,[],[]],[7,[],[]]]]

			
[3] + [2] + [4] + [1] + [6] + [5] + [7]

def inorder(tree):
	if tree == []:
		return []
	elif isleaf(tree):
		return [datum(tree)]
	else:
		return inorder(left_child(tree)) + [datum(tree)] + inorder(right_child(tree))


def isMinHeap(tree):
	if isleaf(tree):
		return True
	elif (left_child(tree) and datum(tree) > datum(left_child(tree))):
		return False
	elif (right_child(tree) and datum(tree) > datum(right_child(tree))):
		return False
	else:
		return isMinHeap(left_child(tree)) and isMinHeap(right_child(tree))


[1,[],[]]
[1,[2,[],[]],[3,[],[]]]
[5,[2,[],[]],[4,[],[]]]


def datum(t):
	return t[0]

def children(t):
	return t[1:]

def is_leaf(t):
	return len(children(t)) == 0

def is_empty(t):
	return t == []

def print_tree(tree, level =0):
	if not tree:
		return
	print(" " * 4 * level + str(datum(tree)))
	for child in children(tree):
		print_tree(child, level+1)




[1,[2,[3]],[4,[8],[9],[11]]]


def sum_tree(tree):
	if is_leaf(tree):
		return datum(tree)
	return datum(tree) + sum_forest(children(tree))

def sum_forest(forest):
	if len(forest) == 0:
		return 0
	return sum_tree(forest[0]) + sum_forest(forest[1:])

[1,[2],[3]]
1
[1,[2],[3,[4]]]
2
[1,[2],[3,[4,[5]]]]
3

def max_depth(tree):
	if is_leaf(tree):
		return 0
	else:
		return max(max_depth_forest(children(tree))) + 1

def max_depth_forest(forest):
	if len(forest) == 0:
		return []
	else:
		return [max_depth(forest[0])] + max_depth_forest(forest[1:])

def maxdepth(tree):
	if is_leaf(tree):
		return 0
	else:
		maximum = -1
		for child in children(tree):
			currentDepth = 1 + maxdepth(child)
			if currentDepth > maximum:
				maximum = currentDepth
		return maximum


[300,[3],[5],[10],[2]]
[-210, [7],[-10, [-1], [5], [2]],[3]]
[-210, [7],[-10, [-2], [5], [2]],[3]]


def checkMul(tree):
	if is_leaf(tree):
		return True
	mult_child = 1
	for e in children(tree):
		mult_child *= datum(e)
	if datum(tree) == mult_child:
		return checkmul_helper(children(tree))
	else:
		return False

def checkmul_helper(forest):
	result = True
	for e in forest:
		result = result and checkMul(e)
		if not result:
			break
	return result



def pushQueue(q,e):
	return q + [e]

def popQueue(q):
	e = q[0]
	newq = q[1:]
	return (e,newq)

def isEmptyQueue(q):
	return len(q) == 0


[1,[2,[4],[5]],[3,[6],[7],[8]]]
[1,2,3,4,5,6,7,8]

def breadthFirst(tree):
	result = []
	queue = []
	result.append(datum(tree))
	for child in children(tree):
		queue = pushQueue(queue,child)
	while not isEmptyQueue(queue):
		item, queue = popQueue(queue)
		result.append(datum(item))
		for child in children(item):
			if child:
				queue = pushQueue(queue, child)
	return result
