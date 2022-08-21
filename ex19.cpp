#include "Simple_window.h"
#include "Graph.h"

struct Star : Closed_polyline
{
    Star(Point center, int count_of_vertices, int radius);

private:
    Point c;
    int count;
    int R;
    Point coords(const double &angle, const int &cnt);
};

Star::Star(Point center, int count_of_vertices, int radius)
    : c{center}, count{count_of_vertices}, R{radius}
{
    if (count_of_vertices < 4)
        error("The count of vertices is less than four!");
    double step = 360.0 / count / 2;
    for (double i = 0, cnt = 0; i < 360; i += step, cnt++)
        add(coords(i, cnt));
}

Point Star::coords(const double &angle, const int &cnt)
{
    double k = (cnt % 2) ? 0.4 : 1.0;
    int x = int(round(k * R * cos(angle * M_PI / 180)));
    int y = int(round(k * R * sin(angle * M_PI / 180)));
    return Point{c.x + x, c.y - y};
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window
    Point center{x_max() / 2, y_max() / 2};

    Simple_window win{top_left, x_max(), y_max(), "Canvas"};
    win.color(Color::white);

    Vector_ref<Star> vs;
    for (int i = 4; i < 40; i++)
    {
        vs.push_back(new Star(center, i, 300));
        vs[vs.size() - 1].set_fill_color(Color(258 - i*5));
        vs[vs.size() - 1].set_color(Color(258 - i*5));
        win.attach(vs[vs.size() - 1]);
        win.wait_for_button();
        vs[vs.size() - 1].set_fill_color(Color(255));
        vs[vs.size() - 1].set_color(Color(255));
        win.attach(vs[vs.size() - 1]);
    }
}
