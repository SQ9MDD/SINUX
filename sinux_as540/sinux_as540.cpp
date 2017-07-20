#include "Arduino.h"
#include <EEPROM.h>
#include "sinux_as540.h"
#include "mysensors.h"

sinux_as540::sinux_as540(){
}

void sinux_as540::INIT(int net_address){
	if(net_address <= 9){ _net_address = net_address + 10; }
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
	unsigned long startup_delay = (net_address * 1000) - 10000;
	delay(startup_delay);
	Serial.begin(115200);
		
	//if(net_address >= 1){
		//if address bigger than 0 then sent presentation 4 BO and initial state
		digitalWrite(_PTT,HIGH);
		delay(50);
		Serial.print(String(net_address) + ";0;3;0;11;AS-540\n");	//nazwa softu
		delay(15);		
		Serial.print(String(net_address) + ";0;3;0;12;v."+_lib_version+"\n");	//wersja softu
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
	//}
}

void sinux_as540::CONFIG_UI(int _ui, int _type, int _unit){
	digitalWrite(_PTT,HIGH);
	delay(50);
	int b = _ui + 4;
	Serial.print(String(_net_address) + ";"+ b +";0;0;"+_type+";" + String(_net_address) + ".UI"+_ui+"\n");
	delay(15);
	Serial.print(String(_net_address) + ";"+ b +";1;1;"+_unit+";0\n");
	delay(15);
	digitalWrite(_PTT,LOW);	
	//jesli zmieniam typ UI na inne niz domyslne
	switch(_ui){												
		case 1: _ui_unit[1] = _unit; break;
		case 2: _ui_unit[2] = _unit; break;
		case 3: _ui_unit[3] = _unit; break;
		case 4: _ui_unit[4] = _unit; break;
		case 5: _ui_unit[5] = _unit; break;
	}
}
 
void sinux_as540::CONFIG_BV(int _bv, boolean _eeprom_write){
	digitalWrite(_PTT,HIGH);
	delay(50);
	int b = _bv + 20;
	Serial.print(String(_net_address) + ";"+ b +";0;0;3;" + String(_net_address) + ".BV"+ _bv +"\n");
	delay(15);
	
	int _bv_value = 0;
	if(_eeprom_write == true){
		_bv_value = (EEPROM.read(b)); 
		_bv_eeprom_write[_bv] = true;	
	}
	Serial.print(String(_net_address) + ";"+ b +";1;1;2;"+ _bv_value +"\n");
	delay(15);
	digitalWrite(_PTT,LOW);
}	
 
void sinux_as540::CONFIG_AV(int _av){
	digitalWrite(_PTT,HIGH);
	delay(50);
	int b = _av + 10;
	Serial.print(String(_net_address) + ";"+ b +";0;0;29;" + String(_net_address) + ".AV"+ _av +"\n");
	delay(15);
	int _sufix = _av + 100;
	int _av_value = (EEPROM.read(_av)*10) + (EEPROM.read(_sufix));
	Serial.print(String(_net_address) + ";"+ b +";1;1;45;"+ _av_value +"\n");
	delay(15);
	digitalWrite(_PTT,LOW);		
}

void sinux_as540::_decode_packet(){
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
		
		//tutaj dekodowanie AV
		int sens_addr = content.substring(3,5).toInt();
		if(content.substring(0,2).toInt() == _net_address && sens_addr >= 10 && sens_addr <= 20){
			int ack_option = content.substring(8,9).toInt();
			int obw_1_dimm_lvl = 0;
			obw_1_dimm_lvl = content.substring(13).toInt();		
			EEPROM.write((sens_addr-10),(obw_1_dimm_lvl/10));
			EEPROM.write(((sens_addr-10) + 100),(obw_1_dimm_lvl%10));
			digitalWrite(_PTT,HIGH);
			delay(50);
			Serial.print(String(_net_address) + ";" + String(sens_addr) + ";1;0;45;"+ String(obw_1_dimm_lvl) +"\n");    
			delay(15);
			digitalWrite(_PTT,LOW);	
		}
		
		//tutaj dekodowanie BV
		if(content.substring(0,2).toInt() == _net_address && sens_addr >= 21 && sens_addr <= 30){
			int ack_option = content.substring(8,9).toInt();
			int obw_1_dimm_lvl = 0;
			int bv_number = sens_addr - 20;
			obw_1_dimm_lvl = content.substring(12,14).toInt();		
			if(_bv_eeprom_write[bv_number] == true){	
				EEPROM.write((sens_addr),obw_1_dimm_lvl);
			}
			_bv_state[bv_number] = obw_1_dimm_lvl;
			digitalWrite(_PTT,HIGH);
			delay(50);
			Serial.print(String(_net_address) + ";" + String(sens_addr) + ";1;0;2;"+ String(obw_1_dimm_lvl) +"\n");    
			delay(15);
			digitalWrite(_PTT,LOW);			
		}
	}
}

