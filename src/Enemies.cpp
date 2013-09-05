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
				DwarfClips[ i ][ j ].x = j * this->Width;
				DwarfClips[ i ][ j ].y = i * this->Height;
				DwarfClips[ i ][ j ].h = this->Height;
				DwarfClips[ i ][ j ].w = this->Width;
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
				SkeletonClips[ i ][ j ].x = j * this->Width;
				SkeletonClips[ i ][ j ].y = i * this->Height;
				SkeletonClips[ i ][ j ].h = this->Height;
				SkeletonClips[ i ][ j ].w = this->Width;
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

// frame stuff
int Heads::GetFrame()
{
	return Frame;
}

void Heads::SetFrame( int WhichFrame )
{
	Frame = WhichFrame;
}

void Heads::UpdateFrame()
{
	Frame++;
}

float Boss::GetTimerAttack()
{
	return timer.AttackBoss;
}

int Boss::GetState()
{
	return State;
}

void Boss::ResetAttackTimer()
{
	timer.AttackBoss = 0;
}

void Boss::UpdateAttackTimer()
{
	float Speed = 200.0f * ( gamestate.DeltaTime / 1000.0f );
	timer.AttackBoss += Speed;
}

void Boss::SetState( int WhichState )
{
	State = WhichState;
}

void Boss::SetFrame( int WhichFrame )
{
	Frame = WhichFrame;
}
int Boss::GetFrame()
{
	return Frame;
}

void Boss::UpdateFrame()
{
	if( Frame >= 6 )
	{
		Frame = 0;
	}
	else
		Frame++;
}

void Boss::UpdateBoss()
{
	list< Heads* >::iterator i = My_BossHead.begin();
	float HeadSpeed = 70.0f * gamestate.DeltaTime;
	int Length = rand() % ( SDL_GetVideoSurface()->w - 100 ) + 50 ;
	if( timer.Hit > 50 )
		timer.Hit = 0;

	if( timer.Hit == 0 )
	{
		UpdateFrame();
		if( GetFrame() == 5)
			My_BossHead.push_back(	CreateBossHeads( _Position.x, _Position.y + 10, Surface, Length ) );
	}

	if( My_BossHead.size() != 0 )
	{
		for( ; i != My_BossHead.end(); ++i )
		{
			if( (*i)->HowFar >= (*i)->length )
			{
				(*i)->_Position.y += HeadSpeed;
			}
			else
			{
				(*i)->_Position.x -= HeadSpeed;
				(*i)->HowFar += HeadSpeed;
			}
		}
	}

	timer.Hit++;
	if( My_BossHead.size() != 0 )
	{
		list< Heads* >::iterator vRemoveIterHead;
		vRemoveIterHead = My_BossHead.begin();
		for( ; vRemoveIterHead != My_BossHead.end() ; ++vRemoveIterHead )
		{
			if( (*vRemoveIterHead)->_Position.x < 0.0f )
			{
				My_BossHead.remove( *vRemoveIterHead );
				vRemoveIterHead = My_BossHead.begin();
			}
			if( (*vRemoveIterHead)->_Position.y > SDL_GetVideoSurface()->h )
			{
				My_BossHead.remove( *vRemoveIterHead );
				vRemoveIterHead = My_BossHead.begin();
			}
		}
	}


	// updates boss, boss frame and checks collision against BCPlayer
	float x = GetTimerAttack();
	if( x >= BOSS_ATTACK_START || HeadsComing == true )
	{
		//bool CollideWithdemon = false;
		//CollideWithdemon = CollisionController.CollisionCircle( &BCPlayer, gamestate.pBoss, false );
		//if( CollideWithdemon )
		//{	
		//	bool CheckAttack = false;
		//	if( CheckAttack = BCPlayer.IsInStateAttack() )
		//	{
		//		gamestate.AddScore(10);
		//		gamestate.pBoss->BossLife -= 50;

		//		if( gamestate.pBoss->BossLife < 0 )
		//		{
		//			gamestate.pBoss->BossDead = true;
		//		}
		//	}
		//	else
		//	{		
		//		if( timer.Hit > 3 && BCPlayer.isImmortal == false )
		//		{
		//			//timer.Hit = 0;
		//			BCPlayer.Right = true;
		//			BCPlayer.isHit = true;
		//			BCPlayer.demonHealth -= 50;
		//		}
		//		//timer.Hit++;
		//		
		//	}

		//}
	
		//HeadsComing = true;

		float BOSSpeed = 150.0f * ( gamestate.DeltaTime / 1000.0f );
		timer.BossAnim += BOSSpeed;

		float BOSSpeedHead = 70.0f * ( gamestate.DeltaTime / 1000.0f );
		timer.BossHead += BOSSpeedHead;

		ResetAttackTimer();

		SetState( BOSS_ATTACK );
		if( timer.BossAnim >= ANIMPACEBOSSHEAD )
		{
			UpdateFrame();
			timer.BossAnim = 0.0f;
		}

		if( timer.BossHead >= 20 )
		{
			if( HeadAnimation == true )
			{
				timer.BossHead = 0;
				int Length = rand() % ( SDL_GetVideoSurface()->w - 100 ) + 50 ;
				if( Length < 50 )
				{
					Length = 50;
				}
				My_BossHead.push_back(	CreateBossHeads(	_Position.x, 
													_Position.y + 10, 
													Surface,
													Length ) );
				SizeHeads++;
			}

			
			//if( GetFrame() >= 4 )
			//{
			//	HeadAnimation = true;
			//	SetFrame( BOSS_IDLE );
			//}
		}

		if( SizeHeads == 6 )
		{
			HeadsComing = false;
			//SetFrame( BOSS_IDLE );
			SizeHeads = 1;
		}
	}
	else
	{
		//SetFrame( BOSS_IDLE );
		UpdateAttackTimer();
	}
		//sanity check
	switch( GetState() )
	{
		case BOSS_IDLE:
			{
				SDL_BlitSurface( Gfx.GetSurface( Surface ), 
					&GetClips( GetFrame() ),
								Gfx.BackBuffer, &ReturnDestRect() );
			}
		case BOSS_ATTACK:
			{
				SDL_BlitSurface( Gfx.GetSurface( Surface ),
				&GetClips( GetFrame() ), 
				Gfx.BackBuffer, &ReturnDestRect() );
			}
		case BOSS_DIE:
			{
				SDL_BlitSurface( Gfx.GetSurface( Surface ),
				&GetClips( GetFrame() ), 
				Gfx.BackBuffer, &ReturnDestRect() );
			}
	}

	UpdateHeads();
	
}

