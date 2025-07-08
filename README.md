# DivijaShell
Designed and built a mini Linux shell in C, supporting command execution, background processing, signal handling, and custom prompts. Implemented command logging using file I/O. Compiled and tested in Ubuntu (WSL). Demonstrates OS-level programming, process management, and system design.
# shell@divija

A custom Linux shell built in C, inspired by Unix terminals. Supports command execution, history, signals, and background processes — with a personalized twist.

## Features

-  **Custom prompt**: `shell@divija >`
-  **Command execution** (`ls`, `mkdir`, `pwd`, etc.)
-  **Built-in commands** (`cd`, `exit`, `prompt`, `bglist`, `kill`, etc.)
-  **Command history tracking**
-  **Command logging**: All input is saved to `log.txt`
-  **Signal handling** for process termination
-  Developed & tested in **Ubuntu via WSL**

---

## 💻 How to Run

### Compile the shell:
```bash
gcc sh.c linkedlist.c linkedListForHistory.c utilities.c -o shell

### Run the shell:

./shell

You’ll see:
shell@divija >

Example Commands

shell@divija > ls
shell@divija > mkdir test_folder
shell@divija > bg sleep 5
shell@divija > bglist
shell@divija > history
shell@divija > exit

## Skills Demonstrated

Process creation with fork(), execvp(), waitpid()
Signal handling with SIGCHLD
File I/O in C (fopen, fprintf, fclose)
Pointer-based data structures (linked lists for bg jobs/history)
System-level development and shell design
