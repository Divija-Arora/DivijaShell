# Unix Shell

Shell is a special user program which accepts simple human readable commands from user and translates them so that kernel can understand them. Shell provides an interface to user to use operating system services.

### Tech Stack
>This shell is developed completely in C.

## Features and Commands

#### 1. ```help```
> Prints all the builtin commands.

![Image of Yaktocat](/static/help.png)

#### 2. ```cd```
> Used to change the current working directory of the shell.

![Image of Yaktocat](/static/cd.png)
#### 3. ```exit```
> Used to exit the shell.

![Image of Yaktocat](/static/exit.png)
#### 4. ```bg```
> Used to run a command in background.

![Image of Yaktocat](/static/bg.png)
#### 5. ```bglist```
> Prints all the commands running in background.

![Image of Yaktocat](/static/bglist.png)
#### 6. ```kill```
> Used to kill a process with specified *process id*.
#### 7. ```history```
> Prints all the commands which were given to the shell along with their validity (i.e. whether they were valid or not) in the current session.

![Image of Yaktocat](/static/history.png)
I have used a bit of concept of pipelining to implement this feature to send information from child processes to parent process. This command marks the invalid commands with RED color and valid commands with BLUE color.
#### 8. ```prompt```
> Used to change the prompt name of the shell.

![Image of Yaktocat](/static/prompt.png)

#### 9. ```reset-prompt```
> Used to reset the prompt name of the shell to default.

![Image of Yaktocat](/static/reset-prompt.png)

## How to run ?

Follow these steps to run the shell in your pc.

1. Clone the repository.
2. Run following commands in your terminal.
 
     ```
     gcc sh.c linkedlist.c linkedlist.h utilities.h utilities.c linkedListForHistory.c linkedListForHistory.h
     ```

    ```
    ./a.out
    ```
    This will open the shell in your terminal.

**Note** - The commands given in step 2 assumes that you have gcc installed on your system.

## Future Goals

* Adding pipelining in the shell.

* Enhance the ease of use of shell by implementing following -
    * Command navigation using *up arrow* ⬆️ and *down arrow* ⬇️ key.
    * Cursor navigation using *left arrow* ⬅️ and *right arrow* ➡️ key.
    * Function of autocomplete using *tab* key.