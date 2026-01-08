# 📜 Vyom — Changelog

All notable changes to Vyom will be documented in this file.

---

## v0.2 — Stability & String Concatenation (Current)
**Release focus:** cleaner syntax, reliability, and predictable behavior

### Added
- string concatenation support  
  - `print "a = " + x`
  - `print x + " = value"`
  - `print name + " Lang"`
- `type(x)` → prints `number` or `string`
- `exit` — graceful execution stop
- whitespace‑tolerant parsing

### Changed
- switched from `set x = 10` → `x = 10`
- variables are now **case‑sensitive**
- improved error messages
- better handling of invalid identifiers & expressions

---

## v0.1 — Core Interpreter (Initial Release)

### Added
- variables (`set` syntax)
- numbers & strings
- `print`
- math expressions (`+  -  *  /`)
- `if / elif / else`
- `repeat N:`
- comments `#`
- indentation‑based blocks
- `--version` and `--help`

---
