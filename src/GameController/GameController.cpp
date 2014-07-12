#include "GameController.h"
#include "../Game.h"

// 1. this should go into every .cpp , after all header inclusions
#ifdef _WIN32
#ifdef _DEBUG
#include <crtdbg.h>
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new       new( _NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif


// Initializing variables
GameController::GameController()
{
    cout << "Waking up the game controller for duty..." << endl;
}

///Init must be called after SDL is initialied
void GameController::init()
{
    SDL_Joystick *Jayman = NULL;

    if (SDL_JoystickEventState(SDL_ENABLE) != SDL_ENABLE)
    {
        cout << "Cannot enable Joystick event polling!" << endl;
        cin.get();
    }
        int num_joy;
        num_joy = SDL_NumJoysticks();
        printf("Name: %s\n", SDL_JoystickName(0));
        // Close if opened
        if (SDL_JoystickOpened(0))
        {
        
            cout << "Joystick closed" << endl;
            SDL_JoystickClose(GamePad);
        }
        else
        {
            cout << "Opened the joystick" << endl;
            GamePad = SDL_JoystickOpen(0);
        }
        
        //See if there is a joystick connected
        if (num_joy > 0){
            //this->name = SDL_JoystickName(0);
            //this->available = true;
            //GamePad = SDL_JoystickOpen(0);
            //this->availableButtons = SDL_JoystickNumButtons(this->stick);
            //this->availableHats = SDL_JoystickNumHats(this->stick);
        }
        cout << "worked" << endl;
        cin.get();
}
// Cleanup the game controller
GameController::~GameController()
{
    cout << "Putting the game controller to sleep" << endl;
}

// Handles input
void GameController::HandleInput()
{
}

void GameController::Act()
{
}

int GameController::CountDevices()
{
    cout << "(" << SDL_NumJoysticks() << ") Game Controller(s) found..." << endl;

    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        cout << "Controller(" << i << ") info" << endl;
        cout << "---------------" << endl;
        cout << SDL_JoystickName(i) << endl;
    }
    return SDL_NumJoysticks();
}

