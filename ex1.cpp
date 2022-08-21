#include "Simple_window.h"
#include "Graph.h"

struct Arc : Shape
{
    Arc(Point p, int ww, int hh, double aa, double bb);
    void draw_lines() const;

private:
    int w;
    int h;
    double a;
    double b;
};

Arc::Arc(Point p, int ww, int hh, double aa, double bb)
    : w{ww}, h{hh}, a{aa}, b{bb}
{
    add(Point{p.x - w, p.y - h});
}

void Arc::draw_lines() const
{
    if (color().visibility())
        fl_arc(point(0).x, point(0).y, w + w, h + h, a, b);
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window

    const int width = 640;  //1320
    const int height = 640; //700
    Simple_window win{top_left, width, height, "Canvas"};
    Line_style lst{Line_style::solid, 2};

    Arc arc{Point{width / 2, height / 2}, 200, 100, 195, 345};
    arc.set_style(lst);
    win.attach(arc);

    win.wait_for_button();
}