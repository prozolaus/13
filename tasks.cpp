#include "Simple_window.h"
#include "Graph.h"

int main()
{
    using namespace Graph_lib; //our graphics facilities are in Graph_lib (defined in Graph.h)

    Point top_left{0, 0}; //will be top left corner of window

    const int width = 640;  //1320
    const int height = 640; //700
    Simple_window win{top_left, width, height, "Canvas"};
    //Line_style lst{Line_style::solid, 2};

    int x_grid = 80;
    int y_grid = 80;
    Lines grid;
    for (int x = x_grid; x < height; x += x_grid)
        grid.add(Point{x, 0}, Point{x, height});

    for (int y = y_grid; y < width; y += y_grid)
        grid.add(Point{0, y}, Point{width, y});

    Color clr{99};
    grid.set_color(clr);

    win.attach(grid);

    Vector_ref<Rectangle> vr;
    for (int i = 0; i < 8; i++)
    {
        vr.push_back(new Rectangle{Point{x_grid * i, y_grid * i}, x_grid, y_grid});
        vr[i].set_fill_color(Color(Color::red));
        win.attach(vr[i]);
    }

    Vector_ref<Image> vi;
    for (int i = 0; i < 3; i++)
    {
        vi.push_back(new Image{Point{0, y_grid * 2 * (i + 1)}, "vegetables.jpg"});
        vi[i].set_mask(Point{x_grid * 3, 0}, x_grid * 2, y_grid * 2);
        win.attach(vi[i]);
    }

    Image img{top_left, "vegetables.jpg"};
    img.set_mask(Point{x_grid * 3, y_grid * 3}, x_grid, y_grid);
    win.attach(img);
    for (int i = 1; i < 8; i++)
    {
        win.wait_for_button();
        img.move(x_grid, y_grid);
    }

    win.wait_for_button();
}