// does all update on head, against the demon, checks frame, and lifelenght
void Boss::UpdateHeads()
{
	if( My_BossHead.size() != 0 )
	{
		float HeadSpeed = 20.0f * ( gamestate.DeltaTime / 1000.0f );
		float Crash = 50.0f * ( gamestate.DeltaTime / 1000.0f );
		float HowFarSpeed = 300.0f * ( gamestate.DeltaTime / 1000.0f );
		
		
		list< Heads* > vRemoveHead;
		list< Heads* >::iterator vRemoveIterHead;

		list< Heads* >::iterator i = My_BossHead.begin();
		for( ; i != My_BossHead.end(); ++i )
		{
			Heads * temp = (*i);
			bool Collide = false;
			Collide = CollisionController.CollisionCircle( &BCPlayer, temp, false );

			if( Collide )
			{	
				if( BCPlayer.IsInStateAttack() )
				{
					//gamestate.AddScore(5);
					vRemoveHead.push_back((*i));
				}
				else
				{
					//if( timer.Hit > 3 && BCPlayer.isImmortal == false )
					//{
						//timer.Hit = 0;
						//BCPlayer.isHit = true;
						//BCPlayer.Health--;
					//}
					//timer.Hit++;
				}

			}

			if( temp->HowFar >= temp->length )
			{
				temp->state = HEAD_DOWN;

				if( temp->_Position.y > 500 )
				{
					temp->state = HEAD_CRASH;
					if( temp->state == HEAD_CRASH )
					{
						temp->HeadTimer += Crash;
						if( temp->HeadTimer > 5 )
						{
							if( temp->GetFrame() <= 4 )
							{
								temp->UpdateFrame();	
							}
							else
							{
								vRemoveHead.push_back( (*i) );
								temp->SetFrame( 4 );
							}

							temp->HeadTimer = 0;
						}
					}
				}

				if( temp->state == HEAD_DOWN ) 
				{
					temp->HeadTimer += HeadSpeed;
					if( temp->HeadTimer > 3 )
					{
						if( temp->GetFrame() <= 2 )
						{
							temp->SetFrame( 2 );
							temp->HeadTimer = 0;
						}
						else
						{
							temp->UpdateFrame();
						}
					}

					float speed = 200.0f * ( gamestate.DeltaTime / 1000 );
					temp->_Position.y += speed;
				}
			}
			else
			{
				float Speed = 250.0f * ( gamestate.DeltaTime / 1000 );
				temp->_Position.x -= Speed;
				temp->HowFar += HowFarSpeed;
			}

			SDL_Rect HeadDest = { temp->_Position.x, temp->_Position.y, temp->Width, temp->Height };
			
			SDL_BlitSurface(	Gfx.GetSurface( temp->Surface ), &temp->GetClips( temp->GetFrame() ),
								Gfx.BackBuffer, &HeadDest );
	
		}

		vRemoveIterHead = vRemoveHead.begin();
		for( ; vRemoveIterHead != vRemoveHead.end() ; ++vRemoveIterHead )
		{
			My_BossHead.remove( *vRemoveIterHead );
		}
	}

	return;
}

