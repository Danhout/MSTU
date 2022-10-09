# task1.py
def run():
	# lengths of binary sequences
	signs = [4, 8, 12, 16]

	max_sign = max(signs)
	max_width_sign = len (str (max_sign) )
	max_width_symbol = len( str( 1 << max_sign ) )

	print(f'1. Оцените число символов алфавита, кодируемого с помощью двоичных последовательностей длиной:')
	for i, sign in enumerate(signs):
		print(f'{ chr(ord("а") + i) }) {sign : >{max_width_sign}} знаков - {1 << sign : >{max_width_symbol}} символов')
	print(end='\n'*3)