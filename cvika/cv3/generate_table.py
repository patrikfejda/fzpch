file = open("dataset.csv", "w" )
g = -9.80665 #m/s^2

# ysur = 0
# vy = 0

ysur0 = 100
vy0 = 10

# ysur0 = input("Zac y: ")
# vy0 = input("Zac rychlost y: ")

file.write("time;height;velocity\n")
for t in range(0, 100):

    # time
    t /= 10

    vy = vy0 + g*t
    ysur = ysur0 + 0.5 * vy * t


    file.write("{:.1f}".format(t) + ";")
    file.write("{:.6f}".format(ysur) + ";")
    file.write("{:.6f}".format(vy) + ";")
    file.write("\n")










file.close()
