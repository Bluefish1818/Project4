#ifndef ROUTER_H
#define ROUTER_H

#include "base_classes.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <cmath>
#include "geotools.h"

class Router : public RouterBase {
public:
    Router(const GeoDatabaseBase& geoDb) : m_geoDb(geoDb) {}

    virtual std::vector<GeoPoint> route(const GeoPoint& start, const GeoPoint& end) const override {
        // Map from GeoPoint to its predecessor in the shortest path
        std::unordered_map<GeoPoint, GeoPoint, GeoPointHasher> predecessors;
        // Map from GeoPoint to its minimum distance from start
        std::unordered_map<GeoPoint, double, GeoPointHasher> distances;
        // Priority queue to hold the next GeoPoint to visit, sorted by distance
        auto cmp = [&distances](const GeoPoint& a, const GeoPoint& b) { return distances[a] > distances[b]; };
        std::priority_queue<GeoPoint, std::vector<GeoPoint>, decltype(cmp)> queue(cmp);

        // Initialization
        for (const auto& point : m_geoDb.getAllPoints()) { // Assuming this method exists
            distances[point] = std::numeric_limits<double>::infinity();
        }
        distances[start] = 0.0;
        queue.push(start);

        while (!queue.empty()) {
            GeoPoint current = queue.top();
            queue.pop();

            if (current == end) {
                break; // Found the shortest path to the destination
            }

            // Explore the neighbors of the current point
            for (const auto& neighbor : m_geoDb.get_connected_points(current)) {
                double alt = distances[current] + distance_earth_miles(current, neighbor);
                if (alt < distances[neighbor]) {
                    distances[neighbor] = alt;
                    predecessors[neighbor] = current;
                    queue.push(neighbor);
                }
            }
        }

        return reconstructPath(predecessors, start, end);
    }

private:
    const GeoDatabaseBase& m_geoDb;
    

    // do not use?
    double latitude;
    double longitude; 

    // not supposed to be here???
    bool operator!=(const GeoPoint& other) const {
        // Implement your comparison logic here
        // For example, compare x and y coordinates
        return (latitude != other.latitude) || (longitude != other.longitude);
    }

    struct GeoPointHasher {
        size_t operator()(const GeoPoint& p) const {
            return std::hash<std::string>()(p.to_string());
        }
    };

    std::vector<GeoPoint> reconstructPath(const std::unordered_map<GeoPoint, GeoPoint, GeoPointHasher>& predecessors,
        const GeoPoint& start, const GeoPoint& end) const {
        std::vector<GeoPoint> path;
        GeoPoint current = end;
        while (current != start) {
            path.push_back(current);
            current = predecessors.at(current);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
        return path;
    }

};

#endif // ROUTER_H





#if 0

#ifndef ROUTER_H
#define ROUTER_H
#include "base_classes.h"

class Router : public RouterBase
{
public:
    Router(const GeoDatabaseBase& geo_db);
    virtual ~Router();
    virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
};


#endif // !ROUTER_H

#endif // 0
