#include <fstream>
#include <iostream>
#include <algorithm>
#include "graphe.h"
#include "list"
#include "sommet.h"
#include <bitset>
#include "math.h"

/** \brief :constructeur de la classe graphe qui recupere les données des deux fichiers textes pour ensuite les stocker dans
 * un tableau d'aretes et un tableau de sommets
 * \param std::string nomFichier
 * \param std::string Fichier2
 * \return
 *
 */


graphe::graphe(std::string nomFichier, std::string Fichier2)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int id,id2;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.push_back(new Sommet(id,x,y));
    }
    std::ifstream ifs2{Fichier2};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + Fichier2 );
    int taille, taille2;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    ifs2 >> taille2;
    if(ifs2.fail())
        throw std::runtime_error("Probleme lecture données arete");
    if(taille != taille2)
        throw std::runtime_error("Les fichiers ne correspondeng pas");
    int p;
    ifs2>>p;
    if(ifs2.fail())
        throw std::runtime_error("Probleme lecture données arete");
    int s1,s2;
    std::vector<float> pond;
    for(int i=0; i<p; i++)
    {
        pond.push_back(0);
    }
    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extrémités
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données arete");
        ifs>>s1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données arete");
        ifs>>s2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données arete");
        ifs2>>id2;
        if(ifs2.fail())
            throw std::runtime_error("Probleme lecture données arete");
        for(int i=0; i<p; i++)
        {
            ifs2>>pond[i];
            if(ifs2.fail())
                throw std::runtime_error("Probleme lecture données arete");
        }
        m_tabarete.push_back(new Arete(id,s1,s2));
        for(int i=0; i<p; i++)
        {
            m_tabarete[id]->pushpond(pond[i]);
        }
    }
}

/** \brief : Affiche: -les sommets et aretes du graphes avec les pondérations
 *                    -le repere pour Pareto
 * \param Svgfile &svgout
 * \return
 *
 */

void graphe::afficher(Svgfile &svgout)
{
    m_ymax=0.0;
    double ymin;
    int cpt=0;
    int cpt2=0;
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"ordre  : "<<m_sommets.size()<<std::endl;
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        std::cout<<"Sommet :";
        m_sommets[i] -> afficherData();
        std::cout<<std::endl;
    }
    std::cout<<"Taille : "<<m_tabarete.size()<<std::endl;
    for (unsigned int i=0; i<m_tabarete.size(); ++i)
    {
        std::cout<<"Arete :";
        m_tabarete[i]->afficherArete();
        std::cout<<std::endl;
    }
    for (int i=0; i<m_tabarete.size(); ++i)
    {
        svgout.addLine(m_sommets[m_tabarete[i]->gets1()]->getx(),m_sommets[m_tabarete[i]->gets1()]->gety(),m_sommets[m_tabarete[i]->gets2()]->getx(),m_sommets[m_tabarete[i]->gets2()]->gety(),2,"black");
        svgout.addText3((m_sommets[m_tabarete[i]->gets1()]->getx()+m_sommets[m_tabarete[i]->gets2()]->getx())/2,((m_sommets[m_tabarete[i]->gets1()]->gety()+m_sommets[m_tabarete[i]->gets2()]->gety())/2)-5,i,"red");
    }
    for(int i=0; i<m_sommets.size(); i++)
    {
        svgout.addDisk(m_sommets[i]->getx(),m_sommets[i]->gety(),10,"white");
        svgout.addCircle(m_sommets[i]->getx(),m_sommets[i]->gety(),10,2,"black");
        if(i>9)
        {

        svgout.addText3(m_sommets[i]->getx()-8,m_sommets[i]->gety()+5,i,"blue");
        }
        else
        svgout.addText3(m_sommets[i]->getx()-3,m_sommets[i]->gety()+5,i,"blue");

    }
    for(int i=0;i<m_sommets.size();i++)
    {
        if(m_sommets[i]->getx()>m_xmax)
        {
            m_xmax=m_sommets[i]->getx();
        }
    }
        ymin=m_sommets[0]->gety();
    for(int i=1;i<m_sommets.size();i++)
    {
        if(m_sommets[i]->gety()<ymin)
        {
            ymin=m_sommets[i]->gety();
        }
    }

        for(int i=1;i<m_sommets.size();i++)
    {
        if(m_sommets[i]->gety()>m_ymax)
        {
            m_ymax=m_sommets[i]->gety();
        }
    }
        for (int i=0; i<m_tabarete.size(); ++i)
    {
        cpt2=0;
        svgout.addText(m_xmax+100,ymin+cpt*30,"Arete:","black");
        svgout.addText3(m_xmax+150,ymin+cpt*30,i,"black");
        svgout.addText(m_xmax+200,ymin+cpt*30,"ponderation:","black");
        for(int j=0;j<m_tabarete[0]->getaillepond();j++)
       {
        svgout.addText4(m_xmax+300+100*cpt2,ymin+cpt*30,m_tabarete[i]->getpond(j),"black");
        cpt2++;
       }
cpt++;
    }
