To run the program properly and view the UI please do the following

1-Preferably use Visual Studio Code (Clion may cause issues with the UI)
2-Open a new Terminal and use GitBash instead of Powershell
3-Enter the following command to automatically compile and run the program
    the command-> g++ -Wno-literal-suffix -o mainProgram.exe *.cpp
                  ./mainProgram.exe

Note:
    make sure the bash terminal is in the right directory where all the files are if Not
    1- enter the command-> cd
    2- enter the command-> cd fullPathToDirectory
    3- enter the command-> g++ -Wno-literal-suffix -o mainProgram.exe *.cpp
                  ./mainProgram.exe
    

Here is a Test case that we made:

2000    //store in register 0 the value "0x00"
2101    //store in register 1 the value "0X01"
2202    //store in register 2 the value "0X02"
2303    //store in register 3 the value "0X03"
5413    //add the values in register 1 and 3 and store in register 4
7501    //do an OR bitwise operation on register 1 and 0 and store in register 5
7607    //do an OR bitwise operation on register 7 and 0 and store in register 6
8703    //do an AND bitwise operation on register 3 and 0 and store in register 7
8809    //do an AND bitwise operation on register 9 and 0 and store in register 8
8D15    //do an AND bitwise operation on register 1 and 5 and store in register D
9915    //do an XOR bitwise operation on register 1 and 5 and store in register 9
9A23    //do an XOR bitwise operation on register 2 and 3 and store in register A
2204    //store in register 2 the value "0X04"
A201    //do a right rotate bitwise operation on the value in register 2 by 1 bit and store it in the same register
2F55    //Store in register F the value "0X55"
33FF    //store the value in register 3 in the memory cell FF
3200    //store the value in register 2 in the memory cell 00 and screen out the value
1CFF    //load register C with the value in memory cell FF
404E    //copy the value in register 4 to register E
2033    //store in register 0 the value "0x33"
2133    //store in register 1 the value "0x33"
B15E    // if value in register 1 is equal to register 0 jump to instructions in memory cell 5C
2099    //skip this line
B460	// check that jump doesn't do anything when the registers 4 and 0 doesn't match
2077    //load register 0 with the value "0x77"
Koki    //input validation
20C9	//load register 0 with the value "0xC9" 
2180	//load register 1 with the value "0x80"
6710	//float add registers 1 and 0 and store the result in register 7 ["Expected: C9"]
22B4	//load register 2 with the value "0xB4"
2324	//load register 3 with the value "0x24"
6823	//float add register 2 and 3 and store the result in register 8 ["Expected: B2"]
C000    // Halt
