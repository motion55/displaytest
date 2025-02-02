/**
  ******************************************************************************
  * File Name          : Target/lcd_io.c
  * Description        : This file provides code for the configuration
  *                      of the LCD Driver instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lcd_os.h"
#include "lcd_io.h"

/** @addtogroup DISPLAY
  * @brief      DISPLAY Software Expansion Pack.
  * @{
  */
/** @defgroup LCD_Driver LCD Driver
  * @brief    LCD Driver API.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

#define BSP_LCD_CHECK_PARAMS(Instance)

/* Exported variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

static void             *LcdCompObj = NULL;
static LCD_Drv_t        *LcdDrv = NULL;
static ST7789V_IO_t     IOCtx = { 0 };
static ST7789V_Object_t ObjCtx = { 0 };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

static int32_t LCD_SetupBaudRateForReadOperations(uint32_t *UserBaudRatePrescaler);
static int32_t LCD_SetupBaudRateForWriteOperations(uint32_t UserBaudRatePrescaler);
static int32_t LCD_Probe(uint32_t Instance, uint32_t Orientation);
static int32_t LCD_IO_GetTick(void);
static int32_t LCD_IO_Delay(uint32_t Delay);
static int32_t LCD_IO_Init(void);
static int32_t LCD_IO_DeInit(void);
static int32_t LCD_IO_WriteReg(volatile uint8_t *Reg, uint32_t Length);
static int32_t LCD_IO_ReadReg(volatile uint8_t *Reg, uint32_t Length);
static int32_t LCD_IO_SendData(uint8_t *pData, uint32_t Length);
static int32_t LCD_IO_SendDataDMA(uint8_t *pData, uint32_t Length);
static int32_t LCD_IO_RecvData(uint8_t *pData, uint32_t Length);
static int32_t LCD_IO_RecvDataDMA(uint8_t *pData, uint32_t Length);

/* Deprecated functions ------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup LCD_Exported_Functions LCD Exported Functions
  * @brief    LCD Drivers API.
  * @{
  */
/**
  * @brief  Initializes the LCD Controller.
  * @param  Instance:     LCD Instance.
  * @param  Orientation:  LCD Orientation.
  *         This parameter can be one of the following values:
  *          @arg @ref LCD_ORIENTATION_PORTRAIT           Portrait orientation choice of LCD screen
  *          @arg @ref LCD_ORIENTATION_LANDSCAPE          Landscape orientation choice of LCD screen
  *          @arg @ref LCD_ORIENTATION_PORTRAIT_ROT180    Portrait rotated 180° orientation choice of LCD screen
  *          @arg @ref LCD_ORIENTATION_LANDSCAPE_ROT180   Landscape rotated 180° orientation choice of LCD screen
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_Init(uint32_t Instance, uint32_t Orientation)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  if ((Instance >= LCD_INSTANCES_NBR ) || (Orientation > LCD_ORIENTATION_LANDSCAPE_ROT180))
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* LCD OS Initialize */
    if(LCD_OS_Initialize(0) != LCD_OS_ERROR_NONE)
    {
      ret = BSP_ERROR_NO_INIT;
    }
    else
    {
      /* Probe the LCD Component driver */
      ret = LCD_Probe(Instance, Orientation);
    }
  }

  return ret;
}