m_xmax=m_xmax+800;
svgout.addLine(m_xmax,100,m_xmax,800,2,"black");
svgout.addLine(m_xmax,100,m_xmax-10,100+15,2,"black");
svgout.addLine(m_xmax,100,m_xmax+10,100+15,2,"black");
svgout.addLine(m_xmax,800,m_xmax+700,800,2,"black");
svgout.addLine(m_xmax+700,800,m_xmax+700-15,800-10,2,"black");
svgout.addLine(m_xmax+700,800,m_xmax+700-15,800+10,2,"black");
svgout.addText(m_xmax+20,100,"cout 2","black");
svgout.addText(m_xmax+700,830,"cout 1","black");
}



/*void graphe::pareto()
{
    std::bitset<1000> cas;
    std::vector<std::bitset<1000>> cas_admissible;
    std::vector<std::bitset<1000>> sol;
    std::vector<std::string>liste_sommet;
    liste_sommet.push_back("0");
    bool ajout1=true; /// Verification pour ajout du sommet de depart
    bool ajout2=true; /// Verification pour ajout du sommet d'arrivée
    for( int i=0; i<pow(2,m_tabarete.size()); ++i) /// Filtrage cycle
    {
        cas=i;
        if(cas.count()==m_sommets.size()-1)
        {
            //std::cout<<cas<<std::endl;
            cas_admissible.push_back(cas);
        }
    }
    for(std::size_t i=0; i<cas_admissible.size(); ++i) /// Filtrage connexité
    {
        for(std::size_t j=0; j<m_tabarete.size(); ++j)
        {

            if(cas_admissible[i][j]==true)
            {

                for(std::size_t k=0; k<liste_sommet.size(); ++k)
                {
                    if(m_tabarete[j]->gets1()==liste_sommet[k]){ajout1=false;}   /// Si sommet de depart deja contenu dans le vecteur
                    if(m_tabarete[j]->gets2()==liste_sommet[k]){ajout2=false;}   /// Si sommet d'arrivée deja contenur dans le vecteur
                }
                if(ajout1==true)
                {
                    liste_sommet.push_back(m_tabarete[j]->gets1());
                                            std::cout<<cas_admissible[i]<<std::endl;

                }
                if(ajout2==true)
                {
                    liste_sommet.push_back(m_tabarete[j]->gets2());
                                            std::cout<<cas_admissible[i]<<std::endl;

                }

            }

        }
        if(liste_sommet.size()-1==m_sommets.size())
        {
            std::cout<<cas_admissible[i]<<std::endl;
            sol.push_back(cas_admissible[i]);
        }
    }
}
*/
/** \brief : Filtre tous les chemins connexes et sans cycle et stocke tous ces chemins dans un vector<vector<bool>>
 *
 * \param
 * \return
 *
 */
