/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup_LoRa (void)  {

// MODULE SETTINGS ----------------------------------------------
myLoRa = newLoRa();

myLoRa.hSPIx                 = &hspi3;
myLoRa.CS_port               = NSS_GPIO_Port;
myLoRa.CS_pin                = NSS_Pin;
myLoRa.reset_port            = RESET_GPIO_Port;
myLoRa.reset_pin             = RESET_Pin;
myLoRa.DIO0_port						 = DIO0_GPIO_Port;
myLoRa.DIO0_pin							 = DIO0_Pin;

myLoRa.frequency             = 868;					   // default = 433 MHz
myLoRa.spredingFactor        = SF_12;				   // default = SF_7
myLoRa.bandWidth			       = BW_250KHz;		   // default = BW_125KHz
myLoRa.crcRate				       = CR_4_5;		   // default = CR_4_5
myLoRa.power					       = POWER_20db;   // default = 20db
myLoRa.overCurrentProtection = 120; 				   // default = 100 mA
myLoRa.preamble				       = 7 ;		  	   // default = 8;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
   	ILI9341_Draw_Text("CONFIGURATION LORA MODULE", FONT1, 8, misto+=12, WHITE, BLACK, 0);
   	SPIx_SetSpeed(SPI_BR_8);
   	setup_LoRa ();
   	LoRa_reset(&myLoRa);
   	uint16_t ret = LoRa_init(&myLoRa);
   	SPIx_SetSpeed(SPI_BR_2);
   	if((ret != LORA_OK)||(w25q == 0)) {
   		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
   		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 120);
   		if(w25q)
   		ILI9341_Draw_Text("LORA NOT OK", FONT1, 8, misto +=12, RED, BLACK, 0);
   		HAL_Delay(2000);
   		HAL_NVIC_SystemReset();
   		while(1);
   	}
   	else  {

 		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
 		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 120);
          ILI9341_Draw_Text("LORA OK", FONT1, 8, misto +=12, WHITE, BLACK, 0);
  }
   	HAL_Delay(500);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
if(HAL_GPIO_ReadPin(DIO0_GPIO_Port, DIO0_Pin)){
		 //////////////////////////////////////

	SPIx_SetSpeed(SPI_BR_8);

if(LoRa_receive_Nom(&myLoRa, read_data, DATA) != 0){

	if(!strncmp((char*)read_data, "PIDY,", 5)){
		      Pidy((char*)read_data);
	}
	else if(strlen((char*)read_data)>24){
		      screen = 43;
		      trasa_lora = 1;
	}
	else if(!strncmp((char*)read_data, "BOD,", 4)){
		       Zapis_Bodu((char*)read_data);
	}
	else if(!strncmp((char*)read_data, "TRASA,", 6)){
		       Trasa_z_mobilu((char*)read_data);
	}
	else if((strlen((char*)read_data)>5)&&(strlen((char*)read_data)<16)){
	   	LoRa_reset(&myLoRa);
	   	LoRa_init(&myLoRa);
	   	LoRa_startReceiving(&myLoRa);
	}
	else if((strlen((char*)read_data)<2)){
	Rychlost_Lora((char)read_data[0]);   }
	else{
		;
	}
	//////////////////////////////////////////
	if((priznak != 1)&&(priznak != 5)&&(priznak != 43)&&(priznak != 44)){
    sprintf(temp_Buffer_LORA, "RSSI %d %c",LoRa_getRSSI(&myLoRa), (char)read_data[0]);
	ILI9341_Draw_Text(temp_Buffer_LORA, FONT1, 210, 8, WHITE, BLACK, 1);
///////////////////////////////////////////////////////////////////////////////////////////////////////
       }
	else {
		 Lora_poslat = 0;
	     Cas_displej = 0;
	  }
	 }
    SPIx_SetSpeed(SPI_BR_2);
	}
	if((screen != 6)&&(screen != 8)&&(screen != 42)&&(screen != 43)&&(screen != 4)&&(screen != 5)&&(screen != 1)&&(screen != 35)&&(screen != 37)&&(screen != 38)){
	    if((screen == 32)&&(screen32 == 32)){
	    	 if(priznak == 5)
	    	     screen = 5;
	    else if(priznak == 4)
	    	     screen = 4;
	    else if(priznak == 1)
	    	     screen = 1;
	    }
	    else screen = screen32;
	}
	////////////////////////////////////
    NVIC_EnableIRQ(USART6_IRQn);
 	HAL_UART_Receive_DMA(GPS_USART, (uint8_t *)rxbuffer, 128);
 	HAL_Delay(80);
 	IDLE_AKTIV();
 	/////////////////////////////
 	if((priznak != 5)&&(priznak != 4)){
    mereni_vypnuto = 0;
    mereni = 0;
    lora_vypnuto = 0;
    Lora_poslat = 0;
 	}
 	if(priznak_hour == 0){
    hodiny_p = 0;
    hodiny = 0;
 	}
    vyskoc = 0;
    if(priznak != 1){
    mereniLED_vypnuto = 1;
    mereni_LED = 0;
    }
    ////////////////////////////////
	NVIC_EnableIRQ(EXTI1_IRQn);
	    break;
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
void Jedu(char *JED)
{
SPIx_SetSpeed(SPI_BR_8);
sprintf((char*)send_data, "%sW-P\n\r",JED);
LoRa_transmit(&myLoRa,(uint8_t*)send_data, length((uint8_t*)send_data)+1, 100);
SPIx_SetSpeed(SPI_BR_2);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
             SPIx_SetSpeed(SPI_BR_8);
             LoRa_startReceiving(&myLoRa);
          // LoRa_gotoMode(&myLoRa, TRANSMIT_MODE);
             SPIx_SetSpeed(SPI_BR_2);
