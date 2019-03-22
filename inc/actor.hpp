class Actor {
public :
    int x,y; // position on map
    int ch; // ascii code
    TCODColor col; // color

    Actor(int x, int y, int ch, const TCODColor &col, bool is_player);
    void render() const;

private:

	bool is_player;
	const int offsetx = 82;
	const int offsety = 1;
};
