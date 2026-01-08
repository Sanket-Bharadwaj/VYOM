# =========================================
# Vyom v0.2 — test.vy
# Internal test suite (NOT for users)
# This file is used to validate:
# - error messages
# - warnings
# - edge cases
# =========================================


# ---------- UNDEFINED VARIABLES ----------
print unknown
print type(not_defined)


# ---------- INVALID VARIABLE NAMES ----------
1abc = 10
a-b = 5


# ---------- MISSING RHS ----------
bad1 =
bad2 =


# ---------- EXPRESSIONS ----------
x = 10
y = 0

z = x / y        # division by zero (should not crash)
print z


# ---------- INVALID OPERATORS ----------
a = x $ y


# ---------- CONDITIONS ----------
msg = "hello"

if msg > 5:
    print "invalid comparison"


# ---------- REPEAT ----------
repeat -2:
    print "should not run"


# ---------- EXIT ----------
print "before exit"
exit
print "this should not print"


# ---------- UNKNOWN STATEMENTS ----------
hello world
foo(bar)


# ---------- UNTERMINATED STRING ----------
print "this string never ends


# ---------- END ----------
print "test completed"
