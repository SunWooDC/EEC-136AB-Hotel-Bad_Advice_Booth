/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
//#include "wave.h"

int i;
int bb = 0;
int j = 0;
int k = 0;
int f = 0;
char advice[200];
int button1Pressed = 0;
int button2Pressed = 0;
int button3Pressed = 0;
int button4Pressed = 0;
int button5Pressed = 0;

char marriage[5][200] = {"Just have a kid it will fix everything!",
                    "If you both quit your jobs you will have more time for each other",
                    "If you want to be sure never to forget your wife's birthday, just try to forgetting it once!",
                    "You need to have honesty in your relationships. IF she asks you \"Do these pants make me look fat?\", feel free to respond \"yes they do\" and offer to show all the other clothes that do as well",
                    "Being married. is great. It means you found that one special person you want to annoy for the rest of your life."};

char job[5][200] = {"To improve your chances of landing a fireman job start smoking to acclimate your lungs to the smoke in a building fire",
                    "Hard work never killed anybody, but why take a chance?",
                    "Spend 10 min every day pooping at work. At the end of the year you would have been paid for 40 hrs of just pooping",
                    "Put a teabag in your whiskey, so you can day drink without being judged",
                    "Chose a lazy person to do the job because they will find an easy way to do it"};

char love[5][200] = {"Check your phone often while on the date, especially when they are talking. It reminds them that your time and attention is valuable",
                     "If she does not laugh at your jokes make sure you repeat it a couple of times because clearly she is missing something",
                     "If you can't blind them with brilliance, baffle them with bullshit ",
                     "Lonely? Try a jail pen pal",
                     "By the end  of the first date be sure you have detailed the failings of your exes so they can easily avoid making those same mistakes"};

char children[5][200] = {"To get a child's attention - sit down and look comfortable.",
                         "Just be good and kind to your children. Not only are they the future of the world, they're the ones who can sign you into a home",
                         "There is no such thing as fun for the whole family. So always insist on your way",
                         "If you don't know where your kids are in the house, turn off the internet and watch them magically appear",
                         "When your kids start crying, start bawling bigger and better. Soon, they will stop crying & turn their concerns to your welfare"};

char randy[5][200] = {"Sick of following your dreams? Ask them where they are going and hook up with them later",
                      "It's so much easier to suggest solutions when you don't know too much about the problem",
                      "Cookies have very few vitamins, that's why you have to eat so many of them",
                      "No flashlight on your phone? Take a photo of the sun, and use it in the dark",
                      "If you being chased by a wild animal lay on the ground for at least 5 sec. The 5 second rule will prevent them from eating you"};



void setRed()
{
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    
    Cy_SysLib_DelayUs(50);
    
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    
    Cy_SysLib_DelayUs(50);
}

void setYellow()
{
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    
    Cy_SysLib_DelayUs(50);
    
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    
    Cy_SysLib_DelayUs(50);
}

void setGreen()
{
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    
    Cy_SysLib_DelayUs(50);
    
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);
    
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    
    Cy_SysLib_DelayUs(50);
}

void setBlue()
{
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    
    Cy_SysLib_DelayUs(50);
    
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);
    
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    
    Cy_SysLib_DelayUs(50);
}

void setPink()
{
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);

    Cy_SysLib_DelayUs(50);

    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);

    Cy_SysLib_DelayUs(50);
}

void setWhite()
{
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    
    Cy_SysLib_DelayUs(50);
    
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);
    
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    Cy_SCB_SPI_Write(WS_SPI_HW,0xCCC);
    
    Cy_SysLib_DelayUs(50);
}

void setNothing()
{
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    
    Cy_SysLib_DelayUs(50);
    
    Cy_SCB_SPI_Write(WS_SPI_HW,0b0);

    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    Cy_SCB_SPI_Write(WS_SPI_HW,0x888);
    
    Cy_SysLib_DelayUs(50);  
}

void clearAll()
{
    while (bb < 50){
        setNothing();
        bb++;
    }
    bb=0;
    Cy_SysLib_DelayUs(500);
}

void flicker()
{
    while(f < 5)
    {
        while (bb < 25) { 
            setBlue();
            setNothing();                  
            bb++;
        }                    
        Cy_SysLib_Delay(500);
        while (j < 50) { 
            setNothing();                   
            j++;
        } 
        Cy_SysLib_Delay(10);
        while(k < 25) {
            setNothing();                         
            setPink();                                                       
            k++;
        }
        Cy_SysLib_Delay(500);
        bb = 0;
        j = 0;
        k = 0;
        f++;
    }
    f = 0;
}

 /*   
void WS_LEDHandler()
{
    NVIC_ClearPendingIRQ(WS_LED_IRQ_cfg.intrSrc);
    flicker();
    clearAll();
    printf("Button Pressed\n\r");
}
*/

void SendMessageHandler()
{
    NVIC_ClearPendingIRQ(SendMessage_IRQ_cfg.intrSrc);
    i = rand() % 5;
    strcpy(advice, marriage[i]);
    strcat(advice, "\n\r");
    UART_PutString(advice);

}

