#include "Simple_window.h"
#include "Graph.h"

struct Regular_hexagon : Closed_polyline
{
    Regular_hexagon(Point cc, int RR);
    Point center() { return c; }

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

Vector_ref<Regular_hexagon> seven(Point center, int R)
{
    double k = sqrt(3) / 2;
    Vector_ref<Regular_hexagon> vr;
    vector<Point> vp;
    vp.push_back(center);
    vp.push_back(Point{center.x, (int)round(center.y - R * k * 2)});
    vp.push_back(Point{center.x, (int)round(center.y + R * k * 2)});
    vp.push_back(Point{(int)round(center.x + 1.5 * R), (int)round(center.y - R * k)});
    vp.push_back(Point{(int)round(center.x + 1.5 * R), (int)round(center.y + R * k)});
    vp.push_back(Point{(int)round(center.x - 1.5 * R), (int)round(center.y - R * k)});
    vp.push_back(Point{(int)round(center.x - 1.5 * R), (int)round(center.y + R * k)});

    for (int i = 0; i < 7; i++)
    {
        vr.push_back(new Regular_hexagon{vp[i], R});
        vr[i].set_fill_color(Color(i));
    }
    return vr;
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

    int R = 50;
    double k = sqrt(3) / 2;
    int r = R * k;
    Point first{x_max() / 4, y_max() / 2};
    Vector_ref<Regular_hexagon> vr = seven(first, R);
    for (int i = 0; i < vr.size(); i++)
        win.attach(vr[i]);

    Point second{first.x + 4.5 * R, first.y - r};
    Vector_ref<Regular_hexagon> vr2 = seven(second, R);
    for (int i = 0; i < vr2.size(); i++)
        win.attach(vr2[i]);

    Point third{first.x + 3 * R, first.y + 4 * r};
    Vector_ref<Regular_hexagon> vr3 = seven(third, R);
    for (int i = 0; i < vr3.size(); i++)
        win.attach(vr3[i]);

    Point fourth{vr2[0].center().x + 4.5 * R, vr2[0].center().y - r};
    Vector_ref<Regular_hexagon> vr4 = seven(fourth, R);
    for (int i = 0; i < vr4.size(); i++)
        win.attach(vr4[i]);

    Point fifth{vr3[0].center().x + 4.5 * R, vr3[0].center().y - r};
    Vector_ref<Regular_hexagon> vr5 = seven(fifth, R);
    for (int i = 0; i < vr5.size(); i++)
        win.attach(vr5[i]);

    win.wait_for_button();
}