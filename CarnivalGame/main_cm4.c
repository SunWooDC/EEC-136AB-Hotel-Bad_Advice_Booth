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
#include "wave01.h"

uint32_t uI2sCount = 0;


void I2S_isr_Handler(void)
{   
    
    /* Write data for the left side */
    I2S_WriteTxData((int16) (waveData[uI2sCount]));
    
    /* Write data for the right side */
    I2S_WriteTxData((int16) (waveData[uI2sCount]));
            
    /* If reach the end of the wave, stop the ISR */
    if (uI2sCount < NUM_ELEMENTS)
    {
       uI2sCount++; 
    }   
    else
    {
        /* Disable the ISR */
        NVIC_DisableIRQ(I2S_isr_cfg.intrSrc);        
    }

    /* Clear I2S Interrupt */
    I2S_ClearInterrupt(I2S_INTR_TX_TRIGGER_Msk);
}



int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    
    Cy_SysInt_Init(&I2S_isr_cfg, I2S_isr_Handler);
    NVIC_EnableIRQ(I2S_isr_cfg.intrSrc);
    
    I2S_Start();     
    
    for(;;)
    {
        
        if (Cy_GPIO_Read(Button1_PORT, Button1_NUM) == 1 || Cy_GPIO_Read(Button2_PORT, Button2_NUM) == 1 || Cy_GPIO_Read(Button3_PORT, Button3_NUM) == 1 ||
        Cy_GPIO_Read(Button4_PORT, Button4_NUM) == 1 || Cy_GPIO_Read(Button5_PORT, Button5_NUM) == 1)           // = 1 for big dome button
        {
            Cy_GPIO_Inv(GreenLED_PORT,GreenLED_NUM);
            /* Check if the I2S ISR is disabled */
            CyDelay(2000);
            if (NVIC_GetEnableIRQ(I2S_isr_cfg.intrSrc))
            {
                /* I2S is enabled, do not do anything */
            }
            else /* I2S is disabled, re-start the wave buffer */
            {
                /* Restart the sound counter */
                uI2sCount = 0;
                
                /* Re-enabled the I2S ISR */
                NVIC_EnableIRQ(I2S_isr_cfg.intrSrc); 
            }
        }
        
     }
        
    }


/* [] END OF FILE */
