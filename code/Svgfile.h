#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include <string>
#include <fstream>
#include <set>

constexpr char defcol[] = "black";

class Svgfile
{
    public:
        Svgfile(std::string _filename = "output.svg", int _width=4000, int _height=3000);
        ~Svgfile();
        void addEllipse(double x, double y, double rx, double ry, std::string color);
        void addDisk(double x, double y, double r, std::string color=defcol);
        void addCircle(double x, double y, double r, double ep, std::string color=defcol);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);
        void addRectangle (double x,double y,double width,double height,std::string color=defcol);

        void addLine(double x1, double y1, double x2, double y2,double ep, std::string color=defcol);
        void addCross(double x, double y, double span, std::string color=defcol);

        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText2(double x, double y, double val, std::string color=defcol);
        void addText3(double x, double y, int val, std::string color=defcol);
        void addText4(double x, double y, float val, std::string color=defcol);


        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");
        static std::string makeRGB(int r, int g, int b);
void addgradient(double x, double y, double rx, double ry, std::string colorbegin, std::string colorend, std::string grad1);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};

#endif // SVGFILE_H_INCLUDED



