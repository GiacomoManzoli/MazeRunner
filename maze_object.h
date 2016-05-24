#ifndef MAZE_OBJECT_H
#define MAZE_OBJECT_H

class MazeObject {
public:
    virtual ~MazeObject() {}
    virtual void draw() = 0;
};

#endif