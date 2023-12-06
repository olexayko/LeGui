#pragma once
#include "headers.h"

extern RenderWindow window;

class Button: public Drawable {
private:
    //reserved base buttons callbacks
    function<void()> _onLeftPressed;
    function<void()> _onLeftReleased;
public:
    //public user-definable buttons callbacks(payload)
    function<void()> onLeftPressed;
    function<void()> onLeftReleased;

    Texture texture;
    Texture normalTexture;
    Texture pressedTexture;
    Texture hoveredTexture;
    Sprite sprite;
    bool wasClickedLast = false;


    void loadTextures()
    {
        pressedTexture.loadFromFile("button_pressed.png");
        normalTexture.loadFromFile("button_normal.png");
        hoveredTexture.loadFromFile("button_hovered.png");
    }

    Button(function<void()> onClick, Vector2f position)
    {
        this->_onLeftPressed = onClick;
        this->_onLeftReleased = onClick;
        sprite.setPosition(position);
        loadTextures();
        sprite.setTexture(normalTexture);

    }

    explicit Button(function<void()> onClick)
    {
        this->_onLeftPressed = onClick;
        this->_onLeftReleased = onClick;
        loadTextures();
    }

    bool isUnderCursor() const
    {
        return FloatRect(sprite.getGlobalBounds().left,
                         sprite.getGlobalBounds().top,
                         sprite.getGlobalBounds().width,
                         sprite.getGlobalBounds().height).contains(
                                 Mouse::getPosition(window).x,
                                 Mouse::getPosition(window).y);
    }

    explicit Button(Vector2f position)
    {
        loadTextures();

        onLeftPressed = [&](){
            window.setTitle("***************************************************");
        };
        onLeftReleased = [&](){
            window.setTitle("---------------------------------------------------");
        };
        _onLeftPressed = [&](){
            cout << "_onLeftPressed";
            setTexture(pressedTexture);
        };
        _onLeftReleased = [&](){
            cout << "_onLeftReleased";
            if (isUnderCursor())
            {
                setTexture(hoveredTexture);
                cout << "hovered";
            }
            else
            {
                setTexture(normalTexture);
                cout << "normal";
            }

        };
        sprite.setPosition(position);
        setTexture(normalTexture);
    }

    void setTexture(Texture& _texture)
    {
        sprite.setTexture(_texture);
    }

    void processEvent(Event event)
    {
        if (event.mouseButton.button == Mouse::Button::Left)
        {
            if (FloatRect(sprite.getGlobalBounds().left,
                        sprite.getGlobalBounds().top,
                        sprite.getGlobalBounds().width,
                        sprite.getGlobalBounds().height).contains(event.mouseButton.x, event.mouseButton.y))
            {
                switch (event.type)
                {
                    case Event::MouseButtonPressed:
                        wasClickedLast = true;
                        _onLeftPressed();
                        onLeftPressed();
                        //Log
                        cout << "PRESS " << this << "\n"; break;

                }

            }
            switch (event.type)
            {
                case Event::MouseButtonReleased:
                    if (!wasClickedLast) return;

                    wasClickedLast = false;
                    _onLeftReleased();
                    onLeftReleased();
                    /*setTexture(normalTexture)*/;
                    cout << "NORMAL " << this << "\n"; break;
            }
        }
        switch (event.type)
        {
            case Event::MouseMoved:
                if (wasClickedLast) return;
                if (FloatRect(sprite.getGlobalBounds().left,
                          sprite.getGlobalBounds().top,
                          sprite.getGlobalBounds().width,
                          sprite.getGlobalBounds().height).contains(event.mouseMove.x, event.mouseMove.y))
                {
                    setTexture(hoveredTexture);
                    cout << "HOVER " << this << "\n"; break;
                }
                else
                {
                    setTexture(normalTexture);
                }
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override
    {
        target.draw(sprite);
    }
};