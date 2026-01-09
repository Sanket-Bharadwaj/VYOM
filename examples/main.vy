# =========================================
# Vyom v0.3 — main.vy
# Progressive language demonstration
# This file grows as Vyom evolves
# =========================================


# -----------------------------------------
# 1️⃣ Basic values & assignment (dynamic)
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
# 5️⃣ Explicit typed variables (v0.3)
# -----------------------------------------

int a = 10
double b = 2.5
string c = "Hello"

print a
print b
print c


# -----------------------------------------
# 6️⃣ Conditionals
# -----------------------------------------

if a > x:
    print "a is greater than x"
elif a == x:
    print "a equals x"
else:
    print "a is smaller than x"


# -----------------------------------------
# 7️⃣ Loops (repeat)
# -----------------------------------------

repeat 2:
    print "loop iteration"
    print a


# -----------------------------------------
# 8️⃣ Functions
# -----------------------------------------

def add(p, q):
    return p + q

result = add(3, 4)
print "add result = " + result

print add(10, 20)


# -----------------------------------------
# 9️⃣ Local scope
# -----------------------------------------

def local_demo():
    temp = 99
    print temp

local_demo()

# print temp   # ❌ Error (local variable)


# -----------------------------------------
# 🔟 Global variable usage
# -----------------------------------------

counter = 0

def increment():
    global counter
    counter = counter + 1

increment()
increment()
print "counter = " + counter


# -----------------------------------------
# 1️⃣1️⃣ Graceful termination
# -----------------------------------------

print "End of main.vy — Vyom v0.3 demo"