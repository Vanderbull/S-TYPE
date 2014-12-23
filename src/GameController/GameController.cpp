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


//XBox controller deadzones
#define GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define GAMEPAD_TRIGGER_THRESHOLD    30

// Initializing the GameControllers variables
GameController::GameController()
{
    magnitude = 0;
    cout << "Waking up the game controller for duty..." << endl;
    ButtonMap["A"] = 0;
    ButtonMap["B"] = 1;
    ButtonMap["X"] = 2;
    ButtonMap["Y"] = 3;
    ButtonMap["Home"] = -1; // Not a button
    ButtonMap["LB"] = 4;
    ButtonMap["RB"] = 5;
    ButtonMap["Select"] = 6;
    ButtonMap["Start"] = 7;

    //ButtonMap["LT"] = 6;
    //ButtonMap["RT"] = 7;
    //ButtonMap["Select"] = 8;
    //ButtonMap["Start"] = 9;
    ButtonMap["L3"] = 10;
    ButtonMap["R3"] = 11;
    ButtonMap["DPad Up"] = 12;
    ButtonMap["DPad Down"] = 13;
    ButtonMap["DPad Left"] = 14;
    ButtonMap["DPad Right"] = 15;
}

///Init must be called after SDL is initialied
void GameController::init()
{
    // Initialize the joystick subsystem
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    if (SDL_JoystickEventState(SDL_ENABLE) != SDL_ENABLE)
    {
        cout << "Cannot enable Joystick event polling!" << endl;
    }

    for (int i = 0; i < CountDevices(); i++)
    {
        if (SDL_JoystickOpened(i))
        {
            cout << "Joystick " << i << " closed" << endl;
            SDL_JoystickClose(joysticks[i]);
        }
        else
        {
            Open(i);
            //joysticks[i] = SDL_JoystickOpen(i);
        }
    }
    //GamePad = joysticks[1];
}
// Cleanup the game controller
GameController::~GameController()
{
    logger.write(__LINE__,"GameController is Killed by a Headhunter...");
}

// Handles input
void GameController::HandleInput(SDL_Event _event)
{
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
                        Audio.PlaySoundEffect(4);
                    }
                } break;
          } break;
       } break;
    }
    cout << "GameController.cpp is handling the input..." << endl;
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
    GamePad = SDL_JoystickOpen(0);
    joysticks[index] = SDL_JoystickOpen(index);

    if (joysticks[index])
    {
        cout << "Opened Joystick" << index << endl;
        cout << "Name: " << SDL_JoystickName(index) << endl;
        cout << "Number of Axes: " << SDL_JoystickNumAxes(GamePad) << endl;
        cout << "Number of Buttons: " << SDL_JoystickNumButtons(GamePad) << endl;
        cout << "Number of Balls: " << SDL_JoystickNumBalls(GamePad) << endl;
    }
    else
    {
        logger.write(__LINE__,"Something went wrong opening the joystick");
    }
}

void GameController::RenderText()
{
    int w, h;
    if (TTF_SizeText(Gfx.DefaultFont, ControllerInfo.c_str(), &w, &h))
    {
        // perhaps print the current TTF_GetError(), the string can't be rendered...
    }
    else 
    {
        //SDL_Surface * SrfUpdateController;
        //SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, ControllerInfo.c_str(), Gfx.WhiteRGB);
        //Gfx.apply_surface(Gfx.BackBuffer->w - w, 100, SrfUpdateController, Gfx.BackBuffer);
    }

    int counter = 0;
    for (auto &Dota : CtrlData) // access by reference to avoid copying
    {
        int w, h;
        if (TTF_SizeText(Gfx.DefaultFont, Dota.c_str(), &w, &h))
        { }
        else 
        { }
        SDL_Surface * SrfUpdateController;
        SrfUpdateController = TTF_RenderText_Solid(Gfx.DefaultFont, Dota.c_str(), Gfx.WhiteRGB);
        Gfx.apply_surface(Gfx.BackBuffer->w - w, h*counter++, SrfUpdateController, Gfx.BackBuffer);
    }
    CtrlData.clear();
}

