import os, sys
sys.path.append(os.path.dirname(os.path.abspath('.')))
from tasks import task4
#task 5
def run(path):
	shift = 17
	print(f'5. Закодируйте и декодируйте любое текстовое сообщение, усложнив код Цезаря добавлением к каждому последующему числу, заменяющему букву, постоянное число "{shift:+}"\n')
	return task4.run(path, 17)