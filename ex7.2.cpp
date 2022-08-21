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
    const int cell = 80;
    const int k = 32;
    const int count = 256;

    Vector_ref<Rectangle> vr;
    int r = 0, g = 0, b = 0;
    do
    {
        for (int y = 0; y < count / k; y++)
        {
            for (int x = 0; x < count / k; x++)
            {
                vr.push_back(new Rectangle{Point{x * cell, y * cell}, cell, cell});
                vr[vr.size() - 1].set_fill_color(fl_rgb_color(r, g, b));
                win.attach(vr[vr.size() - 1]);
                b += k;
                if (b >= count)
                {
                    b = 0;
                    g += k;
                    if (g >= count)
                    {
                        g = 0;
                        r += k;
                    }
                }
            }
        }
        win.wait_for_button();
    } while (r < count);
}