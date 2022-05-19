from cmath import sin
import math


m = 1450 # kg
a = 1 #m/s^2
alpha = 10 # degrees
v = 27 # m / s
Ft = 218+0.7*(v**2) # N
g = 9.81  # m/s^2
sin_alpha = math.sin(math.radians(alpha))

D = Ft
G = sin_alpha * m *g


# Fv = M - G - D
# m*a = M - G - D
# M = m*a + G + D

M = m*a + G + D
print(f"Sila motora je {M} N")