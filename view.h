#ifndef VIEW_H
#define VIEW_H

enum Viewmode {
	FPS,
	TPS,
};

extern Viewmode view;

void view_change() {
	if (view == TPS) {
		glMatrixMode(GL_PROJECTION);
		glTranslatef(0, 0.2, 1.0);
		view = FPS;
		return;
	}
	else if (view == FPS) {
		glMatrixMode(GL_PROJECTION);
		glTranslatef(0.0, -0.2, -1.0);
		view = TPS;
		return;
	}
}
#endif