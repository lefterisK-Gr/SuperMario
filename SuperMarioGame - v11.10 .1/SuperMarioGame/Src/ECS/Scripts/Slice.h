#pragma once

#include "../Components.h"

class Slice : public Component
{
public:
	SDL_Rect sliceRect;
	int sliceDamage;

	TransformComponent* transform;
	ColliderComponent* collider;

	Slice()
	{

	}

	Slice(SDL_Rect sliceHitbox, int damage)
	{
		sliceRect = sliceHitbox;
		sliceDamage = damage;
	}

	~Slice() {

	}

	void init() override {
		if (!entity->hasComponent<ColliderComponent>())
		{
			entity->addComponent<ColliderComponent>("slice", sliceRect);
		}
		transform = &entity->getComponent<TransformComponent>();
		collider = &entity->getComponent<ColliderComponent>();
	}

	void update(float deltaTime) override {

	}

};