#include "Simple_window.h"
#include "Graph.h"

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window

    const int width = 1366;
    const int height = 768;
    Simple_window win{top_left, width, height, "Canvas"};
    //Line_style lst{Line_style::solid, 2};
    //Point center{650, 350};

    int x_grid = 80;
    int y_grid = 40;
    Lines grid;
    for (int x = x_grid; x < width; x += x_grid)
        grid.add(Point{x, 0}, Point{x, height});

    for (int y = y_grid; y < height; y += y_grid)
        grid.add(Point{0, y}, Point{width, y});

    Color clr{99};
    grid.set_color(clr);

    win.attach(grid);

    win.wait_for_button();
}