void Button1PressedHandler()
{
    Cy_GPIO_Inv(LED1_PORT,LED1_NUM); 
    NVIC_ClearPendingIRQ(Button1Pressed_IRQ_cfg.intrSrc);
    button1Pressed = 1;
    Cy_SysLib_Delay(500);

}

void Button2PressedHandler()
{
    NVIC_ClearPendingIRQ(Button2Pressed_IRQ_cfg.intrSrc);
    button2Pressed = 1;
    Cy_SysLib_Delay(500);

}

void Button3PressedHandler()
{
    NVIC_ClearPendingIRQ(Button3Pressed_IRQ_cfg.intrSrc);
    button3Pressed = 1;
    Cy_SysLib_Delay(500);

}

void Button4PressedHandler()
{
    NVIC_ClearPendingIRQ(Button4Pressed_IRQ_cfg.intrSrc);
    button4Pressed = 1;
    Cy_SysLib_Delay(500);

}

void Button5PressedHandler()
{
    NVIC_ClearPendingIRQ(Button5Pressed_IRQ_cfg.intrSrc);
    button5Pressed = 1;
    Cy_SysLib_Delay(500);
    
}
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 

    UART_Start();
    setvbuf(stdin,NULL,_IONBF,0);
    CyDelay(100);
    
    //Interupt Configuration
    Cy_SysInt_Init(&SendMessage_IRQ_cfg, SendMessageHandler);
    NVIC_EnableIRQ(SendMessage_IRQ_cfg.intrSrc);
    
    Cy_SysInt_Init(&Button1Pressed_IRQ_cfg, Button1PressedHandler);
    NVIC_EnableIRQ(Button1Pressed_IRQ_cfg.intrSrc);
    
    Cy_SysInt_Init(&Button2Pressed_IRQ_cfg, Button2PressedHandler);
    NVIC_EnableIRQ(Button2Pressed_IRQ_cfg.intrSrc);
    
    Cy_SysInt_Init(&Button3Pressed_IRQ_cfg, Button3PressedHandler);
    NVIC_EnableIRQ(Button3Pressed_IRQ_cfg.intrSrc);
    
    Cy_SysInt_Init(&Button4Pressed_IRQ_cfg, Button4PressedHandler);
    NVIC_EnableIRQ(Button4Pressed_IRQ_cfg.intrSrc);
    
    Cy_SysInt_Init(&Button5Pressed_IRQ_cfg, Button5PressedHandler);
    NVIC_EnableIRQ(Button5Pressed_IRQ_cfg.intrSrc);
    
    
    cy_en_scb_spi_status_t initStatus;
   // cy_en_sysint_status_t sysSpistatus;
    
     initStatus = Cy_SCB_SPI_Init(WS_SPI_HW, &WS_SPI_config, &WS_SPI_context);
    if(initStatus != CY_SCB_SPI_SUCCESS)
    {
        //printf("SPI Start Failed\n\r");
        CY_ASSERT(0);
    }
    else
    {
       // printf("SPI Start Success\n\r");
    }
  
    Cy_SCB_SPI_Enable(WS_SPI_HW);
    Cy_SCB_SPI_SetActiveSlaveSelect(WS_SPI_HW, WS_SPI_SPI_SLAVE_SELECT0);
    
  //  Cy_SysInt_Init(&WS_LED_IRQ_cfg, WS_LEDHandler);
  //  NVIC_EnableIRQ(WS_LED_IRQ_cfg.intrSrc);   
    
    
    for(;;)
    {
        
        if (button1Pressed) {
            
            i = rand() % 5;
            strcpy(advice, marriage[i]);
            strcat(advice, "\n\r");
            UART_PutString(advice);
            flicker();
            clearAll();
            button1Pressed = 0;
            Cy_SysLib_Delay(500);
        }               
        
        
        if (button2Pressed) {
            i = rand() % 5;
            strcpy(advice, job[i]);
            strcat(advice, "\n\r");
            UART_PutString(advice);
            flicker();
            clearAll();
            button2Pressed = 0;
            Cy_SysLib_Delay(500);
        }          
        
        if (button3Pressed) {
            i = rand() % 5;
            strcpy(advice, love[i]);
            strcat(advice, "\n\r");
            UART_PutString(advice);
            flicker();
            clearAll();
            button3Pressed = 0;
            Cy_SysLib_Delay(500);
        }
        
        if (button4Pressed) {
            i = rand() % 5;
            strcpy(advice, children[i]);
            strcat(advice, "\n\r");
            UART_PutString(advice);
            flicker();
            clearAll();
            button4Pressed = 0;
            Cy_SysLib_Delay(500);
        }
        
        if (button5Pressed) {
            i = rand() % 5;
            strcpy(advice, randy[i]);
            strcat(advice, "\n\r");
            UART_PutString(advice);
            flicker();
            clearAll();
            button5Pressed = 0;
            Cy_SysLib_Delay(500);
        }
        
    }
}

/* [] END OF FILE */
