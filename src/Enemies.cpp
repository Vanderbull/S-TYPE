#pragma once
#include "Enemies.h"
#include "Game.h"
#include <list>
#include "Timers.h"
#include "Objects.h"
#include "Collision.h"
#include "ControlGfx.h"

Control_Enemies EnemyController;

CDwarf::CDwarf()
{
	CDwarf::Speed = 300;
}

CSkeleton::CSkeleton()
{
	CSkeleton::Speed = 3000;
}

CEnemy::CEnemy()
{
	CEnemy::Speed = 300;
	memset(DwarfClips, 0, sizeof(DwarfClips));
	memset(SkeletonClips, 0, sizeof(SkeletonClips));
}

void CEnemy::Set_Clips( int WhichTypeOfEnemy )
{
	// enemy type Dwarf
	if( WhichTypeOfEnemy == ENEMY_DWARF )
	{
		for( int i = 0; i < 4; i++ )
		{
			for( int j = 0; j < 14; j++ )
			{
				DwarfClips[ i ][ j ].x = j * Width;
				DwarfClips[ i ][ j ].y = i * Height;
				DwarfClips[ i ][ j ].h = Height;
				DwarfClips[ i ][ j ].w = Width;
			}
		}
	}	
	// enemy type Skeleton
	else if( WhichTypeOfEnemy == ENEMY_SKELETON )
	{
		for( int i = 0; i < 4; i++ )
		{
			for( int j = 0; j < 14; j++ )
			{
				SkeletonClips[ i ][ j ].x = j * Width;
				SkeletonClips[ i ][ j ].y = i * Height;
				SkeletonClips[ i ][ j ].h = Height;
				SkeletonClips[ i ][ j ].w = Width;
			}
		}
	}	
}

// sets frame for skeleton
void CEnemy::SetFrame()
{
	PrevFrame = Frame;

	if( Attack )
	{
		Walk = false;
		if( LeftOfPlayer )
		{
			if( AttackFrameRight == 45 )
			{
				AttackFrameRight = 37;
				Walk = true;
				Attack = false;
			}
			else
			{
				AttackFrameRight++;
			}
			Frame = AttackFrameRight;
		}
		else if( RightOfPlayer )
		{
			if( AttackFrameLeft == 18 )
			{
				AttackFrameLeft = 9;
				Walk = true;
				Attack = false;
			}
			else
			{
				AttackFrameLeft++;
			}
			Frame = AttackFrameLeft;
		}
	}
	else if( Die )
	{
		Walk = false;
		Attack = false;

		if( LeftOfPlayer )
		{
			if( DieFrameRight == 54 )
			{
				DieFrameRight = 54;

			}
			else
			{
				DieFrameRight++;
			}

			Frame = DieFrameRight;
		}
		else if( RightOfPlayer )
		{
			if( DieFrameLeft == 27 ) 
			{
				DieFrameLeft = 27;

			}
			else
			{
				DieFrameLeft++;
			}

			Frame = DieFrameLeft;
		}
	}
	else if( Walk )
	{
		if( LeftOfPlayer )
		{
			if( WalkFrameRight == 39 )
			{
				WalkFrameRight = 30;
			}
			else
			{
				WalkFrameRight++;
			}

			Frame = WalkFrameRight;
		}
		else if( RightOfPlayer )
		{
			if( WalkFrameLeft == 8 )
			{
				WalkFrameLeft = 0;
			}
			else
			{
				WalkFrameLeft++;
			}
			
			Frame = WalkFrameLeft;
		}		
	}
}

