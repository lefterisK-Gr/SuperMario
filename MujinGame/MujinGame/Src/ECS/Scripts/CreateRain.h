#pragma once

#include "ECS/Components.h"

class CreateRainDrops : public Component
{
private:
	std::shared_ptr<PerspectiveCamera> main_camera2D = std::dynamic_pointer_cast<PerspectiveCamera>(CameraManager::getInstance().getCamera("main"));

	const int maxParticles = 50;
	float numOfParticles = 0;
	std::default_random_engine generator;  // Random number generator
	float dropRate = 0.2f;
	int radius = 0;
public:

	CreateRainDrops(int radius) :
		radius(radius)
	{
		generator.seed(std::random_device{}());
	}

	~CreateRainDrops() {

	}

	void init() override {

	}

	void update(float deltaTime) override {
		auto& textureraindrop(manager.getGroup(Manager::groupRainDrop));
		auto& players(manager.getGroup(Manager::groupPlayers));

		for (auto& pl : players) {
			TransformComponent* tr = &pl->GetComponent<TransformComponent>();
			std::uniform_real_distribution<float> distributionX(tr->getPosition().x - main_camera2D->getCameraDimensions().x, tr->getPosition().x + main_camera2D->getCameraDimensions().x);

			const unsigned short prevNumOfParticles = static_cast<unsigned short>(numOfParticles);

			if (numOfParticles + dropRate <= maxParticles) {
				numOfParticles += dropRate;
			}

			if (static_cast<unsigned short>(numOfParticles) > prevNumOfParticles && numOfParticles < maxParticles) {
				Entity* raindrop;
				raindrop = &manager.addEntity();

				float randX = distributionX(generator);  // Generate random X within camera width

				TransformComponent& tc = raindrop->addComponent<TransformComponent>(glm::vec2(randX, 0), Manager::foregroundLayer, glm::ivec2( 2, 20), 1);
				tc.setVelocity_X(-0.5);
				tc.setVelocity_Y(5);

				raindrop->addComponent<Rectangle_w_Color>(20);
				raindrop->GetComponent<Rectangle_w_Color>().color = Color(0, 255, 255, 255);
				raindrop->addGroup(Manager::groupRainDrop);
			}

			for (auto& tr : textureraindrop) {
				if (tr->GetComponent<TransformComponent>().getPosition().y > main_camera2D->getCameraDimensions().y) {
					tr->destroy();
					numOfParticles--;
				}
			}
		}
		
	}

	void draw(SpriteBatch& batch, MujinEngine::Window& window) override {
	}
};