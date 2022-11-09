#pragma once
#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>

using namespace std;
using namespace sf;

class gameText // Basic text class
{
    protected:
        Font font;
        Text text;
        Color textColor;
        FloatRect bounds;
        string gameText;
        int xPosition;
        int yPosition;
        int textSize;
    public:
        void initText(string srcText);
        void setTextPosition(int x, int y);
        void showText(RenderWindow& Window);
};

class ClickableText: public gameText // "Button" text class
{
    protected:
        int let;
    public:
        int checkClick(RenderWindow& Window);
};

class menuToggle: public ClickableText // Toggle between Play/Quit and Finish
{
    protected:
        string altGameText;
        int choice;
    public:
        void initText(string srcText, string altText);
        void checkClick(RenderWindow& Window);
};

class gameBoard  // Main board in the game
{
    protected:
        int xPos, yPos;
        int top, left;
        int rowSelect, columnSelect;
        int pegPresent[4];
        int pegDrop, pegCount, keyIndex;
        int win;
        Vector2i mousePosition;
        FloatRect bounds;
        RectangleShape rectangle;
        RectangleShape codeRect;
        CircleShape holeArr[4][10]; // 10 rows of 4 holes
        CircleShape guessArr[4];
        CircleShape keyArr[4][10];
    public:
        gameBoard(void);
        void draw(RenderWindow& Window);
        void placePeg(RenderWindow& Window, int pegSelect);
        int currentRow(void);
        void reset(void);
        int mouseHover(RenderWindow& Window);
};

class peg // Peg class: shape, position, handling mouse events
{
    protected:
        FloatRect bounds;
        CircleShape circle;
        Vector2i mousePosition;
        Vector2f circlePosition;
        int xPos, yPos, xDiff, yDiff, let;
        int xBase, yBase;
        int pressed;

    public:
        void init(RenderWindow& Window);
        void draw(RenderWindow& Window);
        int drag(RenderWindow& Window);
        void setPegPosition(int x, int y);
        void setPegColor(Color pegColor);
        int mouseHover(RenderWindow& Window);
};

#endif
