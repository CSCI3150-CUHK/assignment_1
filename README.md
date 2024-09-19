# CSCI 3150 Introduction to Operating Systems: Assignment One

## 1. Basic Information

- Topic: implementation of a simple shell program in C
- Total Marks: 100
- Deadline: 18:00:00 p.m., Mon, Oct 7th
- Submission: Github classroom
- High-level aim:
  - Understanding how to interact with Linux.
  - Understanding the design choices and rationales of shell.

## 2. Task Instruction

In assignment one, you will be guided to implement a simple shell program. Please check below sections for instructions on the assignment. 

### 2.1. Target

Suppose we have a directory structure shown below as an example:

```
dir1/
├─ dir2/
```

Implement a shell program that supports:

- one built-in command: `cd` command

  Your shell program should be able to change current working directory with `cd` command. For example:

  ```shell
  user@OSLAB1:/dir1/dir2$ cd ..
  user@OSLAB1:/dir1$
  ```

  We only require you to support cd command **with one argument**, which is a path. We do not require you to support other scenarios such as cd with flags.

- single external commands, i.e. `ls`, `ps`, etc. 

  Your shell program should be able to execute single command with arguments. For example:

  ```shell
  user@OSLAB1:/dir1$ ls -l
  total 4
  drwxrwxr-x 2 user user 4096 Jan  12 12:00 dir2
  user@OSLAB1:/dir1$ 
  ```

- pipes between commands. The program should support up to **two pipes**. 

  Your shell program should be able to execute commands with up to two pipes between them. For example:

  ```shell
  user@OSLAB1:/dir1$ ls -l | grep dir | wc -l
  1
  user@OSLAB1:/dir1$
  ```

#### 2.1.1. Additional notes

1. Your program should be able to handle the case in which **there are at least one space (or tab, or both) before and one space (or tab, or both) after the pipe meta character “|”**. If there is no space before or after “|”, for example, for the following case: “ls|” is treated as **one argument** to be executed (rather than “ls” and “|”). Although in real bash shells, "ls|" will still be treated as command "ls" followed by pipe meta character, we do not require you to deal with such scenarios in assignment one. We are also aware of this when designing our grading test cases.

2. For our grading test cases, all commands will be valid (i.e., incomplete/ incorrect commands such as `ls |` will not be tested).

3. Different shells might have [different implementations](https://stackoverflow.com/questions/66882631/builtin-commands-in-a-shell-pipeline) for executing piped commands. For this assignment, we should follow and mimic the bash shell behaviour.

Check `src/README.md` for more test cases.

### 2.2. Implementation Hints

#### 2.2.1. Built-in commands & external commands

Built-in commands are contained within the shell itself, while other commands are supported by compiled binaries. One key difference between these two kinds of commands is that the shell will execute built-in commands in its main process and will fork a child process to execute external commands. 

For example, linux shell supports the `cd` command to change current working directory, which is a built-in command and should be done in the main process of shell since changing directory in a child process will not affect the main process. Linux shell also supports the `ls` command, which is not a built-in command. When you type `ls` in the shell and enter, shell will invoke a child process and execute the corresponding binary in the child process if the binary is found under directories specified in environment variables. For `ls` command, the corresponding binary named `ls` is under `/bin` directory, which is usually a directory included in `PATH` variable so the shell can find where the binary of `ls` is. Forking child process to execute external commands can facilitate parallel execution of several commands of a shell.

In this assignment one, your shell program is only required to support one built-in command, which is `cd`. You should take the behavior difference between built-in commands and external commands into consideration when finishing assignment one. 

#### 2.2.2. Functions to use

Please utilize the following functions to implement your shell program.

- `chdir()`
- `execvp()`
- `dup(), dup2()`
- `pipe()`

Note: other functions can also be utilized but we recommend using the above functions.

#### 2.2.3. TODOs in the code

Please revise `simple-execute.c` to implement required functions of your shell program. In `simple-execute.c`, we provided a general framework to help you better understand the code structure. You can fill in the code in the positions of `TODO`. However, you may also ignore this framework and implement in your own way. 

**Note**: Please **DO NOT** modify any file other than `simple-execute.c`. Modification made to other files may cause unexpected results, e.g. disabling autograding of your project. We configured all files except for `simple-execute.c` as protected path, your modification to these files will be labeled as "Protected file(s) modified" in gh classroom, and will lead to possible grade loss.



## 3. Submission Content

You need to modify `simple-execute.c` to complete the shell program. In addition, please sign declaration of originality. 


## 4. Generative AI Policy
In assignment one, we allow usage of generative AI tools to help you with coding. We allow these tools because the key purpose of assignment one is to help you understand the following ideas
- how to interact with Linux,
- the design choices and rationale of shell,
- what is the role of a shell in the context of the whole OS stack.

Below is the guideline of using AI tools in this assignment.
- Allowed AI tools
  - Any AI model, e.g. GPT-4o, that causes no ethical issues.
- Acknowledgement
  - Acknowledge your use of AI tools in `ai_declaration.txt`.
- Limitations of AI tools (in the context of this assignment)
  - AI may fail to properly use system calls.
  - AI may have misunderstanding on some complex shell behaviors, e.g. three pipes.
  - Using AI tools without properly understanding of the generated code can put you at risk in quizs/exams.


## 5. Other Notes

- We will compile, run and grade your program with Ubuntu latest, which is the same as the autograding environment. Please make sure your program sources are compatible with the corresponding version of Ubuntu. Otherwise, 0 marks will be given. 

- Note that we can only grade what you submit in the github repo. You will lose write access to the github repo after deadline. Please find related policies on the [course website](https://github.com/henryhxu/CSCI3150).

- Several new test cases will be utilized when grading. Test cases in `src/README.md` are provided for validation with autograding.

- TA WU, Shaofeng is responsible for this assignment. Questions about the assignment via Piazza are welcomed. Due to massive class size, no individual email will be replied. Requests including but not limited to asking TA to set up environment, write code and debug for you will be rejected according to regulations.

