# lab3.py
import os
from tasks import task1, task2, task3, task4, task5, task6, task7

path_txts=os.path.abspath('../text-files')
print(path_txts)

task1.run()
task2.run(path_txts)
task3.run(path_txts)
task4.run(path_txts)
task5.run(path_txts)
task6.run(path_txts)
task7.run(path_txts)