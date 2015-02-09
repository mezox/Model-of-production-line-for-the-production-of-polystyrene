#include "zariadenia.h"

void init_zariadenia()
{
//    Queue fronta_predpenovacka("Varky pred predpenovackou");
//    Queue fronta_forma("Varky pred formou");
 //   Queue fronta_rezacka("Varky pred rezackou");


    predpenovacka.Clear();
    predpenovacka.SetName("Predpenovacka");
 //   predpenovacka.SetQueue(fronta_predpenovacka);

    forma.Clear();
    forma.SetName("Forma");
 //   forma.SetQueue(fronta_forma);

    rezacka.Clear();
    rezacka.SetName("Rezacka");
 //   rezacka.SetQueue(fronta_rezacka);

}
