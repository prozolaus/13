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

    const int width = 1366;
    const int height = 768;
    Simple_window win{top_left, width, height, "Canvas"};
    Point center{x_max() / 2, y_max() / 2};
    int thickness = 5;
    Line_style lst{Line_style::solid, thickness};

    Vector_ref<Line> vl;
    for (int i = 0; i < 256; i++)
    {
        vl.push_back(new Line{Point{i * thickness, 0}, Point{i * thickness, y_max()}});
        vl[vl.size() - 1].set_color(fl_rgb_color(0, i, 0));
        vl[vl.size() - 1].set_style(lst);
        win.attach(vl[vl.size() - 1]);
    }

    win.wait_for_button();
}