## <img src="https://github.com/devicons/devicon/blob/master/icons/c/c-original.svg" title="C" alt="C Logo" width="100" height="100" align="left" />&nbsp;  <p align="center">42Paris - Pipex</p>  <img src="https://github.com/devicons/devicon/blob/master/icons/c/c-original.svg" title="C" alt="C Logo" width="100" height="100" align="right" />&nbsp;
</br>
<hr/>
</br>


<p align="center">
  <img src="https://github.com/ayogun/42-project-badges/blob/main/badges/pipexm.png" title="pipex badge" alt="pipex badge with bonus png"/>
</p>


## 📝 Table of Contents
- [About](#about)
- [Standard Part - Mandatory](#100-standard-part---mandatory)
- [Bonus Part - Optional](#bonus-part---optional)
- [Usage](#usage)

## About
This project is on the **3rd** Circle of the Holy circle of the 42 cursus. <br>
Along with the algorithmic project **push_swap** and one of the 3 available graphical projects. <br>


## 1️⃣0️⃣0️⃣ Standard Part - Mandatory
the goal of this project is to create a program that replicates the functionality of the shell pipe command. <br>
more precisely, recreate the following shell command: <br>
```shell
$ ./pipex infile cmd1 cmd2 outfile
$ < infile cmd1 | cmd2 > outfile
```
where file1 and file2 are file names, and cmd1 and cmd2 are shell commands with their parameters. <br>

## 1️⃣2️⃣5️⃣ Bonus Part - Optional
- Handle n-number pipes
- Handle `<<` (heredoc)
- Handle `>>` (append)

be able to recreate the following commands :
```shell
$ ./pipex infile cmd1 cmd2 ... cmdn outfile
$ < infile cmd1 | cmd2 | cmd2 | ... | cmd-n > outfile
```
and this
```shell
$ ./pipex here_doc LIMITER cmd1 cmd2 ... cmd-n outfile
$ cmd1 << LIMITER | cmd2 | cmd3 | ... | cmd-n >> outfile
```

# ⚙️ Usage 
1) `git clone` in your preferred directory
```shell
$ git clone https://github.com/FxmousKid/42Cursus-Pipex.git
```
2) `cd` in the pipex directory
```shell
$ cd 42Cursus-Pipex
```
3) `make`
for standard part :
```shell
$ make pipex
```
for bonus part :
```shell
$ make bonus
```
4) execute your commands ! ex :
```shell
$ ./pipex Makefile "cat" "wc -l" outfile.txt
$ ./pipex_bonus Makefile "cat" "grep CC" "grep clang" "wc -l" outfile.txt
$ ./pipex_bonus here_doc "ABC" "cat" "wc -l" outfile.txt
```
Enjoy ! 😊

</br>

## Some Pipex quirks not to forget :
 * return  `127` if the **last** command is not found
 * try to `open()` first before trying to see if the command exists, and exit
 as soon as one of them fails
 * the main program must only return the exit status of the **last** command (assuming 
 infile and outifle are opened successfully)
 * check for **permission** first before trying to open the file, and exit accordingly
 * bash posix 5.1 with `< file_does_not_exit command_does_not_exit | cat > out.txt` display both 
 file_does_not_exit : No such file or directory and command_does_not_exit : command not found, whereas
 bash posix 5.2 only displays file_does_not_exit : No such file or directory
 * if outfile doesn't exist, check if you have the permission to create it in the directory

