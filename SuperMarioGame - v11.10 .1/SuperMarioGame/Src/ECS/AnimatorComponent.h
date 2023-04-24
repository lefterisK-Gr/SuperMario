#pragma once

#include "Components.h"
#include <map>
#include "Animation.h"
#include "AnimatorManager.h"

class AnimatorComponent : public Component //Animator -> Sprite -> Transform
{
public:
	SpriteComponent* sprite;
	AnimatorManager animManager;
	std::string textureid;
	const char* animimationName = NULL;
	uint32_t resumeTime = 0; //this may need to be in animatorManager
	bool animated = false;
	bool didCoinAnimation = false;
	bool blockAnimation = false;
	bool didBlockAnimation = false;

	//std::map<const char*, Animation> animations; //Animator Manager

	AnimatorComponent()
	{

	}

	AnimatorComponent(std::string id, bool isAnimated, bool isBlockAnim)
	{
		textureid = id;
		animated = isAnimated;
		blockAnimation = isBlockAnim;
	}

	~AnimatorComponent()
	{

	}

	void init() override
	{
		if (!entity->hasComponent<SpriteComponent>())
		{
			entity->addComponent<SpriteComponent>(textureid);
		}
		sprite = &entity->getComponent<SpriteComponent>();

		Play("P1Idle");
		sprite->setTex(textureid);
	}

	void update() override
	{
		int timeslice = 0;

		if (animated)
		{
			sprite->srcRect.x = (sprite->animIndexX * sprite->transform->width) + (sprite->srcRect.w * static_cast<int>((SDL_GetTicks() / sprite->speed) % sprite->frames));
			sprite->srcRect.y = sprite->animIndexY * sprite->transform->height;
		}

		if (didCoinAnimation) //add finished coin animation so its not checked everytime
		{
			if (!sprite->initTime)
			{
				sprite->initTime = SDL_GetTicks();
			}
			sprite->destRect.x = static_cast<int>(sprite->transform->position.x) - Game::camera.x; //make player move with the camera, being stable in centre, except on edges
			if (Game::justResumed)//if we just resumed
			{
				resumeTime += SDL_GetTicks() - Game::pauseTime;
			}
			timeslice = static_cast<int>(((SDL_GetTicks() - resumeTime - sprite->initTime) / sprite->speed) % (sprite->frames + 3));
			sprite->destRect.y = (static_cast<int>(sprite->transform->position.y) - (20 * timeslice) - Game::camera.y);
			if (timeslice == 3)
			{
				sprite->destRect.y += 40;
			}
			else if (timeslice == 4)
			{
				sprite->destRect.y += 80;
			}
			else if (timeslice == 5) // on finish
			{
				sprite->DestroyTex();
			}
		}
		else if (blockAnimation && didBlockAnimation)
		{
			if (!sprite->initTime)
			{
				sprite->initTime = SDL_GetTicks();
			}
			sprite->destRect.x = static_cast<int>(sprite->transform->position.x) - Game::camera.x; //make player move with the camera, being stable in centre, except on edges
			if (Game::justResumed)//if we just resumed
			{
				resumeTime += SDL_GetTicks() - Game::pauseTime;
			}
			timeslice = static_cast<int>(((SDL_GetTicks() - resumeTime - sprite->initTime) / sprite->speed) % (sprite->frames + 4));
			sprite->destRect.y = (static_cast<int>(sprite->transform->position.y) - (8 * (timeslice + 1)) - Game::camera.y);

			if (timeslice == 2)
			{
				sprite->destRect.y += 16;
			}
			else if (timeslice == 3)// on finish
			{
				sprite->destRect.y += 32;
				sprite->initTime = 0;
				didBlockAnimation = false;
			}
		}
		else
		{
			sprite->destRect.x = static_cast<int>(sprite->transform->position.x) - Game::camera.x; //make player move with the camera, being stable in centre, except on edges
			sprite->destRect.y = static_cast<int>(sprite->transform->position.y) - Game::camera.y;

		}
		sprite->destRect.w = sprite->transform->width * sprite->transform->scale;
		sprite->destRect.h = sprite->transform->height * sprite->transform->scale;
	}

	void draw() override
	{
		//sprite->draw();
	}

	void Play(const char* animName)
	{
		animimationName = animName;
		sprite->SetFrames(animManager.animations[animName].indexX, animManager.animations[animName].indexY, animManager.animations[animName].frames, animManager.animations[animName].speed);
	}

	const char* getPlayName()
	{
		return animimationName;
	}

	void DestroyTex()
	{
		sprite->DestroyTex();
		didCoinAnimation = true;
	}

	bool getCoinAnimation()
	{
		return didCoinAnimation;
	}
};