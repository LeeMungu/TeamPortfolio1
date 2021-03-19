#include "pch.h"
#include "Enemy.h"
#include "Item.h"
#include "Animation.h"

Enemy::Enemy()
	:GameObject()
{
}

Enemy::Enemy(float x, float y)
{
	mX = x;
	mY = y;
}


void Enemy::Knockback()
{
	if (mIsKnockback == true)
	{
		mX += cosf(mAngle) * mKnockbackDistance * Time::GetInstance()->DeltaTime();
		mY -= sinf(mAngle) * mKnockbackDistance * Time::GetInstance()->DeltaTime();
		mKnockbackDistance -= 1500.f * Time::GetInstance()->DeltaTime();
		if (mKnockbackDistance <= 0.f)
		{
			mIsKnockback = false;
		}
	}
}

void Enemy::ExecuteKnockback(float angle, float force)
{
	mIsKnockback = true;
	mAngle = angle;
	mKnockbackDistance = force;
}

void Enemy::SetAnimation()
{
	if( mDirection == Direction::Left)
	{
		if (mEnemyState == EnemyState::Idle)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftIdle;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Move)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftMove;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Attack)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftAttack;
			mCurrentAnimation->Play();
		}
	}
	if (mDirection == Direction::Right)
	{
		if (mEnemyState == EnemyState::Idle)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightIdle;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Move)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightMove;
			mCurrentAnimation->Play();
		}
		if (mEnemyState == EnemyState::Attack)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightAttack;
			mCurrentAnimation->Play();
		}
	}
}

//void Enemy::DropItem(Item item)
//{
//}