Lab Goals
    To get acquainted with the low-level interface to system calls.
    To understand how programs can work without the standard library.
    Basics of directory listings, through a first attempt at executable file viruses.
    Debugging programs via printouts (the idea of debug mode, continued).
therefore for this lab we couldnt use any standard libraries.

Task 1a: A restricted count version

The count program

NAME
    count - counts the number of words in an input text
SYNOPSIS
    count [OPTIONS]
DESCRIPTION
    count receives text from standard input, counts the number of words in it and prints it to standart output. 
OPTIONS

    -D
        Activate debug mode (see debug prints below).

EXAMPLES

    #> count
    Hi, my name is Noah
    5
    ^D
    #>

    #> count
    I love                 spaces   
    3
    ^D
    #>   

Comments and tips

    See the next section for debug prints.
    Make sure you compile and link in the same way as in task0. Feel free to adapt the makefile you wrote in task 0.
    It is highly advisable for this lab task to read and write one character at a time (as opposed to using a larger buffer), this way the program is much simpler. However, note that this implementation is inefficient and should not be used in production code due to a large number of system calls that could have been minimized by using a buffer.

Debug prints
When (and only when) the debug flag (-D) is given, your program should prints the following to stderr:

    For each system call (except for "exit"), its ID (the value of the first argument) and its return code.
    Whatever else you think will help you.

Task 1b: Working with files
NAME
    count - counts the number of words in an input text
SYNOPSIS
    count [OPTIONS]
DESCRIPTION
    count receives text from standard input, counts the number of words in it and prints it to standart output. 

    If option '-i' is given, count reads its input from a file, if it is not, count reads its input from standard input.
    If option '-o' is given, count writes its output to a file, if it is not, count writes to standard output.
OPTIONS

    -D
        Activate debug prints.

    -iFILENAME
        Input file. Read input from a file, instead of the standard input.

    -oFILENAME
        Output file. Outputs to a file, instead of the standard output.

EXAMPLES

    #> echo "Hi, my name is Noah" > in
    #> ./count -iin -oout
    #> cat out
    5

    #> ./count -D
    in: 0 out:1
    Hi 
    system call [arg1, arg2, arg3, arg4, ret code] = 3, 0, 72, 1, 1
    system call [arg1, arg2, arg3, arg4, ret code] = 3, 0, 105, 1, 1
    system call [arg1, arg2, arg3, arg4, ret code] = 3, 0, 32, 1, 1
    1
    system call [arg1, arg2, arg3, arg4, ret code] = 4, 1, 1, 1, 1
    ^D

        

Comments and tips

    See comments and tips from Task 1a.
    Make sure to check if there is an error when opening files, your program should print an appropriate error message and exit in the case of an error.

Debug prints
In addition to all the debug prints listed in previous tasks, add these prints:

    The input and output file paths (print "stdin" or "stdout" if -i or -o were not used).
    The ID and return code for all added system calls.


Task 2: First step towards Flame 2
Many computer viruses attach themselves to executable files that may be part of legitimate programs. If a user attempts to launch an infected program, the virus code is executed before the infected program code. The goal is to write a program that attaches its code to files in the current directory.

In the following tasks you will implement the flame2 program:

SYNOPSIS
    flame2 OPTION

DESCRIPTION
    Print a comment line of your choice (such as "Flame 2 strikes!"), and then list all the file names in the current directory.

OPTIONS

-D
    Activate debug prints

-p<prefix>
    Instead of printing all the file names, print only the names of the files in the current directory that begins with the given prefix <prefix>.

-a<prefix>
    Attach the executable code of flame2 at the end of each file in the current directory that begins with the given prefix <prefix>.

Note: The prefix can be any string of any length. You must not assume a maximal length on the prefix.
Task 2a: A restricted flame2 version: printing a list of all files
A restricted version of flame2 is implemented, as follows:

    Print the names of all files in the current directory.

Some Guidelines

    Your program should use the sys_getdents [141] system call.
    The declarations of the dirent type constants can be found in the file dirent.h (can be found in /usr/include/dirent.h).
    Please note that the first argument for getdents is a file descriptor open for reading - it should be for the file "." that represents the current directory.
    In case of an error, the program should terminate with exit code 0x55.
    To make things easier, you may assume that the entire directory data (returned by the getdents call) is smaller than 8192 bytes.
    Dont forget not to use any standard library functions!. Instead, in "util.h" and "util.c", you can find few implementation for some helpful functions. You may use them.


Debug prints

    As before, all return codes and arguments sent to system calls.
    The length and type of each dirent record.


Task 2b: Extending flame2: printing a list of all files with a given prefix

Extend flame2, which is implemented in Task 2a in the following way:
When the flag -p<prefix> is supplied, it will only print the names of the files in the current directory that begins with prefix. In addition, should print the type of each file.
As mentioned, the prefix parameter may contain any string of any length.

Consult the sys_getdents [141] manual page for a way to check the type of the file.


Task 2c: Extending flame2: Add the executable code of flame2 to each file obtained from Task2b
This task may be done in a completion lab if you run out of time during the regular lab.

Warning: You probably want to be very sure that the mechanism for selecting files works correctly at this point, e.g. you may not want the program to operate on your C source code files, etc. Be careful not to destroy your own source code files!

The following contains code you need to write in assembly language. 

Extend flame2, which is implemented in Task 2b in the following way:

    Starting assembly language implementation: begin with a label "code_start".
    Write a function void infection(int) that gets a number. If the number is even it prints to the screen the message "Hello, Infected File", otherwise does nothing. Note: this should be done using just one system call! If you have more than 20 lines of code here then you are doing something wrong!
    Write a function void infector(char *) that opens the file named in its argument, and adds the executable code from "code_start" to "code_end" after the end of that file, and closes the file. Note: this should be done using just a few system calls: open (for append), write, close, each using less than 10 lines of assembly code. Again, if your code is longer then you are doing something wrong!
    End assembly language part with a label "code_end".
    The rest of the task below can be done in C (recommended), even if you wrote the above code in assembly language. Print both the addresses of code_start and code_end to the screen, infer from this information how to reach the executable code of the function infector and the other functions you need to copy to the output file.
    Modify flame2 such that when the flag -a<prefix> is supplied, it will call the infection and infector functions in order to add the executable code of infection to the end of each file with prefix <prefix>. Also, this option will print out the names of these files like the "-p" option. For simplicity, you may assume that only one of the options "-a", "-p" will be set in any single run of the program.

    Note for assembly language implementation: The part of the code that is responsible for actual file handling (i.e. opening the file, adding the executable code of the infection , etc.) should be written in assembly language and done inside the file "start.s". You can add the code after the end of the code for system_call. You can either call the system_call code (note that it uses C calling conventions, as until now you used it through function-calls from C), or re-use part of it to do the system call yourself (shorter and simpler!). Also, it is a good idea to test your infection() function first, before proceeding to infector().

    Make sure you understand the part of the code that follows the "system_call:" label in the file "start.s". You are encouraged to work with an appropriate register in order to implement all the file handling issues.


After completing the task, execute one of the files that were "infected" by flame2 and see what happens: does the virus really work?

    Does it attach its code and infect the executable file(s)?
    Does it run when the infected is executed (if not, why not?)


Test your implementation on at least two files. You can use your previous lab solutions as input.
Use the command chmod u+wx <filename> to give user write/execute permissions.


Debug prints

    Again, all return codes and arguments sent to system calls.
