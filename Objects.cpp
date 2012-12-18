#include <cmath>
#include "Objects.h"
#include "Game.h"
#include "characters.h"
#include "Timers.h"
#include "Collision.h"
#include "Audio.h"

// @date 2012-08-07

Control_Objects Control_OBJ;

int Object::Initialize(float _xPos = 0.0f, float _yPos = 0.0f, int _Width = 0, int _Height = 0, int _Frame = 0, int _Radius = 0 )
{
	xPos = _xPos;
	yPos = _yPos;
	Width = _Width;
	Height = _Height;
	Frame = _Frame;
	radius = _Radius;

	int ArraySize = sizeof(Clips) / sizeof(Clips[0]);
	// Zeroing the Clips array
	for( int i = 0; i < ArraySize; i++ )
	{
		Clips[ i ].x = 0;
		Clips[ i ].y = 0;
		Clips[ i ].w = 0;
		Clips[ i ].h = 0;
	}
	return 0;
}

int Object::SetClips(int _xStepping = 0, int _yStepping = 0, int _Width = 0, int _Height = 0)
{
	int ArraySize = sizeof(Clips) / sizeof(Clips[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
		Clips[ i ].x = _xStepping * i;
		Clips[ i ].y = _yStepping;
		Clips[ i ].w = _Width;
		Clips[ i ].h = _Height;
	}
	return 0;
}

Tree::Tree()
{
	SingleClip.h = 180;
	SingleClip.w = 158;
	SingleClip.x = 0;
	SingleClip.y = 0;
}

PowerUp::PowerUp( int xPos, int yPos, int Surface )
{
	xPos = xPos;
	yPos = yPos;
	surface = Surface;
	Height = 56;
	Width = 50;
	Frame = 0;
	Left = true;
	Right = false;

	radius = ( Width > Height ) ? Width / 2 - 10 : Height/2 - 10;
	this->SetClips(50,54,50,56);
	//SetClips();
}

/*
void PowerUp::SetClips()
{
	for( int i = 0; i < 4; i++ )
	{
		Clips[ i ].x = i * Width;
		Clips[ i ].y = 54;
		Clips[ i ].w = Width;
		Clips[ i ].h = Height;
	}
}
*/

ThingsToDemon::ThingsToDemon()
{
	Width = 50;
	Height = 50;
	surface = gamestate.m_srfDemonLife;
	SurfaceHealth = gamestate.m_srfDemonHealthAndFire;
	SetClips();
	xPos = 0;
	yPos = 0;
}

void ThingsToDemon::SetClips()
{
	for( int i = 0; i < 6; i++ )
	{
		Clips[ i ].x = Width * i;
		Clips[ i ].y = 0;
		Clips[ i ].w = Width;
		Clips[ i ].h = Height;
	}

	int Width_H = 70;
	int Height_H = 20;
	int y_Pos = 0;

	for( int i = 0; i < 6; i++ )
	{
		HealthClips[ i ].x = i * Width_H; 
		HealthClips[ i ].y = y_Pos; 
		HealthClips[ i ].w = Width_H;
		HealthClips[ i ].h = Height_H;
	}
}

Control_Objects::Control_Objects()
{
	DemonLife = new ThingsToDemon;
	DemonLife->Initialize(0,0,50,50,0,0);
	DemonLife->SetClips();
	// Replaced by Initialize function
	//DemonLife->Frame = 0;
	//DemonLife->Height = 43;
	//DemonLife->Width = 49;
	//DemonLife->xPos = 0;
	//DemonLife->yPos = 0;

	WhichLifeToShow = 0;
	
	destHealth.x = 50; 
	destHealth.y = 550;
	destHealth.w = 70;
	destHealth.h = 20;

	FrameHealth = 0;

	Zombie = 7;
	Skeleton = 8;
	Skull = 18;

	WereWolf = NULL;
	PowerUpMan = false;
}

void Control_Objects::CreateObjects()
{
	/*
	if( demon.WhereIsEnd > 200 )
	{
		if( rand() % 50 == 12 && timer.Timer_CreateCoffin > 70 )
		{
			timer.Timer_CreateCoffin = 0;
			List_Coffins.push_back( CreateCoffin(	rand() % 750 + 150, 
													500, gamestate.m_srfCoffin ) );
		}
		timer.Timer_CreateCoffin++;
	}
	else
	{
		if( rand() % 100 == 12 && timer.Timer_CreateCoffin > 70 )
		{
			timer.Timer_CreateCoffin = 0;
			List_Coffins.push_back( CreateCoffin(	rand() % 750 + 150, 
													500, gamestate.m_srfCoffin ) );
		}
		timer.Timer_CreateCoffin++;
	}
	*/
}

void PowerUp::SetFrame()
{
	if( Frame < 3 )
	{
		Frame++;
	}
	else
	{
		Frame = 0;
	}

}

// draws the objects coffins, fireballs etc, that exist and checks for collision 
// fireballs against the enemies and the boss, also the powerup
// shows life and lifeicon
void Control_Objects::DrawObjects()
{
	Control_OBJ.WereWolf = new PowerUp( 50, 400, gamestate.m_srfDemonLife );

	float speed = 500.0f * ( gamestate.dt / 1000.0f );
    float CoffinTim = 50.0f * ( gamestate.dt / 1000.0f );

	list< FireBall* > vRemoveFireBall;
	list< FireBall* >::iterator vRemoveIterFireBall;

	list< Enemy* >vRemoveEnemy;
	list< Enemy* >::iterator vRemoveIterEnemy; 

	list< Heads* > vRemoveHead;
	list< Heads* >::iterator vRemoveIterHead;

	if( Control_OBJ.PowerUpMan == true )
	{
		if( demon.isMovingLeft && demon.xVelocity >= gamestate.SCREEN_WIDTH - 350 )
		{
			Control_OBJ.WereWolf->xPos += CoffinTim;
		}
		else if( demon.isMovingRight )
		{
			Control_OBJ.WereWolf->xPos -= CoffinTim;
		}

		Control_OBJ.WereWolf->yPos -= abs( 2 * cos( CoffinTim ) );
		if( Control_OBJ.WereWolf->Left )
		{	
			Control_OBJ.WereWolf->xPos -= 2 * cos( CoffinTim );
			if( timer.Timer_PowerUpRoll > 20 )
			{
				Control_OBJ.WereWolf->Right = true;
				Control_OBJ.WereWolf->Left = false;
				timer.Timer_PowerUpRoll = 0.0f;
			}
			timer.Timer_PowerUpRoll++;
		}
		else if( Control_OBJ.WereWolf->Right )
		{
			Control_OBJ.WereWolf->xPos += 2 * cos( CoffinTim );
			if( timer.Timer_PowerUpRoll > 20 )
			{
				Control_OBJ.WereWolf->Left = true;
				Control_OBJ.WereWolf->Right = false;
				timer.Timer_PowerUpRoll = 0.0f;
			}
			timer.Timer_PowerUpRoll++;
		}
		
			// draw the powerup here when its created
			SDL_Rect destRect = {	Control_OBJ.WereWolf->xPos,
									Control_OBJ.WereWolf->yPos,
									Control_OBJ.WereWolf->Width,
									Control_OBJ.WereWolf->Height };

			SDL_BlitSurface(	gamestate.GetSurface( Control_OBJ.WereWolf->surface ),
								&Control_OBJ.WereWolf->Clips[ Control_OBJ.WereWolf->Frame ],
								gamestate.BackBuffer,
								&destRect );

		if( timer.Timer_PowerUp > 2 )
		{
			// draw the powerup here when its created
			SDL_Rect destRect = {	Control_OBJ.WereWolf->xPos,
									Control_OBJ.WereWolf->yPos,
									Control_OBJ.WereWolf->Width,
									Control_OBJ.WereWolf->Height };

			SDL_BlitSurface(	gamestate.GetSurface( Control_OBJ.WereWolf->surface ),
								&Control_OBJ.WereWolf->Clips[ Control_OBJ.WereWolf->Frame ],
								gamestate.BackBuffer,
								&destRect );

			Control_OBJ.WereWolf->SetFrame();
			timer.Timer_PowerUp = 0;
		}
		else
		{
			// draw the powerup here when its created
			SDL_Rect destRect = {	Control_OBJ.WereWolf->xPos,
									Control_OBJ.WereWolf->yPos,
									Control_OBJ.WereWolf->Width,
									Control_OBJ.WereWolf->Height };
			SDL_BlitSurface(	gamestate.GetSurface( Control_OBJ.WereWolf->surface ),
								&Control_OBJ.WereWolf->Clips[ Control_OBJ.WereWolf->Frame ],
								gamestate.BackBuffer,
								&destRect );
			timer.Timer_PowerUp++;
		}

		// kolla om han har blivit demon annars så sätt till false igen så den kan skapas en gång till
		bool GettingSpooky = CollisionController.CheckCollisionWithPlayer( Control_OBJ.WereWolf, 1 );
		if( GettingSpooky == true )
		{
			demon.DemonHunter = true;
			demon.SmallHunter = false;
			GettingSpooky = false;
			//delete Control_OBJ.WereWolf;
			Control_OBJ.PowerUpMan = false;
			gamestate.GameCondition = GS_MORPH;
		}	
		if( Control_OBJ.WereWolf->yPos < 50 )
		{
			PowerUpMan = false;
		}
	}

	// Do we have any Fireballs to draw to the screen?
	if( Control_OBJ.List_FireBalls.size() != 0 )
	{
		std::list< FireBall* >::iterator i = Control_OBJ.List_FireBalls.begin();
		for( ; i != Control_OBJ.List_FireBalls.end(); ++i )  
		{
			FireBall * temp = (*i);
			if( gamestate.GameCondition == GS_LEVEL1BOSS )
			{
				if( gamestate.boss->My_BossHead.size() != 0 )
				{
					list< Heads* >::iterator h = gamestate.boss->My_BossHead.begin();
					for( ; h != gamestate.boss->My_BossHead.end(); ++h )
					{
						Heads * head = ( *h );
						if( CollisionController.CollisionCircle( temp, head, false ) )
						{
							demon.Score += 5;
							//gamestate.Score += 5;
							vRemoveHead.push_back( ( *h ) );
							vRemoveFireBall.push_back( ( *i ) );
							Audio.PlaySoundEffect( SOUND_FIREBALL_EXPLODE );

						}
					}
				}

				if( CollisionController.CollisionCircle( temp, gamestate.boss, true ) )
				{
					vRemoveFireBall.push_back( ( *i ) ); 
					Audio.PlaySoundEffect( SOUND_FIREBALL_EXPLODE );
					demon.Score += 5;
					//gamestate.Score += 5;
					gamestate.boss->BossLife -= 50;
					if( gamestate.boss->BossLife < 0 )
					{
						gamestate.boss->BossDead = true;
					}
				}

			}



			if( Control_ENEMY.My_Enemies.size() != 0 )
			{
				std::list< Enemy* >::iterator e = Control_ENEMY.My_Enemies.begin();
				for( ; e != Control_ENEMY.My_Enemies.end(); ++e )
				{
					Enemy * enemy = (*e);

					if( ( *e )->Die != true )
					{
						if( CollisionController.CollisionCircle( temp, enemy, false ) )
						{
							Audio.PlaySoundEffect( SOUND_FIREBALL_EXPLODE );

							demon.Score += 2;
							//gamestate.Score += 2;
							if( (*e)->Surface == Zombie )
							{
								vRemoveEnemy.push_back( ( *e ) );
							}
							else if( (*e)->Surface == Skeleton )
							{
								(*e)->Die = true;
								(*e)->Walk = false;
								if( (*e)->Frame == 28 )
								{
									vRemoveEnemy.push_back( ( *e ) );
								}
							}
							else if( (*e)->Surface ==  Skull )
							{
								vRemoveEnemy.push_back( ( *e ) );
								if( Control_OBJ.PowerUpMan == false && demon.DemonHunter == false )
								{
									Control_OBJ.PowerUpMan = true;
									Control_OBJ.WereWolf = new PowerUp( (*e)->xPos, (*e)->yPos + 20, gamestate.m_srfDemonLife );
								}
							}
						
							vRemoveFireBall.push_back( *i );
						}
					}

				}
			}
			SDL_Rect destRect = { temp->xPos, temp->yPos, temp->Width, temp->Height };
			
			if( temp->FireLeft == true )
			{
				SDL_BlitSurface(	gamestate.GetSurface( temp->surface ), &temp->Clips[ temp->FrameLeft ],
									gamestate.BackBuffer, &destRect );
				temp->xPos -= speed;
				if( temp->FrameLeft == 5 )
				{
					temp->FrameLeft = 5;
				}
				else
				{
					temp->FrameLeft++;
				}
			}
			else
			{
				SDL_BlitSurface(	gamestate.GetSurface( temp->surface ), &temp->Clips[ temp->FrameRight ],
									gamestate.BackBuffer, &destRect );

				temp->xPos += speed;

				if( temp->FrameRight == 2 )
				{
					temp->FrameRight = 2;
				}
				else
				{
				temp->FrameRight++;
				}
				
				if( temp->xPos > 790 || temp->xPos < 20 )
				{
					vRemoveFireBall.push_back( (*i) );
				}

			}
		
		}

		vRemoveIterEnemy = vRemoveEnemy.begin();
		for( ; vRemoveIterEnemy != vRemoveEnemy.end(); ++vRemoveIterEnemy )
		{
			Control_ENEMY.My_Enemies.remove( ( *vRemoveIterEnemy ) );
		}

		vRemoveIterHead = vRemoveHead.begin();
		for( ; vRemoveIterHead != vRemoveHead.end(); ++vRemoveIterHead )
		{
			gamestate.boss->My_BossHead.remove( ( *vRemoveIterHead ) );
		}
			
	}
	
	list< Coffin* > vRemoveCoffin;
	list< Coffin* >::iterator vRemoveIterCoffin;

	if( Control_OBJ.List_Coffins.size() != 0 )
	{
		std::list< Coffin* >::iterator i = Control_OBJ.List_Coffins.begin();
		for( ; i != Control_OBJ.List_Coffins.end(); i++ )
		{
			Coffin * temp = (*i);
			/*temp->xPos -= speed;*/
			if( demon.isMovingLeft && demon.xVelocity >= gamestate.SCREEN_WIDTH - 350 )
			{
				temp->xPos += CoffinTim;
			}
			else if( demon.isMovingRight )
			{
				temp->xPos -= CoffinTim;
			}
			

			SDL_Rect srcRect = {	temp->Clips[ temp->Frame ].x, 
									temp->Clips[ temp->Frame ].y, 
									temp->Width, temp->Height };

			SDL_Rect dstRect = {	temp->xPos, 
									temp->yPos + 10, 
									temp->Width, 
									temp->Height };

			if( timer.Timer_CoffinTimer > 5 )
			{
				timer.Timer_CoffinTimer = 0.0f;
				temp->SetFrames();
			}
			else
			{
				timer.Timer_CoffinTimer++;
			}

			if( temp->Frame == 11 )
			{
				
				Control_ENEMY.My_Enemies.push_back( Control_ENEMY.CreateEnemy( temp->xPos, temp->yPos - 30, gamestate.m_srfSkeleton ) );
				vRemoveCoffin.push_back( (*i) );
			}


				SDL_BlitSurface(	gamestate.GetSurface( temp->surface ), &srcRect,
									gamestate.BackBuffer, &dstRect );	
		}
	}

	vRemoveIterCoffin = vRemoveCoffin.begin();

	for( ; vRemoveIterCoffin != vRemoveCoffin.end() ; ++vRemoveIterCoffin )
	{
		List_Coffins.remove( ( *vRemoveIterCoffin ) );
	}

		vRemoveIterFireBall = vRemoveFireBall.begin();
	for( ; vRemoveIterFireBall != vRemoveFireBall.end() ; ++vRemoveIterFireBall )
	{
		List_FireBalls.remove( ( *vRemoveIterFireBall ) );
	}
	
	SDL_Rect dstRect = { DemonLife->xPos, DemonLife->yPos, DemonLife->Width, DemonLife->Height };

	if( demon.LifeFull_Small )
	{
		if( demon.DemonHunter )
		{
			DemonLife->Frame = 5;
		}
		else
		{
			DemonLife->Frame = 2;
		}

		SDL_BlitSurface(	gamestate.GetSurface( gamestate.m_srfDemonLife ), &DemonLife->Clips[ DemonLife->Frame ],
							gamestate.BackBuffer, &dstRect );
	}
	else if( demon.LifeMedium_Small )
	{
		if( demon.DemonHunter )
		{
			DemonLife->Frame = 4;
		}
		else
		{
			DemonLife->Frame = 1;
		}

		SDL_BlitSurface(	gamestate.GetSurface( gamestate.m_srfDemonLife ), &DemonLife->Clips[ DemonLife->Frame ],
							gamestate.BackBuffer, &dstRect );
	}
	else if( demon.LifeLittle_Small )
	{
		if( demon.DemonHunter )
		{
			DemonLife->Frame = 3;
		}
		else
		{
			DemonLife->Frame = 0;
		}

		SDL_BlitSurface(	gamestate.GetSurface( gamestate.m_srfDemonLife ), &DemonLife->Clips[ DemonLife->Frame ],
							gamestate.BackBuffer, &dstRect );
	}

	switch( WhichLifeToShow )
	{
	case 0:
		//FrameHealth = 0;
		SDL_BlitSurface(	gamestate.GetSurface( gamestate.m_srfDemonHealthAndFire ), &DemonLife->HealthClips[ WhichLifeToShow  ],
							gamestate.BackBuffer, &Control_OBJ.destHealth );
		break;
	case 1:
		//FrameHealth = 1;
		SDL_BlitSurface(	gamestate.GetSurface( gamestate.m_srfDemonHealthAndFire ), &DemonLife->HealthClips[ WhichLifeToShow  ],
							gamestate.BackBuffer, &Control_OBJ.destHealth );
		break;
	case 2:
		//FrameHealth = 2;
		SDL_BlitSurface(	gamestate.GetSurface( gamestate.m_srfDemonHealthAndFire ), &DemonLife->HealthClips[ WhichLifeToShow  ],
							gamestate.BackBuffer, &Control_OBJ.destHealth );
		break;
	case 3:
		//FrameHealth = 3;
		SDL_BlitSurface(	gamestate.GetSurface( gamestate.m_srfDemonHealthAndFire ), &DemonLife->HealthClips[ WhichLifeToShow  ],
							gamestate.BackBuffer, &Control_OBJ.destHealth );
		break;
	case 4:
		//FrameHealth = 4;
		SDL_BlitSurface(	gamestate.GetSurface( gamestate.m_srfDemonHealthAndFire ), &DemonLife->HealthClips[ WhichLifeToShow ],
							gamestate.BackBuffer, &Control_OBJ.destHealth );
		break;
	case 5:
		//FrameHealth = 5;
		SDL_BlitSurface(	gamestate.GetSurface( gamestate.m_srfDemonHealthAndFire ), &DemonLife->HealthClips[ WhichLifeToShow  ],
							gamestate.BackBuffer, &Control_OBJ.destHealth );
		break;
	}	
}

Coffin::Coffin()
{
	Width = 64;
	Height = 64;
	Frame = 0;
	this->SetClips(64,0,64,64);
}

/*
void Coffin::SetClips()
{
	for( int i = 0; i < 10; i++ )
	{
		Clips[ i ].x = i * Width;
		Clips[ i ].y = 0;
		Clips[ i ].w = Width;
		Clips[ i ].h = Height;
	}
}
*/

void Coffin::SetFrames()
{
	if( Frame > 10 )
	{
		Frame = 0;
	}
	else
	{
		Frame++;
	}
}

Coffin * Control_Objects::CreateCoffin( int xPos, int yPos, int Surface )
{
	Coffin * TemporaryCoffin = new Coffin;
	TemporaryCoffin->xPos = xPos;
	TemporaryCoffin->yPos = yPos;
	TemporaryCoffin->surface = Surface;
	TemporaryCoffin->SetClips();

	return TemporaryCoffin;
}

FireBall::FireBall()
{
	xPos = 0;
	yPos = 0;

	FrameRight = 0;
	FrameLeft = 3;
	FireRight = false;
	FireLeft = false;

	FireWidth = 35;
	FireHeight = 35;
	this->SetClips(35,35,35,35);
}

/*
void FireBall::SetClips()
{
	for( int i = 0; i < 6; i++ )
	{
		Clips[ i ].x = Width * i;
		Clips[ i ].y = 70;
		Clips[ i ].w = Width;
		Clips[ i ].h = Height;
	}

	Clips[ 6 ].x = 420;
	Clips[ 6 ].y = 60;
	Clips[ 6 ].w = 40;
	Clips[ 6 ].h = 40;

	Clips[ 7 ].x = 480;
	Clips[ 7 ].y = 45;
	Clips[ 7 ].w = 80;
	Clips[ 7 ].h = 70;
}
*/

FireBall * Control_Objects::CreateFireBall( int xPos, int yPos, int Surface, bool Right, bool Left )
{
	FireBall * TemporaryFireball = new FireBall;
	TemporaryFireball->xPos = xPos;
	TemporaryFireball->yPos = yPos;
	TemporaryFireball->surface = Surface;
	TemporaryFireball->Width = 70;
	TemporaryFireball->Height = 30;
	TemporaryFireball->FireRight = Right;
	TemporaryFireball->FireLeft = Left;
	TemporaryFireball->SetClips(70,30,70,30);
	TemporaryFireball->radius = ( TemporaryFireball->FireWidth > TemporaryFireball->FireHeight ) ? TemporaryFireball->FireWidth / 2 : TemporaryFireball->FireHeight / 2;

	return TemporaryFireball;
}
