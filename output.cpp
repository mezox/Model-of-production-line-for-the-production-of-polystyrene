#include "output.h"
#include <iostream>
#include "zariadenia.h"

using namespace std;

Output::Output()
{
    f.open ("out/silo.txt");
    f << "# 1(cas) 2(fronta pred silom)\n";

    sklad.open("out/sklad.txt");
    sklad << "# 1(cas) 2(kapacita)\n";

    objednavky.open("out/objednavky.txt");
    objednavky << "# 1(prichod) 2(odchod)\n";


    // PLOT FILE
    plotfile.open("out/plot.plt");

    plotfile << "set terminal png size 1000,600" << std::endl;
    plotfile << "set autoscale y" << std::endl;
    plotfile << "set autoscale x" << std::endl;
    plotfile << "set key below" << std::endl;
    plotfile << "set xlabel \"Čas (h)\"" << std::endl;
    plotfile << "set ylabel \"Počet plných síl\"" << std::endl;
    plotfile << "set title \"Vyťaženie síl za jeden mesiac pri počte 14 \"" << std::endl;
    plotfile << "set output 'silo2.png'" << std::endl;
    plotfile << "plot \"silo.txt\" using 1:2 title \"Plné silá v danom čase\" with steps linewidth 3" << std::endl;

    plotfile << "unset autoscale x" << std::endl;
    plotfile << "set xrange [\"0\":\"200\"]" << endl;
    plotfile << "set xlabel \"Číslo objednávky\"" << endl;
    plotfile << "set ylabel \"Doby spracovania objednávky (hodiny)\"" << endl;
    plotfile << "set title \"Doby spracovania objednávok za jeden mesiac pri použití 10 síl\"" << endl;
    plotfile << "set output 'objednavky3.png'" << endl;
    plotfile << "plot \"objednavky.txt\" using 1:2 smooth frequency with boxes linewidth 3 title \"Doby spracovania\"" << endl;

    plotfile.close();
}

void Output::CloseAll()
{
//    f.close();
//    sklad.close();
}

void Output::Behavior()
{

    f << Time << "\t" << silo->getFulls() << "\n";

    Activate(Time + 1.0/60);
}

void Output::LogObjednavka(double prichod, double odchod)
{
    objednavky << prichod << "\t" << odchod << "\n";
}
void Output::LogObjednavka2(double rozdiel)
{
    objednavky << rozdiel << "\t" << 1 << "\n";
}
