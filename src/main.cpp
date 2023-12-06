#include "headers.h"
#include "button.cpp"
#include "LGui.cpp"

RenderWindow window(VideoMode(1920,1080), "My window" /*, Style::Fullscreen*/);


int main()
{
    //window.setMouseCursorGrabbed(true);

    Cursor handCursor;
    handCursor.loadFromSystem(Cursor::Hand);

    Cursor arrowCursor;
    arrowCursor.loadFromSystem(Cursor::Arrow);


    //Button btn;
    Texture t; t.loadFromFile("button_normal.png");
    /*Texture pressedTexture; pressedTexture.loadFromFile("button_pressed.png");
    Texture normalTexture; normalTexture.loadFromFile("button_normal.png");*/
    //Sprite s(t);


    Clock clock;
    Time elapsedSinceLastPress;
    bool isScreenDraggable = false;
    bool countingForDragging = false;
/*
    auto release = [&](){
        isScreenDraggable = false;
        countingForDragging = false;
        window.setMouseCursor(arrowCursor);
        clock.restart();
        //btn.sprite.setTexture(normalTexture);

        btn.setTexture(btn.normalTexture); //works!!!
    };
    auto press = [&](){
        clock.restart();
        countingForDragging = true;
        //btn.sprite.setTexture(pressedTexture);
        btn.setTexture(btn.pressedTexture); //works!!!
    };
*/

    LGui lgui(
            {
                new Button(Vector2f(500,400)),
                new Button(Vector2f(500,500)),
            });

    window.setFramerateLimit(240);
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) { window.close(); }

            lgui.processEvent(event);
        }
        //window.setView(view);

        window.clear(Color::Black);

        window.draw(lgui);
        //window.draw(btn);


        window.display();


        if (clock.getElapsedTime().asMilliseconds() >= 100 && countingForDragging)
        {
            isScreenDraggable = true;
            window.setMouseCursor(handCursor);
        }
        //window.setTitle(isScreenDraggable? "dragging" : "non-dragging");
    }
}