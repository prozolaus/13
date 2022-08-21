#include "Simple_window.h"
#include "Graph.h"

struct Regular_polygon : Closed_polyline
{
    Regular_polygon(Point center, int count_of_sides, int radius);
    Vector_ref<Point> get_points() { return vp; }

private:
    Point c;
    int count;
    int R;
    Point coords(const double &angle);
    Vector_ref<Point> vp;
};

Regular_polygon::Regular_polygon(Point center, int count_of_sides, int radius)
    : c{center}, count{count_of_sides}, R{radius}
{
    if (count_of_sides < 3)
        error("The count of sides is less than three!");
    int step = round(360 / count);
    for (double i = 0; i < 360; i += step)
        vp.push_back(new Point(coords(i)));
}

Point Regular_polygon::coords(const double &angle)
{
    int x = round(R * cos(angle * M_PI / 180));
    int y = round(R * sin(angle * M_PI / 180));
    return Point{c.x + x, c.y - y};
}

//--------------------------------------------------------------------------------

struct Right_triangle : Polygon
{
    Right_triangle(Point aa, Point bb, Point cc);

private:
    Point a, b, c;
    void check();
};

Right_triangle::Right_triangle(Point aa, Point bb, Point cc)
    : a{aa}, b{bb}, c{cc}
{
    check();
    add(a);
    add(b);
    add(c);
}

void Right_triangle::check()
{
    double ab = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    double bc = sqrt(pow(c.x - b.x, 2) + pow(c.y - b.y, 2));
    double ca = sqrt(pow(c.x - a.x, 2) + pow(c.y - a.y, 2));

    double cos_alpha = (pow(ab, 2) + pow(ca, 2) - pow(bc, 2)) / (2 * ab * ca);
    double cos_beta = (pow(ab, 2) + pow(bc, 2) - pow(ca, 2)) / (2 * ab * bc);
    double cos_gamma = (pow(bc, 2) + pow(ca, 2) - pow(ab, 2)) / (2 * ca * bc);

    double alpha = acos(cos_alpha) * 180 / M_PI;
    double beta = acos(cos_beta) * 180 / M_PI;
    double gamma = acos(cos_gamma) * 180 / M_PI;

    if ((round(alpha) == 90 || round(beta) == 90 || round(gamma) == 90) && (round(alpha + beta + gamma) == 180))
        return;
    else
        error("this isn't right triangle!");
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window
    Point center{x_max() / 2, y_max() / 2};

    Simple_window win{top_left, x_max(), y_max(), "Canvas"};
    win.color(Color::white);

    Regular_polygon r{center, 8, 300};
    Vector_ref<Point> vp = r.get_points();

    Vector_ref<Right_triangle> vr;
    vr.push_back(new Right_triangle{vp[0], vp[1], vp[5]});
    vr.push_back(new Right_triangle{vp[1], vp[2], vp[5]});
    vr.push_back(new Right_triangle{vp[2], vp[3], vp[7]});
    vr.push_back(new Right_triangle{vp[3], vp[4], vp[7]});
    vr.push_back(new Right_triangle{vp[4], vp[5], vp[1]});
    vr.push_back(new Right_triangle{vp[5], vp[6], vp[1]});
    vr.push_back(new Right_triangle{vp[6], vp[7], vp[2]});
    vr.push_back(new Right_triangle{vp[7], vp[0], vp[3]});

    for (int i = 0; i < vr.size(); i++)
    {
        vr[i].set_fill_color(i);
        win.attach(vr[i]);
        win.wait_for_button();
    }
}
