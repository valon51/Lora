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
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HAL_Delay(200);
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(HAL_GPIO_ReadPin(DIO0_GPIO_Port, DIO0_Pin)){
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
 //////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////
void Lora_Senden(char* tem){
SPIx_SetSpeed(SPI_BR_8);
LoRa_transmit(&myLoRa,(uint8_t*)tem, length((uint8_t*)tem)+1, 10);
SPIx_SetSpeed(SPI_BR_2);
}

    
