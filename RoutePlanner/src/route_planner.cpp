#include "route_planner.h"
#include <algorithm>

namespace route_planner {

	RoutePlanner::RoutePlanner(RouteModel& model, float start_x
		, float start_y, float end_x, float end_y) : m_model(model)
	{
		/* Scale values to be between 0 and 1*/
		start_x *= 0.01;
		start_y *= 0.01;
		end_x *= 0.01;
		end_y *= 0.01;

		/* Find our closest start and end node for the coordinates */
		start_node = &m_model.find_closest_node(start_x, start_y);
		end_node = &m_model.find_closest_node(end_x, end_y);
	}

	void RoutePlanner::a_star_search()
	{

		start_node->visited = true;
		open_list.emplace_back(start_node);


		while (!open_list.empty())
		{
			/* Find best next node for exploration */
			RouteModel::Node* current_node = next_node();

			/* Check if we have reached our goal already */
			if (current_node->distance(*end_node) == 0)
			{
				m_model.path = construct_final_path(end_node);
				return;
			}

			/* Otherwise, add our current node to the neighbors */
			add_neighbors(current_node);
		}
	}

	void RoutePlanner::add_neighbors(RouteModel::Node* current_node)
	{
		/* Populate current node's neighbors vector */
		current_node->find_neighbors();

		/* Go through each neighbor, calc its attributes and then add it to the open list */
		for (auto neighbor : current_node->neighbors)
		{
			neighbor->parent = current_node;
			neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
			neighbor->h_value = calc_h_value(neighbor);

			open_list.emplace_back(neighbor);
			neighbor->visited = true;
		}
	}

	RouteModel::Node* RoutePlanner::next_node()
	{
		/* Sort our list of open nodes by their sum of h and g value */
		std::sort(open_list.begin(), open_list.end(), [](const auto& a, const auto& b)
			{
				return (a->h_value + a->g_value) < (b->h_value + b->g_value);
			});

		/* Get the node with lowest value and remove it from the list */
		RouteModel::Node* lowest_node = open_list.front();
		open_list.erase(open_list.begin());
		return lowest_node;
	}

	float RoutePlanner::calc_h_value(RouteModel::Node* node) const
	{
		return node->distance(*end_node);
	}

	std::vector<RouteModel::Node> RoutePlanner::construct_final_path(RouteModel::Node* current_node)
	{
		distance = 0.0f;
		std::vector<RouteModel::Node> path_found;

		/* Repeat as long as we are not at the starting point */
		while (current_node->parent != nullptr)
		{
			path_found.emplace_back(*current_node);
			const RouteModel::Node parent = *(current_node->parent);
			distance += current_node->distance(parent);
			current_node = current_node->parent;
		}

		/* Add start node and multiply with metric scale to convert to meters */
		path_found.emplace_back(*current_node);
		distance *= m_model.MetricScale();
		return path_found;
	}
}