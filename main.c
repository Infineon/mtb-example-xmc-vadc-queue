/*******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the XMC MCU: VADC QUEUE Example for
*              ModusToolbox.
*              This example shows how to convert multiple channels in a
*              dedicated sequence using the queue source. The CCU4 is used to
*              trigger the queue periodically. The ADC results will be
*              displayed on UART Terminal.
*
* Related Document: See README.md
*
********************************************************************************
*
* Copyright (c) 2015-2022, Infineon Technologies AG
* All rights reserved.
*
* Boost Software License - Version 1.0 - August 17th, 2003
*
* Permission is hereby granted, free of charge, to any person or organization
* obtaining a copy of the software and accompanying documentation covered by
* this license (the "Software") to use, reproduce, display, distribute,
* execute, and transmit the Software, and to prepare derivative works of the
* Software, and to permit third-parties to whom the Software is furnished to
* do so, all subject to the following:
*
* The copyright notices in the Software and this entire statement, including
* the above license grant, this restriction and the following disclaimer,
* must be included in all copies of the Software, in whole or in part, and
* all derivative works of the Software, unless such copies or derivative
* works are solely in the form of machine-executable object code generated by
* a source language processor.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
* SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
* FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*
*******************************************************************************/

#include "cybsp.h"
#include "cy_utils.h"
#include <stdio.h>
#include "cy_retarget_io.h"

#define ENABLE_XMC_DEBUG_PRINT (0)

#if ENABLE_XMC_DEBUG_PRINT
static bool LOOP_ENTER = false;
#endif

/*******************************************************************************
* Global Variable
*******************************************************************************/
XMC_VADC_RESULT_SIZE_t adc_result[16] = { 0 };

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function.
* It sets up a VADC using Queue scan source.
* The Queue source is continuously requesting the conversion.
* The result is stored in the result register and read out in the while loop.
* The result values will be printed in UART Terminal.
* On board LED glows high when ADC counts are more than 2000.
*
* Parameters:
*  none
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t res;

    /* Initialize the device and board peripherals */
    res = cybsp_init();
    if (res != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize retarget-io to use the debug UART port */
    cy_retarget_io_init(CYBSP_DEBUG_UART_HW);
    printf("ADC Conversion starts\r\n");

    while (1U)
    {
        /* Retrieve result from result register. */
        adc_result[1] = XMC_VADC_GROUP_GetResult(VADC_G0, 1);
        adc_result[2] = XMC_VADC_GROUP_GetResult(VADC_G0, 3);
        adc_result[3] = XMC_VADC_GROUP_GetResult(VADC_G0, 5);

    #if ENABLE_XMC_DEBUG_PRINT
        if(!LOOP_ENTER)
        {
        printf("Conversion complete\r\n");
        LOOP_ENTER = true;
        }
    #else
        /* Print the result values */
        printf("ADC result value of channel 1: %x, channel 3: %x and channel 5: %x \r\n", adc_result[1], adc_result[2], adc_result[3]);
        XMC_Delay(500);
    #endif
    }
    return 1;
}
/* [] END OF FILE */
