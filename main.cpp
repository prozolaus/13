#include "Simple_window.h"
#include "Graph.h"

struct Arrow : Line
{
    using Line::Line;
    void draw_lines() const;
};

void Arrow::draw_lines() const
{
    Line::draw_lines();
    // add arrowhead: p2 and two points
    double line_len =
        sqrt(double(pow(point(1).x - point(0).x, 2) + pow(point(1).y - point(0).y, 2))); // length of p1p2

    const double k1 = 25;
    const double k2 = 5;

    // coordinates of the a point on p1p2 with distance 25 from p2
    double pol_x = k1 / line_len * point(0).x + (1 - k1 / line_len) * point(1).x;
    double pol_y = k1 / line_len * point(0).y + (1 - k1 / line_len) * point(1).y;

    // pl is 5 away from p1p2 on the "left", pl_pol is orthogonal to p1p2
    double pl_x = pol_x + k2 / line_len * (point(1).y - point(0).y);
    double pl_y = pol_y + k2 / line_len * (point(0).x - point(1).x);

    // pr is 5 away from p1p2 on the "right", pr_pol is orthogonal to p1p2a
    double pr_x = pol_x + k2 / line_len * (point(0).y - point(1).y);
    double pr_y = pol_y + k2 / line_len * (point(1).x - point(0).x);

    // draw arrowhead - is always filled in line color
    if (color().visibility())
    {
        fl_begin_complex_polygon();
        fl_vertex(point(1).x, point(1).y);
        fl_vertex(pl_x, pl_y);
        fl_vertex(pr_x, pr_y);
        fl_end_complex_polygon();
    }
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window

    const int width = 1320; //1320
    const int height = 700; //700
    Simple_window win{top_left, width, height, "Canvas"};
    Line_style lst{Line_style::solid, 1};

    Arrow arrow{Point{200, 200}, Point{800, 100}};
    arrow.set_style(lst);
    arrow.set_color(Color(99));
    win.attach(arrow);

    win.wait_for_button();
}