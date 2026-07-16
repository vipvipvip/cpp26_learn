# C++26 Dev Setup — Ubuntu 26.04 LTS

## OS & Kernel
- Ubuntu 26.04 LTS (Resolute Raccoon)
- Kernel 7.0.0-27-generic

## Toolchain

| Tool | Version | Purpose |
|------|---------|---------|
| g++ | 15.2.0 | C++26 compiler |
| gdb | 17.1 | Debugger (terminal) |
| lldb | 21.1.8 | Debugger (VS Code via CodeLLDB) |
| clang++ | 21.1.8 | Cross-check compiler |
| valgrind | 3.26.0 | Memory error/leak detection |
| cppcheck | 2.19.0 | Static analysis |
| make | 4.4.1 | Build automation |
| cmake | 4.2.3 | Build system |

### Installation
```bash
sudo apt install -y valgrind cppcheck clang lldb
```

## VS Code Extensions
- **CodeLLDB** (vadimcn.vscode-lldb) — LLDB debugger integration
- **C/C++** (ms-vscode.cpptools) — IntelliSense, code navigation

### IntelliSense Config
`.vscode/c_cpp_properties.json` sets `cppStandard: "c++26"` so IntelliSense
recognizes C++26 headers like `<print>`, `<expected>`, `<stacktrace>`.

## Project Layout
```
.
├── main.cpp            # entry point
├── calculator.h/.cpp   # std::expected error handling
├── logger.h/.cpp       # std::print, std::stacktrace
├── types.h             # concepts, shared types
├── Makefile
├── obj/                # object files (.o)
├── bin/                # executable (app)
├── docs/
│   └── dev_setup.md
├── .vscode/
│   ├── launch.json     # CodeLLDB debug config
│   ├── tasks.json      # make build task
│   └── c_cpp_properties.json
└── .gdbinit            # GDB convenience commands
```

## Makefile Targets

| Command | What it does |
|---------|-------------|
| `make` | Compile all → `bin/app` |
| `make run` | Compile + run |
| `make debug` | Compile with ASan/UBSan + run |
| `make valgrind` | Compile + run under valgrind |
| `make check` | Static analysis with cppcheck |
| `make clean` | Remove `obj/` and `bin/` |

## C++26 Features Used

| Feature | File | Header |
|---------|------|--------|
| `std::expected` | calculator.cpp | `<expected>` |
| `std::print` | logger.cpp | `<print>` |
| `std::stacktrace` | logger.cpp | `<stacktrace>` |
| `std::source_location` | logger.h | `<source_location>` |
| Concepts (`Arithmetic`) | types.h | `<concepts>` |

## Debugging

### VS Code (F5)
- CodeLLDB extension with native LLDB backend
- Set breakpoints in any file, step through multi-file code
- Breakpoints, watchpoints, call stack, variables panel all work

### Terminal GDB
```bash
make && gdb ./bin/app
(gdb) break calculator.cpp:compute
(gdb) run
(gdb) next / step / continue / print / backtrace
```

`.gdbinit` provides `rerun` command to rebuild + restart in one shot.

### Sanitizers
```bash
make debug
```
Built-in GCC address and undefined behavior sanitizers — no extra install needed.

### Valgrind
```bash
make valgrind
```
Full leak check with origin tracking.

## Notes
- `-lstdc++exp` is required for `std::stacktrace` support in GCC 15
- Compile with `-O0 -g` for debug builds, `-O2` for release
- CodeLLDB (LLDB) is used for VS Code debugging instead of cppdbg (GDB) due to
  known breakpoint issues with the cpptools MI adapter on Ubuntu 26.04

## VS Code Config Files

### `.vscode/launch.json`
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug",
            "type": "lldb",
            "request": "launch",
            "program": "${workspaceFolder}/bin/app",
            "args": [],
            "cwd": "${workspaceFolder}",
            "preLaunchTask": "Make Build"
        }
    ]
}
```

### `.vscode/tasks.json`
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "shell",
            "label": "Make Build",
            "command": "/usr/bin/make",
            "args": ["all"],
            "options": { "cwd": "${workspaceFolder}" },
            "group": { "kind": "build", "isDefault": true },
            "presentation": {
                "echo": true,
                "reveal": "silent",
                "focus": false,
                "panel": "shared",
                "showReuseMessage": false,
                "clear": false
            }
        },
        {
            "type": "shell",
            "label": "Make Clean",
            "command": "/usr/bin/make",
            "args": ["clean"],
            "options": { "cwd": "${workspaceFolder}" },
            "group": "none"
        }
    ]
}
```

### `.vscode/c_cpp_properties.json`
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c26",
            "cppStandard": "c++26",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```
