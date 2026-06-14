# Dart & Flutter ABI Stability PoC (`libabigail`)

This repository serves as a Proof of Concept (PoC) demonstrating automated, deep semantic Application Binary Interface (ABI) stability tracking for Dart Native Extensions (`dart_api_dl.h`) and the Flutter Embedder API (`flutter_embedder.h`) using **Libabigail**.

This project addresses the industry need for automated ABI verification gates in framework codebases without introducing complex in-tree software dependencies.

---
## Key Features

* **Deep Semantic Analysis:** Uses `libabigail` (`abidiff`) to inspect compiled ELF binaries with DWARF debug info. It traces full type dependency graphs rather than just surface-level text or symbol names.
* **Zero In-Tree Dependency Footprint:** The check runs strictly as an environment-level package utility (`libabigail-tools`) inside the CI/CD runner. It requires **zero changes** to core SDK codebases, dependencies (`DEPS`), or build configurations (`GN`/`Ninja`).
* **Framework Alignment:** A unified `.abignore` setup demonstrates how both the Dart VM ecosystem and the Flutter Embedder engine can share a single automated pipeline configuration.
* **Automated CI/CD Gating:** Fully integrated with GitHub Actions to compare the ABI layout of the base branch against incoming merge/pull requests.

---

## Core Validation Value: Indirect Sub-type Breaks

Standard text-based checkers or basic header diff utilities frequently miss **indirect structural modifications**. If a nested child struct changes its size or alignment but the parent function signature looks identical on paper, basic tools report "No Changes" while the binary crashes at runtime.

### See it in action:
* **[Live Example: Pull Request #1]([https://github.com/ankitranjandev/dart_abi_poc/pull/1])**
* **The Scenario:** An inner nested data type was modified while leaving the parent `extern "C"` function signature untouched.
* **The Result:** The GitHub Actions workflow successfully caught the deep layout shift, produced a human-readable diff of the sub-type mismatch, and safely failed the build gate.

---

## 📂 Project Structure

```text
dart_abi_poc/
├── .github/workflows/   
│   └── abi_check.yml          # Automated CI/CD pipeline extracting & comparing ABIs
├── src/
│   ├── my_extension.cpp       # Native extension simulating dart_api_dl.h usage
│   └── flutter_embedder_mock.cpp # Unified alignment mock for flutter_embedder.h
├── dart_ext.abignore          # Suppression file filtering out framework internal noise
└── CMakeLists.txt             # Build blueprint generating binaries with full DWARF info
```

---

## ⚙️ Local Setup & Verification

### 1. Prerequisites
Ensure you have CMake and Libabigail installed on your system.
```bash
# Ubuntu / Debian
sudo apt update && sudo apt install -y cmake build-essential libabigail-tools

# macOS
brew install cmake
```

### 2. Compilation
To generate the binaries with the necessary debug structures:
```bash
mkdir build && cd build
cmake ..
make
```

### 3. Manual ABI Dumping
To inspect the precise XML structural blueprint that `libabigail` generates from your compiled library:
```bash
abidw libdart_abi_extension.so
```

---

## 🛡️ Noise Suppression (`dart_ext.abignore`)

To keep automated pipelines useful, we leverage an abstraction rulebook. The custom `.abignore` file in this repository filters out expected framework-level internal noise (such as changes inside the giant `Dart_ApiDex` structural lookup tables) to ensure code reviews only generate alerts when user-facing extensions or core public boundaries genuinely break.
