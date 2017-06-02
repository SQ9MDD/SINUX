#include "Arduino.h"
#include "sinux_sa522.h"

sinux_sa522::sinux_sa522(){
}

void sinux_sa522::INIT(int net_address){
	_net_address = net_address;
	pinMode(_bo1,OUTPUT);				//BO1
	pinMode(_bo2,OUTPUT);				//BO2
	pinMode(_bo3,OUTPUT);				//BO3
	pinMode(_bo4,OUTPUT);				//BO4
	pinMode(_bo1A,OUTPUT);				//BO1 LED
	pinMode(_bo2A,OUTPUT);				//BO2 LED
	pinMode(_bo3A,OUTPUT);				//BO3 LED
	pinMode(_bo4A,OUTPUT);				//BO4 LED
	pinMode(_HB,OUTPUT);				//HeartBeat LED
	pinMode(_PTT,OUTPUT);				//PTT for RS485 operation
	pinMode(_ui1, INPUT);				//UI1
	pinMode(_ui2, INPUT);				//UI2
	pinMode(_ui3, INPUT);				//UI3
	pinMode(_ui4, INPUT);				//UI4
	pinMode(_ui5, INPUT);				//UI5
	delay(100);
	_time_to_tick = millis() + 1000;
	digitalWrite(_HB,HIGH);
	Serial.begin(115200);
		
	if(net_address >= 1){
		//if address bigger than 0 then sent presentation 4 BO and initial state
		digitalWrite(_PTT,HIGH);
		delay(50);
		Serial.print(String(net_address) + ";0;3;0;11;AS-540\n");	//nazwa softu
		delay(15);		
		Serial.print(String(net_address) + ";0;3;0;12;v.1.0\n");	//wersja softu
		delay(15);	
		Serial.print(String(net_address) + ";1;0;0;3;" + String(net_address) + ".BO1\n"); 
		delay(15);
		Serial.print(String(net_address) + ";2;0;0;3;" + String(net_address) + ".BO2\n"); 
		delay(15);
		Serial.print(String(net_address) + ";3;0;0;3;" + String(net_address) + ".BO3\n"); 
		delay(15);
		Serial.print(String(net_address) + ";4;0;0;3;" + String(net_address) + ".BO4\n"); 
		delay(15);
		Serial.print(String(net_address) + ";1;1;1;2;0\n");
		delay(15);
		Serial.print(String(net_address) + ";2;1;1;2;0\n");	
		delay(15);
		Serial.print(String(net_address) + ";3;1;1;2;0\n");
		delay(15);
		Serial.print(String(net_address) + ";4;1;1;2;0\n");			
		delay(100);
		digitalWrite(_PTT,LOW);
	}
}

void sinux_sa522::decode_packet(){
  //olewamy dekodowanie jesli dane nie sa dla mnie
	if(content.substring(0,2).toInt() != _net_address){
		return;
	}else{
		for(int licznik = 1; licznik <= 4; licznik++){
			if(content == (String(_net_address) + ";" + String(licznik) + ";1;1;2;1")){
				switch(licznik){
				case 1:
					BO_SET(1);
				break;
				case 2:
					BO_SET(2);
				break; 
				case 3:
					BO_SET(3);
				break; 
				case 4:
					BO_SET(4);
				break;          
				} 
			}
		} 
		for(int licznik = 1; licznik <= 4; licznik++){
			if((content == (String(_net_address) + ";" + String(licznik) + ";1;1;2;0"))){
				switch(licznik){
				case 1:
					BO_RESET(1);
				break;
				case 2:
					BO_RESET(2);
				break; 
				case 3:
					BO_RESET(3);
				break; 
				case 4:
					BO_RESET(4);
				break;          
				} 
			}
		}		
	}
}

