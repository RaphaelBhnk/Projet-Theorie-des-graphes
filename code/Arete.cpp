#include "Arete.h"
/** \brief : Constructeur de la classe Arete
 *
 * \param int id
  * \param int sommet initial
 * \param int sommet final

 * \return
 *
 */
Arete::Arete(int id,int s1,int s2)
{
    m_id=id;
    m_s1=s1;
    m_s2=s2;
    m_ok=0;
}

/** \brief : récupere le nombre de pondération
 *
 * \param
 * \return int m_pond.size()
 *
 */
int Arete::getaillepond()
{
    return m_pond.size();
}
/** \brief : recupere la ponderation
 *
 * \param int i
 * \return float la ponderation i
 *
 */
float Arete::getpond(int i)
{
    return m_pond[i];
}

/** \brief : Afficher les infos des aretes de mon graphe
 *
 * \param
 * \return
 *
 */
 void Arete::afficherArete() const{
     std::cout<<"    "<<m_id<<" : "<<"(s1,s2)=("<<m_s1<<","<<m_s2<<")";
     std::cout<<"Ponderation :";
     for(int i=0;i<m_pond.size();i++)
     {
     std::cout<<"         "<<m_pond[i];
     }
     std::cout<<std::endl;
 }

/** \brief :Destructeur de la classe Arete
 *
 * \param
 * \return
 *
 */
Arete::~Arete()
{
    //dtor
}
/** \brief :modifier la valeur de la ponderation i
 *
 * \param float i
 * \return
 *
 */
void Arete::pushpond(float i)
{
        m_pond.push_back(i);
}
/** \brief :recupere le sommet initial de l'arete
 *
 * \param
 * \return int m_s1
 *
 */
        int Arete::gets1() const
        {
            return m_s1;
        }
        /** \brief :recupere le sommet final de l'arete
 *
 * \param
 * \return int m_s2
 *
 */
        int Arete::gets2() const
        {
            return m_s2;
        }
    /** \brief :recupere le booleen pour savoir si l'arete doit être dessine(Kruskal)
 *
 * \param
 * \return bool m_ok
 *
 */
        bool Arete::getok()
        {
            return m_ok;
        }
    /** \brief :modifier la valeur du booleen pour savoir si l'arete doit être dessine(Kruskal)
 *
 * \param bool a
 * \return
 *
 */
        void Arete::setok(bool a)
        {
            m_ok=a;
        }