void GameController::Update()
{
    SDL_Surface * SrfUpdateController;
    std::string SrfText;
    std::string JoystickButtonState;
    
    ControllerInfo = "";
    JoystickButtonState = "";
    /*
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        SrfText = "";
        SrfText = SDL_JoystickName(i);
        ControllerInfo += SDL_JoystickName(i);
        CtrlData.push_back(SDL_JoystickName(i));
        int w, h;
        if (TTF_SizeText(Gfx.DefaultFont, SrfText.c_str(), &w, &h)) {
            // perhaps print the current TTF_GetError(), the string can't be rendered...
        }
        else {
            printf("width=%d height=%d\n", w, h);
        }

        ControllerInfo += " Buttons| ";
        CtrlData.push_back("-------------------------");
        CtrlData.push_back("Buttons");
        CtrlData.push_back("-------------------------");
        for (int button_index = 0; button_index < SDL_JoystickNumButtons(joysticks[i]); button_index++)
        {
            ControllerInfo += " | ";
            ControllerInfo += std::to_string(button_index).c_str();
            ControllerInfo += " : ";
            ControllerInfo.append(std::to_string(SDL_JoystickGetButton(joysticks[i], button_index)));

            CtrlData.push_back(" | " + std::to_string(button_index) + " >>> " + std::to_string(SDL_JoystickGetButton(joysticks[i], button_index)) + " | ");
        }

        ControllerInfo += " Hats| ";
        CtrlData.push_back("-------------------------");
        CtrlData.push_back("Hats");
        CtrlData.push_back("-------------------------");

        for (int hat_index = 0; hat_index < SDL_JoystickNumHats(joysticks[i]); hat_index++)
        {
            ControllerInfo += " | ";
            ControllerInfo += std::to_string(hat_index).c_str();
            ControllerInfo += " : ";
            ControllerInfo.append(std::to_string(SDL_JoystickGetHat(joysticks[i], hat_index)));
            CtrlData.push_back(" | " + std::to_string(hat_index) + " >>> " + std::to_string(SDL_JoystickGetHat(joysticks[i], hat_index)) + " | ");
        }
        
        ControllerInfo += " Axis| ";
        CtrlData.push_back("-------------------------");
        CtrlData.push_back("Axis");
        CtrlData.push_back("-------------------------");

        for (int axes_index = 0; axes_index < SDL_JoystickNumAxes(joysticks[i]); axes_index++)
        {
            ControllerInfo += " | ";
            ControllerInfo += std::to_string(axes_index).c_str();
            ControllerInfo += " : ";
            ControllerInfo.append(std::to_string(SDL_JoystickGetAxis(joysticks[i], axes_index)));
            CtrlData.push_back(" | " + std::to_string(axes_index) + " >>> " + std::to_string(SDL_JoystickGetAxis(joysticks[i], axes_index)) + " | ");
        }
       
        ControllerInfo += " Balls| ";
        CtrlData.push_back("-------------------------");
        CtrlData.push_back("Balls");
        CtrlData.push_back("-------------------------");

        int delta_x, delta_y;

        for (int balls_index = 0; balls_index < SDL_JoystickNumBalls(joysticks[i]); balls_index++)
        {
            ControllerInfo += " | ";
            ControllerInfo += std::to_string(balls_index).c_str();
            ControllerInfo += " : ";
            ControllerInfo.append(std::to_string(SDL_JoystickGetBall(joysticks[i], 0 , &delta_x, &delta_y)));
            CtrlData.push_back(" | " + std::to_string(balls_index) + " >>> " + std::to_string(SDL_JoystickGetBall(joysticks[i], 0, &delta_x, &delta_y)) + " | ");
        }
    }
    */
    signed int LX = SDL_JoystickGetAxis(joysticks[0], 0);
    signed int LY = SDL_JoystickGetAxis(joysticks[0], 1);

    //determine how far the controller is pushed
    float magnitude = sqrt(LX*LX + LY*LY);

    float normalizedMagnitude = 0;
    float normalizedLX = 0;
    float normalizedLY = 0;


    //check if the controller is outside a circular dead zone
    if (magnitude > GAMEPAD_LEFT_THUMB_DEADZONE)
    {
        normalizedLX = LX / magnitude;
        normalizedLY = LY / magnitude;
        //clip the magnitude at its expected maximum value
        if (magnitude > 32767) magnitude = 32767;

        //adjust magnitude relative to the end of the dead zone
        magnitude -= GAMEPAD_LEFT_THUMB_DEADZONE;
        
        //optionally normalize the magnitude with respect to its expected range
        //giving a magnitude value of 0.0 to 1.0
        normalizedMagnitude = magnitude / (32767 - GAMEPAD_LEFT_THUMB_DEADZONE);
        //determine the direction the controller is pushed
    }
    else //if the controller is in the deadzone zero out the magnitude
    {
        magnitude = 0.0;
        normalizedMagnitude = 0.0;
    }

    Spaceship.Accelerate(normalizedLX, normalizedLY);

    if ((Sint16)SDL_JoystickGetAxis(joysticks[0], 1) == -32768)
    {
        //Spaceship.Accelerate(0.0f,-1.0f);
    }
    else if ((Sint16)SDL_JoystickGetAxis(joysticks[0], 1) == 32767)
    {
        //Spaceship.Accelerate(0.0f, 1.0f);
    }
    else if ((Sint16)SDL_JoystickGetAxis(joysticks[0], 1) == -1)
    {
        //Spaceship.Accelerate(0.0f, 0.0f);
    }

    if ((Sint16)SDL_JoystickGetAxis(joysticks[0], 0) == -32768)
    {
        //Spaceship.Accelerate(-1.0f, 0.0f);
    }
    else if ((Sint16)SDL_JoystickGetAxis(joysticks[0], 0) == 32767)
    {
        //Spaceship.Accelerate(1.0f, 0.0f);
    }
    else if ((Sint16)SDL_JoystickGetAxis(joysticks[0], 0) == -1)
    {
        //Spaceship.Accelerate(0.0f, 0.0f);
    }

    if (SDL_JoystickGetButton(joysticks[0], ButtonMap["A"]) == 1)
    {
        if ( (gamestate.GameState.top() == GAME_RUNNING_STATE) )
        {
            if (LaserRecharge <= 0)
                LaserRecharge = 3;
            else
                LaserRecharge -= 0.1;
            if (LaserRecharge <= 0){
            BulletController.Create_Bullets();
            FIRED = 1;
            Audio.PlaySoundEffect(4);
            }
        }
    }
    else if (SDL_JoystickGetButton(joysticks[0], ButtonMap["B"]) == 1)
    {
        if ( (gamestate.GameState.top() == GAME_RUNNING_STATE) )
        {
            Spaceship.DecreasePowerLevel();
            if (PowerLevel >= 5)
            {
                Spaceship.Accelerate(10, normalizedLY);
                PowerLevel -= 5;
            }
           // Afterburner like sound
        }
    }
    else if (SDL_JoystickGetButton(joysticks[0], ButtonMap["X"]) == 1)
    {
        if ( (gamestate.GameState.top() == GAME_RUNNING_STATE) )
        {
        }
    }
    else if (SDL_JoystickGetButton(joysticks[0], ButtonMap["Y"]) == 1)
    {
        if ( (gamestate.GameState.top() == GAME_RUNNING_STATE) )
        {
        }
    }
    else if (SDL_JoystickGetButton(joysticks[0], ButtonMap["LB"]) == 1)
    {
        if ((gamestate.GameState.top() == GAME_RUNNING_STATE))
        {
        }
    }
    else if (SDL_JoystickGetButton(joysticks[0], ButtonMap["Select"]) == 1)
    {
        //SDL_Surface * SrfText;
        //std::string ControlText;
        //ControlText = "Select Button: ";
        //ControlText.append(std::to_string(SDL_JoystickGetButton(GamePad, 0)).c_str());

        //SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, ControlText.c_str(), Gfx.WhiteRGB);
        //Gfx.apply_surface(0, 500, SrfText, Gfx.BackBuffer);
        gamestate.GameState.pop();
        gamestate.GameState.push(MENU_MAIN_STATE);
    }
    else if (SDL_JoystickGetButton(joysticks[0], ButtonMap["Start"]) == 1)
    {
        //SDL_Surface * SrfText;
        //std::string ControlText;
        //ControlText = "Start Button: ";
        //ControlText.append(std::to_string(SDL_JoystickGetButton(GamePad, 0)).c_str());

        //SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, ControlText.c_str(), Gfx.WhiteRGB);
        //Gfx.apply_surface(0, 500, SrfText, Gfx.BackBuffer);
        gamestate.GameState.pop();
        gamestate.GameState.push(MENU_MAIN_STATE);
    }
    else
    {
        FIRED = 0;
    }
    if (gamestate.GameState.top() == GAME_OPTIONS_STATE)
    {
        RenderText();
    }
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