<p align="center">
  <img src="assets/VYOM-Banner.png" alt="Vyom banner" />
</p>

<h1 align="center">Vyom</h1>
<p align="center"><i>Minimal, learning-first scripting language</i></p>

<p align="center">
  Created and maintained by <b>Sanket Bharadwaj</b>
</p>

---

Vyom is a small, indentation-based scripting language written in C, designed with a strong focus on  
**simplicity, clarity, and predictable behavior**.

Vyom is built as a **learning-first language** — making it easy to understand how interpreters work,
how syntax is processed, and how programming languages evolve from a minimal core.

It is intentionally simple, stable, and approachable.

---

## 🚀 Current Version

**Vyom v0.3 — Stable**

This release builds directly on the v0.2 stability core and introduces **typed variables** and
**function definitions**, without breaking existing behavior.

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
- Command-line flags: `--version`, `--help`

---

## ✨ Features (v0.2)

- Assignment using `=`
- Numbers & strings
- String concatenation
- Expression evaluation (`+ - * /`)
- `print` and `print type(x)`
- `if / elif / else`
- `repeat`
- `exit`
- Human-friendly error messages
- Indentation-based blocks

---

## ✨ Features (v0.3)

- Optional explicit typed variables:
  - `int`
  - `double`
  - `string`
- Typed variables are **type-locked**
- Dynamic (untyped) variables still supported
- Function definitions using `def`
- Functions are parsed and stored (not executed)
- Clear type errors for invalid assignments
- Stable execution model preserved from v0.2

### Example

```vy
x = 10

int a = 10
double b = 2.5
string c = "Hello Vyom"

def greet():
    print "Hello from Vyom"
```

> ⚠️ Function calls and `return` are intentionally **not supported in v0.3**.  
> They will be introduced cleanly in **v0.4**.

---

## ⬇️ Download (Windows)

Download the prebuilt Windows packages from the GitHub Releases page:

- **v0.3 (stable):** [Vyom v0.3 - Windows ZIP](https://github.com/Sanket-Bharadwaj/VYOM/releases/download/v0.3/Vyom-0.3-Windows.zip)
- **v0.2:** [Vyom v0.2 - Windows ZIP](https://github.com/Sanket-Bharadwaj/VYOM/releases/download/v0.2/Vyom-0.2-Windows.zip)

Notes

- Verify downloads on the official release page before running binaries.
- If you want checksum or signing info added here, provide them and I'll include verification steps.

Installation (Windows)

1. Download the ZIP for the desired version and extract it to a folder (for example `C:\Vyom`).
2. (Optional) Run `install.bat` as Administrator to copy `vyom.exe` to a system location and add it to your PATH.
3. Run `vyom` from the command prompt:

```cmd
vyom examples\main.vy
```

Contents of the ZIP

- `vyom.exe`
- `install.bat`
- `uninstall.bat`
- `README.md`
- `examples/main.vy`

Uninstall

- Run `uninstall.bat` from the extracted folder (or remove the installed files manually).

Troubleshooting

- If `vyom` is not recognized after running `install.bat`, open a new terminal session or add the install directory to your PATH manually.
- If you prefer to run without installing, run `vyom.exe` from the extracted folder.

---

## ▶️ Quick Start (Windows)

```cmd
vyom main.vy
```

> Restart terminal once after running `install.bat`.

---

## 🛠 Build from Source

```bash
gcc src/vy.c -o vyom
```

---

## 🛣 Roadmap

### v0.4 (planned)

- Function calls
- `return`
- Local scope
- Lists / arrays
- Improved expression engine

---

## 📜 License

MIT License  
Learn • Build • Explore 🚀