void Control_Enemies::Update()
{
	Collide = false;
	list< CEnemy* >::iterator i = Enemies.begin();

	i = Enemies.begin();
	while(i != Enemies.end() )
	{
		(*i)->Update();
		if( (*i)->_Position.x <= 200 )
		{
			i = Enemies.erase(i);
		}
		else
		{
			++i;
		}
	}
}
// draws all enemies skeleton, skull, zombies, checks collision and updates frame
void Control_Enemies::Draw_Enemies()
{


	//list< Enemy* > vRemoveEnemy;
	//list< Enemy* >::iterator vRemoveIterEnemy;
	//float speed = 100.0f * ( gamestate.DeltaTime / 1000.0f );

	if( Enemies.size() != 0 )
	{
		list< CEnemy* >::iterator i = Enemies.begin();
		for( ; i != Enemies.end(); ++i )
		{

				// Check to see if collision occurs and if demon is in any kind of attack state
				//CEnemy * enemy = (*i);

				// checks collision with demon using circlecollision
				//Collide = CollisionController.CheckCollisionWithdemon( enemy, 1 );
				Collide = CollisionController.CheckCollision( (*i), 1, &BCPlayer);

				//Attack = demon.IsInStateAttack();
				
				if( Collide == true && BCPlayer.IsAttacking() ) // && Attack == true
				{
						if( (*i)->Surface == DWARF )
						{
							//vRemoveEnemy.push_back( ( *i ) );
							// Creating PowerUp object
							/*
							if( ControlObjects.PowerUpMan == false && demon.demonHunter == false )
							{
								ControlObjects.PowerUpMan = true;
								ControlObjects.WereWolf = new PowerUp( (*i)->xPos, (*i)->yPos + 20, gamestate.m_srfdemonLife );
							}
							*/
						}
						else if( (*i)->Surface == SKELETON )
						{
							(*i)->Die = true;
							(*i)->Walk = false;
							if( (*i)->Frame == 28 || (*i)->Frame == 56 )
							{
								//vRemoveEnemy.push_back( ( *i ) );
							}
						}
				}
				else if( Collide == true )
				{
					//demon.isHit = true;
					if( (*i)->Surface == 8 )
					{
						//timer.Hit++;
						//BCPlayer.Health--;
						//if( timer.Hit > 3 && BCPlayer.isImmortal == false )
						//{
							//timer.Hit = 0;
							//BCPlayer.isHit = true;
						//}
						(*i)->Attack = true;

					}
					else
					{
						//timer.Hit++;
						//BCPlayer.Health--;
							
						//if( timer.Hit > 3 && BCPlayer.isImmortal == false )
						//{
							//timer.Hit = 0;
							//BCPlayer.isHit = true;
						//}	
					}		
				}
				if( (*i)->Frame == 18 || (*i)->Frame == 46 )
				{
					(*i)->Attack = false;
					(*i)->Walk = true;
				}

				SDL_Rect EnemyDest = {	(*i)->_Position.x, (*i)->_Position.y, 
										Gfx.GetSurface( DWARF )->w, 
										Gfx.GetSurface( DWARF )->h }; 

				
				static int FrameCounter = 0;
				if( FrameCounter > 13)
					FrameCounter = 0;

				if(  (*i)->_Position.x < 0 )
				{
					//vRemoveEnemy.push_back( (*i) );
				}
				else
				{
					if( (*i)->Surface == DWARF )
					{
						if( Collide == false )
						{
							(*i)->_Position.x -= (*i)->Speed * gamestate.DeltaTime;
						}
									 
						SDL_BlitSurface(	Gfx.GetSurface( (*i)->Surface ),&(*i)->DwarfClips[ 0 ][ FrameCounter++ ], 
											Gfx.BackBuffer, &EnemyDest );
					}
					else if( (*i)->Surface == SKELETON )
					{
						if( Collide == false )
						{
							(*i)->_Position.x -= (*i)->Speed * gamestate.DeltaTime;
						}
						
						SDL_BlitSurface(	Gfx.GetSurface( (*i)->Surface ), &(*i)->SkeletonClips[ 0 ][ FrameCounter++ ],
											Gfx.BackBuffer, &EnemyDest );
					}
				}
		}

	}

	//vRemoveIterEnemy = vRemoveEnemy.begin();
	//for( ; vRemoveIterEnemy != vRemoveEnemy.end() ; ++vRemoveIterEnemy )
	//{
	//	Enemies.remove(*vRemoveIterEnemy);
	//}	
}

