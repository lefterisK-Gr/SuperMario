#include "Collision.h"
#include "ECS\ColliderComponent.h"

#define TILE_OFFSET 33
#define TILE_OFFSET_2 25
#define GRID_OFFSET 9

int Collision::countCollisions;
Vector2D Collision::storedCollider;
bool Collision::hittedTopLeft;
bool Collision::hittedTopRight;

bool Collision::checkCollision(const SDL_Rect& moving_recA, const SDL_Rect& recB) {
	Collision::storedColliderRect = recB;

	if (moving_recA.x > recB.x + recB.w || moving_recA.x + moving_recA.w < recB.x ||
		moving_recA.y > recB.y + recB.h || moving_recA.y + moving_recA.h < recB.y) {
		return false; // no collision
	}

	//calculate distX,distY
	Collision::dist.x = recB.x - (moving_recA.x + (moving_recA.w / 2)); //positive if collider on right, negative if collider on left of center
	Collision::dist.y = recB.y - (moving_recA.y + (moving_recA.h / 2));
	//check if it is sideways collision (bool isSidewaysCollision)
	if (abs(dist.x) / moving_recA.w > abs(dist.y) / moving_recA.h) {
		Collision::isSidewaysCollision = true;
	}

	Collision::isCollision = true;
	return true;
}

void Collision::moveFromCollision(Entity& player) {
	auto& playerPos = player.getComponent<TransformComponent>().position;
	auto playerCollider = player.getComponent<ColliderComponent>().collider;

	if (Collision::isSidewaysCollision) { //horizontal move
		if (Collision::dist.x > 0) { //move moving_rect left from collider
			playerPos.x = storedColliderRect.x - playerCollider.w;
		}
		else {
			playerPos.x = storedColliderRect.x + storedColliderRect.w;
		}
	}
	else {
		if (Collision::dist.y > 0) { //move moving_rect down from collider
			playerPos.y = storedColliderRect.y + storedColliderRect.h;
		}
		else {
			playerPos.y = storedColliderRect.y - playerCollider.h;
		}
	}
}