/**
  * @brief  De-Initializes the LCD resources.
  * @param  Instance:     LCD Instance.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_DeInit(uint32_t Instance)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  BSP_LCD_CHECK_PARAMS(Instance);

  if(LcdDrv->DeInit != NULL)
  {
    if(LcdDrv->DeInit(LcdCompObj) < 0)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}

/**
  * @brief  Sets the LCD Orientation.
  * @param  Instance:     LCD Instance.
  * @param  Orientation:  New LCD Orientation.
  *         This parameter can be one of the following values:
  *          @arg @ref LCD_ORIENTATION_PORTRAIT           Portrait orientation choice of LCD screen.
  *          @arg @ref LCD_ORIENTATION_LANDSCAPE          Landscape orientation choice of LCD screen.
  *          @arg @ref LCD_ORIENTATION_PORTRAIT_ROT180    Portrait rotated 180° orientation choice of LCD screen.
  *          @arg @ref LCD_ORIENTATION_LANDSCAPE_ROT180   Landscape rotated 180° orientation choice of LCD screen.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_SetOrientation(uint32_t Instance, uint32_t Orientation)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  BSP_LCD_CHECK_PARAMS(Instance);

  if(LCD_OS_TryLock(Instance, LCD_OS_TIMEOUT_BUSY) != LCD_OS_ERROR_NONE)
  {
    ret = BSP_ERROR_BUSY;
  }
  else
  {
    if(LcdDrv->SetOrientation != NULL)
    {
      if(LcdDrv->SetOrientation(LcdCompObj, Orientation) < 0)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }

    LCD_OS_Unlock(Instance);
  }

  return ret;
}

/**
  * @brief  Gets the LCD Orientation.
  * @param  Instance:     LCD Instance.
  * @param  pOrientation: Pointer to Current LCD Orientation.
  *         This parameter will be set to one of the following values:
  *          @arg @ref LCD_ORIENTATION_PORTRAIT           Portrait orientation choice of LCD screen.
  *          @arg @ref LCD_ORIENTATION_LANDSCAPE          Landscape orientation choice of LCD screen.
  *          @arg @ref LCD_ORIENTATION_PORTRAIT_ROT180    Portrait rotated 180° orientation choice of LCD screen.
  *          @arg @ref LCD_ORIENTATION_LANDSCAPE_ROT180   Landscape rotated 180° orientation choice of LCD screen.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_GetOrientation(uint32_t Instance, uint32_t *pOrientation)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  BSP_LCD_CHECK_PARAMS(Instance);

  if(LCD_OS_TryLock(Instance, LCD_OS_TIMEOUT_BUSY) != LCD_OS_ERROR_NONE)
  {
    ret = BSP_ERROR_BUSY;
  }
  else
  {
    if(LcdDrv->GetOrientation != NULL)
    {
      if(LcdDrv->GetOrientation(LcdCompObj, pOrientation) < 0)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }

    LCD_OS_Unlock(Instance);
  }

  return ret;
}

/**
  * @brief  Gets the LCD X size.
  * @param  Instance:     LCD Instance.
  * @param  pXSize:       Pointer to Used LCD X size.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_GetXSize(uint32_t Instance, uint32_t *pXSize)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  BSP_LCD_CHECK_PARAMS(Instance);

  if(LCD_OS_TryLock(Instance, LCD_OS_TIMEOUT_BUSY) != LCD_OS_ERROR_NONE)
  {
    ret = BSP_ERROR_BUSY;
  }
  else
  {
    if(LcdDrv->GetXSize != NULL)
    {
      if(LcdDrv->GetXSize(LcdCompObj, pXSize) < 0)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }

    LCD_OS_Unlock(Instance);
  }

  return ret;
}

/**
  * @brief  Gets the LCD Y size.
  * @param  Instance:     LCD Instance.
  * @param  pYSize:       Pointer to Used LCD Y size.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_GetYSize(uint32_t Instance, uint32_t *pYSize)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  BSP_LCD_CHECK_PARAMS(Instance);

  if(LCD_OS_TryLock(Instance, LCD_OS_TIMEOUT_BUSY) != LCD_OS_ERROR_NONE)
  {
    ret = BSP_ERROR_BUSY;
  }
  else
  {
    if(LcdDrv->GetYSize != NULL)
    {
      if(LcdDrv->GetYSize(LcdCompObj, pYSize) < 0)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }

    LCD_OS_Unlock(Instance);
  }

  return ret;
}

/**
  * @brief  Switch On the display.
  * @param  Instance:     LCD Instance.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_DisplayOn(uint32_t Instance)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  BSP_LCD_CHECK_PARAMS(Instance);

  if(LCD_OS_TryLock(Instance, LCD_OS_TIMEOUT_BUSY) != LCD_OS_ERROR_NONE)
  {
    ret = BSP_ERROR_BUSY;
  }
  else
  {
    if(LcdDrv->DisplayOn != NULL)
    {
      if(LcdDrv->DisplayOn(LcdCompObj) < 0)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }

    LCD_OS_Unlock(Instance);
  }

  return ret;
}

/**
  * @brief  Switch Off the display.
  * @param  Instance:     LCD Instance.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_DisplayOff(uint32_t Instance)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  BSP_LCD_CHECK_PARAMS(Instance);

  if(LCD_OS_TryLock(Instance, LCD_OS_TIMEOUT_BUSY) != LCD_OS_ERROR_NONE)
  {
    ret = BSP_ERROR_BUSY;
  }
  else
  {
    if(LcdDrv->DisplayOff != NULL)
    {
      if(LcdDrv->DisplayOff(LcdCompObj) < 0)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }

    LCD_OS_Unlock(Instance);
  }

  return ret;
}

/**
  * @brief  Send data to the selected the LCD GRAM.
  * @param  Instance:     LCD Instance.
  * @param  pData:        Pointer to data to write to LCD GRAM.
  * @param  Length:       Length of data to write to LCD GRAM.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_WriteData(uint32_t Instance, uint8_t *pData, uint32_t Length)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  BSP_LCD_CHECK_PARAMS(Instance);

  if(LCD_OS_TryLock(Instance, LCD_OS_TIMEOUT_BUSY) != LCD_OS_ERROR_NONE)
  {
    ret = BSP_ERROR_BUSY;
  }
  else
  {
    if(IOCtx.SendData)
    {
      if(IOCtx.SendData(pData, Length) < 0)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }

    }

    LCD_OS_Unlock(Instance);
  }

  return ret;
}

/**
  * @brief  Send data to select the LCD GRAM.
  * @param  Instance:     LCD Instance.
  * @param  pData:        Pointer to data to write to LCD GRAM.
  * @param  Length:       Length of data to write to LCD GRAM.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_WriteDataDMA(uint32_t Instance, uint8_t *pData, uint32_t Length)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  BSP_LCD_CHECK_PARAMS(Instance);

  if(LCD_OS_TryLock(Instance, LCD_OS_TIMEOUT_BUSY) != LCD_OS_ERROR_NONE)
  {
    ret = BSP_ERROR_BUSY;
  }
  else
  {
    if(IOCtx.SendDataDMA)
    {
      if(IOCtx.SendDataDMA(pData, Length) < 0)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
  }

  return ret;
}

/**
  * @brief  Sets a display window.
  * @param  Instance:     LCD Instance.
  * @param  Xpos:         Specifies the X position.
  * @param  Ypos:         Specifies the Y position.
  * @param  Height:       Specifies the height of the rectangle to fill.
  * @param  Width:        Specifies the width of the rectangle to fill.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_SetDisplayWindow(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height)
{
  int32_t ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;

  BSP_LCD_CHECK_PARAMS(Instance);

  if(LCD_OS_TryLock(Instance, LCD_OS_TIMEOUT_BUSY) != LCD_OS_ERROR_NONE)
  {
    ret = BSP_ERROR_BUSY;
  }
  else
  {
    if(LcdDrv->SetDisplayWindow != NULL)
    {
      /* Fill the Rectangle lines on LCD */
      if (LcdDrv->SetDisplayWindow(LcdCompObj, Xpos, Ypos, Width, Height) < 0)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }

    LCD_OS_Unlock(Instance);
  }

  return ret;
}

