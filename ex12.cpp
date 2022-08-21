#include "Simple_window.h"
#include "Graph.h"

Point coords(const Circle &crcl, const int &angle)
{
    return Point{crcl.center().x + int(crcl.radius() * cos(-M_PI * angle / 180)), crcl.center().y + int(crcl.radius() * sin(-M_PI * angle / 180))};
}

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window
    Point center{x_max() / 2, y_max() / 2};

    Simple_window win{top_left, x_max(), y_max(), "Canvas"};
    win.color(Color::white);

    Circle c{center, 200};
    c.set_style(Line_style(Line_style::solid, 2));
    c.set_color(Color::red);
    win.attach(c); //attach poly to window

    Vector_ref<Mark> vm;
    for (int i = 0; i < 360; i += 30)
    {
        vm.push_back(new Mark(coords(c, i), 'o'));
        win.attach(vm[vm.size() - 1]);
        win.wait_for_button();
        vm[vm.size() - 1].set_color(Color::white);
        win.attach(c);
    }
}
