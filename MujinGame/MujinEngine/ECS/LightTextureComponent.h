#pragma once

#include "ECS/ECS.h"
#include "Components.h"

class LightTextureComponent : public Component {
public:
    float radius = 100.0f;

    TransformComponent* transform = nullptr;
    SpriteComponent* sprite;

    LightTextureComponent(float zIndex)
    {
    }

    ~LightTextureComponent() {

    }

    void init() override {
        if (!entity->hasComponent<SpriteComponent>()) //todo: problem: having transform on top left grid, not every collider its own
        {
            entity->addComponent<SpriteComponent>();
        }
        transform = &entity->GetComponent<TransformComponent>();
        sprite = &entity->GetComponent<SpriteComponent>();

        sprite->destRect.w = radius;
        sprite->destRect.h = radius;
    }

    void update(float deltaTime) override {
        if (sprite->color == Color{ 255,255,255,255 }) {
            std::cout << "holdup";
        }
    }

    void draw(SpriteBatch& batch) override
    {
        float tempScreenScale = Game::_window->getScale();
        glm::vec4 pos((float)sprite->destRect.x * tempScreenScale, (float)sprite->destRect.y * tempScreenScale,
            (float)sprite->destRect.w * tempScreenScale, (float)sprite->destRect.h * tempScreenScale);
        batch.draw(pos, glm::vec4(-1.0f, -1.0f, 2.0f, 2.0f), 0, 0.0f, sprite->color);
    }
};