/**
  * @brief  Send RGB data to select the LCD GRAM.
  * @param  Instance:     LCD Instance.
  * @param  UseDMA:       Specifies if DMA will be used for data Transferring.
  * @param  pData:        Pointer to data to write to LCD GRAM.
  * @param  Xpos:         Specifies the X position.
  * @param  Ypos:         Specifies the Y position.
  * @param  Height:       Specifies the height of the rectangle to fill.
  * @param  Width:        Specifies the width of the rectangle to fill.
  * @retval int32_t:      BSP status.
  */
int32_t BSP_LCD_FillRGBRect(uint32_t Instance, uint8_t UseDMA, uint8_t *pData, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height)
{
  int32_t ret = BSP_ERROR_NONE;

  /* Set display window */
  if(BSP_LCD_SetDisplayWindow(Instance, Xpos, Ypos, Width, Height) == BSP_ERROR_NONE)
  {
    /* Send Pixels Data */
    if(UseDMA)
    {
      ret = BSP_LCD_WriteDataDMA(Instance, pData, (2*Width*Height));
    }
    else
    {
      ret = BSP_LCD_WriteData(Instance, pData, (2*Width*Height));
    }
  }
  else
  {
    ret = BSP_ERROR_BUS_FAILURE;
  }

  return ret;
}

