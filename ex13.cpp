#include "Simple_window.h"
#include "Graph.h"

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

    Vector_ref<Rectangle> vr;
    const int cell = 40;
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
        {
            vr.push_back(new Rectangle{Point{i * cell, j * cell}, cell, cell});
            vr[vr.size() - 1].set_fill_color(Color{i * 16 + j});
            vr[vr.size() - 1].set_color(Color{i * 16 + j});
            win.attach(vr[vr.size() - 1]);
        }

    win.wait_for_button();
}