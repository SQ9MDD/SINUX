// ******************* //
// SINUX Ryszard Labus //
// http://sinux.com.pl //
// AS-540 firmware *** //
// ******************* //

#include <sinux_as540.h>

sinux_as540 sterownik;

void setup() {
  sterownik.INIT(11);                            // inicjalizacja i ustawianie adresu sieciowego
  sterownik.CONFIG_BV(1,false);                  // konfiguracja zmiennej BV1 bez zapisu do eeprom     
  sterownik.CONFIG_BV(2,true);                   // konfiguracja zmiennej BV2 z zapisem do eeprom stan zachowywany pomimo restartów  
}

void loop() { 
  
  if(sterownik.BV_READ(1) == 1){
    sterownik.BO_SET(1);
  }else{
    sterownik.BO_RESET(1); 
  }

   if(sterownik.BV_READ(2) == 1){
    sterownik.BO_SET(2);
  }else{
    sterownik.BO_RESET(2); 
  }
      
  sterownik.MAIN();                              // główny program biblioteki
}