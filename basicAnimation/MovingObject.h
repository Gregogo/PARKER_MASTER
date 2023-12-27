#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>
#include <string>
#include "SFML/System/Vector2.hpp"
#include "CollisionableObject.h"
#include "Car.h"
#include "ParkingLot.h"

class MovingObject;
struct locationMovingObjects{
    std::vector <MovingObject*> objects;
};

class Car;
struct locationCars{
    std::vector <Car*> cars;
};

class MovingObject {
public:
    MovingObject(CollisionableObject &body, float lubricity, float weight);
    CollisionableObject& body;
    sf::Vector2f move(sf::Vector2f delta, float rotation, locationCollisionableObjects &objects, locationMovingObjects &movingObjects, locationCars &Cars, ParkingLot parkingLot);
    sf::Vector2f moveSpeed;
    float weight;
    float lubricity;
    bool moved;
private:
    void generatePossiblePointsInProcess (sf::Vector2f delta, float rotation);
    void generatePointsInProcess (sf::Vector2f delta, float rotation);
    bool isPointInFigure(sf::Vector2f &point, CollisionableObject &object);
    bool isPointInPossibleFigure(sf::Vector2f &point, CollisionableObject &object);
    bool checkOverlap(CollisionableObject &obj);
};
