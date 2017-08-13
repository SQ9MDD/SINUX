// ******************* //
// SINUX Ryszard Labus //
// http://sinux.com.pl //
// AS-540 firmware *** //
// ******************* //

#include <sinux_as540.h>

sinux_as540 sterownik;

void setup() {
  sterownik.INIT(11);                                               // inicjalizacja i ustawianie adresu sieciowego 11-32
}

void loop() {
  if(sterownik.BI_PRESSED(1)){  sterownik.BO_TOGGLE(1); }           // przycisk typu push on push off UI1 -> BO1 
  if(sterownik.BI_PRESSED(2)){  sterownik.BO_TOGGLE(2); }			// przycisk typu push on push off UI2 -> BO2 
  if(sterownik.BI_PRESSED(3)){  sterownik.BO_TOGGLE(3); }			// przycisk typu push on push off UI3 -> BO3 
  if(sterownik.BI_PRESSED(4)){  sterownik.BO_TOGGLE(4); }			// przycisk typu push on push off UI4 -> BO4 

  sterownik.MAIN();                                                 // główny program biblioteki
}
