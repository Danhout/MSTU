from math import ceil, log2

class LZW_Encoder:
	def create_node(self, number):
		return LZW_Encoder.Node(self, number)
	class Node:
		def __init__(self, encoder, number):
			self.number = number
			self.child = [None] * encoder.alphabet_power

	def __init__(self, alphabet):
		self.alphabet, self.alphabet_power = alphabet, len(alphabet)
		self.size_fill_tree, self.size_key = self.alphabet_power + 1, ceil( log2(self.alphabet_power + 1) ) + 1
		self.max_size_fill_tree, self.max_size_key = 1 << self.size_key, self.size_key + 2
		
		self.dict_char2numb = dict()
		for i in range(self.alphabet_power):
			self.dict_char2numb[ alphabet[i] ] = i

		self.root = self.create_node(None)
		for i in range(self.alphabet_power):
			self.root.child[i] = self.create_node(i)

	def is_contains(self, word):
		node = self.root
		for c in word:
			node = node.child[ self.dict_char2numb[c] ]
			if node == None:
				return False
		return True

	def get(self, word):
		node = self.root
		for c in word:
			node = node.child[ self.dict_char2numb[c] ]
		return bin(node.number)[2:].zfill(self.size_key)

	def key_clear(self):
		return bin(self.alphabet_power)[2:].zfill(self.max_size_key)

	def push(self, word):
		# increase count of elements in tree
		self.size_fill_tree += 1
		
		# find the word without last character in the encoder's tree 
		node = self.root
		for c in word[:-1]:
			node = node.child[ self.dict_char2numb[c] ]
		# the number of the word without last character in the encoder's tree
		bin_numb_prev = bin(node.number)[2:].zfill(self.size_key)
		is_increase_size_key = False
		
		# add the word to the tree
		node.child[ self.dict_char2numb[ word[-1] ] ] = self.create_node(self.size_fill_tree)
		# check the filling of element's count for the key's size
		if self.size_fill_tree == self.max_size_fill_tree:
			self.size_key += 1
			is_increase_size_key = True
			self.max_size_fill_tree = self.max_size_fill_tree << 1
			# check the key size for overflow
			if self.size_key > self.max_size_key:
				self.__init__(self.alphabet)
				# return overflowing's number
				return self.key_clear()
		# the encode number of the word without last character
		return bin_numb_prev

	def encode(self, text):
		encode_text, len_text = '', len(text)
		# number of character is outer by while 'cause getting key_clear sign doesn't encode word  
		i = 0
		word = ''
		while i < len_text:
			c = text[i]
			word += c
			i += 1
			if not self.is_contains(word):
				encode_word_without_latest_char = self.push(word)
				if encode_word_without_latest_char == self.key_clear():
					i -= len(word)
					word = ''
				else:
					word = c
				encode_text += encode_word_without_latest_char
		encode_text += self.get(word)
		return encode_text

class LZW_Decoder:
	def __init__(self, alphabet):
		self.alphabet, self.alphabet_power = alphabet, len(alphabet)
		self.max_number = self.alphabet_power
		self.size_key = ceil( log2(self.alphabet_power + 1) ) + 1
		
		self.list_numb2word = list(alphabet)
		# key_clear
		self.list_numb2word.append(None)

	def decode(self, text):
		decode_text, len_text = '', len(text)
		i = 0
		bin_numb = ''
		prev_word, word = '', ''
		while i < len_text:
			bin_numb += text[i]
			len_bin_numb = len(bin_numb)
			i += 1
			if len_bin_numb == self.size_key:
				numb = int(bin_numb, 2)
				bin_numb = ''
				# check key_clear
				if numb == self.alphabet_power:
					self.__init__()
					prev_word = ''
					i -= len_bin_numb
				# translate a number of a word to word and add new word to decoder's list 
				else:
					if numb < self.max_number:
						word = self.list_numb2word[numb]
					elif numb == self.max_number:
						word = prev_word + prev_word[0]
					else:
						raise Exception(f'Decoded number "{numb}" of a word can\'t be more than "{self.max_number}" - count of words in decoder\'s list')
					decode_text += word
					self.list_numb2word.append(prev_word + word[0])
					self.max_number += 1
					if self.max_number == (1 << self.size_key) - 1:
						self.size_key += 1
					prev_word = word
		return decode_text			


# LZW code
# task7
def run(path):
	path_src = f'{path}/task4.txt'
	path_encode = f'{path}/task7encode.txt'
	path_decode = f'{path}/task7decode.txt'

	alphabet = 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ' 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя' '-.,\u2026!?: \n'
	
	# encode
	with open(path_src,'r',encoding='cp1251') as src_file:
		with open(path_encode,'w',encoding='cp1251') as encode_file:
			encode_file.write( LZW_Encoder(alphabet).encode( src_file.read() ) )
	
	# decode
	with open(path_encode,'r',encoding='cp1251') as encode_file:
		with open(path_decode,'w',encoding='cp1251') as decode_file:
			decode_file.write( LZW_Decoder(alphabet).decode( encode_file.read() ) )

	with open(path_src,'r',encoding='cp1251') as src_file:
		with open(path_encode,'r',encoding='cp1251') as encode_file:
			with open(path_decode,'r',encoding='cp1251') as decode_file:
				print('7. Закодируйте и декодируйте текстовое сообщение с применением словарного метода.',end='\n'*2)
				print(f'Исходное сообщение:\n{src_file.read()}',end='\n'*2)
				print(f'Закодированное LZW алгоритмом сообщение:\n{encode_file.read()}',end='\n'*2)
				print(f'Раскодированное LZW алгоритмом сообщение:\n{decode_file.read()}')