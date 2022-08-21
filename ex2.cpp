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
//---------------------------------------------------------------------

struct Box : Shape
{
    Box(Point p, int ww, int hh, int rr);
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
};

Box::Box(Point p, int ww, int hh, int rr)
    : p1{p}, w{ww}, h{hh}, r{rr}
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
        for (int i = 0; i < 4; i++)
            fl_arc(point(i).x, point(i).y, r + r, r + r, vc[i].x, vc[i].y);

    //straight lines drawing
    if (color().visibility())
        for (int i = 4; i < number_of_points(); i += 2)
            fl_line(point(i).x, point(i).y, point(i + 1).x, point(i + 1).y);
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window

    const int width = 1320; //1320
    const int height = 700; //700
    Simple_window win{top_left, width, height, "Canvas"};
    Line_style lst{Line_style::solid, 4};

    Box box{Point{100, 100}, 700, 500, 50};
    box.set_style(lst);
    box.set_color(Color(99));
    win.attach(box);

    win.wait_for_button();
}