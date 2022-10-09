# task4.py
def run(path, shift = 0):
	# encode and decode dictionaries
	encoder = dict()
	decoder = dict()
	for map_num_char in [map( lambda num_char: (num_char[0] + 34 + shift, num_char[1]), enumerate('-.,\u2026!?: \n') ), 
						map( lambda num_char: (num_char[0] + 1 + shift, num_char[1]), enumerate('абвгдеёжзийклмнопрстуфхцчшщъыьэюя') ) ]:
		for num_char in map_num_char:
			encoder[num_char[1]] = num_char[0]
			decoder[num_char[0]] = num_char[1]

	# paths to source and output files
	path_src = f'{path}/task4.txt'
	path_encode = f'{path}/task4encode.txt'
	path_decode = f'{path}/task4decode.txt'

	# encode
	with open(path_src,'r',encoding='cp1251') as src_file:
		with open(path_encode,'w',encoding='cp1251') as encode_file:
			for c in src_file.read():
				if c.lower() in encoder.keys():
					encode_file.write(f'{encoder[c.lower()]} ')
				else:
					encode_file.write(c)
	
	# decode
	with open(path_encode,'r',encoding='cp1251') as encode_file:
		with open(path_decode,'w',encoding='cp1251') as decode_file:
			for encode_line in encode_file.read().splitlines():
				for num in encode_line.split():
					decode_file.write(f'{decoder[int(num)]}')
				decode_file.write('\n')

	# result
	with open(path_src,encoding='cp1251') as src_file:
		with open(path_encode,'r',encoding='cp1251') as encode_file:
			with open(path_decode,'r',encoding='cp1251') as decode_file:
				print('4. Закодируйте и декодируйте любое текстовое сообщение с помощью кода Цезаря '\
				 	  '- пронумеровав алфавит десятичными цифрами и заменив буквы соответствующими им числами',end='\n'*2)	
				print(f'Исходное текстовое сообщение:\n{src_file.read()}',end='\n'*2)
				print(f'Закодированное сообщение:\n{encode_file.read()}',end='\n'*2)
				print(f'Декодированное сообщение:\n{decode_file.read()}',end='\n'*4)