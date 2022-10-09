# nodes for binary tree of Haffman's code
class Node:
	def __init__(self, weight = None, data = None, left = None, right = None):
		self.weight = weight
		self.data = data
		self.left = left
		self.right = right
	
	def __lt__(self, other):
		return self.weight < other.weight


# queue for marging nodes to binary tree (Haffman's algorithm)
class PriorityQueue:
	def __init__(self):
		self.list = list()
	
	def put(self, node):
		self.list.append(node)
		self.list.sort(reverse=True)
	def get(self):
		return self.list.pop()
	
	def size(self):
		return len(self.list)


class Haffman_Encoder:
	def __init__(self, dict_char_count):
		# translate dictionary of character and count of the character in text to tree leaves in priority queue
		pr_queue = PriorityQueue()
		for char, count in dict_char_count.items():
			pr_queue.put( Node(data = char, weight = count) )

		# marge tree leaves to tree
		while(pr_queue.size() > 1):
			node1, node2 = pr_queue.get(), pr_queue.get()
			pr_queue.put( Node(weight = node1.weight + node2.weight, left = node1, right = node2) )
		root = pr_queue.get()

		# Haffman's code by binary tree
		# dictionary from character to binary Haffman's code
		self.dict_char_code = dict()
		def code_Haffman(node, code = ''):
			if node.data is None:
				code_Haffman(node.left, code + '0')
				code_Haffman(node.right, code + '1')
			else:
				self.dict_char_code[node.data] = code
		code_Haffman(root)

	def encode(self, text):
		encode_text = ''
		for c in text:
			encode_text += self.dict_char_code[c]
		return encode_text


class Haffman_Decoder:
	def __init__(self, dict_char_count):
		# translate dictionary of character and count of the character in text to tree leaves in priority queue
		pr_queue = PriorityQueue()
		for char, count in dict_char_count.items():
			pr_queue.put( Node(data = char, weight = count) )

		# marge tree leaves to tree
		while(pr_queue.size() > 1):
			node1, node2 = pr_queue.get(), pr_queue.get()
			pr_queue.put( Node(weight = node1.weight + node2.weight, left = node1, right = node2) )
		self.root = pr_queue.get()

	def decode(self, text):
		decode_text = ''
		node = self.root
		for b in text:
			if b == '0':
				node = node.left
			elif b == '1':
				node = node.right
			if node.data is not None:
				decode_text += node.data
				node = self.root
		return decode_text


# task 6 (Haffman's code)
def run(path):
	# paths to source, encode and decode files 
	path_src = f'{path}/task4.txt'
	path_encode = f'{path}/task6encode.txt'
	path_decode = f'{path}/task6decode.txt'

	# counting the number of letters in source text
	dict_char_count = dict()
	with open(path_src,'r',encoding='cp1251') as src_file:
		for c in src_file.read():
			if dict_char_count.get(c) is None:
				dict_char_count[c] = 0
			dict_char_count[c] += 1
	
	# encode
	with open(path_src,'r',encoding='cp1251') as src_file:
		with open(path_encode,'w',encoding='cp1251') as encode_file:
			encode_file.write( Haffman_Encoder(dict_char_count).encode( src_file.read() ) )
	
	# decode
	with open(path_encode,'r',encoding='cp1251') as encode_file:
		with open(path_decode,'w',encoding='cp1251') as decode_file:
			decode_file.write( Haffman_Decoder(dict_char_count).decode( encode_file.read() ) )
				
	with open(path_src,'r',encoding='cp1251') as src_file:
		with open(path_encode,'r',encoding='cp1251') as encode_file:
			with open(path_decode,'r',encoding='cp1251') as decode_file:
				print('6.Закодируйте и декодируйте текстовое сообщение с помощью кода Хаффмана.',end='\n'*2)
				print(f'Исходное сообщение:\n{src_file.read()}',end='\n'*2)
				print(f'Закодированное сообщение:\n{encode_file.read()}',end='\n'*2)
				print(f'Декодированное сообщение:\n{decode_file.read()}',end='\n'*4)	