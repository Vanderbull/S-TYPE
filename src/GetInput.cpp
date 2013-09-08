#include "GetInput.h"
#include "Game.h"

StringInput::StringInput()
{
    //Initialize the string
    str = "";
    
    //Initialize the surface
    text = NULL;
    
    //Enable Unicode
    SDL_EnableUNICODE( SDL_ENABLE );    
}

StringInput::~StringInput()
{
    //Free text surface
    SDL_FreeSurface( text );
    
    //Disable Unicode
    SDL_EnableUNICODE( SDL_DISABLE );  
}

// checks for input max three letters
bool StringInput::handle_input(   )
{
	while(SDL_PollEvent(&StringEvent)) {  /* Loop until there are no events left on the queue */
	  switch(StringEvent.type) { /* Process the appropriate event type */
		case SDL_KEYDOWN:  /* Handle a KEYDOWN event */
			{
				if( (StringEvent.key.keysym.sym == SDLK_BACKSPACE))
				{
					if( str.length() != 0 )
						str.erase( str.length() - 1 );
					else
						continue;
				}
				else if( StringEvent.key.keysym.sym == SDLK_RETURN )
				{
					return false;
				}
				else 
				{
						str +=  StringEvent.key.keysym.unicode;
				}
			}break;
	  }
	}


	SDL_PollEvent( &StringEvent );
	SDL_Color textColor = { 0,0,0 };
    //If a key was pressed
    if( StringEvent.type == SDL_KEYDOWN )
    {
            //Free the old surface
            SDL_FreeSurface( text );
        
            //Render a new text surface
			text = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), textColor );

		 /*
		if( str.length() > 2 )
		{
						//If backspace was pressed and the string isn't blank
			if( ( StringEvent.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
			{
				//Remove a character from the end
				str.erase( str.length() - 1 );
			}

			return;
		}
        //Keep a copy of the current version of the string
        std::string temp = str;
        
        //If the string less than maximum size
        if( str.length() <= 2 )
        {

            //If the key is a space
            if( StringEvent.key.keysym.unicode == (Uint16)' ' )
            {
                //Append the character
                str += (char)StringEvent.key.keysym.unicode;    
            }
            //If the key is a number
            else if( ( StringEvent.key.keysym.unicode >= (Uint16)'0' ) && ( StringEvent.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Append the character
                str += (char)StringEvent.key.keysym.unicode;
            }
            //If the key is a uppercase letter
            else if( ( StringEvent.key.keysym.unicode >= (Uint16)'A' ) && ( StringEvent.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                str += (char)StringEvent.key.keysym.unicode;
            }
            //If the key is a lowercase letter
            else if( ( StringEvent.key.keysym.unicode >= (Uint16)'a' ) && ( StringEvent.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Append the character
                str += (char)StringEvent.key.keysym.unicode;
            }
        }
    
        //If backspace was pressed and the string isn't blank
        if( ( StringEvent.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
        {
            //Remove a character from the end
            str.erase( str.length() - 1 );
        }
        
        //If the string was changed
        if( str != temp )
        {
            //Free the old surface
            SDL_FreeSurface( text );
        
            //Render a new text surface
            text = TTF_RenderText_Solid( gamestate.font, str.c_str(), textColor );
        }
		*/
			return true;
    }
	return false;
}

void StringInput::show_centered()  
{
    //If the surface isn't blank
    if( text != NULL )
    {
        //Show the name
        //gamestate.apply_surface( ( gamestate.SCREEN_WIDTH - text->w ) / 2, ( gamestate.SCREEN_HEIGHT - text->h ) / 2, text, gamestate.BackBuffer );
		//Gfx.apply_surface( ( gamestate.SCREEN_WIDTH - text->w ) / 2, ( gamestate.SCREEN_HEIGHT - text->h ) / 2, text, gamestate.BackBuffer );
    }
}