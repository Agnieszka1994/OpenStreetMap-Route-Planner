#pragma once

#include <vector>
#include "route_model.h"

namespace route_planner {

	class RoutePlanner
	{

	public:

		RoutePlanner(RouteModel& model, float
			, float start_y, float end_x, float end_y);
		float get_distance() const { return distance; }
		void a_star_search();

	private:

		void add_neighbors(RouteModel::Node* current_node);
		RouteModel::Node* next_node();
		float calc_h_value(RouteModel::Node* node) const;
		std::vector<RouteModel::Node> construct_final_path(RouteModel::Node* current_node);

		std::vector<RouteModel::Node*> open_list;
		RouteModel& m_model;
		RouteModel::Node* start_node{};
		RouteModel::Node* end_node{};
		float distance{};
	};
}