void graphe::bruteforce()
{
   // std::vector<std::vector<int>> cas;
    std::vector<std::vector<int>> cas2;
  //  std::vector<std::vector<int>> casfinal;

 /*   for(int i=0; i<k3; i++)
    {
        std::vector<int> kk(k2,1);
        for(int j=0; j<i; j++)
            kk[j] = 0;
        do
        {
            cas.push_back(kk);
            g3++;
        }
        while(std::next_permutation(kk.begin(),kk.end()));
    }
    for(int i=0; i<k3; i++) //FILTRE CYCLES
    {
        p=0;
        for(int j=0; j<k2; j++)
        {
            if(cas[i][j]==1)
            {
                p++;
            }
        }
        if(p==k-1)
        {
            cas2.push_back(cas[i]);
            g1++;
        }
    }*/
       // int n = m_sommets.size();
        //int o = m_sommets.size()-1;
            std::vector<bool> cas(m_tabarete.size(),true);
            std::vector<std::vector<bool>> casfin;
          //  std::vector<std::vector<bool>> casfinal;


            for(int j=0; j<m_tabarete.size()-(m_sommets.size()-1);j++)
            {
                    cas[j] = false;
            }
            do{
            casfin.push_back(cas);
            }while(std::next_permutation(cas.begin(),cas.end()));
/*
for(int i=0;i<casfin.size();i++)
{
    for(int j=0;j<m_sommets.size()-1;j++)
        std::cout<<casfin[i][j];

}
*/

//filtre conexite
 /*   for(unsigned int i=0; i<casfin.size(); i++)
    {
        p=0;
        for(int t=0; t<m_tabarete.size(); t++)
        {
            tab[t]=t;
        }
        for(int j=0; j<m_tabarete.size(); j++)
        {
            if(casfin[i][j]==1)
            {
                for(int z=0; z<m_tabarete.size(); z++)
                {
                    if(m_tabarete[j]->gets1()==z)
                    {
                        tab[z]=-1;
                    }
                    if(m_tabarete[j]->gets2()==z)
                    {
                        tab[z]=-1;
                    }
                }
            }
        }
        for(int z=0; z<m_tabarete.size(); z++)
        {
            if(tab[z]==-1)
            {
                p++;
            }
        }

        if(p==m_sommets.size())
        {
            casfinal.push_back(casfin[i]);
            g++;
        }



    }
 //               std::cout<<m_casfinal.size();
*/

//dernier filtre
   std::vector<int> tabconnex(m_sommets.size(),0);
   int cpt,premier;

   for(int i=0;i<casfin.size();i++)
   {
    for(unsigned int y=0;y<tabconnex.size();y++)
   {
       tabconnex[y]=y;
   }
       cpt=0;
       for(int j=0;j<m_tabarete.size();j++)
       {
           if(casfin[i][j]==true)
           {
            premier=tabconnex[m_tabarete[j]->gets1()];
            tabconnex[m_tabarete[j]->gets1()]=tabconnex[m_tabarete[j]->gets2()];

               for(int d=0;d<tabconnex.size();d++)
               {
                   if(tabconnex[d]==premier)
                   {
                       tabconnex[d]=tabconnex[m_tabarete[j]->gets2()];
                   }
               }
           }
       }
for(int q=0;q<tabconnex.size()-1;q++)
{
    if(tabconnex[q]==tabconnex[q+1])
    {
        cpt++;
    }
}
if(cpt==tabconnex.size()-1)
{
    m_casfinal.push_back(casfin[i]);
}
}
std::cout<<"Il y a: ";
std::cout<<m_casfinal.size();
std::cout<<"  solutions";

    std::vector<float>pond_arete;
    std::vector<std::vector<float>>ponde_toutes_les_aretes;
    std::vector<float>poid_t;
int taille=m_tabarete[0]->getaillepond();
for(int z=0;z<taille;z++)
{
    poid_t.push_back(0.0);
}
    for(int i=0;i<m_casfinal.size();i++)
    {
        for(int j=0;j<m_tabarete.size();j++)
        {

                if(m_casfinal[i][j]==true)
                {
                    for(int k=0;k<taille;k++)
                    {
                        pond_arete.push_back(m_tabarete[j]->getpond(k));
                    }
                    ponde_toutes_les_aretes.push_back(pond_arete);
                    pond_arete.clear();
                }
        }
        for(int r=0;r<taille;r++)
        {
            for(int a=0;a<ponde_toutes_les_aretes.size();a++)
            {
                poid_t[r]=poid_t[r]+ponde_toutes_les_aretes[a][r];
            }
        }
        m_poids.push_back(poid_t);

    for(int z=0;z<taille;z++)
{
  //  std::cout<<poid_t[z];
    poid_t[z]=0.0;
}

//std::cout<<std::endl;
        }
for(int q=m_poids.size()-1;q>-1;q--)
{
    for(int s=0;s<taille;s++)
    {

        if(q>0)
{m_poids[q][s]=m_poids[q][s]-m_poids[q-1][s];

}
    }
}

}
/*
void graphe::optimum()
{
    std::vector<float>pond_arete;
    std::vector<std::vector<float>>ponde_toutes_les_aretes;
    std::vector<float>poid_t;
    std::vector<std::vector<float>>m_poids;
    for(int i=0; i<m_tabarete[0]->getaillepond(); ++i)
    {
        poid_t.push_back(0.0);
    }
    for(unsigned int z=0; z<m_casfinal.size(); z++)
    {
        for(unsigned int v=0; v<m_tabarete.size(); v++)
        {
            if(m_casfinal[z][v]==1)
            {
                for(int i=0; i<m_tabarete[v]->getaillepond(); ++i)
                {
                    pond_arete.push_back(m_tabarete[v]->getpond(i));
                }
                ponde_toutes_les_aretes.push_back(pond_arete);
                pond_arete.clear();

            }
                for(int i=0; i<m_tabarete[v]->getaillepond(); ++i)
                {
                    poid_t[i]+=ponde_toutes_les_aretes[v][i];
                }
            m_poids.push_back(poid_t);
                for(int i=0; i<m_tabarete[v]->getaillepond(); ++i)
                {
                    poid_t[i]=0;
                }
                }
    }
    for(int i=0;i<m_poids.size();i++)
    {
        for(int j=0;j<m_tabarete[0]->getaillepond();j++)
        {
            std::cout<<m_poids[i][j];
        }
        std::cout<<std::endl;
    }
}
*/
/** \brief : Faire l'optimum de Pareto et le dessiner dans le repère. Appliquer un coef pour pas avoir des points en dehors du repère.
 *
 * \param Svgfile &svgout
 * \return
 *
 */
