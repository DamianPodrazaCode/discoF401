#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
    
#endif
    // 84MHz, dla USB i bez USB
    void SystemClock_Config(void) {
        __HAL_RCC_PWR_CLK_ENABLE();
        __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
        RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
        RCC_OscInitStruct.PLL.PLLM = 4;
        RCC_OscInitStruct.PLL.PLLN = 168;
        RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
        RCC_OscInitStruct.PLL.PLLQ = 7;
        HAL_RCC_OscConfig(&RCC_OscInitStruct);
        RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
        HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
        HAL_RCC_EnableCSS();
        SystemCoreClock = 84000000UL;
        HAL_SYSTICK_Config(SystemCoreClock / (1000U / uwTickFreq));
    }
#ifdef __cplusplus
}
#endif
