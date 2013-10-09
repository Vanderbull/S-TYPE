#include <cmath>
#include "Objects.h"
#include "Game.h"
#include "characters.h"
#include "Timers.h"
#include "Collision.h"
#include "ControlGfx.h"

ControlObject ObjectController;

// Default Constructor for objects
Object::Object()
{
	Active = 0;
	xPos = yPos = 0;
	Width = Height = 0;
	Surface = 0;
	Frame = 0;
	Radius = 0; // fireball crap
	CollisionBox.h = 0;
	CollisionBox.w = 0;
	CollisionBox.x = 0;
	CollisionBox.y = 0;

	int ArraySize = sizeof(Clips) / sizeof(Clips[0]);
	// Zeroing the Clips array
	for( int i = 0; i < ArraySize; i++ )
	{
		Clips[ i ].x = 0;
		Clips[ i ].y = 0;
		Clips[ i ].w = 0;
		Clips[ i ].h = 0;
	}
}

int Object::isActive()
{
	return true;
}

int Object::Initialize(float _xPos = 0.0f, float _yPos = 0.0f, int _Width = 0, int _Height = 0, int _Frame = 0, int _Radius = 0 )
{
	xPos = _xPos;
	yPos = _yPos;
	Width = _Width;
	Height = _Height;
	Frame = _Frame;
	Radius = _Radius;

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

ControlObject::ControlObject()
{
	//demonLife = new ThingsTodemon;
	//demonLife->Initialize(0,0,50,50,0,0);
	//demonLife->SetClips();
	// Replaced by Initialize function
	//demonLife->Frame = 0;
	//demonLife->Height = 43;
	//demonLife->Width = 49;
	//demonLife->xPos = 0;
	//demonLife->yPos = 0;

	WhichLifeToShow = 0;
	
	destHealth.x = 50; 
	destHealth.y = 550;
	destHealth.w = 70;
	destHealth.h = 20;

	FrameHealth = 0;

	Zombie = 7;
	Skeleton = 8;
	Skull = 18;

	PowerUpMan = false;
}

void ControlObject::CreateObjects()
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
void ControlObject::DrawObjects()
{
	float speed = 500.0f * ( gamestate.DeltaTime / 1000.0f );
    float CoffinTim = 50.0f * ( gamestate.DeltaTime / 1000.0f );

	list< Fireball* > vRemoveFireBall;
	list< Fireball* >::iterator vRemoveIterFireBall;

	list< CEnemy* >vRemoveEnemy;
	list< CEnemy* >::iterator vRemoveIterEnemy; 

	list< Heads* > vRemoveHead;
	list< Heads* >::iterator vRemoveIterHead;


	// Do we have any Fireballs to draw to the screen?
	if( ObjectController.List_FireBalls.size() != 0 )
	{
		std::list< Fireball* >::iterator i = ObjectController.List_FireBalls.begin();
		for( ; i != ObjectController.List_FireBalls.end(); ++i )  
		{
			Fireball * temp = (*i);
			//if( gamestate.State == GAME_BOSS_STATE )
			if( gamestate.GameState.top() == GAME_BOSS_STATE )
			{
				
				//if( gamestate.pBoss->My_BossHead.size() != 0 )
				//{
				//	list< Heads* >::iterator h = gamestate.pBoss->My_BossHead.begin();
				//	for( ; h != gamestate.pBoss->My_BossHead.end(); ++h )
				//	{
				//		Heads * head = ( *h );
				//		if( CollisionController.CollisionCircle( temp, head, false ) )
				//		{
				//			gamestate.AddScore(5);
				//			vRemoveHead.push_back( ( *h ) );
				//			vRemoveFireBall.push_back( ( *i ) );
				//		}
				//	}
				//}
				

				//if( CollisionController.CollisionCircle( temp, gamestate.pBoss, true ) )
				//{
				//	vRemoveFireBall.push_back( ( *i ) ); 
				//	gamestate.AddScore(5);
				//	gamestate.pBoss->BossLife -= 50;
				//	if( gamestate.pBoss->BossLife < 0 )
				//	{
				//		gamestate.pBoss->BossDead = true;
				//	}
				//}

			}


			// This part might be removed due to the fact RemoveEnemy is being removed
			if( EnemyController.Enemies.size() != 0 )
			{
				std::list< CEnemy* >::iterator e = EnemyController.Enemies.begin();
				for( ; e != EnemyController.Enemies.end(); ++e )
				{
					CEnemy * enemy = (*e);

					if( ( *e )->Die != true )
					{
						if( CollisionController.CollisionCircle( temp, enemy, false ) )
						{
							//gamestate.AddScore(2);

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
								// Creating the PowerUp object
								/*
								if( ControlObjects.PowerUpMan == false && demon.demonHunter == false )
								{
									ControlObjects.PowerUpMan = true;
									ControlObjects.WereWolf = new PowerUp( (*e)->xPos, (*e)->yPos + 20, gamestate.m_srfdemonLife );
								}
								*/
							}
						
							vRemoveFireBall.push_back( *i );
						}
					}

				}
			}
			SDL_Rect destRect = { temp->xPos, temp->yPos, temp->Width, temp->Height };
			
			if( temp->FireLeft == true )
			{
				SDL_BlitSurface(	Gfx.GetSurface( temp->Surface ), &temp->Clips[ temp->FrameLeft ],
									Gfx.BackBuffer, &destRect );
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
				SDL_BlitSurface(	Gfx.GetSurface( temp->Surface ), &temp->Clips[ temp->FrameRight ],
									Gfx.BackBuffer, &destRect );

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
			EnemyController.Enemies.remove( ( *vRemoveIterEnemy ) );
		}

		//vRemoveIterHead = vRemoveHead.begin();
		//for( ; vRemoveIterHead != vRemoveHead.end(); ++vRemoveIterHead )
		//{
		//	gamestate.pBoss->My_BossHead.remove( ( *vRemoveIterHead ) );
		//}
			
	}
	
	list< Coffin* > vRemoveCoffin;
	list< Coffin* >::iterator vRemoveIterCoffin;

	if( ObjectController.List_Coffins.size() != 0 )
	{
		std::list< Coffin* >::iterator i = ObjectController.List_Coffins.begin();
		for( ; i != ObjectController.List_Coffins.end(); i++ )
		{
			Coffin * temp = (*i);
			/*temp->xPos -= speed;*/
			if( BCPlayer.isMovingLeft && BCPlayer.xVelocity >= SDL_GetVideoSurface()->w - 350 )
			{
				temp->xPos += CoffinTim;
			}
			else if( BCPlayer.isMovingRight )
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

			if( timer.CoffinTimer > 5 )
			{
				timer.CoffinTimer = 0.0f;
				temp->SetFrames();
			}
			else
			{
				timer.CoffinTimer++;
			}

			if( temp->Frame == 11 )
			{
				
				//EnemyController.Enemies.push_back( EnemyController.CreateEnemy( temp->xPos, temp->yPos - 30, gamestate.m_srfSkeleton ) );
				vRemoveCoffin.push_back( (*i) );
			}


				SDL_BlitSurface(	Gfx.GetSurface( temp->Surface ), &srcRect,
									Gfx.BackBuffer, &dstRect );	
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
	
	//SDL_Rect dstRect = { demonLife->xPos, demonLife->yPos, demonLife->Width, demonLife->Height };

	//if( demon.LifeFull_Small )
	//{
	//	demonLife->Frame = 2;

	//	SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfdemonLife ), &demonLife->Clips[ demonLife->Frame ],
	//						Gfx.BackBuffer, &dstRect );
	//}
	//else if( demon.LifeMedium_Small )
	//{
	//	demonLife->Frame = 1;

	//	SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfdemonLife ), &demonLife->Clips[ demonLife->Frame ],
	//						Gfx.BackBuffer, &dstRect );
	//}
	//else if( demon.LifeLittle_Small )
	//{
	//	demonLife->Frame = 0;

	//	SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfdemonLife ), &demonLife->Clips[ demonLife->Frame ],
	//						Gfx.BackBuffer, &dstRect );
	//}

	// x,y,w,h
	BCPlayer._HealthPoints = 3;
	SDL_Rect srfHealth = {0,0,64*BCPlayer._HealthPoints,64};
	SDL_Rect Viewport_srfHealth = {0,0,64*BCPlayer._HealthPoints,64};

	SDL_BlitSurface( Gfx.GetSurface( gamestate.m_srfHealth ), &srfHealth,
					Gfx.BackBuffer, &Viewport_srfHealth );

	//SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfdemonHealthAndFire ), &demonLife->HealthClips[ WhichLifeToShow  ],
	//				Gfx.BackBuffer, &ObjectController.destHealth );
}

Coffin::Coffin()
{
	Width = 64;
	Height = 64;
	Frame = 0;
	this->SetClips(64,0,64,64);
}

void Coffin::Update()
{
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

Coffin * ControlObject::CreateCoffin( int xPos, int yPos, int Surface )
{
	Coffin * TemporaryCoffin = new Coffin;
	TemporaryCoffin->xPos = xPos;
	TemporaryCoffin->yPos = yPos;
	TemporaryCoffin->Surface = Surface;
	TemporaryCoffin->SetClips();

	return TemporaryCoffin;
}

Fireball::Fireball()
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

Fireball * ControlObject::CreateFireBall( int xPos, int yPos, int Surface, bool Right, bool Left )
{
	Fireball * TemporaryFireball = new Fireball;
	TemporaryFireball->xPos = xPos;
	TemporaryFireball->yPos = yPos;
	TemporaryFireball->Surface = Surface;
	TemporaryFireball->Width = 70;
	TemporaryFireball->Height = 30;
	TemporaryFireball->FireRight = Right;
	TemporaryFireball->FireLeft = Left;
	TemporaryFireball->SetClips(70,30,70,30);
	TemporaryFireball->Radius = ( TemporaryFireball->FireWidth > TemporaryFireball->FireHeight ) ? TemporaryFireball->FireWidth / 2 : TemporaryFireball->FireHeight / 2;

	return TemporaryFireball;
}