void graphe::optimum1(Svgfile &svgout)
{
    std::vector<float>pond_arete;
    std::vector<std::vector<float>>ponde_toutes_les_aretes;
    std::vector<float>poid_t;
int taille=m_tabarete[0]->getaillepond();
double m_xmax=0.0;// pour bien placer le repere dans le svg
float cout1max=0.0;//
float cout2max=0.0;
int indice;
float minimum;

 //   std::cout<<"Poids 1:"<<m_poids[q][0]<<"       poids2:"<<m_poids[q][1];
 //   std::cout<<std::endl;


    for(int i=0;i<m_sommets.size();i++)
    {
        if(m_sommets[i]->getx()>m_xmax)
        {
            m_xmax=m_sommets[i]->getx();
        }
    }
m_xmax=m_xmax+800;

for(int q=0;q<m_poids.size();q++)
{
    for(int s=0;s<taille;s++)
    {
        if(s==0)
        {
            if(cout1max<m_poids[q][s])
            {
                cout1max=m_poids[q][s];
            }
        }
        if(s==1)
        {
            if(cout2max<m_poids[q][s])
            {
                cout2max=m_poids[q][s];
            }
        }
    }
}

cout1max=cout1max/600;
cout2max=cout2max/600;
for(int q=0;q<m_poids.size();q++)
{
    for(int s=0;s<taille;s++)
    {
        if(s==0)
        {
                m_poids[q][s]=m_poids[q][s]/cout1max;
        }
        else
        {
                m_poids[q][s]=m_poids[q][s]/cout2max;
        }
    }
    //if(q!=m_poids.size()-1)
   // {
   // if((m_poids[q][0]==m_poids[q+1][0])&&(m_poids[q][1]==m_poids[q+1][1]))
    //{
   //svgout.addDisk(m_poids[q][0]+m_xmax,800-m_poids[q][1],100,"green");
   // }
   // else{svgout.addDisk(m_poids[q][0]+m_xmax,800-m_poids[q][1],4,"green");}
    //}
    //else{svgout.addDisk(m_poids[q][0]+m_xmax,800-m_poids[q][1],4,"green");}
    svgout.addDisk(m_poids[q][0]+m_xmax,800-m_poids[q][1],5,"green");
}
minimum=m_poids[0][0];
for(int q=0;q<m_poids.size();q++)
{

        if(minimum>m_poids[q][1])
        {
            minimum=m_poids[q][1];
            indice=q;
        }
        if(minimum==m_poids[q][1])
        {
            if(m_poids[q][0]<m_poids[indice][0])
            {
                indice=q;
            }
        }
}
svgout.addDisk(m_poids[indice][0]+m_xmax,800-m_poids[indice][1],5,"red");

float i1,i2,i4,i5;
i4=m_poids[indice][0];
i5=m_poids[indice][1];

//trier selon le cout 2 puis par cout 1 pour trouver l'optimum
for(int q=0;q<m_poids.size()-1;q++)
{
for(int q=0;q<m_poids.size()-1;q++)
{
    if(m_poids[q][1]>m_poids[q+1][1])
        {
            for(int s=0;s<taille;s++)
        {
            minimum=m_poids[q][s];
            m_poids[q][s]=m_poids[q+1][s];
            m_poids[q+1][s]=minimum;
        }
        }
}
}

for(int q=0;q<m_poids.size()-1;q++)
{
    for(int q=0;q<m_poids.size()-1;q++)
{
    if(m_poids[q][1]==m_poids[q+1][1])
        {
            if(m_poids[q][0]>m_poids[q+1][0])
            for(int s=0;s<taille;s++)
        {
            minimum=m_poids[q][s];
            m_poids[q][s]=m_poids[q+1][s];
            m_poids[q+1][s]=minimum;
        }
        }
}
}
i1=m_poids[0][1];
i2=m_poids[0][0];
for(int q=0;q<m_poids.size()-1;q++)
{
    if(m_poids[q][1]!=m_poids[q+1][1])
    {
        i1=m_poids[q+1][1];
        if(i2>m_poids[q+1][0])
        {
            i2=m_poids[q+1][0];
            svgout.addDisk(i2+m_xmax,800-i1,5,"red");
            svgout.addLine(i2+m_xmax,800-i1,i4+m_xmax,800-i5,2,"red");
            i4=m_poids[q+1][0];
            i5=m_poids[q+1][1];
        }
    }
}
}
/** \brief : Destructeur de la classe graphe
 *
 * \param Svgfile &svgout
 * \return
 *
 */
