#include <iostream>
#include "graphe.h"

int main()
{
    Svgfile svgout;
    graphe g2("broadway.txt","broadway_weights_0.txt");
    g2.afficher(svgout);
    g2.bruteforce();
    g2.kruskal(svgout);
    g2.optimum1(svgout);

    return 0;
}
