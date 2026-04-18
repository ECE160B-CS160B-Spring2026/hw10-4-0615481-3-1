## Question 3

Use the hash map struct that we created in class to find the intersection (common elements) between two arrays of integers. Your function prototype should be:  
<code>void intersection(int output[], int array1[], int array2[]);</code>  

Alternatively, you can also pass in the lengths of the arrays:
<code>void intersection(int output[], int array1[], int lenArr1, int array2[], int lenArr2);</code> 

Have your main function accept the following inputs: number of points in array1, array1 values, number of points in array2, array2 values. Your main should print out the intersection seprated by a space. (e.g. If the intersection was 2 and 5, you'd print out ```2 5```).

Compile Steps:
    ./a.out
Output:

    input: 

        3

        1 2 3

        4
        
        2 3 4 5

    output: 2 3 