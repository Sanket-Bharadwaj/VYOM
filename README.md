<p align="center">
  <img src="assets/banner.png" alt="Vyom banner" />
</p>

# 🌌 Vyom — Minimal Scripting Language (v0.2)

Created and maintained by **Sanket Bharadwaj**

Vyom is a small, indentation-based scripting language written in C, focused on **simplicity, readability, and predictable behavior**.

Vyom is a **learning-first language** — ideal for understanding how programming languages and interpreters work.

---

## ✅ Who is Vyom for?

- Beginners learning how programming languages work
- Students exploring interpreters & compilers
- Developers who want a tiny scripting language
- Anyone curious about language design

---

## 🚀 Current Version

**Vyom v0.2 — Stability Core**

This release establishes a stable and usable foundation.

---
## ✨ Features (v0.1)

- Variable assignment using `set`
- Numbers & strings
- Basic math expressions (`+ - * /`)
- `print`
- `if / elif / else`
- `repeat N:`
- Comments using `#`
- Indentation-based blocks
- Simple, predictable execution model
- Command-line flags: `--version`, `--help`

## ✨ Features (v0.2)

- Assignment using `=`
- Numbers & strings
- String concatenation
- Expression evaluation (`+ - * /`)
- `print` and `print type(x)`
- `if / elif / else`
- `repeat`
- `exit`
- Comments using `#`
- Indentation-based blocks
- Human-friendly error messages
- Command-line flags: `--version`, `--help`

---

## ⬇️ Download (Windows)

👉 **[Download Vyom-0.2-Windows.zip](https://github.com/Sanket-Bharadwaj/VYOM/releases/download/v0.2/Vyom-0.2-Windows.zip)**

This package includes:

- `vyom.exe` — Vyom interpreter
- `install.bat` — system installer
- `uninstall.bat` — uninstaller
- example programs

No compiler or additional setup is required.

---

## ▶️ Quick Start (Windows)

### 1️⃣ Install (one time)

1. Extract the ZIP file
2. Double-click `install.bat`
3. Restart your terminal

---

### 2️⃣ Write a Vyom program

Create a file `main.vy`:

```vy
print "Hello, Vyom!"
```

For more examples, visit the [EXAMPLES](https://github.com/Sanket-Bharadwaj/VYOM/tree/main/examples)

---

### 3️⃣ Run it

```cmd
vyom main.vy
```

---

## 📂 Examples

Vyom uses a **single progressive example file** that demonstrates the language step-by-step.

### `examples/main.vy` (Recommended)

This is the **official demo file** for Vyom v0.2.  
It shows language features in a clean, learning-friendly order:

- variables & assignment
- expressions
- string concatenation
- type checking
- conditionals
- loops (`repeat`)

👉 New users should start here.

---

### About `test.vy` (Internal)

Earlier versions used a `test.vy` file containing:
- runtime errors
- invalid syntax
- edge cases

This file is **not included in v0.2 releases** to avoid confusing users.

Advanced users can create their own test files if needed.

---

## ⚙️ Power Users

You can also run `vyom.exe` directly without installation:

```cmd
vyom.exe main.vy
```

---

## 🛠 Build from Source

```bash
gcc src/vy.c -o vyom
```

---

## 🛣 Roadmap

### v0.3 (planned)

- Functions (`def`)
- Local scope
- Lists / arrays
- Improved expression engine

---

## 📜 License

MIT License  
Learn • Build • Explore 🚀
