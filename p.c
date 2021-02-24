#include <stdio.h>
int fizz(int*);


int main(){
    int a;
    int *p = 0;

    p = &a;
    

    printf("Enter an int: ");
    scanf("%d", p);
    printf("You have entered: %d, at adress: %p\n", *p,p);

         int t = fizz(p);
    
    }

    int fizz(int *p) {
        int i; 
    for (i=0; i<=*p; i++) 
    {     

        if (i%3 == 0 && i%5 == 0)         
            printf ("Fizzbuzz\n");

        else if ((i%3) == 0)     
            printf("Fizz\n");                  

        else if ((i%5) == 0)                        
                printf("Buzz\n"); 

        else // print the number             
            printf("%d\n", i);                  
    } 
    return 0; 
    } 