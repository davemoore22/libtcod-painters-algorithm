// Copyright 2019 Dave Moore
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

class Engine {
public :
    TCODList<Actor *> actors;
    Actor *player;
    Map *map;
    int fovRadius;

    int facing;

    Engine();
    ~Engine();
    void update();
    void render();
    void render_3d();
    void render_tile(int pos_x, int pos_y, int position);
    void setup_render();

private :
    bool computeFov;

    TCODConsole* OffScreenConsole;
    TCODConsole* DungeonWalls;
    TCODConsole* DungeonFloor;
    TCODConsole* DungeonCeiling;

    unsigned int width[13];
    unsigned int height[13];
    unsigned int src_x[13];
    unsigned int src_y[13];
    unsigned int dest_x[13];
    unsigned int dest_y[13];
};

extern Engine engine;
