#ifndef VIEW_HPP
#define VIEW_HPP

#include "../Model/state.hpp"

class WindowSize{
public:
    int width;
    int height;

    WindowSize(int width, int height){
	this->width = width;
	this->height = height;
    }

    WindowSize(){
	width = height = 0;
    }
};

class View{
private:
    WindowSize winsize;
public:
    View(const WindowSize &size);
    void Draw(const State& state);
};

#endif
