// ******************* //
// SINUX Ryszard Labus //
// http://sinux.com.pl //
// AS-540 firmware *** //
// ******************* //

#include <sinux_as540.h>

sinux_as540 sterownik;

boolean BI_1_STATE = false;											// zmienna pomocnicza stan wejscia UI1
boolean BI_1_LAST_STATE = false;									// zmienna pomocnicza poprzedni stan wejścia UI1 

void setup() {
  sterownik.INIT(11);                                               // inicjalizacja i ustawianie adresu sieciowego
}

void loop() {
  BI_1_STATE = sterownik.BI_STATE(1);								// odczytuję stan wejscia
  if(BI_1_LAST_STATE != BI_1_STATE){								// jeśli bieżący stan wejścia się zmienił (wykrywamy tylko zmiany) to
    if(BI_1_STATE){													// ustawiamy wyjście w takim stanie jak wejście
      sterownik.BO_SET(1); 
    }else{ 
      sterownik.BO_RESET(1); 
    }
	BI_1_LAST_STATE = BI_1_STATE;									
  }

  sterownik.MAIN();                                                 // główny program biblioteki
}