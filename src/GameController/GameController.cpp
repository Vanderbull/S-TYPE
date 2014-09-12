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

// Initializing the GameControllers variables
GameController::GameController()
{
    cout << "Waking up the game controller for duty..." << endl;
}

///Init must be called after SDL is initialied
void GameController::init()
{
    if (SDL_JoystickEventState(SDL_ENABLE) != SDL_ENABLE)
    {
        cout << "Cannot enable Joystick event polling!" << endl;
    }

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
}
// Cleanup the game controller
GameController::~GameController()
{
    cout << "GameController is Killed by a Headhunter..." << endl;
}

// Handles input
void GameController::HandleInput(SDL_Event _event)
{
    //Calculate angle
    //double joystickAngle = atan2((double)yDir, (double)xDir) * (180.0 / M_PI);

    switch (_event.type)
    {
        case SDL_KEYUP:
        {
            switch (_event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            {
                gamestate.GameState.push(MENU_MAIN_STATE);
            } break;
            case SDLK_RIGHT:
            {
                Spaceship.xVelocity = NO_VELOCITY;
            } break;
            case SDLK_LEFT:
            {
                Spaceship.xVelocity = NO_VELOCITY;
            } break;
            case SDLK_UP:
            {
                Spaceship.yVelocity = NO_VELOCITY;
            } break;
            case SDLK_DOWN:
            {
                Spaceship.yVelocity = NO_VELOCITY;
            } break;
            case SDLK_SPACE:
            {
                if (FIRED == 0)
                {
                    BulletController.Create_Bullets();
                    FIRED = 1;
                    Gfx.FLIP();
                    Audio.PlaySoundEffect(4);
                }
            } break;
            } break;

        } break;

        case SDL_KEYDOWN:
        {
            switch (_event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    gamestate.GameState.push(MENU_MAIN_STATE);
                } break;
                case SDLK_RIGHT:
                {
                    Spaceship.xVelocity = MAX_VELOCITY;
                } break;
                case SDLK_LEFT:
                {
                    Spaceship.xVelocity = MIN_VELOCITY;
                } break;
                case SDLK_UP:
                {
                    Spaceship.yVelocity = MIN_VELOCITY;
                } break;
                case SDLK_DOWN:
                {
                    Spaceship.yVelocity = MAX_VELOCITY;
                } break;
                case SDLK_SPACE:
                {
                    if (FIRED == 0)
                    {
                        BulletController.Create_Bullets();
                        FIRED = 1;
                        Gfx.FLIP();
                        Audio.PlaySoundEffect(4);
                    }
                } break;
          } break;
       } break;
    }
    cout << "GameController.cpp is handling the input..." << endl;
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
        cout << "Number of Buttons: " << SDL_JoystickNumButtons(GamePad) << endl;
        cout << "Number of Balls: " << SDL_JoystickNumBalls(GamePad) << endl;
    }
    else
    {
        printf("Couldn't open Joystick 0\n");
    }
}
void GameController::Update()
{
    SDL_Surface * SrfUpdateController;
    std::string SrfText;

    SrfText = "Updating the GameController";
    SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, SrfText.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(0, 200, SrfUpdateController, Gfx.BackBuffer);
    SrfText = "Red button: ";
    SrfText.append(std::to_string(SDL_JoystickGetButton(GamePad, 0)).c_str());
    SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, SrfText.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(0, 230, SrfUpdateController, Gfx.BackBuffer);
    SrfText = "Blue button: ";
    SrfText.append(std::to_string(SDL_JoystickGetButton(GamePad, 3)).c_str());
    SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, SrfText.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(0, 260, SrfUpdateController, Gfx.BackBuffer);
    SrfText = "Green button: ";
    SrfText.append(std::to_string(SDL_JoystickGetButton(GamePad, 2)).c_str());
    SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, SrfText.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(0, 290, SrfUpdateController, Gfx.BackBuffer);
    SrfText = "Yellow button: ";
    SrfText.append(std::to_string(SDL_JoystickGetButton(GamePad, 1)).c_str());
    SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, SrfText.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(0, 310, SrfUpdateController, Gfx.BackBuffer);

    SrfText = "Xaxis: ";
    SrfText.append(std::to_string(SDL_JoystickGetAxis(GamePad, 0)).c_str());
    SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, SrfText.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(0, 330, SrfUpdateController, Gfx.BackBuffer);

    SrfText = "Yaxis: ";
    SrfText.append(std::to_string(SDL_JoystickGetAxis(GamePad, 1)).c_str());
    SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, SrfText.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(0, 350, SrfUpdateController, Gfx.BackBuffer);

    SrfText = "Velocity(X): ";
    SrfText.append(std::to_string(Spaceship.GetVelocityX()).c_str());
    SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, SrfText.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(0, 370, SrfUpdateController, Gfx.BackBuffer);

    SrfText = "Velocity(Y): ";
    SrfText.append(std::to_string(Spaceship.GetVelocityY()).c_str());
    SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, SrfText.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(0, 390, SrfUpdateController, Gfx.BackBuffer);

    //Gfx.FLIP();

    //Audio.Render();
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

    cout << "x-axis: " << (Sint16)SDL_JoystickGetAxis(GamePad, 0) << endl;
    cout << "y-axis: " << (Sint16)SDL_JoystickGetAxis(GamePad, 1) << endl;

    if ((Sint16)SDL_JoystickGetAxis(GamePad, 1) == -32768)
    {
        Spaceship.Accelerate(0.0f,-1.0f);
    }
    else if ((Sint16)SDL_JoystickGetAxis(GamePad, 1) == 32767)
    {
        Spaceship.Accelerate(0.0f, 1.0f);
    }
    else if ((Sint16)SDL_JoystickGetAxis(GamePad, 1) == -1)
    {
        Spaceship.Accelerate(0.0f, 0.0f);
    }

    if ((Sint16)SDL_JoystickGetAxis(GamePad, 0) == -32768)
    {
        Spaceship.Accelerate(-1.0f, 0.0f);
    }
    else if ((Sint16)SDL_JoystickGetAxis(GamePad, 0) == 32767)
    {
        Spaceship.Accelerate(1.0f, 0.0f);
    }
    else if ((Sint16)SDL_JoystickGetAxis(GamePad, 0) == -1)
    {
        Spaceship.Accelerate(0.0f, 0.0f);
    }

    if (SDL_JoystickGetButton(GamePad, 0) == 1)
    {
        if ((gamestate.GameState.top() != MENU_MAIN_STATE) && PowerLevelSecond > 0)
        {
        BulletController.Create_Bullets();
        FIRED = 1;
        Gfx.FLIP();
        Audio.PlaySoundEffect(4);
        PowerLevelSecond -= 5;
        }
    }
    else if (SDL_JoystickGetButton(GamePad, 1) == 1)
    {
        if ((gamestate.GameState.top() != MENU_MAIN_STATE) && PowerLevelSecond > 0)
        {
            BulletController.Create_Bullets();
            FIRED = 1;
            Gfx.FLIP();
            Audio.PlaySoundEffect(4);
            PowerLevelSecond -= 5;
        }
    }
    else if (SDL_JoystickGetButton(GamePad, 2) == 1)
    {
        if ((gamestate.GameState.top() != MENU_MAIN_STATE) && PowerLevelSecond > 0)
        {
            BulletController.Create_Bullets();
            FIRED = 1;
            Gfx.FLIP();
            Audio.PlaySoundEffect(4);
            PowerLevelSecond -= 5;
        }
    }
    else if (SDL_JoystickGetButton(GamePad, 3) == 1)
    {
        Spaceship.DecreasePowerLevel();
        if ((gamestate.GameState.top() != MENU_MAIN_STATE) && PowerLevel > 0)
        {
            BulletController.Create_Bullets();
            FIRED = 1;
            Gfx.FLIP();
            Audio.PlaySoundEffect(4);

            if (PowerLevel > 0)
            {
                PowerLevel -= 5;
            }
        }
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

void GameController::KeyMapping(SDL_Event _event)
{
    bool KEYS[322];  // 322 is the number of SDLK_DOWN events

    for (int i = 0; i < 322; i++) { // init them all to false
        KEYS[i] = false;
    }

    SDL_EnableKeyRepeat(0, 0); // you can configure this how you want, but it makes it nice for when you want to register a key continuously being held down

    switch (_event.type)
    {
    case SDL_KEYDOWN:
        KEYS[_event.key.keysym.sym] = true;
        break;
    case SDL_KEYUP:
        KEYS[_event.key.keysym.sym] = false;
        break;
    }
}