# 🌌 Vyom — Minimal Scripting Language

Vyom is a small, indentation-based scripting language written in C —
focused on **simplicity, readability, and predictable behavior**.

This document preserves version history as the language evolves.

---

## 🟢 Vyom v0.1 — Core (Initial Release)

A minimal, stable foundation to start the language journey.

### ✨ Features (v0.1)

- variables using `set`
- numbers & strings
- math expressions (`+  -  *  /`)
- `print`
- `if / elif / else`
- `repeat N:`
- comments `#`
- indentation-based blocks
- `--version` and `--help`

### 🛠 Build (v0.1 style)

```bash
gcc src/vy.c -o vy
```

---

## 🚀 Vyom v0.2 — Stability & String Concatenation (Current)

This version focuses on **cleaner syntax, better error messages,
and more natural variable assignment**.

### ✨ New in v0.2

- assignment using `=` (no `set`)
- case‑sensitive variables
- whitespace‑tolerant parsing
- string concatenation:

  ```
  print "a = " + x
  print x + " = value"
  print name + " Lang"
  ```

- `type(x)` → prints `number` or `string`
- `exit` to stop execution
- improved error messages

### 🧪 Examples

```vy
x = 10
name = "Vyom"
print "a = " + x
print name + " Lang"
```

### 🔧 Build (v0.2)

```bash
gcc src/vy.c -o vyom
./vyom examples/test.vy
```

---

## 📜 Changelog

### v0.2
- added string concatenation
- added `exit`
- switched to `=` for assignment
- improved parsing & error messages

### v0.1
- initial interpreter core
- variables, print, repeat, conditionals

---

## 🛣 Roadmap

**v0.3 (planned)**  
- improved expression engine  
- optional `print()` form  
- lists / arrays  
- performance upgrades  

---

## 📜 License

MIT — learn, build, explore 🚀
