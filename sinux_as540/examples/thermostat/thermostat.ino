// ******************* //
// SINUX Ryszard Labus //
// http://sinux.com.pl //
// AS-540 firmware *** //
// ******************* //

#include <sinux_as540.h>

sinux_as540 sterownik;

void setup() {
  sterownik.INIT(75);                            // inicjalizacja i ustawianie adresu sieciowego
  sterownik.CONFIG_UI(1,6);                      // CONFIG_UI(input,type) konfiguracja wejscia nr 1 jako UI typdomyślny to 3 : 3-BI(binary on/off),6-AI(Temp),16-AI(uncalibrated lux) for more see: http://mysensors.org
}

void loop() {
  if(sterownik.UI_READ(1,6) >= 29.5){            // point ON
    sterownik.BO_SET(1);
  }
  
  if(sterownik.UI_READ(1,6) <= 24.0){            // point OFF
    sterownik.BO_RESET(1);
  }
  
  sterownik.MAIN();                              // główny program biblioteki
}