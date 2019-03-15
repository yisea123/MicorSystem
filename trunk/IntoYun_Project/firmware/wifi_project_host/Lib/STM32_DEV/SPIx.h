#ifndef __SPIX_H
#define __SPIX_H

#define EN_SPI2             1         //Enable SPI2
#define SPI2_SPEED          1         //Enable SPI2 speed controler 
#define SPI_SPEED_LOW       0
#define SPI_SPEED_HIGH      1

typedef enum{
    SPI_NULL = 0,
    SPIX1,
    SPIX2,
    SPIX3,
}SPI_ENUM;

void  SPIx_Init( uint8_t SPIX );
void  SPIX_SetSpeed( uint8_t SPIXN ,uint8_t SpeedSet );
uint8_t SPI1_ReadWriteByte( uint8_t TxData );
uint8_t SPI2_ReadWriteByte( uint8_t TxData );
uint8_t SPI3_ReadWriteByte( uint8_t TxData );

#endif  /* __SPIX_H */