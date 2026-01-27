#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
      public:
        static void handleMouse(int button, int state, int x, int y, int window_width, int window_height);
};

#endif // !MOUSE_H
