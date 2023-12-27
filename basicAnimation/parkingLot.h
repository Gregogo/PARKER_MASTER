#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>
#include <string>

class ParkingLot
{
public:
    ParkingLot(sf::Vector2f position, float angle, std::vector <sf::Vector2f> points);
    std::vector <sf::Vector2f> points;
    sf::ConvexShape body;
    sf::Vector2f point1 = { 9999, 9999};
    sf::Vector2f point2 = { -9999, -9999};
    std::vector <sf::Vector2f> possiblePoints;
    sf::Vector2f position;
    std::vector <sf::Vector2f> originalPoints;
    float angle;
private:
    void generatePossiblePoints(sf::Vector2f delta, float rotation);
    void generatePoints(sf::Vector2f delta, float rotation);
    sf::Vector2f texturePoint1;
    sf::Vector2f texturePoint2;
};