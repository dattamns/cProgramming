// BitManipulationPrograms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h> 
#include <math.h>


void toggleBits_Naive(void);
void toggleBits_Optimized(void);
void toggleOnlySetBits(void);
void countSetBits(void); 
void checkifNumIsPowerOf2();
void findRightMostSetBit(void); 

int main()
{
    findRightMostSetBit();
    checkifNumIsPowerOf2(); 
    toggleBits_Naive();
    toggleBits_Optimized();
    toggleOnlySetBits();

    printf(" Thanks for trying Bit Manipulation Program Demos"); 
    std::cout << "Hello World!\n";

}


/*
Toggle (or Flip) the bits of number 
Input : 10
Output : 5
(10)Base10  = (1010)Base2.
After toggling the bits we get:
(0101)Base2 = (101)Base2
            = (5)Base10.
*/

// function to Toggle the bits of a number 
void toggleBits_Naive(void)
{
    int n = 10, res, i=0, count, one=1; 
    res = n; 

    count = sizeof(int) * 8;     // So many number of bits in the data type 

    // traversing bits of 'n' from the right 
    while(i<count) 
    {
        // bitwise left shift  
        res = (res ^ (one<<i));
        i++; 
    }

    printf(" Toggled number = %d \n", res);
}   
    
    
// function to toggle bits of a number  - Optimized Way O(1) 
void toggleBits_Optimized(void)
{   
    int num = 10, res, negOne = -1;

    res = num ^ negOne; 
    printf(" Toggled number = %d \n", res);
}   


// function to toggle only those bits which are set 
// This is as good as ZEROing out the number 
void toggleOnlySetBits(void)
{
    int n = 10, res, i=0, count, one = 1, pos;
    res = n;

    count = sizeof(int) * 8;     // These many number of bits in the data type 

    // traversing bits of 'n' from the right 
    do 
    {
        pos = one << i; 
        if (res & pos)
        {
            // bitwise left shift  
            res = (res ^ pos); 
        }
        i++; 
    } while (i <= count); 

    // Or simply ... 
    res = 0; 


    printf(" Toggled number = %d \n", res);
}



#define MASK 0x1; 
#define BYTE_SIZE 8  

void countSetBits(void) 
{
    int num = 1073741808, res=0;
    int noOfSetBits = 0;
    int tmpMask = MASK;

    for (int i = 0; i < sizeof(int) * BYTE_SIZE; i++)
    {
        if (num & tmpMask)
        {
            noOfSetBits++;
        }
        tmpMask <<= 0x1;
    }

    printf(" Number of Set Bits = %d \n", noOfSetBits);
}   


/* Subtracting 1 from a number flips all the bits to the righmost one 
   For Powe of 2 : Only one of the bits should be set 
   So combining the above two properties gives the most optimal solution  
*/

void checkifNumIsPowerOf2(void)
{
    int num = 7; 

    // Does not work for 'Zero' - Take care .. Instead Do : (x && !(x & (x - 1))) 
    if (num & (num - 1))
        printf(" Not a power of 2 \n"); 
    else
        printf(" Power of 2 \n");

}


/* 
    Find out the Right-most bit which is Set in a given number 

    Trick 1 : x ^ ( x & (x-1)) : Returns the rightmost 1 in binary representation of x.
    x = 10 = (1010)2
    x & (x-1) = (1010)2 & (1001)2 = (1000)2
    x ^ (x & (x-1)) = (1010)2 ^ (1000)2 = (0010)2


    Trick 2: x & (-x) : Returns the rightmost 1 in binary representation of x
    x = 10 = (1010)2
    (-x) = -10 = (0110)2
    x & (-x) = (1010)2 & (0110)2 = (0010)2

*/
void findRightMostSetBit(void)
{   
    int x = 12, rmsb;

    // Using Trick-1 
    rmsb = x ^ (x & (x - 1));
    printf(" Trick-1 : Position of the Set Bit = %d \n", (int)log2(rmsb));

    // Using Trick-2 
    rmsb = x & (-x);
    printf(" Trick-2 : Position of the Set Bit = %d \n", (int)log2(rmsb));

}


int bitrev(int x, int bitcount)
{
	int res = 0;
	int i;
	for (i = 0; i < bitcount; ++i) 
	{
		res = (res << 1) | (x & 1);
		x >>= 1;
	}
	return res;
}