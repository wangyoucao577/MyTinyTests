

import matplotlib.pyplot
import numpy

def my_sin_taylor_around_0(x):
    # sin(x) = x - 1/6*(x^3)
    y = float(x) - (1.0 / 6.0 * (float(x) ** 3)) 
    return y

# split x between -PI ~ PI
x_values = numpy.linspace(-numpy.pi, numpy.pi, 360)

# calculate y
numpy_sin_y_values = numpy.sin(x_values)
my_sin_y_values = []
for x in x_values:
    y = my_sin_taylor_around_0(x)
    my_sin_y_values.append(y)

# draw
matplotlib.pyplot.xlabel("x (-PI ~ PI)")
matplotlib.pyplot.ylabel("y")
matplotlib.pyplot.plot(x_values, numpy_sin_y_values)
matplotlib.pyplot.plot(x_values, my_sin_y_values)
matplotlib.pyplot.show()

