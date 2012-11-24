#ifndef VIEW_HPP
#define VIEW_HPP


typedef struct WindowSize{
    int width;
    int height;

    Size(int width, int height){
	this->width = width;
	this->height = height;
    }
} SIZE;

class View{
private:
    Model* model;
    SIZE size;
public:
    View(const SIZE &size);
    void Draw();
};

#endif
