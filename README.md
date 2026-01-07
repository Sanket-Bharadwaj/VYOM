# 🌌 Vyom — Minimal Scripting Language (v0.1 Core)

Vyom is a small, indentation-based scripting language written in C.  
This v0.1 release focuses on a clean, simple and stable core.

## ✨ Features (v0.1)

- variables (`set`)
- numbers & strings
- math expressions (`+  -  *  /`)
- `print`
- `if / elif / else`
- `repeat N:`
- comments `#`
- indentation-based blocks
- command-line flags (`--version`, `--help`)

---

## 🛠 Build

```bash
gcc src/vy.c -o vy
```

---

## ▶️ Run a program

```bash
./vy examples/hello.vy
```

---

## 🖥 Command-line usage

Show help:

```bash
./vy --help
```

Show version:

```bash
./vy --version
```

Run any Vyom script:

```bash
./vy <file.vy>
```

---

## 📂 Examples

```
examples/hello.vy
examples/math_demo.vy
examples/conditions.vy
examples/repeat_pattern.vy
```

---

## 🎯 Philosophy

Vyom keeps the core small and stable first,  
and adds new features gradually in future versions.
