#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet(int,double,double);
        void afficherData() const;
        double getx() const;
        double gety() const;
        ~Sommet();
        void setetat(bool etat);

    protected:

    private:

        /// Données spécifiques du sommet
        int m_id; // Identifiant
        double m_x, m_y; // Position
        bool m_etat; // Etat du sommet (visité ou non)

};

#endif // SOMMET_H
