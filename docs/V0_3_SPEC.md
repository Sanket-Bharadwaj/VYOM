# 🌌 Vyom v0.3 — Language Specification

Version: **v0.3 (Planned)**  
Status: **Design Locked / Implementation Pending**

Vyom v0.3 focuses on **core language power**, while preserving
simplicity, clarity, and learning-first design.

This version introduces **typed variables, functions, and scope rules**
to move Vyom closer to a serious scripting language — without copying Python.

---

## 🎯 Design Goals (v0.3)

- Simple syntax
- Predictable behavior
- Beginner-friendly errors
- Optional performance via explicit typing
- No magic, no hidden behavior

---

## ✨ New Features in v0.3

- Explicit typed variables (`int`, `string`, `double`)
- Delayed initialization allowed
- Strict type checking
- Functions (`def`)
- Local scope by default
- Optional `global` keyword
- Improved `type()` output
- Whitespace-tolerant function syntax

---

## 🔢 Data Types

Supported types in v0.3:

- `int`
- `double`
- `string`

Dynamic typing (v0.2 style) **still allowed**,
but typed variables enable **faster execution** and **stricter checks**.

---

## 🧠 Variable Declaration Rules

### ✅ Typed declaration with initialization

```vy
int a = 10
double b = 2.5
string name = "Vyom"