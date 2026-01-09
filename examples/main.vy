# =========================================
# Vyom v0.3 — main.vy
# Official stable demonstration
# =========================================


# -----------------------------------------
# 1️⃣ Dynamic variables
# -----------------------------------------

x = 10
y = 5

print x
print y


# -----------------------------------------
# 2️⃣ Typed variables (NEW in v0.3)
# -----------------------------------------

int a = 10
double b = 2.5
string c = "Hello Vyom"

print a
print b
print c


# -----------------------------------------
# 3️⃣ Re-assignment rules
# -----------------------------------------

a = 20        # ✅ allowed
# a = "oops"  # ❌ Type Error (intentional)

print a


# -----------------------------------------
# 4️⃣ Function definitions (parsed only)
# -----------------------------------------

def greet():
    print "Hello from function"

def show(v):
    print v

def local_demo():
    temp = 99
    print temp

# NOTE:
# Function CALLS are intentionally NOT supported in v0.3.
# They will be added cleanly in v0.4.


# -----------------------------------------
# 5️⃣ End
# -----------------------------------------

print "End of main.vy — Vyom v0.3"