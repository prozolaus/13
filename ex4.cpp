#include "Simple_window.h"
#include "Graph.h"

Point n(const Rectangle &r)
{
    return Point{r.point(0).x + r.width() / 2, r.point(0).y};
}

Point s(const Rectangle &r)
{
    return Point{r.point(0).x + r.width() / 2, r.point(0).y + r.height()};
}

Point e(const Rectangle &r)
{
    return Point{r.point(0).x + r.width(), r.point(0).y + r.height() / 2};
}

Point w(const Rectangle &r)
{
    return Point{r.point(0).x, r.point(0).y + r.height() / 2};
}

Point center(const Rectangle &r)
{
    return Point{r.point(0).x + r.width() / 2, r.point(0).y + r.height() / 2};
}

Point ne(const Rectangle &r)
{
    return Point{r.point(0).x + r.width(), r.point(0).y};
}

Point se(const Rectangle &r)
{
    return Point{r.point(0).x + r.width(), r.point(0).y + r.height()};
}

Point sw(const Rectangle &r)
{
    return Point{r.point(0).x, r.point(0).y + r.height()};
}

Point nw(const Rectangle &r)
{
    return Point{r.point(0).x, r.point(0).y};
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window

    const int width = 1320; //1320
    const int height = 700; //700
    Simple_window win{top_left, width, height, "Canvas"};
    Line_style lst{Line_style::solid, 2};

    Rectangle rec{Point{450, 200}, 400, 200};
    rec.set_style(lst);
    rec.set_color(Color(99));
    win.attach(rec);

    Point p = nw(rec);
    Circle c{p,10};
    win.attach(c);

    win.wait_for_button();
}