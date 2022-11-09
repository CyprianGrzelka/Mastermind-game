#include "../include/Mastermind.h"

gameBoard::gameBoard(void) // Orange board with holes
{
    rectangle.setSize(Vector2f(400, 600));
    FloatRect boardRect = rectangle.getLocalBounds();

    left = 1024.0f/2.0f - boardRect.width/1.1f;
    top = 768.0f/2.0f - boardRect.height/2.0f;

    rectangle.setPosition(Vector2f(1024.0f/2.0f, 768.0f/1.9f));

    rectangle.setOrigin(boardRect.left + boardRect.width/1.1f,
                        boardRect.top + boardRect.height/2.0f);
    rectangle.setFillColor(Color(200,100,50));

    reset();
}

void gameBoard::reset(void) // Clear board
{
    rowSelect = 9;
    columnSelect = 0;
    keyIndex = 0;
    pegDrop = 0;
    pegCount = 0;
    win = 0;
    int bigHoleX = left + 30, bigHoleY = top + 100;
    bigHoleY ;
    bigHoleX ;
    int i, j;
    for(j = 0; j < 10; j++) // Draw all holes on the board
    {
        for(i = 0; i < 4; i++)
        {
            holeArr[i][j].setRadius(22);
            holeArr[i][j].setFillColor(Color::Black);
            holeArr[i][j].setPosition(bigHoleX, bigHoleY);
            bigHoleX += 22 + 2*holeArr[i][j].getRadius();
        }
        bigHoleX = left + 30;
        bigHoleY += 50;
    }

    int smallHoleX = left + 80, smallHoleY = top + 20;

    for(i = 0; i < 4; i++)
    {
        guessArr[i].setRadius(22);
        switch(rand() % 6)
            {
                case 0:
                    guessArr[i].setFillColor(Color::Blue);
                    break;
                case 1:
                    guessArr[i].setFillColor(Color::Red);
                    break;
                case 2:
                    guessArr[i].setFillColor(Color::Yellow);
                    break;
                case 3:
                    guessArr[i].setFillColor(Color::White);
                    break;
                case 4:
                    guessArr[i].setFillColor(Color::Green);
                    break;
                case 5:
                    guessArr[i].setFillColor(Color(30, 0, 80));
                    break;
                default:
                    break;
            }
        guessArr[i].setPosition(smallHoleX, smallHoleY);
        smallHoleX += 40 + 2*guessArr[i].getRadius();
    }

    smallHoleY = top + 105;
    smallHoleX = left + 320;
    for(j = 0; j < 10; j++)
    {
        for(i = 0; i < 4; i++)
        {
            keyArr[i][j].setRadius(9); // small hole radius
            keyArr[i][j].setFillColor(Color::Black);
            if(i == 0)
                keyArr[i][j].setPosition(smallHoleX, smallHoleY);
            else if(i == 1)
                keyArr[i][j].setPosition(smallHoleX + 20, smallHoleY);
            else if(i == 2)
                keyArr[i][j].setPosition(smallHoleX, smallHoleY + 20);
            else if(i == 3)
                keyArr[i][j].setPosition(smallHoleX + 20, smallHoleY + 20);
        }
        smallHoleY += 50 + 2*keyArr[i][j].getRadius();
    }
    for(i = 0; i < 4; i++)
        pegPresent[i] = 0;
}

void gameBoard::draw(RenderWindow& Window) // Draw all the board
{
    Window.draw(rectangle);
    int i, j;
    for(j = 0; j < 10; j++)
    {
        for(i = 0; i < 4; i++)
        {
            Window.draw(holeArr[i][j]);
            Window.draw(keyArr[i][j]);
        }
    }
    if( rowSelect < 0)
        for(i = 0; i < 4; i++)
            Window.draw(guessArr[i]);
    else
    {
        Window.draw(codeRect);
    }
}

int gameBoard::mouseHover(RenderWindow& Window)
{
    FloatRect pegBounds;
    Vector2f pegPosition;
    Vector2i mousePosition;
    mousePosition = Mouse::getPosition(Window);
    int i, j;
    for(i = 0; i < 4; i++)
    {
        pegBounds = holeArr[i][rowSelect].getLocalBounds();
        pegPosition = holeArr[i][rowSelect].getPosition();
        if(mousePosition.x > pegPosition.x && mousePosition.y > pegPosition.y
           && mousePosition.x - pegBounds.width < pegPosition.x
           && mousePosition.y - pegBounds.height < pegPosition.y)
        {
            if(!pegPresent[i])
                holeArr[i][rowSelect].setFillColor(Color(137,137,137));
            if(!pegDrop)
                return i;
            else
                pegDrop = 0;
        }
        else
        {
            if(!pegPresent[i])
                holeArr[i][rowSelect].setFillColor(Color::Black);
        }
    }
    return -1;
}

void gameBoard::placePeg(RenderWindow& Window, int pegSelect)
{
    int pegPosition = mouseHover(Window);
    if(pegPosition >= 0 && pegSelect)
    {
        pegDrop = 1;
    }
    if(!Mouse::isButtonPressed(Mouse::Left) && pegDrop && pegPosition >= 0)
    {
        switch(pegSelect)
        {
            case 1:
                holeArr[pegPosition][rowSelect].setFillColor(Color::Blue);
                break;
            case 2:
                holeArr[pegPosition][rowSelect].setFillColor(Color::Red);
                break;
            case 3:
                holeArr[pegPosition][rowSelect].setFillColor(Color::Yellow);
                break;
            case 4:
                holeArr[pegPosition][rowSelect].setFillColor(Color::White);
                break;
            case 5:
                holeArr[pegPosition][rowSelect].setFillColor(Color::Green);
                break;
            case 6:
                holeArr[pegPosition][rowSelect].setFillColor(Color(30, 0, 80));
                break;
            default:
                break;
        }
        if(!pegPresent[pegPosition])
            pegCount++;
        pegPresent[pegPosition] = 1;
        pegDrop = 0;
    }
}

