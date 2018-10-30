Biggest Readme Problem - inconsistent when using in.txt, but works fine for prompted input.
----------------------

I have tested my program using prompted input and the program works fine every time.

The problem happens when piping input using the in.txt file, but only on specific lines of text is there a problem.

For specific lines of text, the word with the biggest weight is incorrect. 
For the majority of input from in.txt, the word with the biggest weight is outputted correctly. 
I have tried to figure out the problem, but I am unable to figure it out. 

To explain my problem, here is an example:

In line 7 of the in.txt, I expect "William" to be the output, but instead my program outputs "Gilbert".

Out of the many lines of output, There are maybe about 2 other lines of text where this unexpected output happens 
when using the in.txt file, otherwise the rest of the code outputs as expected.
