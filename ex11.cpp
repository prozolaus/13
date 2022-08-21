#include "Simple_window.h"
#include "Graph.h"

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window

    const int width = 1366;
    const int height = 768;
    Simple_window win{top_left, width, height, "Canvas"};
    int thickness = 5;
    Line_style lst{Line_style::solid, thickness};
    Point cntr{x_max() / 2, y_max() / 2};

    Ellipse el{cntr, 300, 200};
    win.attach(el);
    Point f1 = el.focus1();
    Mark mf1{f1, 'x'};
    win.attach(mf1);
    Point f2 = el.focus2();
    Mark mf2{f2, 'x'};
    win.attach(mf2);

    Axis ax{Axis::x, cntr, 400};
    win.attach(ax);
    Axis ay{Axis::y, cntr, 300};
    win.attach(ay);

    double angle = -2 * M_PI / 16;
    Point p{el.major() * cos(angle) + cntr.x, el.minor() * sin(angle) + cntr.y};

    Line l1{p, f1};
    win.attach(l1);
    Line l2{p, f2};
    win.attach(l2);

    win.wait_for_button();
}