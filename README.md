# DivijaShell
Designed and built a mini Linux shell in C, supporting command execution, background processing, signal handling, and custom prompts. Implemented command logging using file I/O. Compiled and tested in Ubuntu (WSL). Demonstrates OS-level programming, process management, and system design.
# 🐚 shell@divija

A custom Linux shell built in C, inspired by Unix terminals. Supports command execution, history, signals, and background processes — with a personalized twist.

## 🚀 Features

- ✅ **Custom prompt**: `shell@divija >`
- 🧠 **Command execution** (`ls`, `mkdir`, `pwd`, etc.)
- 🕹️ **Built-in commands** (`cd`, `exit`, `prompt`, `bglist`, `kill`, etc.)
- 📝 **Command history tracking**
- 🧵 **Background process management** using `fork()` and linked list
- 📦 **Command logging**: All input is saved to `log.txt`
- 🔔 **Signal handling** for process termination
- ✅ Developed & tested in **Ubuntu via WSL**

---

## 💻 How to Run

### 🔧 Compile the shell:
```bash
gcc sh.c linkedlist.c linkedListForHistory.c utilities.c -o shell
