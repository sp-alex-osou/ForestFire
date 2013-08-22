#pragma once

#include "GameComponent.h"

class Forest : public GameComponent
{
public:
	Forest(Game& game, int size, float fireChance, float treeChance);

	void update(float elapsed);
	void draw(float elapsed);
private:
	float fireChance;
	float treeChance;

	int currentCells;
	int size;
	std::vector<byte> cells[2];

	void set(int row, int col, int value);
	int get(int row, int col) const;
	int getIndex(int row, int col) const;
	int getOffset(int row, int col) const;
	bool isValid(int row, int col) const;
	bool neighborFire(int row, int col) const;
	float rand() const;

	static const int EMPTY = 0;
	static const int TREE = 1;
	static const int FIRE = 2;
	
	static const int SPEED = 60;

	static const byte MASK = 3;

	typedef unsigned char byte;
};

