#pragma once

#include "../AnimatorComponent.h"


class PlatformBlock_AnimatorComponent : public AnimatorComponent //PlayerAnimator -> Animator -> Sprite -> Transform
{
public: // it is like it has init that creates Animator Component since it inherits it
	bool didBlockAnimation = false;

	PlatformBlock_AnimatorComponent()
	{

	}

	PlatformBlock_AnimatorComponent(std::string texID)
		: AnimatorComponent(texID)
	{

	}

	~PlatformBlock_AnimatorComponent() {

	}

	void update() override {

		int timeslice = 0;

		sprite->srcRect.x = (sprite->animIndexX * sprite->transform->width) + (sprite->srcRect.w * static_cast<int>((SDL_GetTicks() / sprite->speed) % sprite->frames));
		sprite->srcRect.y = sprite->animIndexY * sprite->transform->height;

		if (didBlockAnimation)
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

};