graphe::~graphe()
{
    //dtor
}

/** \brief : Afficher les graphes de Kruskal en fonction des pondérations
 *
 * \param Svgfile &svgout
 * \return
 *
 */
void graphe::kruskal(Svgfile &svgout)
{
            std::vector<std::vector<int>> cas2;
            std::vector<bool> cas(m_tabarete.size(),true);
            std::vector<std::vector<bool>> casfin;


            for(int j=0; j<m_tabarete.size()-m_sommets.size()-1;j++)
            {
                    cas[j] = false;
            }
            do{
            casfin.push_back(cas);
            }while(std::next_permutation(cas.begin(),cas.end()));
//dernier filtrestd::cout
   std::vector<int> tabconnex(m_sommets.size(),0);
   int cpt,premier;
   float compteur=0.0;
   float compteur2=0.0;

   for(int i=0;i<casfin.size();i++)
   {
    for(unsigned int y=0;y<tabconnex.size();y++)
   {
       tabconnex[y]=y;
   }
       cpt=0;
       for(int j=0;j<m_tabarete.size();j++)
       {
           if(casfin[i][j]==true)
           {

                premier=tabconnex[m_tabarete[j]->gets1()];
               tabconnex[m_tabarete[j]->gets1()]=tabconnex[m_tabarete[j]->gets2()];
               for(int d=0;d<tabconnex.size();d++)
               {
                   if(tabconnex[d]==premier)
                   {
                       tabconnex[d]=tabconnex[m_tabarete[j]->gets2()];
                   }
               }
           }
       }
for(int q=0;q<tabconnex.size()-1;q++)
{
    if(tabconnex[q]==tabconnex[q+1])
    {
        cpt++;
    }
}
if(cpt==tabconnex.size()-1)
{
    m_casfinal.push_back(casfin[i]);
}
}


int indice;
bool a=1;
float minimum;

minimum=m_poids[0][0];
//Kruskal pour cout 2
for(int i=0;i<m_tabarete.size();i++)
{
        m_tabarete[i]->setok(0);
}
//Kruskal pour cout 1

for(int q=0;q<m_poids.size();q++)
{

        if(minimum>m_poids[q][1])
        {
            minimum=m_poids[q][1];
            indice=q;
        }
        if(minimum==m_poids[q][1])
        {
            if(m_poids[q][0]<m_poids[indice][0])
            {
                indice=q;
            }
        }
}
for(int i=0;i<m_tabarete.size();i++)
{
    if(m_casfinal[indice][i]==1)
    {
        m_tabarete[i]->setok(a);
    }
}
for(int i=0;i<m_tabarete.size();i++)
{
    if(m_tabarete[i]->getok()==1)
    {
    svgout.addLine(m_sommets[m_tabarete[i]->gets1()]->getx(),m_sommets[m_tabarete[i]->gets1()]->gety()+2*m_ymax+200,m_sommets[m_tabarete[i]->gets2()]->getx(),m_sommets[m_tabarete[i]->gets2()]->gety()+2*m_ymax+200,2,"red");
    compteur=m_poids[indice][1];
    compteur2=m_poids[indice][0];
    }
}
    for(int i=0; i<m_sommets.size(); i++)
    {
        svgout.addDisk(m_sommets[i]->getx(),m_sommets[i]->gety()+2*m_ymax+200,10,"white");
        svgout.addCircle(m_sommets[i]->getx(),m_sommets[i]->gety()+2*m_ymax+200,10,2,"black");
        svgout.addText3(m_sommets[i]->getx()-3,m_sommets[i]->gety()+5+2*m_ymax+200,i,"blue");
    }
        svgout.addText4(m_xmax+300-800,2*m_ymax+400,compteur,"blue");
        svgout.addText4(m_xmax+250-800,2*m_ymax+400,compteur2,"blue");
        svgout.addText(m_xmax+100-800,2*m_ymax+400,"PONDERATION:","blue");

for(int i=0;i<m_tabarete.size();i++)
{
        m_tabarete[i]->setok(0);
}
//Kruskal pour cout 1
minimum=m_poids[0][0];

for(int q=0;q<m_poids.size();q++)
{

        if(minimum>m_poids[q][0])
        {
            minimum=m_poids[q][0];
            indice=q;
        }
        if(minimum==m_poids[q][0])
        {
            if(m_poids[q][1]<m_poids[indice][1])
            {
                indice=q;
            }
        }
}
for(int i=0;i<m_tabarete.size();i++)
{
    if(m_casfinal[indice][i]==1)
    {
        m_tabarete[i]->setok(a);
    }
}
for(int i=0;i<m_tabarete.size();i++)
{
    if(m_tabarete[i]->getok()==1)
    {
    svgout.addLine(m_sommets[m_tabarete[i]->gets1()]->getx(),m_sommets[m_tabarete[i]->gets1()]->gety()+m_ymax+200,m_sommets[m_tabarete[i]->gets2()]->getx(),m_sommets[m_tabarete[i]->gets2()]->gety()+m_ymax+200,2,"red");
    compteur=m_poids[indice][1];
    compteur2=m_poids[indice][0];
    }
}
    for(int i=0; i<m_sommets.size(); i++)
    {
        svgout.addDisk(m_sommets[i]->getx(),m_sommets[i]->gety()+m_ymax+200,10,"white");
        svgout.addCircle(m_sommets[i]->getx(),m_sommets[i]->gety()+m_ymax+200,10,2,"black");
        svgout.addText3(m_sommets[i]->getx()-3,m_sommets[i]->gety()+5+m_ymax+200,i,"blue");
    }
        svgout.addText(100,m_ymax+200,"KRUSKAL","blue");
        svgout.addText4(m_xmax+300-800,m_ymax+400,compteur,"blue");
        svgout.addText4(m_xmax+250-800,m_ymax+400,compteur2,"blue");
        svgout.addText(m_xmax+100-800,m_ymax+400,"PONDERATION:","blue");
}


void graphe::dijkstra()
{
    //int sommet;
    //std::cout<<"veuillez saisir un sommet:";
    //std::cin>>sommet;

    //faire un tableau de N*N avec N l'ordre du graphe

  //  int etapes=m_sommet.size();
  //  tab
  //  for(int=0;i<=etapes;i++)

    /*Pour chaque sommet en partant du sommet de depart
        faire une liste des arettes
        pour chaque arettes
                ajouter le poids de l'arette à la distance deja parcouru
                noter le sommet précédent
        interdire le sommet le sommet visité
        recherche du chemin minimal dans les colonnes non interdites
       recopier ce chemin dans la colonne de l'etape suivante
    */
    //m_sommets.find(sommet)->setetat(true);
}
