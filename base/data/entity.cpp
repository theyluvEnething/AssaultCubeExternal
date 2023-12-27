#include "entity.h"
#include <iostream>
#include <iomanip>


void entity::print() {
	std::cout << "\n====== PRINTING ENTITY ======" << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Health: " << health << " | Ammo: " << ammo << std::endl;
	std::cout << std::fixed << std::setprecision(2);
	for (int i = 0; i < 16; i++) {
		if ((i+1) % 4 == 0) std::cout << view_matrix[i] << std::endl;
		else std::cout << view_matrix[i] << ", ";
	}
	std::cout << "=============================\n" << std::endl;
}

void entity::print_angles() {
	std::cout << std::fixed << std::setprecision(2);
	for (int i = 0; i < 16; i++) {
		if (i == 15) {
			std::cout << view_matrix[i] << std::endl;
			break;
		}
		std::cout << view_matrix[i] << ", ";
	}
	return;
}