# Pi Cluster Control System

A modular C++ control system for managing and orchestrating a fleet of Raspberry Pi nodes.  
This project is being built using a Behavior-Driven Development (BDD) approach and emphasizes maintainability, extensibility, and developer ergonomics.

---

## 🧱 Project Structure

This repository is organized as a **multi-module C++ project**, designed to scale with independent components like:

- `agent/` – Worker agent running on each Pi
- `master/` – Central controller and orchestrator
- `backend/` – REST API adapter for GUI and automation
- `common/` – Shared utility code and interfaces
- `scripts/` – Infrastructure automation (e.g., Ansible, shell)
- `tests/` – BDD-aligned integration and service tests

---

## 🛠 Bootstrap Environment

Before contributing or running anything, validate your macOS C++ environment:

```bash
./bootstrap.sh
```

This checks for required tools (`cmake`, `make`, `clang++`, `brew`, etc.).  
It’s automatically enforced via a **Git pre-commit hook**.

To install the hook:

```bash
./setup-hooks.sh
```

This ensures no code is committed unless your environment is ready.

---

## 🚀 Module Scaffolding

To create a new module (executable or library), use the built-in scaffolding tool:

```bash
./scaffold_module.sh <module_name> [--lib] [--test]
```

### Flags:
- `--lib` – Create a C++ library instead of an executable
- `--test` – Scaffold a matching test directory under `tests/`

This generates:
- `src/`, `include/` folders
- CMakeLists from `.mustache` templates
- Optional `tests/<module>_tests` folder

All new modules are automatically added to the root `CMakeLists.txt`.

---

## 🧰 Templates

Scaffolding templates live in the `templates/` directory.  
These include:

- `CMakeLists.txt.mustache` (for executables)
- `CMakeLists-lib.mustache` (for libraries)
- `main.cpp.mustache`
- `class.cpp.mustache`
- `test-main.cpp.mustache`
- `test-module.cpp.mustache`
- `test-CMakeLists.txt.mustache`

---

## 🧪 Behavior-Driven Development

This project uses `.feature` files to describe all expected system behaviors before implementation.  
BDD specs exist for modules like the Pi Agent, telemetry, command execution, and provisioning.

---

## 📦 Coming Soon

- Initial implementation of `agent/` and `master/` services
- Build script (`build.sh`) for automating build/test
- Deployment specs for running via `k3s` on Raspberry Pi cluster

---

## 🧠 Philosophy

This project is built with long-term control, clean architecture, and infrastructure extensibility in mind.  
Tooling is prioritized as much as functionality, so the system grows sustainably and remains hackable.

---

## 👨‍💻 Author

Crafted by a developer who originally got into programming to build games,  
but fell in love with the systems side of software engineering.

