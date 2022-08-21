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

    const int width = 1366;
    const int height = 768;
    Simple_window win{top_left, width, height, "Canvas"};
    int thickness = 5;
    Line_style lst{Line_style::solid, thickness};
    Point cntr{x_max() / 2, y_max() / 2};

    Regular_polygon r{cntr, 8, 300};
    win.attach(r);

    win.wait_for_button();
}