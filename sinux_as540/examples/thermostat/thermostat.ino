// ******************* //
// SINUX Ryszard Labus //
// http://sinux.com.pl //
// AS-540 firmware *** //
// ******************* //

#include <sinux_as540.h>

sinux_as540 sterownik;

boolean on_off_flag = false;                     // zmienna flaga pomocnicza
boolean on_off_last_flag = false;                // zmienna flaga pomocnicza

void setup() {
  sterownik.INIT(75);                            // inicjalizacja i ustawianie adresu sieciowego
  sterownik.CONFIG_UI(1, S_TEMP, V_TEMP);        // CONFIG_UI(input,presentation,set/req) konfiguracja wejscia nr 1 jako UI typ 6-AI(Temp)patrz: http://mysensors.org
  sterownik.CONFIG_AV(1);                        // punkt załączenia S_HVAC, V_HVAC_SETPOINT_HEAT
  sterownik.CONFIG_AV(2);                        // punkt wyłączenia
}

void loop() { 
  
  if(sterownik.UI_READ(1) >= sterownik.AV_READ(1)){            // point ON
    on_off_flag = true;
  }
  
  if(sterownik.UI_READ(1) <= sterownik.AV_READ(2)){            // point OFF 
    on_off_flag = false;
  }

  if(on_off_flag != on_off_last_flag){          // wykrywanie zmianu stanu wysterowania i sterowanie wyjsciem tylko na zboczu narastajacym i opadajacym
    on_off_last_flag = on_off_flag;
    if(on_off_flag == true){
      sterownik.BO_SET(1);  
    }else{
      sterownik.BO_RESET(1); 
    }
  }
  
  sterownik.MAIN();                              // główny program biblioteki
}