Heads * Boss::CreateBossHeads( int xPos, int yPos, int surface, int lengthOfTravel )
{
	Heads * temp = new Heads;
	temp->_Position.x = xPos;
	temp->_Position.y = yPos;
	temp->Surface = surface;
	temp->length = lengthOfTravel;

	temp->Radius = ( temp->HeadWidth > temp->HeadHeight ) ? temp->HeadWidth / 2 : temp->HeadHeight;

	return temp;
}

SDL_Rect Boss::ReturnDestRect()
{
	
	SDL_Rect destRect = {	_Position.x, 
							_Position.y,
							Width,  
							Height };
	return destRect;
}

SDL_Rect Boss::GetClips( int WhichClip )
{
	return Clips[ WhichClip ];
}

SDL_Rect Heads::GetClips( int WhichClip )
{
	return Clips[ WhichClip ];
}

Boss::Boss()
{
	Height = 300;
	Width = 150;

	BossLife = 400;
	BossDead = false;

	BossWidth = 0; 
	BossHeight = 120;

	HeadsComing = false;
	HeadAnimation = false;
	HeadTimer = 0;
	SizeHeads = 1;
	
	AnimPaceBoss = 0;
	State = 0;
	Frame = 0;

	for( int i = 0; i < 8; i++ )
	{
		Clips[ i ].x = i * Width;
		Clips[ i ].y = 0;
		Clips[ i ].h = Height;
		Clips[ i ].w = Width;
	}
}

Heads::Heads()
{
	Width = 54;
	Height = 54;

	HeadHeight = 30;
	HeadWidth = 30;

	Frame = 0;
	HowFar = 0.0f;
	HeadTimer = 0.0f;
	HowFarSpeed = 0.0f;

	state = 0;
	
	Clips[0].x = 1050;
	Clips[0].y = 0;
	Clips[0].h = 77;
	Clips[0].w = 55;

	Clips[1].x = 1125;
	Clips[1].y = 0;
	Clips[1].h = 74;
	Clips[1].w = 65;

	Clips[2].x = 1190;
	Clips[2].y = 0;
	Clips[2].h = 74;
	Clips[2].w = 75;

	Clips[3].x = 1060;
	Clips[3].y = 87;
	Clips[3].h = 50;
	Clips[3].w = 55;

	Clips[4].x = 1125;
	Clips[4].y = 85;
	Clips[4].h = 55;
	Clips[4].w = 60;

	Clips[5].x = 1195;
	Clips[5].y = 80;
	Clips[5].h = 54;
	Clips[5].w = 70;
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
				
				if( Collide == true && BCPlayer.IsInStateAttack() ) // && Attack == true
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

