#pragma once
template<typename T>
struct Coordinates {
	T start_x{0};
	T start_y{ 0 };
	T end_x{ 0 };
	T end_y{ 0 };
};

template<typename T>
T getInput()
{
	T input;
	std::cin >> input;
	// error check
	while (std::cin.good() == false) {
		// clear stream
		std::cout << "Wrong input type! Please try again.\n" << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		// get input again		
		std::cin >> input;
	}
	return input;
}

template<typename T>
Coordinates<T> getCoordinatesFromInput() {
	Coordinates<T> coords;
	std::cout << "Enter start x btw. 0 - 99: ";
	coords.start_x = getInput<T>();
	std::cout << "Enter start y btw. 0 - 99: ";
	coords.start_y = getInput<T>();
	std::cout << "Enter end x btw. 0 - 99: ";
	coords.end_x = getInput<T>();
	std::cout << "Enter end y btw. 0 - 99: ";
	coords.end_y = getInput<T>();

	return coords;
}