void sinux_as540::MAIN(){
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
		_decode_packet();
		content = "";
		str_ready = false;
	}	 

	
	if(millis() >= _time_to_tick){
		digitalWrite(_HB,HIGH);
		delay(3);
		digitalWrite(_HB,LOW);
		
		//reseting bo
		if(_bo1_countdown >= 0){
			if(_bo1_countdown < 32000){
				_bo1_countdown--;
			}
		}else{
			digitalWrite(_bo1,LOW);
			digitalWrite(_bo1A,LOW);
			_bo_state[0] = false;
		}
		if(_bo2_countdown >= 0){
			if(_bo2_countdown < 32000){
				_bo2_countdown--;
			}
		}else{
			digitalWrite(_bo2,LOW);
			digitalWrite(_bo2A,LOW);
			_bo_state[1] = false;
		}
		if(_bo3_countdown >= 0){
			if(_bo3_countdown < 32000){
				_bo3_countdown--;
			}
		}else{
			digitalWrite(_bo3,LOW);
			digitalWrite(_bo3A,LOW);
			_bo_state[2] = false;
		}
		if(_bo4_countdown >= 0){
			if(_bo4_countdown < 32000){
				_bo4_countdown--;
			}
		}else{
			digitalWrite(_bo4,LOW);
			digitalWrite(_bo4A,LOW);
			_bo_state[3] = false;
		}	
		_time_to_tick = millis() + 100;
	}
	
	//testing BO and sending changes to the network
	for(int a = 0; a <= 3; a++){
		int b = a + 1;
		if(_bo_state[a] != _bo_prev_state[a]){
			if(_bo_state[a]){
				digitalWrite(_PTT,HIGH);
				delay(15);
				Serial.print(String(_net_address) + ";" + b + ";1;1;2;1\n");
				delay(15);
				digitalWrite(_PTT,LOW);				
			}else{
				digitalWrite(_PTT,HIGH);
				delay(15);
				Serial.print(String(_net_address) + ";" + b + ";1;1;2;0\n");
				delay(15);
				digitalWrite(_PTT,LOW);			
			}
			
		}	
		_bo_prev_state[a] = _bo_state[a];
	}	

	if(millis() >= _time_to_send_UI){
		for(int a=1; a <= 5; a++){
			if(_ui_unit[a] != 2){										// send only analog inputs
				int _unit = _ui_unit[a];
				digitalWrite(_PTT,HIGH);
				float pomiar = UI_READ(a);
				delay(15);
				int b = a + 4;
				Serial.print(String(_net_address) + ";"+ b +";1;1;"+_unit+";"+pomiar+"\n");
				delay(15);
				digitalWrite(_PTT,LOW);
			}			
		}
	_time_to_send_UI = millis() + 240000;
	}
}

float sinux_as540::UI_READ(int _ui){
	float _pomiar_ui = 0;
	switch(_ui){
		case 1:
			if(_ui_unit[1] == 0){	
				_pomiar_ui = ((1023 - float(analogRead(_ui1)))-238)/10;
			}else if(_ui_unit[1] == 3){
				_pomiar_ui = map((1023 - analogRead(_ui1)),0,1023,0,100);
			}else{
				_pomiar_ui = 1023 - analogRead(_ui1);
			}
			return(_pomiar_ui);
		break;
		case 2:
			if(_ui_unit[2] == 0){	
				_pomiar_ui = ((1023 - float(analogRead(_ui2)))-238)/10; 
			}else if(_ui_unit[2] == 3){
				_pomiar_ui = map((1023 - analogRead(_ui2)),0,1023,0,100);				
			}else{
				_pomiar_ui = 1023 - analogRead(_ui2);
			}
			return(_pomiar_ui);
		break;
		case 3:
			if(_ui_unit[3] == 0){	
				_pomiar_ui = ((1023 - float(analogRead(_ui3)))-238)/10; 
			}else{
				_pomiar_ui = 1023 - analogRead(_ui3);
			}
			return(_pomiar_ui);
		break;
		case 4:
			if(_ui_unit[4] == 0){	
				_pomiar_ui = ((1023 - float(analogRead(_ui4)))-238)/10; 
			}else{
				_pomiar_ui = 1023 - analogRead(_ui4);
			}
			return(_pomiar_ui);
		break;
		case 5:
			if(_ui_unit[5] == 0){	
				_pomiar_ui = ((1023 - float(analogRead(_ui5)))-238)/10; 
			}else{
				_pomiar_ui = 1023 - analogRead(_ui5);
			}
			return(_pomiar_ui);
		break;		
	}
}

