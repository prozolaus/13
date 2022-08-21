#include "Simple_window.h"
#include "Graph.h"

struct Right_triangle : Polygon
{
    Right_triangle(Point aa, Point bb, Point cc);

private:
    Point a, b, c;
    void check();
};

Right_triangle::Right_triangle(Point aa, Point bb, Point cc)
    : a{aa}, b{bb}, c{cc}
{
    check();
    add(a);
    add(b);
    add(c);
}

void Right_triangle::check()
{
    double ab = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    double bc = sqrt(pow(c.x - b.x, 2) + pow(c.y - b.y, 2));
    double ca = sqrt(pow(c.x - a.x, 2) + pow(c.y - a.y, 2));

    double cos_alpha = (pow(ab, 2) + pow(ca, 2) - pow(bc, 2)) / (2 * ab * ca);
    double cos_beta = (pow(ab, 2) + pow(bc, 2) - pow(ca, 2)) / (2 * ab * bc);
    double cos_gamma = (pow(bc, 2) + pow(ca, 2) - pow(ab, 2)) / (2 * ca * bc);

    double alpha = acos(cos_alpha) * 180 / M_PI;
    double beta = acos(cos_beta) * 180 / M_PI;
    double gamma = acos(cos_gamma) * 180 / M_PI;

    if ((round(alpha) == 90 || round(beta) == 90 || round(gamma) == 90) && (round(alpha + beta + gamma) == 180))
        return;
    else
        error("this isn't right triangle!");
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window
    Point center{x_max() / 2, y_max() / 2};

    Simple_window win{top_left, x_max(), y_max(), "Canvas"};
    win.color(Color::white);

    Vector_ref<Right_triangle> vr;
    const int cell = 80;
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
        {
            vr.push_back(new Right_triangle{Point{i * cell, j * cell / 2}, Point{i * cell + cell, j * cell / 2}, Point{i * cell + cell, j * cell / 2 + cell}});
            vr.push_back(new Right_triangle{Point{i * cell, j * cell / 2}, Point{i * cell, j * cell / 2 + cell}, Point{i * cell + cell, j * cell / 2 + cell}});
            vr[vr.size() - 2].set_fill_color(Color{i * 16 + j++});
            vr[vr.size() - 1].set_fill_color(Color{i * 16 + j});
            win.attach(vr[vr.size() - 2]);
            win.attach(vr[vr.size() - 1]);
        }

    win.wait_for_button();
}
