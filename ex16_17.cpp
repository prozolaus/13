#include "Simple_window.h"
#include "Graph.h"

struct Regular_polygon : Closed_polyline
{
    Regular_polygon(Point center, int count_of_sides, int radius);

private:
    Point c;
    int count;
    int R;
    Point coords(const double &angle);
};

Regular_polygon::Regular_polygon(Point center, int count_of_sides, int radius)
    : c{center}, count{count_of_sides}, R{radius}
{
    if (count_of_sides < 3)
        error("The count of sides is less than three!");
    int step = round(360 / count);
    for (double i = 0; i < 360; i += step)
        add(coords(i));
}

Point Regular_polygon::coords(const double &angle)
{
    int x = round(R * cos(angle * M_PI / 180));
    int y = round(R * sin(angle * M_PI / 180));
    return Point{c.x + x, c.y - y};
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window
    Point center{x_max() / 2, y_max() / 2};

    Simple_window win{top_left, x_max(), y_max(), "Canvas"};
    win.color(Color::white);

    Vector_ref<Regular_polygon> vr;
    const int cell = 24;
    double r = cell * cos(M_PI / 6);
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
        {
            vr.push_back(new Regular_polygon{Point{int(i * cell * 1.5 + cell), int(j * r * 2 + r + (i % 2 ? r : 0))}, 6, cell});
            vr[vr.size() - 1].set_fill_color(Color{i * 16 + j});
            win.attach(vr[vr.size() - 1]);
        }

    win.wait_for_button();
}
