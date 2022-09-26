this code is a shell like program built upon the original linux shell, using execv and fork commands, 
assignment description follows:

Lab 6
Lab 6 is built on top of the code infrastructure of Lab 5, i.e., the "shell". Naturally, you are expected to use the
code you wrote for the previous lab.
Motivation
In this lab you will enrich the set of capabilities of your shell by implementing input/output
redirection and pipelines (see the reading material). Your shell will then be able to execute
non-trivial commands such as "tail -n 2 in.txt| cat > out.txt", demonstrating the power of
these simple concepts.
Lab 6 tasks
Task 0a
Pipes
A pipe is a pair of input stream/output stream, such that one stream feeds the other stream
directly. All data that is written to one side (the "write end") can be read from the other side
(the "read end"). This sort of feed becomes pretty useful when one wishes to communicate
between processes.
Your task: Implement a simple program called mypipe, which creates a child process that
sends the message "hello" to its parent process. The parent then prints the incoming
message and terminates. Use the pipe system call (see man) to create the pipe.
Task 0b
Here we wish to explore the implementation of a pipeline. In order to achieve such a
pipeline, one has to create pipes and properly redirect the standard outputs and standard
inputs of the processes.
Please refer to the 'Introduction to Pipelines' section in the reading material.
Your task: Write a short program called mypipeline which creates a pipeline of 2 child
processes. Essentially, you will implement the shell call "ls -l | tail -n 2".
(A question: what does "ls -l" do, what does "tail -n 2" do, and what should their combination
produce?)
Follow the given steps as closely as possible to avoid synchronization problems:
1. Create a pipe.
2. Fork to a child process (child1).
3. On the child1 process:
1. Close the standard output.
2. Duplicate the write-end of the pipe using dup (see man).
3. Close the file descriptor that was duplicated.
4. Execute "ls -l".
4. On the parent process: Close the write end of the pipe.
5. Fork again to a child process (child2).
6. On the child2 process:
1. Close the standard input.
2. Duplicate the read-end of the pipe using dup.
3. Close the file descriptor that was duplicated.
4. Execute "tail -n 2".
7. On the parent process: Close the read end of the pipe.
8. Now wait for the child processes to terminate, in the same order of their
execution.
Mandatory Requirements
1. Compile and run the code and make sure it does what it's supposed to do.
2. Your program must print the following debugging messages if the argument -d is
provided. All debugging messages must be sent to stderr! These are the
messages that should be added:
- On the parent process:
- Before forking, "(parent_process>forking...)"
- After forking, "(parent_process>created process
with id: )"
- Before closing the write end of the pipe,
"(parent_process>closing the write end of the
pipe...)"
- Before closing the read end of the pipe,
"(parent_process>closing the read end of the
pipe...)"
- Before waiting for child processes to terminate,
"(parent_process>waiting for child processes to
terminate...)"
- Before exiting, "(parent_process>exiting...)"
- On the 1st child process:
- "(child1>redirecting stdout to the write end of the
pipe...)"
- "(child1>going to execute cmd: ...)"
- On the 2nd child process:
- "(child2>redirecting stdin to the read end of the
pipe...)"
- "(child2>going to execute cmd: ...)"
3. How does the following affect your program:
- Comment out step 4 in your code (i.e. on the parent process:do
not Close the write end of the pipe). Compile and run your code.
(Also: see "man 7 pipe")
