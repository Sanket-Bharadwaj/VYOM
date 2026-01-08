# =========================================
# Vyom v0.2 — Full Test Suite
# This file intentionally includes:
# - valid code
# - warnings
# - runtime errors
# - edge cases
# =========================================


# ---------- BASIC ASSIGNMENT ----------
x = 10 
y   =   5
msg = "Vyom Lang"

print x
print y
print msg


# ---------- EXPRESSIONS ----------
z = x + y
print z

a = x * y
print a

b = z / 0        # allowed (prints 0, no crash)
print b


# ---------- STRING CONCAT ----------
print "a = " + x
print x + " = value"
print msg + " rocks"


# ---------- TYPE BUILTIN ----------
print type(x)
print type(msg)

# Error: variable not defined
print type(unknown_var)


# ---------- UNDEFINED VARIABLE ----------
print k


# ---------- INVALID VARIABLE NAME ----------
1abc = 10
a-b = 5


# ---------- MISSING RHS ----------
bad1 =
bad2 =    


# ---------- IF / ELIF / ELSE ----------
if x > 10:
    print "x > 10"
elif x == 10:
    print "x == 10"
else:
    print "x < 10"


# ---------- INVALID CONDITION ----------
if msg > 5:
    print "this should error"


# ---------- REPEAT ----------
repeat 2:
    print "repeat works"
    print x


# ---------- INVALID REPEAT ----------
repeat -3:
    print "should not run"


# ---------- EXIT ----------
print "before exit"
exit
print "this should NOT print"


# ---------- UNKNOWN STATEMENTS ----------
hello world
foo(bar)


# ---------- UNTERMINATED STRING ----------
print "this string never ends


# ---------- DONE ----------
print "end of file"