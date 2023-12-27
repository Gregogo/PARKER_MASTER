#include "MovingObject.h"
#include "Car.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>
#include <string>
#include "CollisionableObject.h"
#include "ParkingLot.h"

MovingObject::MovingObject(CollisionableObject &body, float lubricity, float weight)
: body(body)
{
    moveSpeed = {0, 0};
    this->lubricity = lubricity;
    this->weight = weight;
    this->moved = false;
}

void MovingObject::generatePossiblePointsInProcess (sf::Vector2f delta, float rotation) {
    body.possiblePoints.clear();
    for(int i = 0; i <= body.points.size() - 1; i++) {
        body.possiblePoints.emplace_back((body.originalPoints[i].x) * cos(rotation + body.angle * M_PI / 180) - (body.originalPoints[i].y) * sin(rotation + body.angle * M_PI / 180) + delta.x + body.position.x, (body.originalPoints[i].x) * sin(rotation + body.angle * M_PI / 180) + (body.originalPoints[i].y) * cos(rotation + body.angle * M_PI / 180) + delta.y + body.position.y);
    }
}
void MovingObject::generatePointsInProcess (sf::Vector2f delta, float rotation) {
    for(int i = 0; i <= body.points.size() - 1; i++) {
        body.points[i] = (sf::Vector2f ((body.originalPoints[i].x) * cos(rotation + body.angle * M_PI / 180) - (body.originalPoints[i].y) * sin(rotation + body.angle * M_PI / 180) + delta.x + body.position.x, (body.originalPoints[i].x) * sin(rotation + body.angle * M_PI / 180) + (body.originalPoints[i].y) * cos(rotation + body.angle * M_PI / 180) + delta.y + body.position.y));
    }
}

//void MovingObject::generatePossiblePointsInProcess (sf::Vector2f delta, float rotation) {
//    body.possiblePoints.clear();
//    for(int i = 0; i <= body.points.size() - 1; i++) {
//        body.possiblePoints.emplace_back((body.points[i].x - body.position.x) * cos(rotation) - (body.points[i].y - body.position.y) * sin(rotation) + delta.x + body.position.x, (body.points[i].x  - body.position.x) * sin(rotation) + (body.points[i].y - body.position.y) * cos(rotation) + delta.y + body.position.y);
//    }
//}
//void MovingObject::generatePointsInProcess (sf::Vector2f delta, float rotation) {
//    for(int i = 0; i <= body.points.size() - 1; i++) {
//        body.points[i] = (sf::Vector2f ((body.points[i].x - body.position.x) * cos(rotation) - (body.points[i].y - body.position.y) * sin(rotation) + delta.x + body.position.x, (body.points[i].x  - body.position.x) * sin(rotation) + (body.points[i].y - body.position.y) * cos(rotation) + delta.y + body.position.y));
//    }
//}

bool MovingObject::isPointInFigure(sf::Vector2f &point, CollisionableObject &object) {
    std::vector <float> k;
    std::vector <float> b;
    std::vector <bool> isAbove;
    for(int i = 0; i < object.points.size(); i++) {
        if ( i == object.points.size() - 1) {
            k.push_back((object.points[i].y - object.points[0].y) / (object.points[i].x - object.points[0].x));
            b.push_back(object.points[0].y + - k[i] * object.points[0].x);
            if (object.points[0].x > object.points[i].x) {
                isAbove.push_back(true);
            }
            else {
                isAbove.push_back(false);
            }
        } else {
            k.push_back((object.points[i].y - object.points[i + 1].y) / (object.points[i].x - object.points[i + 1].x));
            b.push_back(object.points[i + 1].y - k[i] * object.points[i + 1].x);
            if (object.points[i+1].x > object.points[i].x) {
                isAbove.push_back(true);
            }
            else {
                isAbove.push_back(false);
            }
        }
    }
    int inFigure = 0;
    for(int i = 0; i < object.points.size(); i++) {
        if ((((k[i] * point.x + b[i]) > point.y) && !isAbove[i]) || (((k[i] * point.x + b[i]) < point.y) && isAbove[i])) {
            inFigure++;
        }
    }
    return inFigure == object.points.size();
};

