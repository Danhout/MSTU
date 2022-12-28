import math
from enum		 import IntEnum
from functools   import reduce
from queue       import PriorityQueue
from scipy.stats import poisson, uniform
from matplotlib  import pyplot as plt

def value_counts(container):
	return list(map(lambda x: container.count(x), sorted(set(container))))
	
# defaults
count_patients = 1000
count_categories  = 3


# distributions
t_operations = list(map(lambda x: math.floor(x * 0.2 + 5), poisson.rvs(mu = 40, size = count_patients)))
t_intervals  = list(map(lambda x: math.floor(x * 0.5 + 1), poisson.rvs(mu = 10,  size = count_patients)))
categories   = list(map(math.floor, uniform.rvs(loc = 1, scale = count_categories, size = count_patients)))
# subdata
t_entries = list(map(lambda i: reduce(lambda x, y: x + y, t_intervals[:i]), range(1, count_patients + 1)))


# histograms
# Timings of operations in cabinet
x = sorted(set(t_operations))
y = value_counts(t_operations)
plt.subplot(321)
plt.title('Операция')
plt.xlabel('Длительность (мин.)')
plt.bar(x, y, edgecolor = 'black')

# Timings of intervals betveen entered to queue
x = sorted(set(t_intervals))
y = value_counts(t_intervals)
plt.subplot(322)
plt.title('Вход в очередь')
plt.xlabel('Интервал (мин.)')
plt.bar(x, y, edgecolor = 'black')

# Pacients
x = sorted(set(categories))
y = value_counts(categories)
plt.subplot(313)
plt.title('Пациенты')
plt.xlabel('Степень тяжести травм')
plt.ylabel('Количество')
plt.ylim([0, max(y) * 1.2])
for i in range(len(x)):
    plt.annotate(y[i], xy=(x[i], y[i]), ha='center', va='bottom')
plt.bar(x, y, edgecolor = 'black')


# Model
class Clock(object):
	minute = 0
	@staticmethod
	def get(): 
		return Clock.minute
	@staticmethod
	def set(minute):
		Clock.minute = minute

class Pacient(object):
	max_id = 0
	def __init__(self):
		self.id = Pacient.max_id
		self.category = categories[self.id]
		Pacient.max_id += 1
	def __lt__(self, other):
		return self.id < other.id if self.category == other.category else self.category < other.category

class Doctor(object):
	class Entry(object):
		def __init__(self, pacient = None, enter = None, exit = None):
			self.pacient = pacient
			self.enter = enter
			self.exit = exit
	def __init__(self, entries = []):
		self.entries = entries
	def heal(self, pacient):
		time_enter = Clock.get()
		time_exit  = time_enter + t_operations[len(self.entries)]
		self.entries.append(Doctor.Entry(pacient, time_enter, time_exit))
		return time_exit
	def is_free(self):
		return True if not self.entries else Clock.get() >= self.entries[-1].exit

class Event(object):
	class Type(IntEnum):
		FREE_DOCTOR = 1,
		ADD_PACIENT = 2
	def __init__(self, time, type_event):
		self.time = time
		self.type = type_event
	def __lt__(self, other):
		return  self.type < other.type if self.time == other.time else self.time < other.time

doctor = Doctor()
queue_events   = PriorityQueue()
for t_enter in t_entries:
	queue_events.put(Event(t_enter, Event.Type.ADD_PACIENT))
queue_pacients = PriorityQueue()

while not queue_events.empty():
	event = queue_events.get()
	Clock.set(event.time)
	if event.type == Event.Type.FREE_DOCTOR:
		if not queue_pacients.empty():
			time_free = doctor.heal(queue_pacients.get())
			queue_events.put(Event(time_free, Event.Type.FREE_DOCTOR))
	else:
		if doctor.is_free():
			time_free = doctor.heal(Pacient())
			queue_events.put(Event(time_free, Event.Type.FREE_DOCTOR))
		else:
			queue_pacients.put(Pacient())

t_enters = list(map(lambda entry : entry.enter, doctor.entries))
t_exits  = list(map(lambda entry : entry.exit,  doctor.entries))
t_waits  = list(map(lambda x, y : y - x, t_entries, t_enters))


# Table
data = []
for p_id in range(count_patients):
	t_oper_id = [i for i in range(count_patients) if doctor.entries[i].pacient.id == p_id][0]
	data.append([p_id, categories[p_id], t_operations[t_oper_id], 
										 t_intervals[p_id], 
										 t_entries[p_id], 
										 t_enters[t_oper_id], 
										 t_exits[t_oper_id], 
										 t_waits[t_oper_id]])
column_labels = ['A','B','C','D','E','F','G','H']
plt.figure()
plt.axis('off')
plt.table(cellText = data[:17], colLabels = column_labels, loc = 'center')

av_waitings = map(lambda i: reduce(lambda x, y: x + y, map(lambda d: d[-1], filter(lambda l: l[1] == i, data)), 0) / categories.count(i), range(1, count_categories + 1))
print(list(av_waitings))

plt.show()