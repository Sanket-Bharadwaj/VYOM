# 🌌 Vyom --- Language Syntax Guide (v0.2)

Vyom is a minimal, indentation‑based scripting language focused on
clarity and stability. Version **v0.2** extends the core with safer
assignment rules, better errors, `exit` support, string concatenation in
`print`, and `type(x)` inspection.

------------------------------------------------------------------------

## ✨ Core Concepts

-   indentation defines blocks (spaces recommended)
-   variables are **case‑sensitive**
-   assignment uses `=` (no `set` from v0.2 onward)
-   numbers and strings are dynamically typed
-   whitespace around operators is flexible

------------------------------------------------------------------------

## 📝 Variables & Assignment

    x = 10
    name = "Vyom"
    pi = 3.14

Rules:

-   variable names must start with a letter or `_`
-   may contain letters, digits, `_`
-   `A` and `a` are **different variables**
-   invalid identifiers raise clear errors

------------------------------------------------------------------------

## 🧮 Expressions

Supported operators:

    +   -   *   /

Examples:

    a = 10 + 5
    b = a * 2

Expressions may use variables, numbers, or both.

------------------------------------------------------------------------

## 🖨 print

### Print values

    print x
    print "Hello"
    print 10 + 5

### String concatenation

    print "a = " + a
    print name + " Lang"

### Type inspection

    print type(x)
    # → number / string

------------------------------------------------------------------------

## 🔁 repeat blocks

    repeat 3:
        print "Hi"

------------------------------------------------------------------------

## 🔀 Conditions

    if x > 10:
        print "big"
    elif x == 10:
        print "equal"
    else:
        print "small"

Supported comparison operators:

    >  <  ==  !=  >=  <=

------------------------------------------------------------------------

## ⛔ exit

Stops execution immediately inside any block:

    if x < 0:
        print "Stopping"
        exit

------------------------------------------------------------------------

## 💬 Comments

    # this is a comment

------------------------------------------------------------------------

## ⚠️ Errors & Warnings

Vyom v0.2 focuses on readable messages like:

    Error (line N): variable "x1-" is not defined
    Error (line N): invalid variable name "1x"

Program continues where reasonable; fatal issues stop execution.

------------------------------------------------------------------------

## 📌 Notes

-   strings must be on one line
-   indentation controls scope
-   unknown statements produce warnings

------------------------------------------------------------------------

## ▶️ Example Program

    x = 5
    y = 10
    print "a = " + x
    print type(y)

    if y > 5:
        print "ok"

------------------------------------------------------------------------

Vyom keeps the core small and predictable --- features expand carefully
in future versions.
