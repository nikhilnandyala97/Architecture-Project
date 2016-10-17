# PYhtongeneral

================================================
Functional Simulator for simpleRISC processor
================================================

README

Table of contents
1.Functioning of the SoftWare
2.Limitations/Bugs
3. Directory Structure
4. How to build
5. How to execute

Functioning of the SoftWare :
-----------------------------
It is a Simple Risc Simulator which compiles your encoded format of your simple risc code and runs and gives the output of the code by saving the results in the registers. And it also prints the elements in the memory in a file created by the code . 


Limitations/Bugs Known So far:
------------------------------
1.For an invalid instruction it will only consider opcode if the opcode is in not valid ,But for other type invalid instuctions it wont terminate 
2. the instructions should ordered .i.e :
                                         0x0 
                                         0x4
                                         0x16 is not valid 
                                         the next instruction should be 0x8


Directory Structure:
--------------------
CS112-Project
  |
  |- bin
      |
      |- mySimpleSim
  |- doc
      |
      |- design-doc.docx
  |- include
      |
      |- mySimpleSim.h
  |- src
      |- main.c
      |- Makefile
      |- mySimpleSim.c
  |- test
      |- simple_add.mem
      |- fib.mem
      |- array_add.mem

How to build
------------
For building:
	$cd src
	$make
  copy and paste the 
For cleaning the project:
	$cd src
	$make clean

How to execute
--------------

Before executing copy and paste the mySimpleSim from bin to src and then execute using the below command.

./mySimpleSim test/simple_add.mem
