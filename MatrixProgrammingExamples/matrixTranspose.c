// MatrixPrograms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <math.h> 


//Custom defines 
#define NO_OF_ROWS 8 
#define NO_OF_COLS 8 


// Test Functions 
void matrixTranspose(void); 
void matrixCopy(void);

// Helper Functions 
void swap(int* src, int* dst); 


// experiment PlayGround 
void testGround(void); 


// Global Data 
static int inpMat[NO_OF_ROWS][NO_OF_COLS], trasnpMat[NO_OF_COLS][NO_OF_ROWS], destMat[NO_OF_ROWS][NO_OF_COLS];


int main()
{   

    testGround(); 

    matrixTranspose(); 
    //matrixCopy();

    return (0); 
}   
    
    
void matrixTranspose(void)
{      
    int i, j, tmp=0; 

    //populate the matrix 
    for (i = 0; i < NO_OF_ROWS; i++)
    {
        for (j = 0; j < NO_OF_COLS; j++)
        {
            // inpMat[i][j] = (rand() % 50); 
            inpMat[i][j] = tmp++;
        }
    }

NAIVE: 
    // Matrix transposition loop -> Input and Output Matrices are different 
    for (i = 0; i < NO_OF_ROWS; i++)
    {       
        for (j = 0; j < NO_OF_COLS; j++)
        {   
            trasnpMat[j][i] = inpMat[i][j]; 
        }   
    } 


    int iRow, jCol, block = 4;
    goto SUBBLOCK_OUTOFPLACE;


IN_PLACE:
    // Matrix transposition loop -> In Place Transposition, Works only for Square Matricies
    // If NO_OF_ROWS != NO_OF_COLS -> Assert !! 
    for (i = 0; i < NO_OF_ROWS; i++)
    {
        for (j = i+1; j < NO_OF_ROWS; j++)
        {
            // swap(&inpMat[i][j],&inpMat[j][i]);
            tmp = inpMat[j][i];
            inpMat[j][i] = inpMat[i][j];
            inpMat[i][j] = tmp; 
        }
    }  

SUBBLOCK_OUTOFPLACE:
    // Matrix transpose -> Blocked version (Subdivide into multiple blocks). Matrix Size hould be an integral multiple of Block Size 

    //populate the matrix 
    tmp = 0;
    for (i = 0; i < NO_OF_ROWS; i++)
    {
        for (j = 0; j < NO_OF_COLS; j++)
        {
            // inpMat[i][j] = (rand() % 50); 
            inpMat[i][j] = tmp++;
        }
    }
    // Zerop out dstMatrx for debugging after copy
    memset(trasnpMat, 0, sizeof(trasnpMat));
    
    for (iRow = 0; iRow < NO_OF_ROWS; iRow += block)
    {
        for (jCol = 0; jCol < NO_OF_ROWS; jCol += block)
        {
            for (i = iRow; i < (iRow + block); i++)
            {
                for (j = jCol; j < (jCol + block); j++)
                {
                    *(*(trasnpMat + j) + i) = *(*(inpMat + i) + j);
                }
            }
        }
    }


SUBBLOCK_INPLACE: 
    // Matrix transpose -> Blocked version (Subdivide into multiple blocks). Matrix Size hould be an integral multiple of Block Size 
    for (iRow = 0; iRow < NO_OF_ROWS; iRow += block)
    {
        for (jCol = iRow+1; jCol < NO_OF_ROWS; jCol += block)
        {
            for (i = iRow; i < (iRow + block); i++)
            {
                for (j = i+1; j < (jCol + block)-1; j++)
                {
                    tmp = *(*(inpMat + j) + i);
                    *(*(inpMat + j) + i) = *(*(inpMat + i) + j);
                    *(*(inpMat + i) + j) = tmp; 
                }
            }
        }
    }


    // matrixCopy();

    printf("Thanks for trying the Matrix Transpose Function"); 
}   


void matrixCopy(void)
{   
    int i, j;
    
    // Check if the dimensions of Source and Destination are same  

    // Zerop out dstMatrx for debugging after copy 
    for (i = 0; i < NO_OF_ROWS; i++)
    {
        for (j = 0; j < NO_OF_COLS; j++)
        {
            destMat[i][j] = 0;
        }
    }
    // Copy Source Matrix to Destination Matrix  -> Element by Element Copy 
    for (i = 0; i < NO_OF_ROWS; i++)
    {
        for (j = 0; j < NO_OF_COLS; j++)
        {
            destMat[i][j] = inpMat[i][j];
        }
    }
        
    // Zerop out dstMatrx for debugging after copy
    memset(destMat, 0, sizeof(inpMat));
    // Copy Source Matrix to Destination Matrix  -> Bulk Memcopy  
    memcpy(destMat, inpMat, sizeof(inpMat));
          
    printf("Thanks for trying the Matrix Copy Function");
}   
    
    
void testGround(void)
{   
    int i, j, tmp=0; 

    //populate the matrix 
    for (i = 0; i < NO_OF_ROWS; i++)
    {
        for (j = 0; j < NO_OF_COLS; j++)
        {
            inpMat[i][j] = tmp++;
            
        }
    }


OUT_OF_PLACE_TRANSPOSE: 
    // Access Matrix with a single index / pointer  
    for (i = 0; i < NO_OF_ROWS; i++)
    {
        for (j = 0; j < NO_OF_COLS; j++)
        {
            *(*(destMat + j) + i) = *(*(inpMat + i) + j);
        }
    }


IN_PLACE_TRANSPOSE:
    // Access Matrix with a single index / pointer  
    for (i = 0; i < NO_OF_ROWS; i++)
    {
        for (j = i+1; j < NO_OF_COLS; j++)
        {
            tmp = *(*(inpMat + i) + j); 
            *(*(inpMat + i) + j) = *(*(inpMat + j) + i);
            *(*(inpMat + j) + i) = tmp; 
        }
    }

}   



//Helper Functions 
void swap(int *src, int *dst)
{   
    int tmp = *src; 
    *src = *dst; 
    *dst = tmp; 
}  