//TODO: cleanup class to be more general to cover the cases
bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) //A for terrain B for player
{
	if ( //top left
		recA.x + recA.w > recB.x &&
		recB.x			>= recA.x &&
		recA.y + recA.h > recB.y &&
		recB.y			>= recA.y
		)
	{
		Collision::countCollisions += CollisionDirections::COL_TOP_LEFT;
		if (Collision::countCollisions == 1)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 3)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 5)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 7)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 9)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 11)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 13)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if(Collision::countCollisions == 15)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		Collision::hittedTopLeft = true;
		return true;
	}
	else if ( //top right
		recA.x + recA.w > recB.x + recB.w	&&
		recB.x + recB.w >= recA.x			&&
		recA.y + recA.h > recB.y			&&
		recB.y			>= recA.y
		)
	{
		Collision::countCollisions += CollisionDirections::COL_TOP_RIGHT;
		if (Collision::countCollisions == 2)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 3)
		{
			//Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 6)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 7)
		{
			//Collision::storedCollider.x = recA.x;
			//Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 10)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 11)
		{
			//Collision::storedCollider.x = recA.x;
			//Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 14)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 15)
		{
			//Collision::storedCollider.x = recA.x;
			//Collision::storedCollider.y = recA.y;
		}
		Collision::hittedTopRight = true;
		return true;
	}
	else if ( //down left
		recA.x + recA.w > recB.x			&&
		recB.x			>= recA.x			&&
		recA.y + recA.h > recB.y + recB.h	&&
		recB.y + recB.h >= recA.y
		)
	{
		Collision::countCollisions += CollisionDirections::COL_DOWN_LEFT;
		if (Collision::countCollisions == 4)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 5)
		{
			//Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 6)
		{
			//Collision::storedCollider.x = recA.x;
		}
		else if (Collision::countCollisions == 7)
		{
			//Collision::storedCollider.x = recA.x;
			//Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 12)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 13)
		{
		//Collision::storedCollider.x = recA.x;
		//Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 14)
		{
			//Collision::storedCollider.x = recA.x;
			//Collision::storedCollider.y = recA.y;
		}
		else if (Collision::countCollisions == 15)
		{
			//Collision::storedCollider.x = recA.x;
			//Collision::storedCollider.y = recA.y;
		}
		return true;
	}
	else if ( //down right
		recA.x + recA.w > recB.x + recB.w	&&
		recB.x + recB.w >= recA.x			&&
		recA.y + recA.h > recB.y + recB.h	&&
		recB.y + recB.h >= recA.y
		)
	{
		Collision::countCollisions += CollisionDirections::COL_DOWN_RIGHT;
		if (Collision::countCollisions == 8)
		{
			Collision::storedCollider.x = recA.x;
			Collision::storedCollider.y = recA.y;
		}
		return true;
	}
	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	return AABB(colA.collider, colB.collider);
}

void Collision::checkCollision(Vector2D &playerVel, Vector2D &playerPos, bool &rigidBodyOnGround , bool colHasCollAbove)
{
	switch (Collision::countCollisions) //weird for 1,2,4,8 when going toward the block and suddenly release
	{
	case 1:
		if ((playerVel.x < 0 && playerVel.y > 0) || (playerVel.x < 0 && playerVel.y == 0) || (playerVel.x < 0 && playerVel.y < 0))
		{
			playerPos.x = Collision::storedCollider.x + TILE_OFFSET;
		}
		else if ((playerVel.x > 0 && playerVel.y < 0) || (playerVel.y < 0))
		{
			playerPos.y = Collision::storedCollider.y + TILE_OFFSET;
		}
		break;
	case 2:
		if ((playerVel.x > 0 && playerVel.y < 0) || (playerVel.x > 0 && playerVel.y > 0) || (playerVel.x > 0 && playerVel.y == 0))
		{
			playerPos.x = Collision::storedCollider.x - TILE_OFFSET;
		}
		else if ((playerVel.x < 0 && playerVel.y < 0) || (playerVel.y < 0))
		{
			playerPos.y = Collision::storedCollider.y + TILE_OFFSET;
		}
		break;
	case 3:
		playerPos.y = Collision::storedCollider.y + TILE_OFFSET;
		break;
	case 4:
		if ((playerVel.x < 0 && playerVel.y < 0) || (playerVel.x < 0 && playerVel.y == 0))
		{
			playerPos.x = Collision::storedCollider.x + GRID_OFFSET;
		}
		else if ((playerVel.x > 0 && playerVel.y > 0) || (playerVel.y > 0) || (playerVel.x < 0 && playerVel.y > 0 && ((playerPos.y + 63) < Collision::storedCollider.y)))
		{
			if (colHasCollAbove)
			{
				playerPos.y = Collision::storedCollider.y - TILE_OFFSET - 8;
			}
			else
			{
				playerPos.y = Collision::storedCollider.y - TILE_OFFSET;
			}
			rigidBodyOnGround = true;
		}
		break;
	case 5:
		playerPos.x = Collision::storedCollider.x;
		break;
	case 6:
		if (playerVel.x > 0 && playerVel.y > 0)
		{
			playerPos.x = Collision::storedCollider.x - TILE_OFFSET;
			playerPos.y = Collision::storedCollider.y;
			rigidBodyOnGround = true;
		}
		else if (playerVel.x < 0 && playerVel.y < 0)
		{
			playerPos.x = Collision::storedCollider.x;
			playerPos.y = Collision::storedCollider.y + TILE_OFFSET;
		}
		break;
	case 7:
		playerPos.x = Collision::storedCollider.x + TILE_OFFSET;
		playerPos.y = Collision::storedCollider.y + TILE_OFFSET;
		break;
	case 8:
		if ((playerVel.x > 0 && playerVel.y < 0) || (playerVel.x > 0 && playerVel.y == 0))
		{
			playerPos.x = Collision::storedCollider.x - TILE_OFFSET;
		}
		else if ((playerVel.x > 0 && playerVel.y > 0 && (playerPos.y + 63) < Collision::storedCollider.y) || (playerVel.x < 0 && playerVel.y > 0) || (playerVel.y > 0))
		{
			if (colHasCollAbove)
			{
				playerPos.y = Collision::storedCollider.y - TILE_OFFSET - 8;
			}
			else
				playerPos.y = Collision::storedCollider.y - TILE_OFFSET;
			rigidBodyOnGround = true;
		}
		break;
	case 9:
		if (playerVel.x > 0 && playerVel.y < 0)
		{
			playerPos.x = Collision::storedCollider.x;
			playerPos.y = Collision::storedCollider.y + TILE_OFFSET;
		}
		else if (playerVel.x < 0 && playerVel.y > 0)
		{
			playerPos.x = Collision::storedCollider.x + TILE_OFFSET;
			playerPos.y = Collision::storedCollider.y;
			rigidBodyOnGround = true;
		}
		break;
	case 10:
		playerPos.x = Collision::storedCollider.x - TILE_OFFSET + 8;
		break;
	case 11:
		playerPos.x = Collision::storedCollider.x;
		playerPos.y = Collision::storedCollider.y + TILE_OFFSET;
		break;
	case 12:
		if (colHasCollAbove)
		{
			playerPos.y = Collision::storedCollider.y - TILE_OFFSET - 8;
		}
		else
			playerPos.y = Collision::storedCollider.y - TILE_OFFSET;
		rigidBodyOnGround = true;
		break;
	case 13:
		playerPos.x = Collision::storedCollider.x;
		if (colHasCollAbove)
		{
			playerPos.y = Collision::storedCollider.y - 16;
		}
		else
			playerPos.y = Collision::storedCollider.y - 8;
		rigidBodyOnGround = true;
		break;
	case 14:
		playerPos.x = Collision::storedCollider.x - TILE_OFFSET_2;
		if (colHasCollAbove)
		{
			playerPos.y = Collision::storedCollider.y - 16;
		}
		else
			playerPos.y = Collision::storedCollider.y - 8;
		rigidBodyOnGround = true;
		break;
	case 15:
		playerPos.x = Collision::storedCollider.x;
		playerPos.y = Collision::storedCollider.y;
		rigidBodyOnGround = true;
		break;
	default:
		break;
	}
}