/**
  * @brief  Get the status of the LCD Transfer.
  * @param  Instance:     LCD Instance.
  * @retval uint8_t:      Zero if no Transfer, Transfer Operation code otherwise.
  */
uint8_t BSP_LCD_GetTransferStatus(uint32_t Instance)
{
  BSP_LCD_CHECK_PARAMS(Instance);

  return LCD_OS_IsLocked(Instance);
}

/**
  * @brief  Wait for until complete LCD Transfer.
  * @param  Instance:     LCD Instance.
  */
void BSP_LCD_WaitForTransferToBeDone(uint32_t Instance)
{
  if (Instance < LCD_INSTANCES_NBR)
  {
    LCD_OS_WaitForTransferToBeDone(Instance);
  }
}

/**
  * @brief  Signal Transfer Event.
  * @param  Instance:     LCD Instance.
  */
__WEAK void BSP_LCD_SignalTransferDone(uint32_t Instance)
{
  if (Instance < LCD_INSTANCES_NBR)
  {
    /* This is the user's Callback to be implemented at the application level */
  }
}

/**
  * @brief  Signal Transfer Event.
  * @param  Instance:     LCD Instance.
  * @param  State:        Event value.
  * @param  Line:         Line counter.
  */
__WEAK void BSP_LCD_SignalTearingEffectEvent(uint32_t Instance, uint8_t State, uint16_t Line)
{
  /* Prevent unused argument(s) compilation warning */;
  UNUSED(Line);

  if (Instance < LCD_INSTANCES_NBR)
  {
    /* This is the user's Callback to be implemented at the application level */
    if(State)
    {
      /* TE event is done : de-allow display refresh */
    }
    else
    {
      /* TE event is received : allow display refresh */
    }
  }
}
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/* USER CODE BEGIN PF */

/* USER CODE END PF */

/**
  * @brief  Register Bus IOs if ST7789V ID is OK
  * @param  Instance:     LCD Instance.
  * @param  Orientation:  LCD Orientation
  * @retval int32_t:      BSP status.
  */