void sinux_sa522::MAIN(){
	if(_net_address >= 1){
		//reading commands
		//listening RS485
		boolean str_ready = false;
		while(Serial.available()){
			character = (char)Serial.read();
			//content.concat(character);
			content += character;
			if(character == '\n'){
				str_ready = true;
			}
			delay (10);
		}
      
		//if(content != ""){
		if(str_ready == true){
			content.trim();//clearing CR i LF
			delay(50);
			decode_packet();
			content = "";
			str_ready = false;
		}	 
	}
	
	if(millis() >= _time_to_tick){
		digitalWrite(_HB,HIGH);
		delay(5);
		digitalWrite(_HB,LOW);
		
		//reseting bo
		if(_bo1_countdown >= 0){
			if(_bo1_countdown < 32000){
				_bo1_countdown--;
			}
		}else{
			digitalWrite(_bo1,LOW);
			digitalWrite(_bo1A,LOW);
			_bo1_state = false;
		}
		if(_bo2_countdown >= 0){
			if(_bo2_countdown < 32000){
				_bo2_countdown--;
			}
		}else{
			digitalWrite(_bo2,LOW);
			digitalWrite(_bo2A,LOW);
			_bo2_state = false;
		}
		if(_bo3_countdown >= 0){
			if(_bo3_countdown < 32000){
				_bo3_countdown--;
			}
		}else{
			digitalWrite(_bo3,LOW);
			digitalWrite(_bo3A,LOW);
			_bo3_state = false;
		}
		if(_bo4_countdown >= 0){
			if(_bo4_countdown < 32000){
				_bo4_countdown--;
			}
		}else{
			digitalWrite(_bo4,LOW);
			digitalWrite(_bo4A,LOW);
			_bo4_state = false;
		}
		//testing BO and sending changes to the network
		if(_net_address >= 1){
			if(_bo1_state != _bo1_prev_state){
				if(_bo1_state == true){
					digitalWrite(_PTT,HIGH);
					delay(15);
					Serial.print(String(_net_address) + ";1;1;1;2;1\n");
					delay(15);
					digitalWrite(_PTT,LOW);
				}else{
					digitalWrite(_PTT,HIGH);
					delay(15);
					Serial.print(String(_net_address) + ";1;1;1;2;0\n");
					delay(15);
					digitalWrite(_PTT,LOW);
				}
			_bo1_prev_state = _bo1_state;
			}
			if(_bo2_state != _bo2_prev_state){
				if(_bo2_state == true){
					digitalWrite(_PTT,HIGH);
					delay(15);
					Serial.print(String(_net_address) + ";2;1;1;2;1\n");
					delay(15);
					digitalWrite(_PTT,LOW);
				}else{
					digitalWrite(_PTT,HIGH);
					delay(15);
					Serial.print(String(_net_address) + ";2;1;1;2;0\n");
					delay(15);
					digitalWrite(_PTT,LOW);
				}
				_bo2_prev_state = _bo2_state;
			}
			if(_bo3_state != _bo3_prev_state){
				if(_bo3_state == true){
					digitalWrite(_PTT,HIGH);
					delay(15);
					Serial.print(String(_net_address) + ";3;1;1;2;1\n");
					delay(15);
					digitalWrite(_PTT,LOW);
				}else{
					digitalWrite(_PTT,HIGH);
					delay(15);
					Serial.print(String(_net_address) + ";3;1;1;2;0\n");
					delay(15);
					digitalWrite(_PTT,LOW);
			}
			_bo3_prev_state = _bo3_state;
			}
			if(_bo4_state != _bo4_prev_state){
				if(_bo4_state == true){
					digitalWrite(_PTT,HIGH);
					delay(15);
					Serial.print(String(_net_address) + ";4;1;1;2;1\n");
					delay(15);
					digitalWrite(_PTT,LOW);
				}else{
					digitalWrite(_PTT,HIGH);
					delay(15);
					Serial.print(String(_net_address) + ";4;1;1;2;0\n");
					delay(15);
					digitalWrite(_PTT,LOW);
				}
				_bo4_prev_state = _bo4_state;
			}			
		}	
		_time_to_tick = millis() + 100;
	}
}

int sinux_sa522::AI_STATE(int _ui){
	switch(_ui){
		case 1:
			return(analogRead(_ui1));
		break;
		case 2:
			return(analogRead(_ui2));
		break;
		case 3:
			return(analogRead(_ui3));
		break;
		case 4:
			return(analogRead(_ui4));
		break;
		case 5:
			return(analogRead(_ui5));
		break;		
	}
}
// ************* //
// GOTOWE poniżej
// ************* //
boolean sinux_sa522::BI_PRESSED(int _ui){
	switch(_ui){
		case 1:
			_bi1_state = BI_STATE(1);
			if(_bi1_state != _bi1_prev_state){
				_bi1_prev_state = _bi1_state;
				return(_bi1_state);
			}else{
				return(0);
			}
		break;
		case 2:
			_bi2_state = BI_STATE(2);
			if(_bi2_state != _bi2_prev_state){
				_bi2_prev_state = _bi2_state;
				return(_bi2_state);
			}else{
				return(0);
			}
		break;
		case 3:
			_bi3_state = BI_STATE(3);
			if(_bi3_state != _bi3_prev_state){
				_bi3_prev_state = _bi3_state;
				return(_bi3_state);
			}else{
				return(0);
			}
		break;
		case 4:
			_bi4_state = BI_STATE(4);
			if(_bi4_state != _bi4_prev_state){
				_bi4_prev_state = _bi4_state;
				return(_bi4_state);
			}else{
				return(0);
			}
		break;
		case 5:
			_bi5_state = BI_STATE(5);
			if(_bi5_state != _bi5_prev_state){
				_bi5_prev_state = _bi5_state;
				return(_bi5_state);
			}else{
				return(0);
			}
		break;
	}
}

