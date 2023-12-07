//#include <utility>

#include <utility>

#include "headers.h"
#include "button.cpp"

class LGui: public Drawable {
public:
    explicit LGui(vector<Button*> buttons): buttons(buttons)
    {

    }

private:
    vector<Button*> buttons; //change to set to avoid sending duplicates

public:
    void processEvent(Event event)
    {
        for (Button* button: buttons)
        {
            button->processEvent(event);
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override
    {
        for (Button* button: buttons)
        {
            button->draw(target, states);
        }
    }
};