static int32_t LCD_Probe(uint32_t Instance, uint32_t Orientation)
{
  int32_t ret = BSP_ERROR_NONE;
  ST7789V_InitParams_t ST7789V_InitParams;
  uint32_t UserBaudRatePrescaler = 0;
  uint32_t id = 0;

  /* Configure the lcd driver : map to LCD_IO function*/
  IOCtx.Init             = LCD_IO_Init;
  IOCtx.DeInit           = LCD_IO_DeInit;
  IOCtx.ReadReg          = LCD_IO_ReadReg;
  IOCtx.WriteReg         = LCD_IO_WriteReg;
  IOCtx.SendData         = LCD_IO_SendData;
  IOCtx.SendDataDMA      = LCD_IO_SendDataDMA;
  IOCtx.RecvData         = LCD_IO_RecvData;
  IOCtx.RecvDataDMA      = LCD_IO_RecvDataDMA;
  IOCtx.GetTick          = LCD_IO_GetTick;
  IOCtx.Delay            = LCD_IO_Delay;

  if(ST7789V_RegisterBusIO(&ObjCtx, &IOCtx) != ST7789V_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    LcdCompObj = &ObjCtx;

    ret = LCD_SetupBaudRateForReadOperations(&UserBaudRatePrescaler);
    if(ret == BSP_ERROR_NONE)
    {
      if((ST7789V_LCD_Driver.ReadID(LcdCompObj, &id) == ST7789V_OK) && (id == ST7789V_ID))
      {
        ret = LCD_SetupBaudRateForWriteOperations(UserBaudRatePrescaler);
        if(ret == BSP_ERROR_NONE)
        {
          /* LCD Initialization */
          LcdDrv = (LCD_Drv_t *)&ST7789V_LCD_Driver;

          ObjCtx.IsInitialized = 0;

          ST7789V_InitParams.Endian         = ST7789V_ENDIAN_LITTLE;
          ST7789V_InitParams.SwapRB         = 0;
          ST7789V_InitParams.ColorCoding    = ST7789V_FORMAT_DEFAULT;
          ST7789V_InitParams.Orientation    = Orientation;
          ST7789V_InitParams.TEScanline     = 0;
          ST7789V_InitParams.TEMode         = ST7789V_TE_DISABLED;
          ST7789V_InitParams.Timings.hsync  = ST7789V_HSYNC;
          ST7789V_InitParams.Timings.hbp    = ST7789V_HBP;
          ST7789V_InitParams.Timings.hfp    = ST7789V_HFP;
          ST7789V_InitParams.Timings.vsync  = ST7789V_VSYNC;
          ST7789V_InitParams.Timings.vbp    = ST7789V_VBP;
          ST7789V_InitParams.Timings.vfp    = ST7789V_VFP;
          if(LcdDrv->Init(LcdCompObj, &ST7789V_InitParams) != ST7789V_OK)
          {
            ret = BSP_ERROR_COMPONENT_FAILURE;
          }
        }
      }
      else
      {
        ret = BSP_ERROR_UNKNOWN_COMPONENT;
      }
    }
  }

  return ret;
}

/**
  * @brief  Provide a tick value in millisecond.
  * @retval int32_t:  Tick value.
  */
static int32_t LCD_IO_GetTick(void)
{
  uint32_t ret;
  ret = HAL_GetTick();
  return (int32_t)ret;
}

/**
  * @brief  LCD IO delay
  * @param  Delay:    Delay in ms
  * @retval int32_t:  Error status
  */
static int32_t LCD_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
  return BSP_ERROR_NONE;
}

/**
  * @brief  Writes register address.
  * @param  Reg: Register to be written
  */
__STATIC_INLINE void FMC_BANK1_WriteReg(uint8_t Reg)
{
    /* Write 16-bits Index, then write register */
    *(uint8_t *)(FMC_BANK1_REG) = Reg;
    __DSB();
}

/**
  * @brief  Writes register value.
  * @param  Data: Data to be written
  */
__STATIC_INLINE void FMC_BANK1_WriteData(uint16_t Data)
{
    /* Write 16-bits Reg */
    *(uint8_t *)(FMC_BANK1_MEM) = Data;
    __DSB();
}

/**
  * @brief  Reads register value.
  * @retval Read value
  */
__STATIC_INLINE uint16_t FMC_BANK1_ReadData(void)
{
    return *(uint8_t *)(FMC_BANK1_MEM);
}

/**
  * @brief  Setup SPI Baud Rate for Read Operations
  * @param  UserBaudRatePrescaler User's Baud Rate
  * @retval BSP status
  */
static int32_t LCD_SetupBaudRateForReadOperations(uint32_t *UserBaudRatePrescaler)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(UserBaudRatePrescaler);

  return BSP_ERROR_NONE;
}

/**
  * @brief  Setup SPI Baud Rate for Write Operations
  * @param  UserBaudRatePrescaler User's Baud Rate
  * @retval BSP status
  */
static int32_t LCD_SetupBaudRateForWriteOperations(uint32_t UserBaudRatePrescaler)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(UserBaudRatePrescaler);

  return BSP_ERROR_NONE;
}

