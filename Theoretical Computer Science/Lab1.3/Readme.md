# Теоретическая информатика
## Лабораторная № 1.3
## Вариант № 9

***Исходные коды программы***

[lab3.py](src/lab3.py)

**Исходники заданий**

[task1.py](src/tasks/task1.py)
&nbsp;
[task2.py](src/tasks/task2.py)
&nbsp;
[task3.py](src/tasks/task3.py)
&nbsp;
[task4.py](src/tasks/task4.py)
&nbsp;
[task5.py](src/tasks/task5.py)
&nbsp;
[task6.py](src/tasks/task6.py)
&nbsp;
[task7.py](src/tasks/task7.py)

[***Отчёт***](Демин_ДП_ИУК4_12_Б_2022_ЛР1.3_Теоретическая_информатика.pdf)

***Особые моменты в исходных программе***

- Все задания реализованны в разных файлах, и точкой их объединения является единственный файл [lab3.py](lab3.py)
```python
# lab3.py
import os
from tasks import task1, task2, task3, ...

path_txts=os.path.abspath('../text-files')

task1.run()
task2.run(path_txts)
task3.run(path_txts)
...
```
- В задания № 6, 7 на кодировку с сжатием файлов кодировка и декодировка вынесены в отдельные классы (инкапсуляция)
```python
class Haffman_Encoder:
	def __init__(self, dict_char_count):
		...
	def encode(self, text):
		...
		return encode_text


class Haffman_Decoder:
	def __init__(self, dict_char_count):
		...
	def decode(self, text):
		...
		return decode_text


# task 6 (Haffman's code)
def run(path):
	...
	# encode
	with open(path_src,'r',encoding='cp1251') as src_file:
		with open(path_encode,'w',encoding='cp1251') as encode_file:
			encode_file.write( Haffman_Encoder(dict_char_count).encode( src_file.read() ) )
      
	# decode
	with open(path_encode,'r',encoding='cp1251') as encode_file:
		with open(path_decode,'w',encoding='cp1251') as decode_file:
			decode_file.write( Haffman_Decoder(dict_char_count).decode( encode_file.read() ) )
```

- В задании № 7 реализован внутренний класс `Node`, из-за чего его конструктор вызывается через отдельный метод
```python
class LZW_Encoder:
  def create_node(self, number):
		return LZW_Encoder.Node(self, number)
	class Node:
		def __init__(self, encoder, number):
			...
```
