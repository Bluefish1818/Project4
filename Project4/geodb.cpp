#if 1
#include "geodb.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>

bool GeoDatabase::load(const std::string& map_data_file) {
    std::ifstream file(map_data_file);
    if (!file) {
        std::cerr << "Failed to open file: " << map_data_file << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string streetName;
        std::getline(iss, streetName, '|');

        StreetSegment segment;
        segment.streetName = streetName;

        std::string lat1, lon1, lat2, lon2;
        std::getline(iss, lat1, ' ');
        std::getline(iss, lon1, ' ');
        std::getline(iss, lat2, ' ');
        std::getline(iss, lon2, '|');
        segment.startPoint = GeoPoint(lat1, lon1);
        segment.endPoint = GeoPoint(lat2, lon2);

        std::string poi;
        while (std::getline(iss, poi, '|')) {
            segment.pois.push_back(poi);
            // Assuming the POI format is "POI Name,Lat,Lon"
            auto delimiterPos = poi.find_last_of(',');
            std::string poiName = poi.substr(0, delimiterPos);
            std::string poiLocation = poi.substr(delimiterPos + 1);
            // Split poiLocation into lat and lon
            delimiterPos = poiLocation.find(',');
            std::string poiLat = poiLocation.substr(0, delimiterPos);
            std::string poiLon = poiLocation.substr(delimiterPos + 1);
            poiLocations[poiName] = GeoPoint(poiLat, poiLon);
        }

        segmentsByStreet[streetName].push_back(segment);
    }

    return true;
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {
    auto it = poiLocations.find(poi);
    if (it != poiLocations.end()) {
        point = it->second;
        return true;
    }
    return false;
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
    std::vector<GeoPoint> connectedPoints;
    // Assuming we have a method to find connected points based on the loaded data
    // This will depend on the internal data structures and how they're indexed
    return connectedPoints;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
    // Assuming we have a method to find the street name given two GeoPoints
    // This will depend on how segments are stored and indexed
    return "";
}

#endif


#if 0
#include "geodb.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <list>
#include <stack>

using namespace std;

GeoDatabase::GeoDatabase()
	:totalLines(0),fileLine(""),m_map(nullptr),tempAddressString("")
{

}

GeoDatabase::~GeoDatabase()
{

}

bool GeoDatabase::load(const std::string& map_data_file)
{
	ifstream inputFile(map_data_file);
	if (!inputFile)
	{
		cerr << "Failed to open " << map_data_file << "!\n";
		return false;
	}

	while(getline(inputFile, fileLine))
	{
		istringstream test_stream(fileLine);
		int countType = totalLines % 3;
		if (countType == streetSegLine)
		{
			tempAddressString = fileLine;
			// set the street address between two points 
		}
		else if (countType == geoPointLine)
		{
			string latitude;
			string longitude;
			test_stream >> latitude;
			test_stream >> longitude;
			new GeoPoint(latitude, longitude);
		}
		else if (countType == pointsInterestLine)
		{
			test_stream >> pointsOfInterest;
			if (fileLine != "0")
			{
				return false;
			}
			else
			{
				return true;
			}

		}
	}
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const
{

}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const
{

}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const
{

}

#endif