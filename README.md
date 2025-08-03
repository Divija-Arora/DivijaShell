# DivijaShell
Designed and built a mini Linux shell in C, supporting command execution, background processing, signal handling, and custom prompts. 

# shell@divija

A custom Linux shell built in C, supporting command execution, background processes, and command history — with a personalized prompt.

# Screenshot
![Screenshot (175)](https://github.com/user-attachments/assets/bc52034d-62ba-47db-8e0f-6f46d26ab318)



## 🚀 Features
- Custom prompt: `shell@divija >`
- Command execution (`ls`, `mkdir`, `pwd`, etc.)
- Background process handling with `bg`, `bglist`, `kill`
- Built-in commands: `cd`, `exit`, `prompt`, `reset-prompt`
- Command logging to `log.txt`
- Developed & tested in Ubuntu (WSL)

## Tech-Stack
- Linux(Ubuntu , WSL)
- C
- GCC

## 💻 How to Run
```bash
gcc sh.c linkedlist.c linkedListForHistory.c utilities.c -o shell
./shell
```
## Example
```bash
shell@divija > ls
shell@divija > mkdir test
shell@divija > history
```
## Built By
Divija Arora
(Lover of clean terminals)