// gives the enemy the attributes he should have
CEnemy * Control_Enemies::CreateEnemy( int xPos, int yPos, int surface )
{
	CEnemy * temp = new CEnemy;
	temp->Surface = surface;
	temp->AnimCounter = 1;
	temp->PrevFrame = 0;
	
	temp->_Position.x = xPos;
	temp->_Position.y = yPos;

	temp->Height = 96;
	temp->Width = 96;
	temp->Walk = true;
	temp->Attack = false;
	temp->Die = false;
	temp->LeftOfPlayer = false; 
	temp->RightOfPlayer = false;

	temp->AttackFrameLeft = 9;
	temp->AttackFrameRight = 37;
	temp->DieFrameLeft = 18;
	temp->DieFrameRight = 46;
	temp->WalkFrameLeft = 0;
	temp->WalkFrameRight = 28;

	int Height, Width;
	Height = temp->Height / 2;
	Width = temp->Width / 2;


	if( temp->Surface == DWARF )
	{
		temp->Radius = ( Width > Height ) ? Width / 2 - 10 : Height / 2 - 10 ;
		temp->Set_Clips( ENEMY_DWARF );
	}
	else if( temp->Surface == SKELETON )
	{
		temp->Radius = ( Width > Height ) ? Width / 2 : Height / 2;
		temp->Set_Clips( ENEMY_SKELETON );
	}
	
	return temp;
}

void Control_Enemies::Create_Enemies()
{
	if( SpawnTimer < 0 )
	{
		SpawnTimer = 500;
		Enemies.push_back( CreateEnemy( SDL_GetVideoSurface()->w, GROUND_Y, SKELETON ) );
	}
	else
		SpawnTimer--;
	//if( rand() % 350 == 2)
		//Enemies.push_back( CreateEnemy( gamestate.SCREEN_WIDTH, GROUND_Y, ZOMBIE ) );
	//if( rand() % 500 == 2)
		//Enemies.push_back( CreateEnemy( SDL_GetVideoSurface()->w, GROUND_Y, SKELETON ) );
	//if( rand() % 1000 == 2)
		//Enemies.push_back( CreateEnemy( gamestate.SCREEN_WIDTH, GROUND_Y, SKULL ) );
	/*
	if( demon.WhereIsEnd > 200 )
	{
		if( rand() % 40 == 2 &&  timer.AttackTimer_Zombie >= 35 )
		{
			Enemies.push_back( CreateEnemy( gamestate.SCREEN_WIDTH, GROUND_Y, ZOMBIE ) );
			timer.AttackTimer_Zombie = 0;
		}
		timer.AttackTimer_Zombie++;
			
		if( rand() % 50 == 2 &&  timer.AttackTimer_Head >= 50 )
		{
			timer.AttackTimer_Head = 0;
			Enemies.push_back( CreateEnemy( gamestate.SCREEN_WIDTH - 40, GROUND_Y, SKULL ) );
		}
		timer.AttackTimer_Head++;
	}
	else
	{
		if( rand() % 100 == 2 &&  timer.AttackTimer_Zombie >= 50 )
		{
			Enemies.push_back( CreateEnemy( gamestate.SCREEN_WIDTH, GROUND_Y, ZOMBIE ) );
			timer.AttackTimer_Zombie = 0;
		}
		timer.AttackTimer_Zombie++;
			
		if( rand() % 100 == 2 &&  timer.AttackTimer_Head >= 100 )
		{
			timer.AttackTimer_Head = 0;
			Enemies.push_back( CreateEnemy( gamestate.SCREEN_WIDTH - 40, GROUND_Y, SKULL ) );
		}
		timer.AttackTimer_Head++;
	}
	*/
}

Control_Enemies::Control_Enemies()
{
	Attack = false;
	Collide = false;
	CollideFire = false;
	SpawnTimer = 0;

	//Zombie = 7;
	//Skeleton = 8;
}

