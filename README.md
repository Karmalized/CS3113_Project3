# CS3113 Project 3: Bounded Buffer (Producer/Consumer Problem)

This project/lab provides a general overview of how the producer/consumer problem works in real time with file reading and output onto the terminal using semaphores and pthreads.

## Installation
**'NOTE: THE IMPLEMENTATION OF THIS CODE IS ONLY FEASIBLE ON LINUX SYSTEMS, THIS IS DENOTED BY THE <UNISTD.H> LIBRARY'**

To install and run the C code provided in the repository we will do the following:
1. download and unzip the CS3113_Project3 file in any directory, using the terminal we will navigate to the directory and to do so we use the ```cd <file_name>``` command:
  
<img width="389" alt="Result" src="https://github.com/user-attachments/assets/95f49111-8334-40ec-8493-757d6a1f0e9d">

Helpful Tip: Use "ls", shorthand for list services, to determine which directory you are in. Depending on where you are on your local computer you may have to use multiple ```cd <file_name>``` commands in order to reach the right directory!

2. Once we are in the right directory, this should be the CS3113_Project3 folder, do "ls" again and identify the "BoundedBuffer.c" folder in the directory. This is the file we will be compiling!

<img width="299" alt="Code" src="https://github.com/user-attachments/assets/e540e0ba-f953-4820-aff3-6d344e474176">

3. Once you've found the "BoundedBuffer.c" file, we will use the command ```gcc BoundedBuffer.c -lpthread -lrt``` to compile our code and create the executable for the respective code we are compiling!

<img width="385" alt="Result" src="https://github.com/user-attachments/assets/96de0a27-ccb2-40d9-8547-9f419e42e083">

executing the above command (```gcc BoundedBuffer.c -lpthread -lrt```) creates a standard ```a.out``` executable that can be run in the terminal

Once you've compiled the C file on your machine, we will use the terminal command ```./``` which is the executable command for linux systems. To use this command type in the terminal ```./<EXE_FILENAME_HERE>``` to run the generated program file. For the example shown above that command will look like: ```./a.out```. After doing so, you will have successfully run the BoundedBuffer.c file from the executable.
