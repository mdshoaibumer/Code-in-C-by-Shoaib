/*
Task
Given a five digit integer, print the sum of its digits.

Input Format
The input contains a single five digit number, .

Output Format
Print the sum of the digits of the five digit number.
Sample Input 0
10564
Sample Output 0
16

*/
#include <stdio.h>

int main() {
	
    int nNumber = 0;
    int nSumOfDigits = 0;
    //Takes the input;
    scanf("%d", &nNumber);
    int nRemainder = nNumber;
    for(int i =0; i < 5 ; ++i){
        //Adds the Modulus Remainder to nSumofDigits
        nSumOfDigits += nRemainder%10;
        //When divides by 10 it removes the last digit.
        nRemainder = nRemainder/10;
    }
    printf("%d", nSumOfDigits);
    return 0;
}
