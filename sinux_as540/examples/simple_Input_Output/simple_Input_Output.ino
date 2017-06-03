// ******************* //
// SINUX Ryszard Labus //
// http://sinux.com.pl //
// AS-540 firmware *** //
// ******************* //

#include <sinux_as540.h>

sinux_as540 sterownik;

void setup() {
  sterownik.init(73);                                               // inicjalizacja i podanie adresu sieciowego
}

void loop() {
  if(sterownik.BI_STATE(1) == true){ sterownik.BO_SET(1); }     // wysteruj BO1 ON jeśli wejście jest w stanie zamknietym 
  if(sterownik.BI_STATE(2) == true){ sterownik.BO_SET(2); }
  if(sterownik.BI_STATE(3) == true){ sterownik.BO_SET(3); }
  if(sterownik.BI_STATE(4) == true){ sterownik.BO_SET(4); }
   
  sterownik.MAIN();                                                 // główny program biblioteki
}