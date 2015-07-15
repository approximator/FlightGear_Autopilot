
import matplotlib.pyplot as plt

LATITUDE = 0
LONGITUDE = 1
PITCH = 2
ROLL = 3
ALTITUDE = 4
HEADING = 5
AILERONS = 6
ELEVATOR = 7

latitude = []
longitude = []
pitch = []
roll = []
altitude = []
heading = []
ailerons = []
elevator = []

time = []

file_name = '/tmp/fgap.log'
data = open(file_name, 'r').read()
lines = data.split('\n')

for line in lines:
    if len(line) < 1:
        continue
    items = line.split('\t')
    print items
    latitude.append(float(items[LATITUDE]))
    longitude.append(float(items[LONGITUDE]))
    pitch.append(float(items[PITCH]))
    roll.append(float(items[ROLL]))
    altitude.append(float(items[ALTITUDE]))
    heading.append(float(items[HEADING]))
    ailerons.append(float(items[AILERONS]))
    elevator.append(float(items[ELEVATOR]))

time = range(len(latitude))

max_ailerons = max(ailerons)
max_roll = max(roll)

# ailerons = map(lambda x: x / max_ailerons, ailerons)
# roll = map(lambda x: x / max_roll, roll)

plt.plot(time, roll, '-r', label='Pitch')
# plt.plot(time, roll, '-g', label='Roll')
plt.legend(loc='upper right')
plt.xlabel('Time')
plt.ylabel('Degrees')
plt.grid()
plt.show()
