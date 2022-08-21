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

struct Box : Shape
{
    Box(Point p, int ww, int hh, int rr, const string s);
    void draw_lines() const;

private:
    Point p1;
    Point p2;
    Point p3;
    Point p4;
    int w; //width of a box
    int h; //height of a box
    int r; //rounding radius
    //adding angles for drawing arcs
    vector<Point> vc{Point{90, 180}, Point{0, 90}, Point{270, 360}, Point{180, 270}};
    string str;
};

Box::Box(Point p, int ww, int hh, int rr, const string s = "")
    : p1{p}, w{ww}, h{hh}, r{rr}, str{s}
{
    if (r > h / 2 || r > w / 2)
        error("Invalid rounding radius");

    p2 = Point{p1.x + w - r * 2, p1.y};
    p3 = Point{p2.x, p2.y + h - r * 2};
    p4 = Point{p3.x - w + r * 2, p3.y};

    //p1...p4 - points for drawing arcs
    add(p1);
    add(p2);
    add(p3);
    add(p4);

    //adding points of straight lines
    add(Point{p1.x + r, p1.y});
    add(Point{p2.x + r, p2.y});
    add(Point{p2.x + r * 2, p2.y + r});
    add(Point{p3.x + r * 2, p3.y + r});
    add(Point{p3.x + r, p3.y + r * 2});
    add(Point{p4.x + r, p4.y + r * 2});
    add(Point{p4.x, p4.y + r});
    add(Point{p1.x, p1.y + r});
}

void Box::draw_lines() const
{
    //arcs drawing
    if (color().visibility())
    {
        for (int i = 0; i < 4; i++)
            fl_arc(point(i).x, point(i).y, r + r, r + r, vc[i].x, vc[i].y);

        //straight lines drawing
        for (int i = 4; i < number_of_points(); i += 2)
            fl_line(point(i).x, point(i).y, point(i + 1).x, point(i + 1).y);

        //text drawing
        fl_draw(str.c_str(), p1.x + w / 2 - 9 * str.size() / 2, p1.y + h / 2 + 5);
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

    Box window{Point{100, 100}, 100, 40, 10, "Window"};
    Box simple_window{Point{50, 200}, 200, 40, 10, "Simple_window"};
    Arrow arrow1{Point{150, 200}, Point{150, 140}};

    win.attach(window);
    win.attach(simple_window);
    win.attach(arrow1);

    win.wait_for_button();
}