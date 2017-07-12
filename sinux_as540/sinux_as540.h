#ifndef sinux_as540_h
#define sinux_as540_h

#include "Arduino.h"

class sinux_as540{
	public: 
		//functions
		sinux_as540();
		void INIT(int net_address);
		void CONFIG_UI(int _ui, int _type);
		void BO_SET(int pin);
		void BO_RESET(int pin);
		void BO_TOGGLE(int pin);
		void BO_SET_TIME(int pin, int time);
		void MAIN();
		boolean BI_PRESSED(int _ui);
		boolean BI_STATE(int _ui);
		float UI_READ(int _ui, int _type);
	private:
		//functons
		
		void _decode_packet();
		//variables
		char character;
		String content = "";
		int _bo1 = 8;
		int _bo2 = 7;
		int _bo3 = 5;
		int _bo4 = 3;
		int _bo1A = 9;
		int _bo2A = 10;
		int _bo3A = 11;
		int _bo4A = 12;
		int _HB = 13;
		int _PTT = 2;
		int _net_address = 0;
		int _ui1 = A0;
		int _ui2 = A1;
		int _ui3 = A2;
		int _ui4 = A3;
		int _ui5 = A4;
		int _ui_type[6] = {0,3,3,3,3,3};
		unsigned long _time_to_tick = 0;
		unsigned long _time_to_send_UI = 0;
		int _bo1_countdown = 0;
		int _bo2_countdown = 0;
		int _bo3_countdown = 0;
		int _bo4_countdown = 0;
		boolean _bo1_state = false;	
		boolean _bo2_state = false;	
		boolean _bo3_state = false;	
		boolean _bo4_state = false;	
		boolean _bo1_prev_state = false;
		boolean _bo2_prev_state = false;
		boolean _bo3_prev_state = false;
		boolean _bo4_prev_state = false;
		boolean _bi1_state = false;
		boolean _bi2_state = false;
		boolean _bi3_state = false;
		boolean _bi4_state = false;
		boolean _bi5_state = false;
		boolean _bi1_prev_state = false;
		boolean _bi2_prev_state = false;
		boolean _bi3_prev_state = false;
		boolean _bi4_prev_state = false;
		boolean _bi5_prev_state = false;
		boolean _HB_state = false;
	
};

#endif