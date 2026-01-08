# =========================================
# Vyom v0.2 — main.vy
# Progressive language demonstration
# This file grows over time with new features
# =========================================


# -----------------------------------------
# 1️⃣ Basic values & assignment
# -----------------------------------------

x = 10
y = 5
name = "Vyom"

print "x = " + x
print "y = " + y
print "name = " + name


# -----------------------------------------
# 2️⃣ Expressions
# -----------------------------------------

sum = x + y
product = x * y

print "sum = " + sum
print "product = " + product


# -----------------------------------------
# 3️⃣ String concatenation
# -----------------------------------------

print name + " Lang"
print "x + y = " + sum


# -----------------------------------------
# 4️⃣ Type inspection
# -----------------------------------------

print type(x)
print type(name)


# -----------------------------------------
# 5️⃣ Conditionals
# -----------------------------------------

if x > y:
    print "x is greater than y"
elif x == y:
    print "x equals y"
else:
    print "y is greater than x"


# -----------------------------------------
# 6️⃣ Loops (repeat)
# -----------------------------------------

repeat 2:
    print "loop iteration"
    print x


# -----------------------------------------
# 7️⃣ Graceful termination
# -----------------------------------------

print "End of main.vy"