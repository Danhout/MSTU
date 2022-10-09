# task3.py
def run(path):
	# text file with a word
	with open(f'{path}/task3.txt') as src_file:
		message = src_file.read()

	# encode word
	bytes_message = message.encode('cp1251')
	hex_message = ' '.join( map( lambda byte : f'0x{hex(byte)[2:].upper()}', list(bytes_message) ) )
	
	print(f'3. С помощью кодовой таблицы ASCII закодируйте в последовательность шестнадцатеричных чисел слово: \'{message}\'',end='\n'*2)
	print(f'Закодированное слово:\n{hex_message}',end='\n'*4)