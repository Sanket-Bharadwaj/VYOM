# 🌌 Vyom — Minimal Scripting Language (v0.2)

Vyom is a small, indentation‑based scripting language written in C, focused on **simplicity, readability, and predictable behavior**.

Vyom is designed as a **learning‑first language** — easy to read, easy to reason about, and easy to extend.

---

## ✅ Who is Vyom for?

- Beginners learning how programming languages work
- Students exploring interpreters & compilers
- Developers who want a tiny scripting language
- Anyone curious about language design

---

## 🚀 Current Version

**Vyom v0.2 — Stability Core**

This version establishes a stable base and improves usability.

---

## ✨ Features (v0.2)

- Assignment using `=`
- Numbers & strings
- String concatenation
- Expression evaluation (`+ - * /`)
- `print`
- `print type(x)`
- `if / elif / else`
- `repeat`
- `exit`
- Comments using `#`
- Indentation‑based blocks
- Human‑friendly error messages
- Command‑line flags: `--version`, `--help`

---

## ⬇️ Download (Windows)

Download the Vyom v0.2 Windows package:

👉 **[Download Vyom-0.2-Windows.zip](https://github.com/Sanket-Bharadwaj/VYOM/releases/download/v0.2/Vyom-0.2-Windows.zip)**

Includes:
- `vyom.exe`
- installer (`install.bat`)
- examples

No compiler required. Just download and run.

---

## ▶️ Run Vyom (Windows)

1. Download `vyom.exe`
2. Open Command Prompt in the folder where `vyom.exe` exists
3. Run:

```cmd
vyom test.vy

vyom C:\Users\<your-name>\Desktop\test.vy
```

---

### (Optional) Add Vyom to PATH

If you add `vyom.exe` to your system PATH, you can run it from anywhere:

```cmd
vyom test.vy
```

⚠️ Restart your terminal after running `install.bat` for PATH changes to take effect.

---

## 🧪 Example Program

```vy
x = 10
name = "Vyom"

print "x = " + x
print name + " Lang"

if x < 20:
    print "small number"
```

---

## 🖥 Windows — How to Use (IMPORTANT)

### 1️⃣ Download Vyom

Go to **GitHub Releases** and download:

```
Vyom-0.2-Windows.zip
```

Extract it anywhere (recommended: `C:\Vyom`).

---

### 2️⃣ Install Vyom (one time)

Double‑click:

```
install.bat
```

This will:
- Add Vyom to your system PATH
- Allow `vyom` command from any terminal

---

### 3️⃣ Write a Vyom program

Create a file anywhere, for example:

```
test.vy
```

```vy
print "Hello from Vyom"
```

---

### 4️⃣ Run the program

Open **Command Prompt** or **PowerShell**:

```bat
vyom test.vy
```

Output:
```
Hello from Vyom
```

✅ Works from Desktop, VS Code, or any folder.

---

### 5️⃣ Uninstall (optional)

Run:
```
uninstall.bat
```

---

## 🛠 Build from Source (Developers)

### Linux / macOS / Windows (using GCC / MinGW)

```bash
gcc src/vy.c -o vyom
```

Run:
```bash
./vyom examples/test.vy
```

---

## 📂 Project Structure

```
VYOM/
├── src/
│   └── vy.c
├── examples/
│   └── test.vy
├── windows/
│   ├── install.bat
│   ├── uninstall.bat
│   └── README.txt
├── docs/
├── README.md
```

---

## 📜 Changelog

### v0.2
- Stable `=` assignment
- String concatenation
- `exit` statement
- Better error handling
- Windows installer support

### v0.1
- Initial interpreter core

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
