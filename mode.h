#ifndef MODE_H
#define MODE_H

enum Gamemode {
	NORMAL,
	ALLPASS,
	ALLFAIL,
};

enum LineRendering {
	SHOWING,
	HIDING
};

extern Gamemode mode;
extern LineRendering line_rendering;
#endif