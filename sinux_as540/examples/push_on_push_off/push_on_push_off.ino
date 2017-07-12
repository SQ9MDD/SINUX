// ******************* //
// SINUX Ryszard Labus //
// http://sinux.com.pl //
// AS-540 firmware *** //
// ******************* //

#include <sinux_as540.h>

sinux_as540 sterownik;

void setup() {
  sterownik.INIT(75);                                               // inicjalizacja i ustawianie adresu sieciowego
}

void loop() {
  if(sterownik.BI_PRESSED(1)){  sterownik.BO_TOGGLE(1); }           // przycisk typu push on push off 
  if(sterownik.BI_PRESSED(2)){  sterownik.BO_TOGGLE(2); }
  if(sterownik.BI_PRESSED(3)){  sterownik.BO_TOGGLE(3); }
  if(sterownik.BI_PRESSED(4)){  sterownik.BO_TOGGLE(4); }

  sterownik.MAIN();                                                 // główny program biblioteki
}
