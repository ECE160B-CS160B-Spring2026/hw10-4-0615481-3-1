## Question 1

Modify the keyword count program that we wrote in class to handle all of the keywords in C. For example, the keyword, int, was not being counted.

Compile Steps: 
    gcc q1.c

Command(s) to run the program:

    ./a.out < test1.c

    ./a.out < test2.c

Output:

    ./a.out < test1.c:

        1 const

        1 continue

        1 default

        3 else

        3 for
        
        9 if

        16 int
        
        6 return

        2 sizeof

        9 struct

        1 unsigned

        7 void

        1 volatile

        4 while

    ./a.out < test2.c:

        1 break

        14 char

        4 else

        3 for

        10 if

        12 int

        7 return

        1 sizeof

        14 struct

        8 void
        
        2 while
                