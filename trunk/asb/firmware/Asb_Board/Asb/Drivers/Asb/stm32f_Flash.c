/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f_Flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint32_t GetSector(uint32_t Address);

/* Export functions ---------------------------------------------------------*/
void stm32fdisk_Init(void)
{
    /* Unlock the Program memory */
    HAL_FLASH_Unlock();

    /* Clear all FLASH flags */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |\
    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR| FLASH_FLAG_PGSERR);

    /* Unlock the Program memory */
    HAL_FLASH_Lock();   
}

uint32_t stm32fdisk_Read(uint32_t destination, uint8_t *p_source, uint32_t length)
{
    uint32_t i = 0, size = 0;
    uint32_t readLength;
    uint32_t readData;

    readLength = length/4;
    readLength +=  ((length%4) == 0) ? 0 : 1;
  
    for ( i = 0; i < readLength; i++)
    {     
        readData =  (*(uint32_t*)(destination + 4 * i));  
        p_source[size++] = (uint8_t)(readData >> 24);
        p_source[size++] = (uint8_t)(readData >> 16);
        p_source[size++] = (uint8_t)(readData >> 8);
        p_source[size++] = (uint8_t)(readData);
    }    

    return size;   
}

/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  destination: start address for target location
  * @param  p_source: pointer on buffer with data to write
  * @param  length: length of data buffer (unit is 32-bit word)
  * @retval uint32_t 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t stm32fdisk_Write(uint32_t destination, const uint8_t *p_source, uint32_t length)
{
  uint32_t status = FLASHIF_OK;
  uint32_t wIndex = 0;
  uint32_t CopyIndex = 0;
  uint32_t dataLength = 0;
  uint32_t Wdata;

  
  dataLength = length/4;
  dataLength +=  ((length%4) == 0) ? 0 : 1;
  
  HAL_FLASH_Unlock();
  while ( wIndex  < dataLength )
  {
      Wdata =  p_source[CopyIndex++]<<24;
      Wdata |= p_source[CopyIndex++]<<16;
      Wdata |= p_source[CopyIndex++]<<8;
      Wdata |= p_source[CopyIndex++];    
       
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, destination, Wdata) == HAL_OK)
      {
          destination = destination + 4;
          wIndex++;
      }
      else
      {
        /* Error occurred while writing data in Flash memory.
           User can add here some code to deal with this error */
         status = FLASHIF_WRITING_ERROR;
      }
  }  

  HAL_FLASH_Lock();

  return status;
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  This function does an erase of  user flash area
  * @param  start: start of user flash area
  * @retval FLASHIF_OK : user flash area successfully erased
  *         FLASHIF_ERASEKO : error occurred
  */
uint32_t stm32fdisk_Erase(uint32_t Addr, uint32_t size)
{
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t  SectorError = 0;
    uint8_t  res = FLASHIF_OK;
    uint32_t FirstSector = 0;
    uint32_t NbOfSectors = 0;
		
    /*Variable used for Erase procedure*/
    /* Unlock the Flash to enable the flash control register access *************/
    HAL_FLASH_Unlock();
    
    /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

    /* Fill EraseInit structure*/
    FirstSector = GetSector(Addr);
    
    /* Get the number of sector to erase from 1st sector*/
    NbOfSectors = GetSector(Addr + size) - FirstSector + 1;
    EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector        = FirstSector;
    EraseInitStruct.NbSectors     = NbOfSectors;
		
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK)
    {
      res = FLASHIF_ERASE_ERRROR; 
    }

    HAL_FLASH_Lock();  

    return res;
}



/**
  * @brief  Gets the sector of a given address
  * @param  None
  * @retval The sector of a given address
  */
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10;  
  }
  else /* (Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11) */
  {
    sector = FLASH_SECTOR_11;
  }

  return sector;
}

/* End of this file */