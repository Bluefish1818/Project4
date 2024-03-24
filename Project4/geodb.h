#ifndef GEOBD_H
#define GEOBD_H

#include "base_classes.h"
#include "hashmap.h"

class GeoDatabase : public GeoDatabaseBase
{
public:
	GeoDatabase();
	virtual ~GeoDatabase();
	virtual bool load(const std::string& map_data_file);
	virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;
	virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
	virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;

#if 0
private:
	HashMap<string>* m_map;
	string fileLine;
	unsigned int totalLines;
	unsigned int pointsOfInterest;
	
	const int streetSegLine = 0;
	const int geoPointLine = 1;
	const int pointsInterestLine = 2;

	string tempAddressString;
#endif

	// Additional private member in GeoDatabase class for storing street segments and POIs
private:

	// Helper structure to represent a street segment
	struct StreetSegment {
		std::string streetName;
		GeoPoint startPoint;
		GeoPoint endPoint;
		std::vector<std::string> pois;
	};

	std::unordered_map<std::string, std::vector<StreetSegment>> segmentsByStreet;
	std::unordered_map<std::string, GeoPoint> poiLocations;
	std::unordered_map<std::string, std::vector<std::string>> connectedStreets;


};

#endif // !GEOBD_H
