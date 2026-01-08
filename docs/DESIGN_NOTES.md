# 🌌 Vyom — Design Notes (v0.2)

Vyom is a small, human‑friendly scripting language written in C.
Its design philosophy focuses on **clarity, predictability, and gradual evolution**.

---
## 🎯 Core Principles

### ✔ Simplicity First
Vyom avoids complexity when a simple rule is enough.
Language behavior should feel *obvious*, not surprising.

### ✔ Human‑Readable, Not Compiler‑Centric
The syntax is shaped for the person reading code — not the parser.
Errors explain **what went wrong and why** instead of failing silently.

### ✔ Stability Before Features
Features are added **slowly and deliberately**.
Each version strengthens the foundation instead of rushing growth.

### ✔ Performance With Restraint
Vyom is implemented in C for speed — but never at the cost of readability.
Consistency > micro‑optimizations.

### ✔ Learning‑Friendly
Vyom is also a vehicle to explore:
- language design
- interpreter architecture
- parsing and execution models

Every feature should *teach something meaningful*.

---
## 🧩 Design Choices (v0.2)

### 🔹 Assignment Uses `=` Only
Explicit assignment keeps the grammar predictable.
No implicit typing keywords — values determine type dynamically.

### 🔹 Case‑Sensitive Variables
`A` and `a` are intentionally different.
This avoids ambiguity in execution logic.

### 🔹 Strings & Numbers Only (for now)
A minimal and reliable type system is easier to reason about.
New types will be added **only when justified**.

### 🔹 Meaningful Error Messages
Instead of:  
```
syntax error
```
Vyom prefers:
```
Error (line 5): variable "msg" is not defined
```
Errors should guide — not punish.

### 🔹 Whitespace‑Aware, But Forgiving
Spaces should not cause surprising behavior,
but indentation remains meaningful for structure.

---
## 🚧 Why Features Are Added Slowly

Large language jumps cause:
- fragile implementations
- inconsistent behavior
- confusing rules for users

Vyom grows through **incremental milestones**:
- v0.1 → core execution model
- v0.2 → stability & ergonomics
- future → features layered carefully

Every change must answer two questions:

1️⃣ *Does this make Vyom more expressive without breaking clarity?*  
2️⃣ *Would a beginner understand why the language behaves this way?*

Only then, it ships.

---
## 🧭 Long‑Term Vision

Vyom should feel like:
- **Python‑like readability**
- **Lua‑like minimalism**
- **C‑like performance roots**
- **Vyom‑specific identity**

The goal is not to copy other languages —  
but to grow a clean, opinionated, small language that feels **calm and intentional**.

---
## 📝 Notes for Future Contributors

When proposing a feature:

- Prefer small additions over big jumps
- Explain *why* it belongs in the language
- Consider readability, not just capability
- Think about new users

A language is a design philosophy — not just syntax.

---
## 🌟 Closing Thought

Vyom will evolve — but it will never stop being **simple, honest, and understandable**.

> “Do fewer things — but do them well.”

