#include "Simple_window.h"
#include "Graph.h"

Point n(const Circle &c)
{
    return Point{c.center().x, c.center().y - c.radius()};
}

Point s(const Circle &c)
{
    return Point{c.center().x, c.center().y + c.radius()};
}

Point w(const Circle &c)
{
    return Point{c.center().x - c.radius(), c.center().y};
}

Point e(const Circle &c)
{
    return Point{c.center().x + c.radius(), c.center().y};
}

Point center(const Circle &c)
{
    return c.center();
}

Point ne(const Circle &c)
{
    return Point{c.center().x + int(c.radius() / sqrt(2)), c.center().y - int(c.radius() / sqrt(2))};
}

Point se(const Circle &c)
{
    return Point{c.center().x + int(c.radius() / sqrt(2)), c.center().y + int(c.radius() / sqrt(2))};
}

Point sw(const Circle &c)
{
    return Point{c.center().x - int(c.radius() / sqrt(2)), c.center().y + int(c.radius() / sqrt(2))};
}

Point nw(const Circle &c)
{
    return Point{
        c.center().x - abs(int(c.radius() * cos(3 * M_PI / 4))),
        c.center().y - abs(int(c.radius() * sin(3 * M_PI / 4)))};
}

//---------------------------------------------------------------------------------------

Point n(const Ellipse &e)
{
    return Point{e.center().x, e.center().y - e.minor()};
}

Point s(const Ellipse &e)
{
    return Point{e.center().x, e.center().y + e.minor()};
}

Point e(const Ellipse &e)
{
    return Point{e.center().x + e.major(), e.center().y};
}

Point w(const Ellipse &e)
{
    return Point{e.center().x - e.major(), e.center().y};
}

Point center(const Ellipse &e)
{
    return e.center();
}

Point ne(const Ellipse &e)
{
    return Point{e.center().x + int(e.major() / sqrt(2)), e.center().y - int(e.minor() / sqrt(2))};
}

Point se(const Ellipse &e)
{
    return Point{e.center().x + int(e.major() / sqrt(2)), e.center().y + int(e.minor() / sqrt(2))};
}

Point sw(const Ellipse &e)
{
    return Point{e.center().x - int(e.major() / sqrt(2)), e.center().y + int(e.minor() / sqrt(2))};
}

Point nw(const Ellipse &e)
{
    return Point{e.center().x - int(e.major() / sqrt(2)), e.center().y - int(e.minor() / sqrt(2))};
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window

    const int width = 1320; //1320
    const int height = 700; //700
    Simple_window win{top_left, width, height, "Canvas"};
    Line_style lst{Line_style::solid, 2};

    Ellipse ellipse{Point{650, 300}, 200, 100};
    ellipse.set_style(lst);
    ellipse.set_color(Color(99));
    win.attach(ellipse);

    Rectangle rec{Point{450,200}, 400, 200};
    win.attach(rec);

    Mark m{Point{650,300},'x'};
    win.attach(m);

    Point p = nw(ellipse);
    Circle c{p, 5};
    win.attach(c);

    win.wait_for_button();
}