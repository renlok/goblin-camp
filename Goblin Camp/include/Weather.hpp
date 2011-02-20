/* Copyright 2010-2011 Ilkka Halila
This file is part of Goblin Camp.

Goblin Camp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Goblin Camp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with Goblin Camp. If not, see <http://www.gnu.org/licenses/>.*/
#pragma once

#include "Coordinate.hpp"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/shared_ptr.hpp>

class Map;

enum WeatherType {
	NORMALWEATHER,
	RAIN
};

class Weather {
	friend class boost::serialization::access;
private:
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const;
	template<class Archive>
	void load(Archive & ar, const unsigned int version);
	BOOST_SERIALIZATION_SPLIT_MEMBER()

	Map* map;
	Direction windDirection;
	WeatherType currentWeather;

public:
	Weather(Map* map = 0);
	Direction GetWindDirection();
	void RandomizeWind();
	void ShiftWind();
	std::string GetWindAbbreviation();
	void Update();
	void ChangeWeather(WeatherType);
};

BOOST_CLASS_VERSION(Weather, 0)

template<class Archive>
void Weather::save(Archive & ar, const unsigned int version) const {
	ar & map;
	ar & windDirection;
	ar & currentWeather;
}

template<class Archive>
void Weather::load(Archive & ar, const unsigned int version) {
	ar & map;
	ar & windDirection;
	ar & currentWeather;
}