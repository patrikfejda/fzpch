import math

# auto ide hore kopcom bez pociatocnej rychlosti so zapnutym motorom

m = 1000  # kg
alpha = 5  # degree
Cx = 0.31  # koeficient
ro = 1.26  # kg/m^3
S = 2.162  # m^2
g = 9.81  # m/s^2
sin_alpha = math.sin(math.radians(alpha))

v_term = math.sqrt((2 * m * g * sin_alpha) / (Cx * ro * S))


M = (0.5 * ro * S * Cx * (v_term) ** 2) + (m * g * sin_alpha)

print("To get terminal speed of:")
print(f"{v_term} m/s")
print(f"{v_term*3.6} km/h")

print(f"The engine needs power of {M} N")
