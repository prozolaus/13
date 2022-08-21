#include "Simple_window.h"
#include "Graph.h"

struct Poly : Polygon
{
    Poly(initializer_list<Point> lst);
};

Poly::Poly(initializer_list<Point> lst)
{
    for (auto p : lst) add(p);
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window
    Point center{x_max() / 2, y_max() / 2};

    Simple_window win{top_left, x_max(), y_max(), "Canvas"};
    win.color(Color::white);

    Poly poly{center,Point{100,100},Point{1000,100},Point{1200,100}};
    win.attach(poly);
    win.wait_for_button();
}