/********************************* LINK LCD ***********************************/
/**
  * @brief  Initializes LCD low level.
  * @retval BSP status
  */
static int32_t LCD_IO_Init(void)
{
  /* USER CODE BEGIN LCD_IO_Init 1 */

  /* USER CODE END LCD_IO_Init 1 */

  LCD_RST_LOW();
  LCD_IO_Delay(120);
  LCD_RST_HIGH();
  LCD_IO_Delay(120);

  /* USER CODE BEGIN LCD_IO_Init 2 */

  /* USER CODE END LCD_IO_Init 2 */

  return BSP_ERROR_NONE;
}

/**
  * @brief  DeInitializes LCD low level
  * @retval BSP status
  */
static int32_t LCD_IO_DeInit(void)
{
  /* USER CODE BEGIN LCD_IO_DeInit */

  return BSP_ERROR_NONE;

  /* USER CODE END LCD_IO_DeInit */
}

/**
  * @brief  Writes register on LCD register.
  * @param  Reg    Register to be written
  * @param  Length length of data be read from the LCD GRAM
  * @retval BSP status
  */
static int32_t LCD_IO_WriteReg(volatile uint8_t *Reg, uint32_t Length)
{
  /* There is only one register which is the command register */
  FMC_BANK1_WriteReg(*Reg);

  return BSP_ERROR_NONE;
}

/**
  * @brief  Read register on LCD register.
  * @param  Reg    Register to be read
  * @param  Length length of data be read from the LCD GRAM
  * @retval BSP status
  */
static int32_t LCD_IO_ReadReg(volatile uint8_t *Reg, uint32_t Length)
{
  /* USER CODE BEGIN LCD_IO_ReadReg */

  return BSP_ERROR_FEATURE_NOT_SUPPORTED;

  /* USER CODE END LCD_IO_ReadReg */
}

/**
  * @brief  Send data to select the LCD GRAM.
  * @param  pData  pointer to data to write to LCD GRAM.
  * @param  Length length of data to write to LCD GRAM
  * @retval Error status
  */
static int32_t LCD_IO_SendData(uint8_t *pData, uint32_t Length)
{
  uint32_t  i;

  for (i = 0; i < (Length / 2); i+=2)
  {
    FMC_BANK1_WriteData(pData[i]);
  }

  return BSP_ERROR_NONE;
}

/**
  * @brief  Send data to select the LCD GRAM.
  * @param  pData  pointer to data to write to LCD GRAM.
  * @param  Length length of data to write to LCD GRAM
  * @retval Error status
  */
static int32_t LCD_IO_SendDataDMA(uint8_t *pData, uint32_t Length)
{
  /* USER CODE BEGIN LCD_IO_SendDataDMA */

  return BSP_ERROR_FEATURE_NOT_SUPPORTED;

  /* USER CODE END LCD_IO_SendDataDMA */
}

/**
  * @brief  Receive data from selected LCD GRAM.
  * @param  pData  pointer to data to read to from selected LCD GRAM.
  * @param  Length length of data to read from selected LCD GRAM
  * @retval Error status
  */
static int32_t LCD_IO_RecvData(uint8_t *pData, uint32_t Length)
{
  uint32_t  i;

  /* Write Register value */
  FMC_BANK1_WriteReg(*pData);

  /* Read data */
  for (i = 0; i < Length; i++)
  {
    pData[i] = FMC_BANK1_ReadData();
  }

  return BSP_ERROR_NONE;
}

/**
  * @brief  Receive data using DMA from selected LCD GRAM.
  * @param  pData  pointer to data to read to from selected LCD GRAM.
  * @param  Length length of data to read from selected LCD GRAM
  * @retval Error status
  */
static int32_t LCD_IO_RecvDataDMA(uint8_t *pData, uint32_t Length)
{
  /* USER CODE BEGIN LCD_IO_RecvDataDMA */

  return BSP_ERROR_FEATURE_NOT_SUPPORTED;

  /* USER CODE END LCD_IO_RecvDataDMA */
}
/**
  * @}
  */
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
