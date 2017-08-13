// ******************* //
// SINUX Ryszard Labus //
// http://sinux.com.pl //
// AS-540 firmware *** //
// ******************* //

#include <sinux_as540.h>

sinux_as540 sterownik;

void setup() {
  sterownik.INIT(11);                                               // inicjalizacja i ustawianie adresu sieciowego
  sterownik.CONFIG_AV(1);                                           // zmienne AV1 do przetrzymywania czasu świecenia w sekundach
  sterownik.CONFIG_AV(2);                                           // zmienna AV2 do przechowywania poziomu natezenia oswietlenia ponizej ktorego ma dzialac obwod
  sterownik.CONFIG_UI(5,S_LIGHT_LEVEL, V_LEVEL);                    // wejście UI5 czujnik natezenia oswietlenia
}

void loop() {
  
  if(sterownik.BI_PRESSED(1) == true && sterownik.UI_READ(5) < float(sterownik.AV_READ(2)) ){  
    sterownik.BO_SET_TIME(1,sterownik.AV_READ(1));
  }
  
  sterownik.MAIN();                                                 // główny program biblioteki
}