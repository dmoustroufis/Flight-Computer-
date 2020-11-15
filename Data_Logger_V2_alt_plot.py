# The file datalog.txt is a text file created by arduino code and it has the following form
# Each line contains just 2 numbers with the first number being the altitude of the rocket
# and the second being the time at which that altitude was reached. (the file has no header)
# Also, depending on the arduino code, there might be big number of lines in the file containing the same altitude
# this happens if the data logging is not stopped when the rocket lands. It is pretty easy to find and those values
# so that the plot will look cleaner.

import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv('datalog.txt', delimiter='\s+', index_col=False, header=None)

altitude = list(data.iloc[:, 0])
time = list(data.iloc[:, 1])

max_alt = max(altitude)
max_alt_index = altitude.index(max_alt)
time_max_alt = time[max_alt_index]
print("Max Altitude : " + str(max_alt) + "meters  " + "And it was reached at : " + str(time_max_alt) + "seconds")

plot = plt.plot(time, altitude)
plt.xlabel("Time")
plt.ylabel("Altitude")
plt.title("Data Logger V1 alt-time graph")

# according to the measurements we can also change the range of the axes
# plt.xlim()
# plt.ylim()

# here we show the apogee on the plot, just for decorative purposes
plot1 = plt.scatter(time_max_alt, max_alt, c='red')

plt.show()
