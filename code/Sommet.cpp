#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

    /** \brief :constructeur de la classe sommet
 * \param int identifiant
  * \param double la position x
   * \param double la position y
 * \return
 *
 */
Sommet::Sommet(int id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
    /** \brief :affiche les infos des sommets du graphe
 * \param
 * \return
 *
 */
 void Sommet::afficherData() const{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
 }
    /** \brief :destructeur de la classe sommet
 * \param
 * \return
 *
 */
Sommet::~Sommet()
{
    //dtor
}
    /** \brief :recuper la position x d'un sommet
 * \param
 * \return double m_x
 *
 */
double Sommet::getx() const
{
    return m_x;
}
    /** \brief :recuper la position y d'un sommet
 * \param
 * \return double m_y
 *
 */
double Sommet::gety() const
{
    return m_y;
}
    /** \brief :recuper l'etat d'un sommet(pour Dijkstra)
 * \param
 * \return bool m_etat
 *
 */
void Sommet::setetat(bool etat)
{
    m_etat=etat;
}