int gameBoard::currentRow(void)
{
    int checkCodePeg[4];
    int checkKeyPeg[4];

    if(pegCount == 4)
    {
        int i, j;
        for(i = 0; i < 4; i++)
        {
            checkCodePeg[i] = 0;
            checkKeyPeg[i] = 0;
        }
        for(i = 0; i < 4; i++)
        {
            if(holeArr[i][rowSelect].getFillColor() == guessArr[i].getFillColor())
            {
                keyArr[keyIndex][rowSelect].setFillColor(Color::Red);
                checkKeyPeg[i] = 1;
                checkCodePeg[i] = 1;
                keyIndex++;
            }
        }

        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
                if(!checkCodePeg[i] && !checkKeyPeg[j])
                    if(holeArr[i][rowSelect].getFillColor() == guessArr[j].getFillColor())
                    {
                        keyArr[keyIndex][rowSelect].setFillColor(Color::White);
                        keyIndex++;
                        checkCodePeg[i] = 1;
                        checkKeyPeg[j] = 1;
                    }
            pegPresent[i] = 0;
        }
        if(keyArr[0][rowSelect].getFillColor() == Color::Red &&
           keyArr[1][rowSelect].getFillColor() == Color::Red &&
           keyArr[2][rowSelect].getFillColor() == Color::Red &&
           keyArr[3][rowSelect].getFillColor() == Color::Red)
            win = 1;
        keyIndex = 0;
        pegCount = 0;
        rowSelect--;
        if(rowSelect < 0 && !win)
            return 1;
    }
    return win;

}

void gameText::initText(string srcText)
{
    gameText = srcText.c_str();
    xPosition = 0;
    yPosition = 0;
    textSize = 48;
    textColor = Color::White;
    font.loadFromFile("Fonts/aAbsoluteEmpire.ttf");
    text.setFont(font);
    text.setString(gameText);
    text.setCharacterSize(textSize);
    text.setPosition(xPosition, yPosition);
    text.setColor(textColor);
    bounds = text.getLocalBounds();
}

void gameText::setTextPosition(int x, int y)
{
    xPosition = x;
    yPosition = y;
    text.setPosition(xPosition, yPosition);
}

void gameText::showText(RenderWindow& Window)
{
    Window.draw(text);
}

int ClickableText::checkClick(RenderWindow& Window)
{
    if(Mouse::isButtonPressed(Mouse::Left))
    {
        Vector2i mousePosition = Mouse::getPosition(Window);
        if(mousePosition.x > xPosition && mousePosition.y > yPosition
            && mousePosition.x - bounds.width < xPosition
            && mousePosition.y - bounds.height < yPosition)
            return 1;
    }
    return 0;
}


void menuToggle::checkClick(RenderWindow& Window)
{
    if(Mouse::isButtonPressed(Mouse::Left))
    {
        Vector2i mousePosition = Mouse::getPosition(Window);
        if( mousePosition.x > xPosition && mousePosition.y > yPosition
            && mousePosition.x - bounds.width < xPosition
            && mousePosition.y - bounds.height < yPosition )
        {
            if(choice == 0)
            {
                text.setString(altGameText);
                choice = 1;
            }
            else if(choice == 1)
            {
                text.setString(gameText);
                choice = 0;
            }
            bounds = text.getLocalBounds();
        }
    }
}

int peg::drag(RenderWindow& Window)
{
    circlePosition = circle.getPosition();
    mousePosition = Mouse::getPosition(Window);

    if(Mouse::isButtonPressed(Mouse::Left))
    {
        if(pressed || mouseHover(Window))
        {
            if(let)
            {
                xDiff = mousePosition.x - circlePosition.x;
                yDiff = mousePosition.y - circlePosition.y;
                let = 0;
                pressed = 1;
            }
            xPos = mousePosition.x - xDiff;
            yPos = mousePosition.y - yDiff;
            circle.setPosition(xPos, yPos);
        }
    }
    else
    {
        mouseHover(Window);
        let = 1;
        xPos = xBase;
        yPos = yBase;
        xDiff = 0;
        yDiff = 0;
        circle.setPosition(xBase, yBase);
        pressed = 0;
    }
    return pressed;
}

int peg::mouseHover(RenderWindow& Window)
{
    mousePosition = Mouse::getPosition(Window);
    if(mousePosition.x > xPos && mousePosition.y > yPos
        && mousePosition.x - bounds.width < xPos
        && mousePosition.y - bounds.height < yPos)
        return 1;
    return 0;
}

void peg::init(RenderWindow& Window)
{
    circle.setRadius(22);
    circle.setFillColor(Color::Black);
    circle.setOutlineColor(Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(xPos, yPos);
    bounds = circle.getLocalBounds();
    xPos = 0;
    yPos = 0;
    xBase = 0;
    yBase = 0;
    let = 1;
    xDiff = 0;
    yDiff = 0;
}

void peg::setPegPosition(int x, int y)
{
    circle.setPosition(xPos, yPos);
    xPos = x;
    yPos = y;
    xBase = x;
    yBase = y;
}

void peg::setPegColor(Color pegColor)
{
    circle.setFillColor(pegColor);
}

void peg::draw(RenderWindow& Window)
{
    Window.draw(circle);
}
