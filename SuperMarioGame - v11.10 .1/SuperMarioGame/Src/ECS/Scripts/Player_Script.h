#pragma once

#include "../Components.h"


class Player_Script : public Component //PlayerAnimator -> Animator -> Sprite -> Transform
{
public: // it is like it has init that creates Animator Component since it inherits it
	bool attackAnimation = false;

	bool vertTransitionPlayerAnimation = false;
	bool horTransitionPlayerAnimation = false;

	bool finishedVertAnimation = false;
	bool finishedHorAnimation = false;

	bool onPipe = false;
	bool leftofPipe = false;

	typedef enum {
		PLAYERACTION_IDLE = 0,
		PLAYERACTION_WALK = 1,
		PLAYERACTION_RUN = 2,
		PLAYERACTION_JUMP = 3,
		PLAYERACTION_ATTACK = 4
	} playerAction;

	playerAction action = playerAction::PLAYERACTION_IDLE;

	RigidBodyComponent* rigidbody;
	AnimatorComponent* animator;
	MovingAnimatorComponent* moving_animator;
	SpriteComponent* sprite;
	TransformComponent* transform;
	KeyboardControllerComponent* keyboard;
	Sword* sword;
	LivingCharacter* living;

	Player_Script()
	{

	}

	~Player_Script() {

	}

	void init() override {
		rigidbody = &entity->getComponent<RigidBodyComponent>();
		animator = &entity->getComponent<AnimatorComponent>();
		moving_animator = &entity->getComponent<MovingAnimatorComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		transform = &entity->getComponent<TransformComponent>();
		keyboard = &entity->getComponent<KeyboardControllerComponent>();
		sword = &entity->getComponent<Sword>();
		if (!entity->hasComponent<LivingCharacter>()) //todo: problem: having transform on top left grid, not every collider its own
		{
			entity->addComponent<LivingCharacter>();
		}
		living = &entity->getComponent<LivingCharacter>();
	}

	void update(float deltaTime) override {
		if (!attackAnimation) {
			if (Game::_inputManager.isKeyDown(keyboard->attackKey)) {
				animator->Play("P1Attack");
				this->attackAnimation = true;
				this->action = Player_Script::playerAction::PLAYERACTION_ATTACK;
			}
		}

		if (attackAnimation) {
			if (sprite->animation.hasFinished()) {
				this->attackAnimation = false;
				this->action = Player_Script::playerAction::PLAYERACTION_IDLE;
			}
		}

		if (!vertTransitionPlayerAnimation && !horTransitionPlayerAnimation) 
		{
			if (Game::_inputManager.isKeyDown(keyboard->walkRightKey))
			{
				if (this->leftofPipe)
				{
					sprite->transform->velocity.x = 0;
					moving_animator->Play("PlayerHorTransition");
					this->horTransitionPlayerAnimation = true;
					this->action = Player_Script::playerAction::PLAYERACTION_JUMP;
				}
			}
			if (Game::_inputManager.isKeyDown(keyboard->downKey))
			{
				if (this->onPipe)
				{
					sprite->transform->velocity.x = 0;
					moving_animator->Play("PlayerVertTransition");
					this->vertTransitionPlayerAnimation = true;
					this->action = Player_Script::playerAction::PLAYERACTION_JUMP;
				}
			}
		}
		if (vertTransitionPlayerAnimation || horTransitionPlayerAnimation) // transition on pipe
		{	
			if (sprite->moving_animation.hasFinished()) {
				if (vertTransitionPlayerAnimation) {
					finishedVertAnimation = true;
					vertTransitionPlayerAnimation = false;
				}
				else {
					finishedHorAnimation = true;
					horTransitionPlayerAnimation = false;
				}
			}
		}

		if (action == playerAction::PLAYERACTION_ATTACK) { //if playerAttackAnimation is on 3rd frame then deal damage i.e create entity from sword that deal damage.
			if (sprite->animation.cur_frame_index == 1 && sprite->animation.frame_times_played == 1)
			{
				std::cout << "attacking!" << std::endl;
				sword->attack();
			}
			return;
		}
		else if (!rigidbody->onGround)
		{
			if (action == playerAction::PLAYERACTION_JUMP)
				return;
			action = playerAction::PLAYERACTION_JUMP;
		}
		else if (rigidbody->onGround && transform->velocity.x == 0 && action != playerAction::PLAYERACTION_ATTACK)
		{
			if (action == playerAction::PLAYERACTION_IDLE)
				return;
			action = playerAction::PLAYERACTION_IDLE;
		}
		else if (rigidbody->onGround && transform->velocity.x != 0)
		{
			if (action == playerAction::PLAYERACTION_WALK)
				return;
			action = playerAction::PLAYERACTION_WALK;
		}

		switch (action)
		{
		case playerAction::PLAYERACTION_IDLE:
			animator->Play(keyboard->idleAnimation);
			break;
		case playerAction::PLAYERACTION_WALK:
			animator->Play(keyboard->walkAnimation);
			break;
		case playerAction::PLAYERACTION_RUN:
			animator->Play(keyboard->walkAnimation);
			break;
		case playerAction::PLAYERACTION_JUMP:
			animator->Play(keyboard->jumpAnimation);
			break;
		case playerAction::PLAYERACTION_ATTACK:
			animator->Play(keyboard->attackAnimation);
			break;
		default:
			break;
		}

		onPipe = false;
		leftofPipe = false;
	}

};