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
}

void loop() {
  
  if(sterownik.BI_PRESSED(1)){										// jeśli UI1 wciśnięty
    int czas_podtrzymania = sterownik.AV_READ(1);  					// pobieram czas podtrzymania świecenia ze zmiennej AV1
    sterownik.BO_SET_TIME(1,czas_podtrzymania);						// wysteruj BO1 na czas poprzednio odczytany
  }
  
  sterownik.MAIN();                                                 // główny program biblioteki
}