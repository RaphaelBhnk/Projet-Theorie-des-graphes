#ifndef ARETE_H
#define ARETE_H
#include <string>
#include <vector>
#include <iostream>

class Arete
{
    public:
        Arete(int,int,int);
        void afficherArete()const;
        ~Arete();
        int gets1() const;
        int gets2() const;
        void pushpond(float);
        float getpond(int i);
        int getaillepond();
        bool getok();
        void setok(bool);

    protected:

    private:
        int m_id;
        int m_s1;
        int m_s2;
        std::vector<float> m_pond;
        bool m_ok;

};
#endif // ARETE_H