boolean sinux_sa522::BI_STATE(int _ui){	//false-Open Loop, true-Short
	switch(_ui){
		case 1:
			if(analogRead(_ui1) >= 700){
				return(false);
			}else{
				return(true);
			}	
		break;
		case 2:
			if(analogRead(_ui2) >= 700){
				return(false);
			}else{
				return(true);
			}
		break;		
		case 3:
			if(analogRead(_ui3) >= 700){
				return(false);
			}else{
				return(true);
			}
		break;		
		case 4:
			if(analogRead(_ui4) >= 700){
				return(false);
			}else{
				return(true);
			}
		break;
		case 5:
			if(analogRead(_ui5) >= 700){
				return(false);
			}else{
				return(true);
			}
		break;
	}
}

void sinux_sa522::BO_SET(int pin){
	int _pin_out = 0;
	int _led_out = 0;
	switch(pin){
		case 1:
			_pin_out = _bo1;
			_led_out = _bo1A;
			_bo1_countdown = 32000;
			_bo1_state = true;
		break;
		case 2:
			_pin_out = _bo2;
			_led_out = _bo2A;
			_bo2_countdown = 32000;
			_bo2_state = true;
		break;
		case 3:
			_pin_out = _bo3;
			_led_out = _bo3A;
			_bo3_countdown = 32000;
			_bo3_state = true;
		break;
		case 4:
			_pin_out = _bo4;
			_led_out = _bo4A;
			_bo4_countdown = 32000;
			_bo4_state = true;
		break;
	}
	//sterowanie wyjsciem
	digitalWrite(_pin_out,HIGH);
	digitalWrite(_led_out,HIGH);
}

void sinux_sa522::BO_RESET(int pin){
	int _pin_out = 0;
	int _led_out = 0;
	switch(pin){
		case 1:
			_pin_out = _bo1;
			_led_out = _bo1A;
			_bo1_countdown = 32000;
			_bo1_state = false;
		break;
		case 2:
			_pin_out = _bo2;
			_led_out = _bo2A;
			_bo2_countdown = 32000;
			_bo2_state = false;
		break;
		case 3:
			_pin_out = _bo3;
			_led_out = _bo3A;
			_bo3_countdown = 32000;
			_bo3_state = false;
		break;
		case 4:
			_pin_out = _bo4;
			_led_out = _bo4A;
			_bo4_countdown = 32000;
			_bo4_state = false;
		break;
	}
	//sterowanie wyjsciem
	digitalWrite(_pin_out,LOW);
	digitalWrite(_led_out,LOW);
}

void sinux_sa522::BO_TOGGLE(int pin){
	int _pin_out = 0;
	int _led_out = 0;
	boolean _command = false;
	switch(pin){
		case 1:
			_pin_out = _bo1;
			_led_out = _bo1A;
			_bo1_countdown = 32000;
			if(_bo1_state == true){
				_bo1_state = false;
				_command = false;
			}else{
				_bo1_state = true;
				_command = true;
			}
		break;
		case 2:
			_pin_out = _bo2;
			_led_out = _bo2A;
			_bo2_countdown = 32000;
			if(_bo2_state == true){
				_bo2_state = false;
				_command = false;
			}else{
				_bo2_state = true;
				_command = true;
			}
		break;
		case 3:
			_pin_out = _bo3;
			_led_out = _bo3A;
			_bo3_countdown = 32000;
			if(_bo3_state == true){
				_bo3_state = false;
				_command = false;
			}else{
				_bo3_state = true;
				_command = true;
			}
		break;
		case 4:
			_pin_out = _bo4;
			_led_out = _bo4A;
			_bo4_countdown = 32000;
			if(_bo4_state == true){
				_bo4_state = false;
				_command = false;
			}else{
				_bo4_state = true;
				_command = true;
			}
		break;
	}
	//sterowanie wyjsciem
	if(_command == true){
	digitalWrite(_pin_out,HIGH);
	digitalWrite(_led_out,HIGH);		
	}else{
	digitalWrite(_pin_out,LOW);
	digitalWrite(_led_out,LOW);		
	}
}

void sinux_sa522::BO_SET_TIME(int pin, int time){
	//zamiana numery wyjscia binarnego na pin arduino 
	time = time * 10;
	int _pin_out = 0;
	int _led_out = 0;
	switch(pin){
		case 1:
			_pin_out = _bo1;
			_led_out = _bo1A;
			_bo1_countdown = time;
			_bo1_state = true;
		break;
		case 2:
			_pin_out = _bo2;
			_led_out = _bo2A;
			_bo2_countdown = time;
			_bo2_state = true;
		break;
		case 3:
			_pin_out = _bo3;
			_led_out = _bo3A;
			_bo3_countdown = time;
			_bo3_state = true;
		break;
		case 4:
			_pin_out = _bo4;
			_led_out = _bo4A;
			_bo4_countdown = time;
			_bo4_state = true;
		break;
	}
	//sterowanie wyjsciem
	digitalWrite(_pin_out,HIGH);
	digitalWrite(_led_out,HIGH);
}