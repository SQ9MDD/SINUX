// ******************* //
// SINUX Ryszard Labus //
// http://sinux.com.pl //
// AS-540 firmware *** //
// ******************* //

#include <sinux_as540.h>

sinux_as540 sterownik;

boolean BI_1_STATE = false;
boolean BI_1_LAST_STATE = false;

void setup() {
  sterownik.INIT(75);                                               // inicjalizacja i ustawianie adresu sieciowego
}

void loop() {
  BI_1_STATE = sterownik.BI_STATE(1);
  
  if(BI_1_LAST_STATE != BI_1_STATE){
    if(BI_1_STATE){
      sterownik.BO_SET(1); 
    }else{ 
      sterownik.BO_RESET(1); 
    }
  }
  
  BI_1_LAST_STATE = BI_1_STATE;
  
  sterownik.MAIN();                                                 // główny program biblioteki
}