//
// Created by foebus on 31/03/18.
//

#include "Player.h"

void Player::evolve(int choice, int level) {
	monster[level] = choice;
}

void Player::shoot(int monsterType) {
	lifePoint -= monsterType;
}

void Player::_init() {
	Unit::_init();

	for (int &i : monster) {
		i = 0;
	}
}

void Player::_update(const UpdateState &us) {
}
