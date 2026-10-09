/**
 * @file route_network.cpp
 * @brief Adjacency list + Dijkstra for the depot road network (Bonus).
 */

#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class RouteNetwork
{
private:
    struct Edge
    {
        int to;
        double km;
    };

    std::vector<std::vector<Edge>> adjacency;

    void check_node(int node) const
    {
        if (node < 0 || node >= static_cast<int>(adjacency.size()))
        {
            throw std::out_of_range("Ungueltiger Knoten: " + std::to_string(node));
        }
    }

public:
    explicit RouteNetwork(int node_count) : adjacency(node_count)
    {
    }

    /** @brief Adds an undirected road. */
    void add_road(int from, int to, double km)
    {
        check_node(from);
        check_node(to);
        adjacency[from].push_back({to, km});
        adjacency[to].push_back({from, km});
    }

    /**
     * @return Shortest distance from start to every node (infinity if unreachable)
     */
    std::vector<double> shortest_distances(int start) const
    {
        check_node(start);
        const double INF = std::numeric_limits<double>::infinity();
        std::vector<double> distance(adjacency.size(), INF);

        // (distance, node), smallest distance on top
        using Entry = std::pair<double, int>;
        std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> queue;

        distance[start] = 0.0;
        queue.push({0.0, start});

        while (!queue.empty())
        {
            auto [current_distance, node] = queue.top();
            queue.pop();

            if (current_distance > distance[node])
            {
                continue; // outdated entry, a shorter path was found already
            }

            for (const Edge& edge : adjacency[node])
            {
                double candidate = current_distance + edge.km;
                if (candidate < distance[edge.to])
                {
                    distance[edge.to] = candidate;
                    queue.push({candidate, edge.to});
                }
            }
        }
        return distance;
    }
};

int main()
{
    const std::vector<std::string> NAMES = {"Stuttgart", "Esslingen", "Ludwigsburg", "Goeppingen",
                                            "Heilbronn"};
    RouteNetwork network(static_cast<int>(NAMES.size()));
    network.add_road(0, 1, 15);
    network.add_road(0, 2, 20);
    network.add_road(1, 2, 30);
    network.add_road(1, 3, 30);
    network.add_road(2, 4, 35);
    network.add_road(3, 4, 80);
    network.add_road(1, 4, 70);

    std::vector<double> distances = network.shortest_distances(0);
    for (std::size_t node = 0; node < distances.size(); node++)
    {
        std::cout << NAMES[node] << ": " << distances[node] << " km\n";
    }
    return 0;
}