int sinux_as540::AV_READ(int _av){
	int _sufix = _av + 100;
	int _av_value = (EEPROM.read(_av)*10) + (EEPROM.read(_sufix));	
	return(_av_value);
}

int sinux_as540::BV_READ(int _bv){
	int _sufix = _bv + 100;
	int  _bv_value = _bv_state[_bv];
	if(_bv_eeprom_write[_bv] == true){
		if(EEPROM.read(_bv + 20) >= 1){
			_bv_value = 1;
		}else{
			_bv_value = 0;
		}	
	}
	return(_bv_value);	
}

boolean sinux_as540::BI_PRESSED(int _ui){
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

boolean sinux_as540::BI_STATE(int _ui){	//false-Open Loop, true-Short
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

void sinux_as540::BO_SET(int pin){
	int _pin_out = 0;
	int _led_out = 0;
	switch(pin){
		case 1:
			_pin_out = _bo1;
			_led_out = _bo1A;
			_bo1_countdown = 32000;
			_bo_state[0] = true;
		break;
		case 2:
			_pin_out = _bo2;
			_led_out = _bo2A;
			_bo2_countdown = 32000;
			_bo_state[1] = true;
		break;
		case 3:
			_pin_out = _bo3;
			_led_out = _bo3A;
			_bo3_countdown = 32000;
			_bo_state[2] = true;
		break;
		case 4:
			_pin_out = _bo4;
			_led_out = _bo4A;
			_bo4_countdown = 32000;
			_bo_state[3] = true;
		break;
	}
	//sterowanie wyjsciem
	digitalWrite(_pin_out,HIGH);
	digitalWrite(_led_out,HIGH);
}

void sinux_as540::BO_RESET(int pin){
	int _pin_out = 0;
	int _led_out = 0;
	switch(pin){
		case 1:
			_pin_out = _bo1;
			_led_out = _bo1A;
			_bo1_countdown = 32000;
			_bo_state[0] = false;
		break;
		case 2:
			_pin_out = _bo2;
			_led_out = _bo2A;
			_bo2_countdown = 32000;
			_bo_state[1] = false;
		break;
		case 3:
			_pin_out = _bo3;
			_led_out = _bo3A;
			_bo3_countdown = 32000;
			_bo_state[2] = false;
		break;
		case 4:
			_pin_out = _bo4;
			_led_out = _bo4A;
			_bo4_countdown = 32000;
			_bo_state[3] = false;
		break;
	}
	//sterowanie wyjsciem
	digitalWrite(_pin_out,LOW);
	digitalWrite(_led_out,LOW);
}

void sinux_as540::BO_TOGGLE(int pin){
	int _pin_out = 0;
	int _led_out = 0;
	boolean _command = false;
	switch(pin){
		case 1:
			_pin_out = _bo1;
			_led_out = _bo1A;
			_bo1_countdown = 32000;
			if(_bo_state[0] == true){
				_bo_state[0] = false;
				_command = false;
			}else{
				_bo_state[0] = true;
				_command = true;
			}
		break;
		case 2:
			_pin_out = _bo2;
			_led_out = _bo2A;
			_bo2_countdown = 32000;
			if(_bo_state[1] == true){
				_bo_state[1] = false;
				_command = false;
			}else{
				_bo_state[1] = true;
				_command = true;
			}
		break;
		case 3:
			_pin_out = _bo3;
			_led_out = _bo3A;
			_bo3_countdown = 32000;
			if(_bo_state[2] == true){
				_bo_state[2] = false;
				_command = false;
			}else{
				_bo_state[2] = true;
				_command = true;
			}
		break;
		case 4:
			_pin_out = _bo4;
			_led_out = _bo4A;
			_bo4_countdown = 32000;
			if(_bo_state[3] == true){
				_bo_state[3] = false;
				_command = false;
			}else{
				_bo_state[3] = true;
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

void sinux_as540::BO_SET_TIME(int pin, int time){
	//zamiana numery wyjscia binarnego na pin arduino 
	time = time * 10;
	int _pin_out = 0;
	int _led_out = 0;
	switch(pin){
		case 1:
			_pin_out = _bo1;
			_led_out = _bo1A;
			_bo1_countdown = time;
			_bo_state[0] = true;
		break;
		case 2:
			_pin_out = _bo2;
			_led_out = _bo2A;
			_bo2_countdown = time;
			_bo_state[1] = true;
		break;
		case 3:
			_pin_out = _bo3;
			_led_out = _bo3A;
			_bo3_countdown = time;
			_bo_state[2] = true;
		break;
		case 4:
			_pin_out = _bo4;
			_led_out = _bo4A;
			_bo4_countdown = time;
			_bo_state[3] = true;
		break;
	}
	//sterowanie wyjsciem
	digitalWrite(_pin_out,HIGH);
	digitalWrite(_led_out,HIGH);
}