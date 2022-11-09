#include<iostream>
#include "include/Mastermind.h"

int main()
{
    srand(time(NULL));
    RenderWindow Window(VideoMode(1024, 768, 32),"Mastermind!");

    int selectPeg = 0;
    int mode = 0;

    Texture texture;
    if(!texture.loadFromFile("background.png"))
        std::cout<<"background image load failed";

    Sprite background(texture);
    gameBoard Board;

    ClickableText play, quit, finish; // Class Play/Quit/Finish buttons

    play.initText("Play");
    play.setTextPosition(800, 100);

    quit.initText("Quit");
    quit.setTextPosition(800, 200);

    finish.initText("Finish");
    finish.setTextPosition(800, 300);

    peg pegBlue;
    pegBlue.init(Window);
    pegBlue.setPegPosition(800, 400);
    pegBlue.setPegColor(Color::Blue);

    peg pegRed;
    pegRed.init(Window);
    pegRed.setPegPosition(800, 450);
    pegRed.setPegColor(Color::Red);

    peg pegYellow;
    pegYellow.init(Window);
    pegYellow.setPegPosition(800, 500);
    pegYellow.setPegColor(Color::Yellow);

    peg pegWhite;
    pegWhite.init(Window);
    pegWhite.setPegPosition(900, 400);
    pegWhite.setPegColor(Color::White);

    peg pegGreen;
    pegGreen.init(Window);
    pegGreen.setPegPosition(900, 450);
    pegGreen.setPegColor(Color::Green);

    peg pegPurple;
    pegPurple.init(Window);
    pegPurple.setPegPosition(900, 500);
    pegPurple.setPegColor(Color(30, 0, 80));

    Event event;
    while(Window.isOpen())
    {
        while(Window.pollEvent(event))
            switch(event.type)
            {
                case Event::Closed:
                    Window.close();
                    break;
                default:
                    break;
            }
            Window.draw(background);
            Board.draw(Window);

            if(mode == 0)
            {
                if(play.checkClick(Window))
                    if(Mouse::isButtonPressed(Mouse::Left))
                        mode = 1;

                if(quit.checkClick(Window))
                    if(Mouse::isButtonPressed(Mouse::Left))
                        Window.close();

                play.showText(Window);
                quit.showText(Window);
            }
            if(mode == 1)
            {
                if(!Board.currentRow())
                {
                    Board.placePeg(Window, selectPeg);

                    switch(selectPeg)
                    {
                        case 0:
                            if(pegBlue.drag(Window))
                                selectPeg = 1;
                            if(pegRed.drag(Window))
                            selectPeg = 2;
                            if(pegYellow.drag(Window))
                                selectPeg = 3;
                            if(pegWhite.drag(Window))
                                selectPeg = 4;
                            if(pegGreen.drag(Window))
                                selectPeg = 5;
                            if(pegPurple.drag(Window))
                                selectPeg = 6;
                            break;
                        case 1:
                            if(pegBlue.drag(Window))
                                selectPeg = 1;
                            else
                                selectPeg = 0;
                            break;
                        case 2:
                            if(pegRed.drag(Window))
                                selectPeg = 2;
                            else
                                selectPeg = 0;
                            break;
                        case 3:
                            if(pegYellow.drag(Window))
                                selectPeg = 3;
                            else
                                selectPeg = 0;
                            break;
                        case 4:
                            if(pegWhite.drag(Window))
                                selectPeg = 4;
                            else
                                selectPeg = 0;
                            break;
                        case 5:
                            if(pegGreen.drag(Window))
                                selectPeg = 5;
                            else
                                selectPeg = 0;
                            break;
                        case 6:
                            if(pegPurple.drag(Window))
                                    selectPeg = 6;
                            else
                                selectPeg = 0;
                            break;
                    }
                }
                finish.showText(Window);

                pegRed.draw(Window);
                pegGreen.draw(Window);
                pegBlue.draw(Window);
                pegYellow.draw(Window);
                pegWhite.draw(Window);
                pegPurple.draw(Window);
                if(finish.checkClick(Window))
                {
                    if(Mouse::isButtonPressed(Mouse::Left)){
                        Board.reset();
                        mode = 0;
                    }
                }
                finish.showText(Window);
            }

    Window.display();
    }
    return 0;
}
