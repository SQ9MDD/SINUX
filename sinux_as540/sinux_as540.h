#ifndef sinux_as540_h
#define sinux_as540_h

#include "mysensors.h"
#include "Arduino.h"

class sinux_as540{
	public: 
		//functions
		sinux_as540();
		void MAIN();
		void INIT();
		void INIT(int net_address);						// BO range: 2-4,  child sensors id: 1-4
		void CONFIG_UI(int _ui, int _type, int _unit);	// UI range: 1-5,  child sensors id: 5-9
		void CONFIG_AV(int _av);						// AV range: 1-10, child sensors id: 11-20
		void CONFIG_BV(int _bv, boolean _eeprom_write);	// BV range: 1-10, child sensors id: 21-30
		void BO_SET(int pin);
		void BO_RESET(int pin);
		void BO_TOGGLE(int pin);
		void BO_SET_TIME(int pin, int time);
		boolean BI_PRESSED(int _ui);
		boolean BI_STATE(int _ui);
		int AV_READ(int _av);
		int BV_READ(int _bv);
		float UI_READ(int _ui);
	private:
		//functons
		void _decode_packet();
		void _send_reply(int _sens_addr, int _sens_state);
		//variables
		char character;
		String content = "";
		#define _lib_version 1.21
		#define _bo1  8
		#define _bo2  7
		#define _bo3  5
		#define _bo4  3
		#define _bo1A  9
		#define _bo2A  10
		#define _bo3A  11
		#define _bo4A  12
		#define _HB  13
		#define _PTT  2
		#define _ui1  A0
		#define _ui2  A1
		#define _ui3  A2
		#define _ui4  A3
		#define _ui5  A4	
		int _ui_unit[6] = {0,2,2,2,2,2};	//dynamic this are default value for UI1-5
		int _net_address = 0;
		unsigned long _prev_millis = 0;
		unsigned long _time_to_send_UI = 0;
		int _bo1_countdown = 0;
		int _bo2_countdown = 0;
		int _bo3_countdown = 0;
		int _bo4_countdown = 0;
		boolean _bv_eeprom_write[10] = {false,false,false,false,false,false,false,false,false,false};
		boolean _bv_state[10] = {false,false,false,false,false,false,false,false,false,false};
		boolean _bo_state[4] = {false,false,false,false};
		boolean _bo_prev_state[4] = {false,false,false,false}; 
				
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