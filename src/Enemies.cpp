#pragma once
#include "Enemies.h"
#include "Game.h"
#include <list>
#include "Timers.h"
#include "Objects.h"
#include "Collision.h"

// @date 2012-08-07

Control_Enemies Control_ENEMY;

CZombie::CZombie()
{
	CZombie::Speed = 100;
}

CSkeleton::CSkeleton()
{
	CSkeleton::Speed = 100;
}

CEnemy::CEnemy()
{
	CEnemy::Speed = 100;
	memset(ZombieClips, 0, sizeof(ZombieClips));
	memset(SkeletonClips, 0, sizeof(SkeletonClips));
}

void CEnemy::Set_Clips( int WhichTypeOfEnemy )
{

	// enemy type zombie
	if( WhichTypeOfEnemy == 0 )
	{
		for( int i = 0; i < 10; i++ )
		{
			ZombieClips[ i ].x = i * this->Width;
			ZombieClips[ i ].y = 0;
			ZombieClips[ i ].h = this->Height;
			ZombieClips[ i ].w = this->Width;
			Clips.push_back(ZombieClips[ i ]);
		}
	}
	// enemy type 1 Skelton
	else if( WhichTypeOfEnemy == 1 )
	{
		//Frame = 0;
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
		if( LeftOf_Demon )
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
		else if( RightOf_Demon )
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

		if( LeftOf_Demon )
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
		else if( RightOf_Demon )
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
		if( LeftOf_Demon )
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
		else if( RightOf_Demon )
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
	return timer.Timer_AttackBoss;
}

int Boss::GetState()
{
	return State;
}

void Boss::ResetAttackTimer()
{
	timer.Timer_AttackBoss = 0;
}

void Boss::UpdateAttackTimer()
{
	float Speed = 200.0f * ( gamestate.dt / 1000.0f );
	timer.Timer_AttackBoss += Speed;
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
	if( Frame >= 4 )
	{
		Frame = 0;
	}
	else
		Frame++;
}

void Boss::UpdateBoss()
{
	// updates boss, boss frame and checks collision against player
	float x = GetTimerAttack();
	if( x >= BOSS_ATTACK_START || HeadsComing == true )
	{
		bool CollideWithPlayer = false;
		CollideWithPlayer = CollisionController.CollisionCircle( &demon, gamestate.boss, false );
		if( CollideWithPlayer )
		{	
			bool CheckAttack = false;
			if( CheckAttack = demon.IsInStateAttack() )
			{
				demon.Score += 10;
				//gamestate.Score += 10;
				gamestate.boss->BossLife -= 50;

				if( demon.Triangle )
				{
					demon.TriangleState = 1;
				}

				if( gamestate.boss->BossLife < 0 )
				{
					gamestate.boss->BossDead = true;
				}
			}
			else
			{		
				if( demon.DieOneLife != true && timer.Timer_Hit > 3 && 
					demon.isImmortal == false )
				{
					timer.Timer_Hit = 0;
					demon.Right = true;
					demon.isHit = true;
					demon.Demon_Health -= 50;
				}
				timer.Timer_Hit++;
				
			}

		}
	
		HeadsComing = true;

		float BOSSpeed = 150.0f * ( gamestate.dt / 1000.0f );
		timer.Timer_BossAnim += BOSSpeed;

		float BOSSpeedHead = 70.0f * ( gamestate.dt / 1000.0f );
		timer.Timer_BossHead += BOSSpeedHead;

		ResetAttackTimer();

		SetState( BOSS_ATTACK );
		if( timer.Timer_BossAnim >= ANIMPACEBOSSHEAD )
		{
			UpdateFrame();
			timer.Timer_BossAnim = 0.0f;
		}

		if( timer.Timer_BossHead >= 20 )
		{
			if( HeadAnimation == true )
			{
				timer.Timer_BossHead = 0;
				int Length = rand() % ( gamestate.SCREEN_WIDTH - 100 ) + 50 ;
				if( Length < 50 )
				{
					Length = 50;
				}
				My_BossHead.push_back(	CreateBossHeads(	xPos, 
													yPos + 10, 
													Surface,
													Length ) );
				SizeHeads++;
			}

			
			if( GetFrame() >= 4 )
			{
				HeadAnimation = true;
				SetFrame( BOSS_IDLE );
			}
		}

		if( SizeHeads == 6 )
		{
			HeadsComing = false;
			SetFrame( BOSS_IDLE );
			SizeHeads = 1;
		}
	}
	else
	{
		SetFrame( BOSS_IDLE );
		UpdateAttackTimer();
	}
		//sanity check
	switch( GetState() )
	{
		case BOSS_IDLE:
			{
				SDL_BlitSurface( gamestate.GetSurface( Surface ), 
					&GetClips( GetFrame() ),
								gamestate.BackBuffer, &ReturnDestRect() );
			}
		case BOSS_ATTACK:
			{
				SDL_BlitSurface( gamestate.GetSurface( Surface ),
				&GetClips( GetFrame() ), 
				gamestate.BackBuffer, &ReturnDestRect() );
			}
		case BOSS_DIE:
			{
				SDL_BlitSurface( gamestate.GetSurface( Surface ),
				&GetClips( GetFrame() ), 
				gamestate.BackBuffer, &ReturnDestRect() );
			}
	}

	UpdateHeads();
	
}

// does all update on head, against the demon, checks frame, and lifelenght
void Boss::UpdateHeads()
{
	if( My_BossHead.size() != 0 )
	{

		float HeadSpeed = 20.0f * ( gamestate.dt / 1000.0f );
		float Crash = 50.0f * ( gamestate.dt / 1000.0f );
		float HowFarSpeed = 300.0f * ( gamestate.dt / 1000.0f );
		
		
		list< Heads* > vRemoveHead;
		list< Heads* >::iterator vRemoveIterHead;

		list< Heads* >::iterator i = My_BossHead.begin();
		for( ; i != My_BossHead.end(); ++i )
		{
			Heads * temp = (*i);
			bool Collide = false;
			Collide = CollisionController.CollisionCircle( &demon, temp, false );

			if( Collide )
			{	
				if( demon.IsInStateAttack() )
				{
					demon.Score += 5;
					//gamestate.Score += 5;
					vRemoveHead.push_back((*i));
				}
				else
				{
					if( demon.DieOneLife != true && timer.Timer_Hit > 3 && 
					demon.isImmortal == false )
					{
						timer.Timer_Hit = 0;
						demon.isHit = true;
						demon.Demon_Health -= 50;
					}
					timer.Timer_Hit++;
				}

			}

			if( temp->HowFar >= temp->length )
			{
				temp->state = HEAD_DOWN;

				if( temp->yPos > 500 )
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

					float speed = 200.0f * ( gamestate.dt / 1000 );
					temp->yPos += speed;
				}
			}
			else
			{
				float Speed = 250.0f * ( gamestate.dt / 1000 );
				temp->xPos -= Speed;
				temp->HowFar += HowFarSpeed;
			}

			SDL_Rect HeadDest = { temp->xPos, temp->yPos, temp->Width, temp->Height };
			
			SDL_BlitSurface(	gamestate.GetSurface( temp->Surface ), &temp->GetClips( temp->GetFrame() ),
								gamestate.BackBuffer, &HeadDest );
	
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
	temp->xPos = xPos;
	temp->yPos = yPos;
	temp->Surface = surface;
	temp->length = lengthOfTravel;

	temp->Radius = ( temp->HeadWidth > temp->HeadHeight ) ? temp->HeadWidth / 2 : temp->HeadHeight;

	return temp;
}

SDL_Rect Boss::ReturnDestRect()
{
	
	SDL_Rect destRect = {	xPos, 
							yPos,
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
		if( (*i)->xPos <= 200 )
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
	//float speed = 100.0f * ( gamestate.dt / 1000.0f );

	if( Enemies.size() != 0 )
	{
		list< CEnemy* >::iterator i = Enemies.begin();
		for( ; i != Enemies.end(); ++i )
		{
				// Check to see if collision occurs and if demon is in any kind of attack state
				CEnemy * enemy = (*i);

				// checks collision with player using circlecollision
				//Collide = CollisionController.CheckCollisionWithPlayer( enemy, 1 );
				Collide = CollisionController.CheckCollisionWithPlayer( (*i), 1);

				//Attack = demon.IsInStateAttack();
				
				if( Collide == true && demon.IsInStateAttack() ) // && Attack == true
				{
						if( (*i)->Surface == ZOMBIE )
						{
							//vRemoveEnemy.push_back( ( *i ) );
							if( Control_OBJ.PowerUpMan == false && demon.DemonHunter == false )
							{
								Control_OBJ.PowerUpMan = true;
								Control_OBJ.WereWolf = new PowerUp( (*i)->xPos, (*i)->yPos + 20, gamestate.m_srfDemonLife );
							}
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
					if( enemy->Surface == 8 )
					{
						timer.Timer_Hit++;
						demon.Demon_Health -= 50;
						if( demon.DieOneLife != true && timer.Timer_Hit > 3 && 
							demon.isImmortal == false )
						{
							timer.Timer_Hit = 0;
							demon.isHit = true;
						}
						enemy->Attack = true;

					}
					else
					{
						timer.Timer_Hit++;
						demon.Demon_Health -= 50;
							
						if( demon.DieOneLife != true && timer.Timer_Hit > 3 && 
							demon.isImmortal == false )
						{
							timer.Timer_Hit = 0;
							demon.isHit = true;
						}	
					}		
				}
				if( enemy->Frame == 18 || enemy->Frame == 46 )
				{
					(*i)->Attack = false;
					(*i)->Walk = true;
				}

				SDL_Rect EnemyDest = {	enemy->xPos, enemy->yPos, 
										gamestate.GetSurface( ZOMBIE )->w, 
										gamestate.GetSurface( ZOMBIE )->h }; 

				
				if(  (*i)->xPos < 0 )
				{
					//vRemoveEnemy.push_back( (*i) );
				}
				else
				{
					if( enemy->Surface == ZOMBIE )
					{
						if( Collide == false )
						{
							enemy->xPos -= 3;
						}
						
						SDL_BlitSurface(	gamestate.GetSurface( enemy->Surface ),&enemy->ZombieClips[0], 
											gamestate.BackBuffer, &EnemyDest );
					}
					else if( enemy->Surface == SKELETON )
					{
						if( gamestate.OK_PaceEnemy() )
						{
							if( enemy->Die == false )
							{
								if( Collide == false )
								{
									enemy->xPos -= enemy->Speed;
									/*
									if( enemy->LeftOf_Demon )
									{
										enemy->xPos += speed;
									}
									else
									{
										enemy->xPos -= speed;
									}
									*/
								}
							
/*
							SDL_BlitSurface(	gamestate.GetSurface( enemy->Surface ), &enemy->SkeletonClips[ 0 ][ enemy->Frame ],
												gamestate.BackBuffer, &EnemyDest );*/
							enemy->SetFrame();
							//enemy->PrevFrame = enemy->Frame;
							}
							else
							{
								if( demon.isMovingLeft && demon.xVelocity >= gamestate.SCREEN_WIDTH - 350 )
								{
									enemy->xPos += enemy->Speed;
								}
								else if( demon.isMovingRight )
								{
									enemy->xPos -= enemy->Speed;
								}

								SDL_BlitSurface(	gamestate.GetSurface( enemy->Surface ), &enemy->SkeletonClips[ 0 ][ enemy->Frame ],
												gamestate.BackBuffer, &EnemyDest );
								enemy->SetFrame();
								//enemy->PrevFrame = enemy->Frame;
							}
						}
						else
						{
							SDL_BlitSurface(	gamestate.GetSurface( enemy->Surface ), &enemy->SkeletonClips[ 0 ][ enemy->PrevFrame ],
												gamestate.BackBuffer, &EnemyDest );
						}
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
	
	temp->xPos = xPos;
	temp->yPos = yPos;

	temp->Height = 96;
	temp->Width = 96;
	temp->Walk = true;
	temp->Attack = false;
	temp->Die = false;
	temp->LeftOf_Demon = false; 
	temp->RightOf_Demon = false;

	temp->AttackFrameLeft = 9;
	temp->AttackFrameRight = 37;
	temp->DieFrameLeft = 18;
	temp->DieFrameRight = 46;
	temp->WalkFrameLeft = 0;
	temp->WalkFrameRight = 28;

	int Height, Width;
	Height = temp->Height / 2;
	Width = temp->Width / 2;


	if( temp->Surface == ZOMBIE )
	{
		temp->Radius = ( Width > Height ) ? Width / 2 - 10 : Height / 2 - 10 ;
		temp->Set_Clips( ENEMY_ZOMBIE );
	}
	else if( temp->Surface == SKELETON )
	{
		if( temp->xPos <= demon.xPos )
		{
			temp->LeftOf_Demon = true;
		}

		temp->RightOf_Demon = true;
		temp->Radius = ( Width > Height ) ? Width / 2 : Height / 2;
		temp->Set_Clips( ENEMY_SKELETON );
	}
	
	return temp;
}

void Control_Enemies::Create_Enemies()
{
	
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
}

Control_Enemies::Control_Enemies()
{
	Attack = false;
	Collide = false;
	CollideFire = false;

	//Zombie = 7;
	//Skeleton = 8;
}

