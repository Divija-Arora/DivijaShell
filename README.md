# DivijaShell
Designed and built a mini Linux shell in C, supporting command execution, background processing, signal handling, and custom prompts. 

# shell@divija

A custom Linux shell built in C, supporting command execution, background processes, and command history — with a personalized prompt.

## 🚀 Features
- Custom prompt: `shell@divija >`
- Command execution (`ls`, `mkdir`, `pwd`, etc.)
- Background process handling with `bg`, `bglist`, `kill`
- Built-in commands: `cd`, `exit`, `prompt`, `reset-prompt`
- Command logging to `log.txt`
- Developed & tested in Ubuntu (WSL)

## 💻 How to Run
```bash
gcc sh.c linkedlist.c linkedListForHistory.c utilities.c -o shell
./shell