bool MovingObject::isPointInPossibleFigure(sf::Vector2f &point, CollisionableObject &object) {
    std::vector <float> k;
    std::vector <float> b;
    std::vector <bool> isAbove;
    for(int i = 0; i < object.possiblePoints.size(); i++) {
        if ( i == object.possiblePoints.size() - 1) {
            k.push_back((object.possiblePoints[i].y - object.possiblePoints[0].y) / (object.possiblePoints[i].x - object.possiblePoints[0].x));
            b.push_back(object.possiblePoints[0].y + - k[i] * object.possiblePoints[0].x);
            if (object.possiblePoints[0].x > object.possiblePoints[i].x) {
                isAbove.push_back(true);
            }
            else {
                isAbove.push_back(false);
            }
        } else {
            k.push_back((object.possiblePoints[i].y - object.possiblePoints[i + 1].y) / (object.possiblePoints[i].x - object.possiblePoints[i + 1].x));
            b.push_back(object.possiblePoints[i + 1].y - k[i] * object.possiblePoints[i + 1].x);
            if (object.possiblePoints[i+1].x > object.possiblePoints[i].x) {
                isAbove.push_back(true);
            }
            else {
                isAbove.push_back(false);
            }
        }
    }
    int inFigure = 0;
    for(int i = 0; i < object.possiblePoints.size(); i++) {
        if ((((k[i] * point.x + b[i]) > point.y) && !isAbove[i]) || (((k[i] * point.x + b[i]) < point.y) && isAbove[i])) {
            inFigure++;
        }
    }
    return inFigure == object.possiblePoints.size();
};

bool MovingObject::checkOverlap(CollisionableObject &obj) {
    if (body.point2.x < obj.point1.x || body.point2.y < body.point1.y || body.point1.x > obj.point2.x || obj.point1.y > obj.point2.y) {
        return false;
    }
    bool overlap = false;
    for (auto point : obj.points) {
        if (isPointInPossibleFigure(point, this->body)) {
            overlap = true;
        }
    }
    for (auto point : this->body.possiblePoints) {
        if (isPointInFigure(point, obj)) {
            overlap = true;
        }
    }
    return overlap;
};

