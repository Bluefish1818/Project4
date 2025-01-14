#ifndef TOUR_GEN_H
#define TOUR_GEN_H

#include "base_classes.h"
class TourGenerator : public TourGeneratorBase
{
public:
	TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
	virtual ~TourGenerator();
	virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
};

#endif // !TOUR_GEN_H