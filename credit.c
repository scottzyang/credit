#include <stdio.h>
#include <cs50.h>

bool check_sum(long n);
void verify_card(long n);


int main(void)
{
    // Get credit card number from User
    long credit = get_long("Enter Credit Card Number: ");
    if (check_sum(credit)) // Check validity of card
    {
        verify_card(credit); // Verify the card type
    }
    else
    {
        printf("INVALID\n");
    }
}


// Function to evaluate the validity of the card
bool check_sum(long n)
{   
    int sumprod = 0;
    long cpy = n;
    
    while (cpy > 0)
    {   
        int dgt;
        
        // Extracts the second to last digit
        if (cpy / 10 >= 1 && cpy / 100 < 1) 
        {
            dgt = cpy / 10; // e.g. 23 -> 2
        }
        else 
        {
            dgt = (cpy % 100) / 10; // e.g. 234 -> 3
        }
        
        // Multiplies each digit by two
        int prod = dgt * 2;
        
        if ((prod / 10) >= 1)  // Ensuring the digits of a two-digit product are added together
        {
            sumprod = (prod % 10) + (prod / 10) + sumprod;
        }
        else // Single digit product added to the total
        {
            sumprod = prod + sumprod;
        }
        
        // Removes the last two digit grouping
        cpy = cpy / 100;
        
    }
    // Reset copy to initual user input
    cpy = n;
    
    // Extracts the last digit
    while (cpy > 0)
    {
        int dgt;
        if (cpy / 10 < 1)
        {
            dgt = cpy; // e.g. 2 -> 2
        }
        else 
        {
            dgt = cpy % 10; // e.g. 23 -> 3
        }
        
        // Adding the extracted last digits to total
        sumprod = dgt + sumprod;
        
        // Removes the last two digit grouping
        cpy = cpy / 100;
    }
    
    // Evaluates if the  total sum ends in 0
    return sumprod % 10 == 0;
    
}

// Function to determine the type of card
void verify_card(long n)
{
    long cpy = n;
    int cardlength = 0;
    long stdgts = 0;
    
    
    // Loop to determine the number of digits in user input
    while (cpy > 0)
    {
        cpy = cpy / 10;
        cardlength++;
    }
    
    // Reset copy to initual user input
    cpy = n;
    
    // Loop to determine the start digits of user input
    while (cpy >= 100)
    {
        stdgts = cpy / 10;
        cpy = cpy / 10;
    }
    if (cardlength == 13 || cardlength == 16) 
    {
        if (stdgts >= 40 && stdgts <= 49)
        {
            printf("VISA\n");
        }
        else if (stdgts >= 51 && stdgts <= 55)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (cardlength == 15)
    {
        if (stdgts == 34 || stdgts == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}