TraceBit
========

Tracebit can be used to test or try to reverse hashing functions. By using the Tracebit integers instead of 
normal unsigned integers you can replace individual bits with variables.

Trying a normal hashing function

    Hashing result without variables: 
    INPUT : 00010010000100111101110100100001
    OUTPUT: 00000000011000100000000000100111


This looks reasonable.

Now we replace some bits 4-6 with variables x1-x3.

The input now looks like:

    INPUT :0{x3}{x2}{x1}0010000100111101110100100001


The resulting output in modulo-2 expressions:

    OUTPUT: 00000000{x2 + x1.x2.x3}{x1 + x2.x3}{x2.x3 + 1}{x2 + x3}{x3}{x1.x2 + x3 + x2.x3}{x1 + x2 + x3 + x1.x3 + x2.x3 + x1.x2.x3}{x1 + x2.x3 + 1}00000000{x2.x3}{x1.x2 + x3 + x2.x3 + x1.x2.x3}{x1 + x2 + x2.x3 + x1.x2.x3}{x1 + x2.x3 + 1}{x2 + x3}{x1 + x2 + x3 + x1.x3 + x1.x2.x3}{x1.x3 + x1.x2.x3 + 1}{x1 + x2 + x3 + x2.x3}


Here you can see that with this input, the 8th bit can be directly calculated as x2 + x1x2x3. 


