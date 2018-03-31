//
// Created by foebus on 31/03/18.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#pragma once
#include "Unit.h"

#define MAX_LEVEL_NUMBER 5

DECLARE_SMART(Player, spPlayer);
class Player: public Unit
{
public:
	void evolve(int choice, int level);
	void shoot(int monsterType);

protected:
	void _init() override;
	void _update(const UpdateState& us) override;

	int lifePoint = 100;
	int money = 100;
	int dna = 0;

	int monster[MAX_LEVEL_NUMBER];
};

#endif //PROJECT_PLAYER_H
