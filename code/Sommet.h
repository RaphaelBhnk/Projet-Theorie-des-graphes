#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        Sommet(int,double,double);
        void afficherData() const;
        double getx() const;
        double gety() const;
        ~Sommet();
        void setetat(bool etat);

    protected:

    private:

        /// Donn�es sp�cifiques du sommet
        int m_id; // Identifiant
        double m_x, m_y; // Position
        bool m_etat; // Etat du sommet (visit� ou non)

};

#endif // SOMMET_H
