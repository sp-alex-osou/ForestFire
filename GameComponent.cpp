#include "GameComponent.h"
#include "Game.h"


GameComponent::GameComponent(Game& game) : game(game), window(game.getDisplayWindow())
{
}


GameComponent::~GameComponent()
{
}


void GameComponent::init()
{
}


void GameComponent::update(float elapsed)
{
}


void GameComponent::draw(float elapsed)
{
}