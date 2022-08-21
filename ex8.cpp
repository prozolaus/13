#include "Simple_window.h"
#include "Graph.h"

struct Regular_hexagon : Closed_polyline
{
    Regular_hexagon(Point cc, int RR);

private:
    Point c;
    int R;
    Point coords(const double &angle);
};

Regular_hexagon::Regular_hexagon(Point cc, int RR)
    : c{cc}, R{RR}
{
    for (double i = 0; i < 360; i += 60)
        add(coords(i));
}

Point Regular_hexagon::coords(const double &angle)
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
    Point center{x_max() / 2, y_max() / 2};
    int thickness = 5;
    Line_style lst{Line_style::solid, thickness};

    int R = 100;
    Regular_hexagon reg_hex{center, R};
    reg_hex.set_fill_color(Color(Color::blue));
    win.attach(reg_hex);


    win.wait_for_button();
}