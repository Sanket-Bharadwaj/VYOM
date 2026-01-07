# 📘 Vyom Syntax — v0.1 Core

This document describes the syntax and features available in the Vyom v0.1 core release.

---

## 🧩 Variables

```text
set x = 10
set name = "Vyom"
```

- supports numbers and strings  
- assignment always uses `set`

---

## 🖨 Print

```text
print x
print "hello"
```

- prints either variable values or string literals

---

## ➕ Math Expressions

```text
set a = x + 5
set b = a * 2
set c = b - 3
```

Supported operators:

```
+   -   *   /
```

Expressions may use literals or variables.

---

## 🔀 Conditionals

```text
if x > 5:
    print "big"
elif x == 5:
    print "equal"
else:
    print "small"
```

Comparison operators:

```
>   <   ==   !=   >=   <=
```

Blocks are determined by indentation.

---

## 🔁 Repeat Loop

```text
repeat 3:
    print "hi"
```

Executes the indented block N times.

---

## ⬇️ Indentation Rules

- blocks are controlled by **indent level**
- recommended to use spaces (avoid mixing tabs + spaces)
- no `{}` or `end` keyword

Example:

```text
if x > 0:
    print "inside block"
print "outside block"
```

---

## 📝 Comments

```text
# this is a comment
```

Anything after `#` on a line is ignored.

---

## 🖥 CLI Commands

```bash
vy --help
vy --version
vy <file.vy>
```

---

## 🌱 Notes

Vyom v0.1 intentionally ships with a **small, stable core**.  
Advanced features (functions, lists, file I/O, etc.) will be added gradually in future versions.
