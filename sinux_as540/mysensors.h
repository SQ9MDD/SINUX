#define		S_DOOR  0					// Door and window sensors	V_TRIPPED V_ARMED
#define		S_MOTION  1					// Motion sensors	V_TRIPPED V_ARMED
#define		S_SMOKE  2					// Smoke sensor	V_TRIPPED V_ARMED
#define		S_LIGHT  3					// Light Actuator(on / off)	V_STATUS(or V_LIGHT) V_WATT
#define		S_BINARY  3					// Binary device(on / off) Alias for S_LIGHT	V_STATUS(or V_LIGHT) V_WATT
#define		S_DIMMER  4					// Dimmable device of some kind	V_STATUS(on / off) V_DIMMER(dimmer level 0 - 100) V_WATT
#define		S_COVER  5					// Window covers or shades	V_UP V_DOWN V_STOP V_PERCENTAGE
#define		S_TEMP  6					// Temperature sensor	V_TEMP V_ID
#define		S_HUM  7					// Humidity sensor	V_HUM
#define		S_BARO  8					// Barometer sensor(Pressure)	V_PRESSURE V_FORECAST
#define		S_WIND  9					// Wind sensor	V_WIND V_GUST
#define		S_RAIN  10					// Rain sensor	V_RAIN V_RAINRATE
#define		S_UV  11					// UV sensor	V_UV
#define		S_WEIGHT  12				// Weight sensor for scales etc.V_WEIGHT V_IMPEDANCE
#define		S_POWER  13					// Power measuring device like power meters	V_WATT V_KWH
#define		S_HEATER  14				// Heater device	V_HVAC_SETPOINT_HEAT V_HVAC_FLOW_STATE V_TEMP V_STATUS
#define		S_DISTANCE  15				// Distance sensor	V_DISTANCE V_UNIT_PREFIX
#define		S_LIGHT_LEVEL  16			// Light sensor	V_LIGHT_LEVEL(uncalibrated percentage) V_LEVEL(light level in lux)
#define		S_ARDUINO_NODE  17			// Arduino node device
#define		S_ARDUINO_REPEATER_NODE  18	// Arduino repeating node device
#define		S_LOCK  19					// Lock device	V_LOCK_STATUS
#define		S_IR  20					// Ir sender / receiver device	V_IR_SEND V_IR_RECEIVE
#define		S_WATER  21					// Water meter	V_FLOW V_VOLUME
#define		S_AIR_QUALITY  22			// Air quality sensor e.g.MQ - 2	V_LEVEL V_UNIT_PREFIX
#define		S_CUSTOM  23				// Use this for custom sensors where no other fits.
#define		S_DUST  24					// Dust level sensor	V_LEVEL V_UNIT_PREFIX
#define		S_SCENE_CONTROLLER  25		// Scene controller device	V_SCENE_ON V_SCENE_OFF
#define		S_RGB_LIGHT  26				// RGB light	V_RGB V_WATT
#define		S_RGBW_LIGHT  27			// RGBW light(with separate white component)	V_RGBW V_WATT
#define		S_COLOR_SENSOR  28			// Color sensor	V_RGB
#define		S_HVAC  29					// Thermostat / HVAC device	V_HVAC_SETPOINT_HEAT V_HVAC_SETPOINT_COLD V_HVAC_FLOW_STATE V_HVAC_FLOW_MODE V_HVAC_SPEED V_TEMP V_STATUS
#define		S_MULTIMETER  30			// Multimeter device	V_VOLTAGE V_CURRENT V_IMPEDANCE
#define		S_SPRINKLER  31				// Sprinkler device	V_STATUS(turn on / off) V_TRIPPED(if fire detecting device)
#define		S_WATER_LEAK  32			// Water leak sensor	V_TRIPPED V_ARMED
#define		S_SOUND  33					// Sound sensor	V_LEVEL(in dB) V_TRIPPED V_ARMED
#define		S_VIBRATION  34				// Vibration sensor	V_LEVEL(vibration in Hz) V_TRIPPED V_ARMED
#define		S_MOISTURE  35				// Moisture sensor	V_LEVEL(water content or moisture in percentage ? ) V_TRIPPED V_ARMED
#define		S_INFO  36					//  LCD text device / Simple information device on controller V_TEXT
#define		S_GAS  37					//  Gas meter V_FLOW V_VOLUME
#define		S_GPS  38					//  GPS Sensor V_POSITION
#define		S_WATER_QUALITY  39			//  V_TEMP V_PH V_ORP V_EC V_STATUS 
#define		S_UNKNOWN  200 				// No Type received

 
#define		V_TEMP  0					// Temperature	S_TEMP S_HEATER S_HVAC
#define		V_HUM  1					// Humidity	S_HUM
#define		V_STATUS  2					// Binary status. 0  off 1  on	S_LIGHT S_DIMMER S_SPRINKLER S_HVAC S_HEATER
#define		V_LIGHT  2					// Deprecated.Alias for V_STATUS.Light status. 0  off 1  on	S_LIGHT S_DIMMER S_SPRINKLER
#define		V_PERCENTAGE  3				// Percentage value. 0 - 100 (%)	S_DIMMER
#define		V_DIMMER  3					// Deprecated.Alias for V_PERCENTAGE.Dimmer value. 0 - 100 (%)	S_DIMMER
#define		V_PRESSURE  4				// Atmospheric Pressure	S_BARO
#define		V_FORECAST  5				// Whether forecast.One of "stable" "sunny" "cloudy" "unstable" "thunderstorm" or "unknown"	S_BARO
#define		V_RAIN  6					// Amount of rain	S_RAIN
#define		V_RAINRATE  7				// Rate of rain	S_RAIN
#define		V_WIND  8					// Wind speed	S_WIND
#define		V_GUST  9					// Gust	S_WIND
#define		V_DIRECTION  10				// Wind direction	S_WIND
#define		V_UV  11					// UV light level	S_UV
#define		V_WEIGHT  12				// Weight(for scales etc)	S_WEIGHT
#define		V_DISTANCE  13				// Distance	S_DISTANCE
#define		V_IMPEDANCE  14				// Impedance value	S_MULTIMETER S_WEIGHT
#define		V_ARMED  15					// Armed status of a security sensor. 1  Armed 0  Bypassed	S_DOOR S_MOTION S_SMOKE S_SPRINKLER S_WATER_LEAK S_SOUND S_VIBRATION S_MOISTURE
#define		V_TRIPPED  16				// Tripped status of a security sensor. 1  Tripped 0  Untripped	S_DOOR S_MOTION S_SMOKE S_SPRINKLER S_WATER_LEAK S_SOUND S_VIBRATION S_MOISTURE
#define		V_WATT  17					// Watt value for power meters	S_POWER S_LIGHT S_DIMMER S_RGB S_RGBW
#define		V_KWH  18					// Accumulated number of KWH for a power meter	S_POWER
#define		V_SCENE_ON  19				// Turn on a scene	S_SCENE_CONTROLLER
#define		V_SCENE_OFF  20				// Turn of a scene	S_SCENE_CONTROLLER
#define		V_HVAC_FLOW_STATE  21		// Mode of header.One of "Off" "HeatOn" "CoolOn" or "AutoChangeOver"	S_HVAC S_HEATER
#define		V_HVAC_SPEED  22			// HVAC / Heater fan speed("Min" "Normal" "Max" "Auto")	S_HVAC S_HEATER
#define		V_LIGHT_LEVEL  23			// Uncalibrated light level. 0 - 100 % .Use V_LEVEL for light level in lux.S_LIGHT_LEVEL
#define		V_VAR1  24					// Custom value	Any device
#define		V_VAR2  25					// Custom value	Any device
#define		V_VAR3  26					// Custom value	Any device
#define		V_VAR4  27					// Custom value	Any device
#define		V_VAR5  28					// Custom value	Any device
#define		V_UP  29					// Window covering.Up.S_COVER
#define		V_DOWN  30					// Window covering.Down.S_COVER
#define		V_STOP  31					// Window covering.Stop.S_COVER
#define		V_IR_SEND  32				// Send out an IR - command	S_IR
#define		V_IR_RECEIVE  33			// This message contains a received IR - command	S_IR
#define		V_FLOW  34					// Flow of water(in meter)	S_WATER
#define		V_VOLUME  35				// Water volume	S_WATER S_GAS
#define		V_LOCK_STATUS  36			// Set or get lock status. 1  Locked 0  Unlocked	S_LOCK
#define		V_LEVEL  37					// Used for sending level - value	S_DUST S_AIR_QUALITY S_SOUND(dB) S_VIBRATION(hz) S_LIGHT_LEVEL(lux)
#define		V_VOLTAGE  38				// Voltage level	S_MULTIMETER
#define		V_CURRENT  39				// Current level	S_MULTIMETER
#define		V_RGB  40					// RGB value transmitted as ASCII hex string(I.e "ff0000" for red)	S_RGB_LIGHT S_COLOR_SENSOR
#define		V_RGBW  41					// RGBW value transmitted as ASCII hex string(I.e "ff0000ff" for red + full white)	S_RGBW_LIGHT
#define		V_ID  42					// Optional unique sensor id(e.g.OneWire DS1820b ids)	S_TEMP
#define		V_UNIT_PREFIX  43			// Allows sensors to send in a string representing the unit prefix to be displayed in GUI.This is not parsed by controller!E.g.cm m km inch.S_DISTANCE S_DUST S_AIR_QUALITY
#define		V_HVAC_SETPOINT_COOL  44	// HVAC cold setpoint(Integer between 0 - 100)	S_HVAC
#define		V_HVAC_SETPOINT_HEAT  45	// HVAC / Heater setpoint(Integer between 0 - 100)	S_HVAC S_HEATER
#define		V_HVAC_FLOW_MODE  46		// Flow mode for HVAC("Auto" "ContinuousOn" "PeriodicOn")	S_HVAC
#define		V_TEXT  47					// Text/Info message S_INFO
#define		V_CUSTOM  48 				// Custom messages used for controller/inter node specific commands preferably using S_CUSTOM device type. 
#define		V_POSITION  49				// GPS position and altitude. Payload: latitude;longitude;altitude(m). E.g. "55.722526;13.017972;18"
#define		V_IR_RECORD  50				// Record IR codes S_IR for playback
#define		V_PH  51					// S_WATER_QUALITY water PH
#define		V_ORP  52					// S_WATER_QUALITY water ORP : redox potential in mV
#define		V_EC  53					// S_WATER_QUALITY water electric conductivity ?S/cm (microSiemens/cm)
#define		V_VAR  54					// S_POWER Reactive power: volt-ampere reactive (var)
#define		V_VA  55					// S_POWER Apparent power: volt-ampere (VA)
#define		V_POWER_FACTOR  56			// S_POWER Ratio of real power to apparent power: floating point value in the range [-1..1]
#define		V_UNKNOWN  200				// No value received