#include <stdio.h>
#include <cs50.h>

int main (void){
    long cardnum = get_long("Number: ");
    int cardlegnth = 1;
    long legnthfinder = cardnum;

    while (legnthfinder>10){
        legnthfinder = legnthfinder/10;
        cardlegnth++;
    }
    
    int doubled = 0;
    int singled = 0;
    
    for (int i = 1; i<cardlegnth; i=i+2)
    {
        long temp = 1;
        
        for(int j = 0; j<i; j++){
            temp = 10*temp;
        }
        if(2*((cardnum/temp)%10)>9){
         doubled = doubled+((2*((cardnum/temp)%10))/10);
         doubled = doubled+(2*((cardnum/temp)%10)%10); 
        }
        else{
        doubled = doubled+2*((cardnum/temp)%10);
        }
    }
   
    for (int i = 0; i<cardlegnth; i=i+2)
    {
        long temp = 1;
        
        for(int j = 0; j<i; j++){
            temp = 10*temp;
        }
        singled = singled+((cardnum/temp)%10);
    }
    long divd = 1;
    for(int m = 0; m<13;m++){
        divd = divd*10;
    }
        if((singled+doubled)%10==0){
            if(cardlegnth==15){
                if(cardnum/divd==34||cardnum/divd==37){
                    printf("AMEX\n");
                }
                else{
                    printf("INVALID\n");
                }
            }
            else if(cardlegnth==16){
                if(cardnum/(divd*10)>50&&cardnum/(divd*10)<56){
                    printf("MASTERCARD\n");
                }
                else if(cardnum/(divd*100)==4){
                    printf("VISA\n");
                }
                else{
                    printf("INVALID\n");
                }
            }
            else if(cardlegnth==14){
                if(cardnum/(divd)==4){
                    printf("VISA\n");
                }
                else{
                    printf("INVALID\n");
                }
            }
            else{
                printf("INVALID\n");
            }
        }
        else{
            printf("INVALID\n");
        }

}