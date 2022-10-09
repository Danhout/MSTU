# task2.py
def run(path):
	# text file with encoded message
	with open(f'{path}/task2.txt','r',encoding='cp1251') as src_file:
		hex_message = src_file.read()
	
	# decode message
	bytes_message = bytes.fromhex( ''.join( map( lambda x : x[2:], hex_message.split() ) ) )
	message = bytes_message.decode()
	
	print(f'2. С помощью кодовой таблицы ASCII декодируйте сообщение.\n#9: {hex_message}',end='\n'*2);
	print(f'Декодированное сообщение:\n{message}',end='\n'*4)