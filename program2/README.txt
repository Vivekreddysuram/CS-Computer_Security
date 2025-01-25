
DES Encryption Components Usage Instructions
===========================================

This README provides instructions on how to test the various components of the DES encryption algorithm as implemented in the programs '2a.cpp' through '2e.cpp'.

Compiling the Programs:
-----------------------
Each C++ source file corresponds to a different part of the DES algorithm:

2a.cpp - Expansion function
2b.cpp - S-box implementation
2c.cpp - P-box implementation
2d.cpp - Key schedule
2e.cpp - Remaining DES operations (XORs, etc.)

To compile these programs, use the following commands or use the make command:

g++ -o 2a 2a.cpp
g++ -o 2b 2b.cpp
g++ -o 2c 2c.cpp
g++ -o 2d 2d.cpp
g++ -o 2e 2e.cpp

Using make with any args: (uses default key and plain text in the Makefile)
make

But this key is a preferable 133457799BBCDFF1 and text can be anything. If the key is not in this format 133457799BBCDFF1 then it gives an error.

Running the Programs:
---------------------
After compiling the programs, you can run each executable with the following commands:

./2a
./2b
./2c
./2d
You need to provide the key and plain text for running 2e.
./2e 133457799BBCDFF1 "my plain text" 

Note: when you compile using the make command each file is executed by default. 

Instructions for Each Program:
------------------------------

2a.cpp:
Run './2a' and enter a 32-bit hexadecimal string when prompted to test the expansion function.

2b.cpp:
Run './2b' and enter a 6-bit binary string to test the S-box implementation.

2c.cpp:
Run './2c' and enter a 32-bit binary string to test the P-box implementation.

2d.cpp:
Run './2d' and enter a 64-bit hexadecimal key when prompted to see the generated subkeys from the key schedule.

2e.cpp:
This program combines the expansion function, S-boxes, P-boxes, and key schedule to perform the rest of the DES operations. Run ./2e 133457799BBCDFF1 "my plain text"
You will need to provide the key and plain text the key is 133457799BBCDFF1 and plain text is anything the user wants.


