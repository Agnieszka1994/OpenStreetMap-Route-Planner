#include <optional>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <io2d.h>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;

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
		std::cin.ignore(WINT_MAX, '\n');
		// get input again		
		std::cin >> input;
	}
	return input;
}

template<typename T>
struct Coordinates {
	T start_x{0};
	T start_y{ 0 };
	T end_x{ 0 };
	T end_y{ 0 };
};

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

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
    is.seekg(0);
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    return std::move(contents);
}

int main(int argc, const char **argv)
{    
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map.osm";
    }
    
    std::vector<std::byte> osm_data;
 
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
/* Read user input */
	auto [start_x, start_y, end_x, end_y] = getCoordinatesFromInput<float>();

	/* Build our route model with osm_data */
	RouteModel model{ osm_data };

	/* Perform search using A* algorithm */
	RoutePlanner route_planner{ model, start_x, start_y, end_x, end_y };
	route_planner.a_star_search();
	std::cout << "Distance: " << route_planner.get_distance() << " meters." << std::endl;

    // Render results of search.
    Render render{model};

    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}


