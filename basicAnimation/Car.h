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
#include "MovingObject.h"
#include "ParkingLot.h"

class MovingObject;
struct locationMovingObjects;

class Car;
struct locationCars;

class Car {
public:
    Car(CollisionableObject &body, float lubricity, float weight);
    CollisionableObject& body;
    sf::Vector2f move(sf::Vector2f delta, float rotation, locationCollisionableObjects &objects, locationMovingObjects &movingObjects, locationCars &Cars, ParkingLot parkingLot);
    sf::Vector2f go(int coef, float deltaTime, locationCollisionableObjects &objects, locationMovingObjects &movingObjects, locationCars &Cars, float speed, ParkingLot parkingLot);
    sf::Vector2f moveSpeed;
    float weight;
    float lubricity;
    bool moved;
    void rotateWheelsStraight();
    void rotateWheelsRight();
    void rotateWheelsLeft();
    bool isDriving;
    int wheelDirection;
    int moveDirection;
    sf::Vector2f pivotPoint;
    float carSpeed;
    float rotateSpeed;
    bool won;
    bool lost;
private:
    bool isPointInParking(sf::Vector2f &point, ParkingLot &object);
    bool checkParkingOverlap(ParkingLot &parkingLot);
    void generatePossiblePointsInProcess (sf::Vector2f delta, float rotation);
    void generatePointsInProcess (sf::Vector2f delta, float rotation);
    bool isPointInFigure(sf::Vector2f &point, CollisionableObject &object);
    bool isPointInPossibleFigure(sf::Vector2f &point, CollisionableObject &object);
    bool checkOverlap(CollisionableObject &obj);
};
