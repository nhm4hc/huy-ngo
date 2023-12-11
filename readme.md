modules within interrupt:
module 1 - Duy_DAC(PWM)_14 (dung timer1) 
	void Time1Config(void){
		TMOD|= 0x10;
		TH1 = 0xFF;
		TL1 = 0xff;
		ET1 = 1;
		EA = 1;
		TR1 = 1;
	}

	void Time1(void) interrupt 3{
		TH1 = 0xFF;
		TL1 = 0xFf;
		timer1++;
		count++;
	}
	
module 2 - Huy_button_8led7_18 (dung timer0) 
	void module2_delayMS(unsigned int t){
		TMOD = 0x01;
		TH0 = 0xFC;
		TL0 = 0x18;
		ET0 = 1;
		EA = 1;
		count =0;
		TR0 =1;
		while(count < t);
		ET0 = 0;
		TR0 =0;
	}

	void ISR_timer0(void) interrupt 1{
		TH0 = 0xFC;
		TL0 = 0x18;
		count++;
	}
	
module 3 - Quy_EEPROM24_13 (dung timer0) (only run on actual kit, not simulation kit)
	void Timer0Configuration(void){
		Num = 0;
		TMOD=0X02;
		TH0=0X9C;	
		TL0=0X9C;	
		ET0=1;
		EA=1;
		TR0=1;	
	}

	void DigDisplay(void) interrupt 1{ 
		P1 = disp[7];
		switch(Num)	 
		{
			case(7):
				module3_LSA=0; module3_LSB=0; module3_LSC=0; break;
			case(6):
				module3_LSA=1; module3_LSB=0; module3_LSC=0; break;
			case(5):
				module3_LSA=0; module3_LSB=1; module3_LSC=0; break;
			case(4):
				module3_LSA=1; module3_LSB=1; module3_LSC=0; break;
			case(3):
				module3_LSA=0; module3_LSB=0; module3_LSC=1; break;
			case(2):
				module3_LSA=1; module3_LSB=0; module3_LSC=1; break;
			case(1):
				module3_LSA=0; module3_LSB=1; module3_LSC=1; break;
			case(0):
				module3_LSA=1; module3_LSB=1; module3_LSC=1; break;	
		}
		DIG = disp[Num]; 
		Num++;
		if(Num>7)
			Num=0;
	}
module 4 - Son_PWM-DC_17 (dung timer1) 
	void module4_Time1Config(void){
		module4_timer1 = 0;
		TMOD|= 0x10;   
		TH1 = 0xFE; 
		TL1 = 0x0C;
		ET1 = 1;         
		EA = 1;
		TR1 = 1;            
	}

	void module4_Time1(void) interrupt 3{
		TH1 = 0xFE;  
		TL1 = 0x0C;
		module4_timer1++;    
	}
module 5 - Tai_Timer_8
	void TimerConfiguration(void){
	  TMOD = 0x01; 
	  TH0 = 0x3C;	 
	  TL0 = 0xB0; 
	  EA = 1;			 
	  ET0 = 1;		 
	  TR0 = 1;		 
	}

	void Timer0(void) interrupt 1{
		TH0 = 0x3C;	 
		TL0 = 0xB0;
		Time++;
	}
module 6 - Tam_buzzer_19
	void int0Init(void){
		TMOD&=0x0f;   
		TMOD|=0x01;   
		TH0=0xd8;
		TL0=0xef;   
		IE=0x82;
	}

	void int0(void)  interrupt 1 {  
		TH0=0xd8;   
		TL0=0xef;   
		n--;   
	}   

modules without interrupt:
module 7 - Huy_LCD12864_16
module 8 - Huy_LED7doan_3
module 9 - Kha_MotorULN2003_06
module 10 - Liem_LCD1602_7
module 11 - Thuc_LED_MATRIX_20  (Tri_15 the same module 11)
module 12 - Dat_LED+Button(Polling)_1_2

implement modules (within interrupt):
module 13 - TanLoc_Thoigianthuc_9
	void Timer0Configuration(){
		TMOD=0X02;
		TH0=0X9C;	
		TL0=0X9C;	
		ET0=1;
		EA=1;
		TR0=1;	
	}

	void DigDisplay() interrupt 1{
	//	TH0=0X9c;
	//	TL0=0X00;		
		DIG=0; 
		switch(Num)	 
		{
			case(7):
				LSA=0;LSB=0;LSC=0; break;
			case(6):
				LSA=1;LSB=0;LSC=0; break;
			case(5):
				LSA=0;LSB=1;LSC=0; break;
			case(4):
				LSA=1;LSB=1;LSC=0; break;
			case(3):
				LSA=0;LSB=0;LSC=1; break;
			case(2):
				LSA=1;LSB=0;LSC=1; break;
			case(1):
				LSA=0;LSB=1;LSC=1; break;
			case(0):
				LSA=1;LSB=1;LSC=1; break;	
		}
		DIG=disp[Num]; 
		Num++;
		if(Num>7)
			Num=0;
	}
module 14 - QuangLoc_DS18B20_11
	void Timer0Configuration(void){
		TMOD = 0X02; // Chon che do Timer, che do 2

		TH0 = 0X9C;  // Gia tri khoi tao cho Timer, 100us
		TL0 = 0X9C;  
		ET0 = 1;     // Bat ngat Timer 0
		EA = 1;      // Bat ngat toan cuc
		TR0 = 1;     // Khoi dong Timer 0
	}

	// Ham ngat Timer 0 de hien thi tren man hinh LED 7 doan
	void DigDisplay(void) interrupt 1{
		DIG = 0; // Tat hien thi
		switch(Num)  
		{
			case(7):
				LSA = 0; LSB = 0; LSC = 0; break;
			case(6):
				LSA = 1; LSB = 0; LSC = 0; break;
			case(5):
				LSA = 0; LSB = 1; LSC = 0; break;
			case(4):
				LSA = 1; LSB = 1; LSC = 0; break;
			case(3):
				LSA = 0; LSB = 0; LSC = 1; break;
			case(2):
				LSA = 1; LSB = 0; LSC = 1; break;
			case(1):
				LSA = 0; LSB = 1; LSC = 1; break;
			case(0):
				LSA = 1; LSB = 1; LSC = 1; break; 
		}
		DIG = disp[Num]; 
		Num++;
		if(Num > 7)
			Num = 0;
	}

-> integration module: super_module

note: module 12 Button (trouble)
