#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "Arete.h"
#include "Svgfile.h"
class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string, std::string);
        ~graphe();
        void afficher(Svgfile &svgout) ;
        void bruteforce();
        void optimum1(Svgfile &svgout);
        void kruskal(Svgfile &svgout);
        void dijkstra();

    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*>m_sommets;
        std::vector<Arete*>m_tabarete;
        std::vector<std::vector<bool>> m_casfinal;
        std::vector<std::vector<float>> m_poids;
        double m_ymax,m_xmax;

};

#endif // GRAPHE_H