sf::Vector2f MovingObject::move(sf::Vector2f delta, float rotation, locationCollisionableObjects &objects, locationMovingObjects &movingObjects, locationCars &Cars, ParkingLot parkingLot) {
    generatePossiblePointsInProcess(delta, rotation * M_PI / 180);
    for (auto object : objects.objects)
    {
        if (body.index != object.index && checkOverlap(object)) {
            for (auto obj : movingObjects.objects) {
                if (obj->body.index == object.index) {
                    sf::Vector2f commonSpeed = {
                            (delta.x * this->weight + obj->moveSpeed.x * obj->weight) / (this->weight + obj->weight),
                            (delta.y * this->weight + obj->moveSpeed.y * obj->weight) / (this->weight + obj->weight),
                    };
                    sf::Vector2f howMoved = obj->move( commonSpeed, 0, objects, movingObjects, Cars, parkingLot);
                    if (howMoved != sf::Vector2f(0, 0)) {
                        sf::Vector2f howMovedAgain = this->move( howMoved, rotation, objects, movingObjects, Cars, parkingLot);
                        if (howMovedAgain != sf::Vector2f(0, 0)) {
                            moveSpeed = sf::Vector2f(howMovedAgain.x, howMovedAgain.y);
                            moveSpeed.x = moveSpeed.x < 0 ? moveSpeed.x + (0.01 / lubricity) : moveSpeed.x - (0.01 / lubricity);
                            if (moveSpeed.x > -(0.01 / lubricity) * 2 && moveSpeed.x < (0.01 / lubricity) * 2) {
                                moveSpeed.x = 0;
                            }
                            moveSpeed.y = moveSpeed.y < 0 ? moveSpeed.y + (0.01 / lubricity) : moveSpeed.y - (0.01 / lubricity);
                            if (moveSpeed.y > -(0.01 / lubricity) * 2 && moveSpeed.y < (0.01 / lubricity * 2)) {
                                moveSpeed.y = 0;
                            }
                            this->moved = true;
                            return commonSpeed;
                        }
                    }
                }
            }
            for (auto obj : Cars.cars) {
                if (obj->body.index == object.index) {
                    sf::Vector2f commonSpeed = {
                            (delta.x * this->weight + obj->moveSpeed.x * obj->weight) / (this->weight + obj->weight),
                            (delta.y * this->weight + obj->moveSpeed.y * obj->weight) / (this->weight + obj->weight),
                    };
//                    std::cout << commonSpeed.x << ' ' << commonSpeed.y << std::endl;
                    sf::Vector2f howMoved = obj->move( commonSpeed, 0, objects, movingObjects, Cars, parkingLot);
                    if (howMoved != sf::Vector2f(0, 0)) {
//                        std::cout << "k" << std::endl;
                        sf::Vector2f howMovedAgain = this->move( howMoved, rotation, objects, movingObjects, Cars, parkingLot);
                        if (howMovedAgain != sf::Vector2f(0, 0)) {
                            moveSpeed = sf::Vector2f(howMovedAgain.x, howMovedAgain.y);
                            moveSpeed.x = moveSpeed.x < 0 ? moveSpeed.x + (0.01 / lubricity) : moveSpeed.x - (0.01 / lubricity);
                            if (moveSpeed.x > -(0.01 / lubricity) * 2 && moveSpeed.x < (0.01 / lubricity) * 2) {
                                moveSpeed.x = 0;
                            }
                            moveSpeed.y = moveSpeed.y < 0 ? moveSpeed.y + (0.01 / lubricity) : moveSpeed.y - (0.01 / lubricity);
                            if (moveSpeed.y > -(0.01 / lubricity) * 2 && moveSpeed.y < (0.01 / lubricity * 2)) {
                                moveSpeed.y = 0;
                            }
                            this->moved = true;
                            return commonSpeed;
                        }
                    }
                }
            }
            moveSpeed.x = 0;
            moveSpeed.y = 0;
            return {0 , 0};
        }
    }
    body.position = body.position + delta;
    moveSpeed.x = delta.x;
    moveSpeed.y = delta.y;
    body.body.setPosition(body.position);
//    generatePointsInProcess(delta, rotation * M_PI / 180);
    for (int i; i < body.points.size(); i++) {
        body.points[i] = body.possiblePoints[i];
    }
    body.point1 = {-999999, -9999999};
    body.point2 = {999999, 9999999};
    for( auto &point: body.points) {
        body.point1.x = point.x < body.point1.x ? point.x : body.point1.x;
        body.point1.y = point.y < body.point1.y ? point.y : body.point1.y;
        body.point2.x = point.x > body.point2.x ? point.x : body.point2.x;
        body.point2.y = point.y > body.point2.y ? point.y : body.point2.y;
    }
    body.angle += float(rotation * M_PI / 180 / M_PI * 180);
    body.body.setRotation(body.angle);
    moveSpeed.x = moveSpeed.x < 0 ? moveSpeed.x + (0.01 / lubricity) : moveSpeed.x - (0.01 / lubricity);
    if (moveSpeed.x > -(0.01 / lubricity) * 2 && moveSpeed.x < (0.01 / lubricity) * 2) {
        moveSpeed.x = 0;
    }
    moveSpeed.y = moveSpeed.y < 0 ? moveSpeed.y + (0.01 / lubricity) : moveSpeed.y - (0.01 / lubricity);
    if (moveSpeed.y > -(0.01 / lubricity) * 2 && moveSpeed.y < (0.01 / lubricity) * 2) {
        moveSpeed.y = 0;
    }
    this->moved = true;
    return delta;
}
