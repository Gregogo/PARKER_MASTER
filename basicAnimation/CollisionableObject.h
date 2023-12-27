#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>
#include <string>
#include "init.h"

class CollisionableObject;
struct locationCollisionableObjects{
    std::vector <CollisionableObject> objects;
};

class CollisionableObject
{
public:
    CollisionableObject(bool isCar, int index, sf::Vector2f position, float angle, std::vector <sf::Vector2f> points, const std::string& texturePath, sf::Vector2f texturePoint1, sf::Vector2f texturePoint2, float scale);
    std::vector <sf::Vector2f> points;
    sf::ConvexShape body;
    sf::Texture texture;
    sf::Vector2f point1 = { 9999, 9999};
    sf::Vector2f point2 = { -9999, -9999};
    std::vector <sf::Vector2f> possiblePoints;
    std::vector <movingVector> vectorsOfMovement;
    sf::Vector2f position;
    std::vector <sf::Vector2f> originalPoints;
    float angle;
    int index;
    float scale;
private:
    void generatePossiblePoints(sf::Vector2f delta, float rotation);
    void generatePoints(sf::Vector2f delta, float rotation);
    sf::Vector2f texturePoint1;
    sf::Vector2f texturePoint2;
};