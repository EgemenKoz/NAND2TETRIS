//get the numbers into registers
//use a loop and add the values over and over
//can be optimized with looping using the lower value

@i 
M=1
@R2
M=0

(LOOP) //Addition loop
@i
D=M
@R1
D=D-M
@END
D;JGT
@R0
D=M
@R2
M=D+M
@i
M=M+1
@LOOP
0;JMP
(END) //Infinite end loop
@END
0;JMP