void GameController::Open(int index)
{
    GamePad = SDL_JoystickOpen(index);

    if (GamePad)
    {
        cout << "Opened Joystick" << index << endl;
        cout << "Name: " << SDL_JoystickName(index) << endl;
        cout << "Number of Axes: " << SDL_JoystickNumAxes(GamePad) << endl;
        //printf("Opened Joystick 0\n");
        //printf("Name: %s\n", SDL_JoystickName(index));
        //printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
        //printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
        //printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
    }
    else
        printf("Couldn't open Joystick 0\n");

}
void GameController::Update()
{
    SDL_JoystickUpdate();
    //Update all the buttons
    for (int i = 0; i < SDL_JoystickNumButtons(GamePad); i++){
        //unsigned int n = SDL_JoystickGetButton(GamePad, this->Buttons[i]->number);
        //if (n == 0){
            //this->Buttons[i]->release();
        //}
        //else{
            //this->Buttons[i]->press();
        //}
    }

    //Update the direction pad
    //this->axis_old = this->axis;
    Sint16 raw;

    cout << "x-axis: " << (Sint16)SDL_JoystickGetAxis(GamePad, 0) << endl;
    cout << "y-axis: " << (Sint16)SDL_JoystickGetAxis(GamePad, 1) << endl;

    if ((Sint16)SDL_JoystickGetAxis(GamePad, 1) == -32768)
        Spaceship.yVelocity = -1.0f;
    else if ((Sint16)SDL_JoystickGetAxis(GamePad, 1) == 32767)
        Spaceship.yVelocity = 1.0f;
    else
        Spaceship.yVelocity = 0.0f;

    if ((Sint16)SDL_JoystickGetAxis(GamePad, 0) == -32768)
        Spaceship.xVelocity = -1.0f;
    else if ((Sint16)SDL_JoystickGetAxis(GamePad, 0) == 32767)
        Spaceship.xVelocity = 1.0f;
    else
        Spaceship.xVelocity = 0.0f;

    if (SDL_JoystickGetButton(GamePad, 0) == 1)
    {
        if (FIRED == 0 && (gamestate.GameState.top() != MENU_MAIN_STATE))
        {
        BulletController.Create_Bullets();
        FIRED = 1;
        Gfx.FLIP();
        Audio.PlaySoundEffect(4);
        }
        SDL_Surface * SrfText;
        std::string ControlText;
        ControlText = "Red Button: ";
        ControlText.append(std::to_string(SDL_JoystickGetButton(GamePad, 0)).c_str());

        SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, ControlText.c_str(), Gfx.WhiteRGB);
        Gfx.apply_surface(0, 500, SrfText, Gfx.BackBuffer);
        Gfx.FLIP();
    }
    else if (SDL_JoystickGetButton(GamePad, 1) == 1)
    {
        if (FIRED == 0 && (gamestate.GameState.top() != MENU_MAIN_STATE))
        {
            BulletController.Create_Bullets();
            FIRED = 1;
            Gfx.FLIP();
            Audio.PlaySoundEffect(4);
        }
        SDL_Surface * SrfText;
        std::string ControlText;
        ControlText = "Yellow Button: ";
        ControlText.append(std::to_string(SDL_JoystickGetButton(GamePad, 0)).c_str());

        SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, ControlText.c_str(), Gfx.WhiteRGB);
        Gfx.apply_surface(0, 500, SrfText, Gfx.BackBuffer);
        Gfx.FLIP();
    }
    else if (SDL_JoystickGetButton(GamePad, 2) == 1)
    {
        SDL_Surface * SrfText;
        std::string ControlText;
        ControlText = "Green Button: ";
        ControlText.append(std::to_string(SDL_JoystickGetButton(GamePad, 0)).c_str());

        SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, ControlText.c_str(), Gfx.WhiteRGB);
        Gfx.apply_surface(0, 500, SrfText, Gfx.BackBuffer);
        Gfx.FLIP();
        gamestate.GameState.pop();
        gamestate.GameState.push(MENU_MAIN_STATE);
    }
    else if (SDL_JoystickGetButton(GamePad, 3) == 1)
    {
        SDL_Surface * SrfText;
        std::string ControlText;
        ControlText = "Blue Button: ";
        ControlText.append(std::to_string(SDL_JoystickGetButton(GamePad, 0)).c_str());

        SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, ControlText.c_str(), Gfx.WhiteRGB);
        Gfx.apply_surface(0, 500, SrfText, Gfx.BackBuffer);
        Gfx.FLIP();
        gamestate.GameState.pop();
        gamestate.GameState.push(MENU_MAIN_STATE);
    }
    else if (SDL_JoystickGetButton(GamePad, 8) == 1)
    {
        SDL_Surface * SrfText;
        std::string ControlText;
        ControlText = "Select Button: ";
        ControlText.append(std::to_string(SDL_JoystickGetButton(GamePad, 0)).c_str());

        SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, ControlText.c_str(), Gfx.WhiteRGB);
        Gfx.apply_surface(0, 500, SrfText, Gfx.BackBuffer);
        Gfx.FLIP();
        gamestate.GameState.pop();
        gamestate.GameState.push(MENU_MAIN_STATE);
    }
    else if (SDL_JoystickGetButton(GamePad, 9) == 1)
    {
        SDL_Surface * SrfText;
        std::string ControlText;
        ControlText = "Start Button: ";
        ControlText.append(std::to_string(SDL_JoystickGetButton(GamePad, 0)).c_str());

        SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, ControlText.c_str(), Gfx.WhiteRGB);
        Gfx.apply_surface(0, 500, SrfText, Gfx.BackBuffer);
        Gfx.FLIP();
        gamestate.GameState.pop();
        gamestate.GameState.push(MENU_MAIN_STATE);
    }
    else
    {
        FIRED = 0;
    }

    //this->hat_old = this->hat;
    //this->hat = SDL_JoystickGetHat(this->stick, 0);
}