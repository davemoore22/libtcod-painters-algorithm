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
