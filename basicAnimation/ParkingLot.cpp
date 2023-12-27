#include "ParkingLot.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>
#include <string>


ParkingLot::ParkingLot(sf::Vector2f position, float angle, std::vector <sf::Vector2f> points) {
    {
        this->position = position;
        this->angle = angle;
        this->points = points;
        this->texturePoint1 = texturePoint1;
        this->texturePoint2 = texturePoint2;
        body.setOrigin(0, 0);
        body.setPointCount(points.size());
        for(int i = 0; i <= points.size() - 1; i++) {
            body.setPoint(i, points[i]);
        }
        body.setPosition(position);
        body.setFillColor(sf::Color(124,252,0));
        body.setRotation(angle);

        originalPoints.clear();
        for( auto &point: this->points) {
            point.x = point.x;
            point.y = point.y;
            originalPoints.emplace_back(point.x, point.y);
        }
        for( auto &point: this->points) {
            std::cout << point.x << ' ' << point.y << std::endl;
            point1.x = point.x < point1.x ? point.x : point1.x;
            point1.y = point.y < point1.y ? point.y : point1.y;
            point2.x = point.x > point2.x ? point.x : point2.x;
            point2.y = point.y > point2.y ? point.y : point2.y;
        }
        generatePossiblePoints(sf::Vector2f(position.x, position.y), angle * M_PI / 180);
        generatePoints(sf::Vector2f(position.x, position.y), angle * M_PI / 180);
    }
}

void ParkingLot::generatePossiblePoints (sf::Vector2f delta, float rotation) {
    possiblePoints.clear();
    for(int i = 0; i <= points.size() - 1; i++) {
        possiblePoints.emplace_back(points[i].x * cos(rotation) - points[i].y * sin(rotation) + delta.x, points[i].x * sin(rotation) + points[i].y * cos(rotation) + delta.y);
    }
}

void ParkingLot::generatePoints (sf::Vector2f delta, float rotation) {
    for(int i = 0; i <= points.size() - 1; i++) {
        points[i] = (sf::Vector2f (points[i].x * cos(rotation) - points[i].y * sin(rotation) + delta.x, points[i].x * sin(rotation) + points[i].y * cos(rotation) + delta.y));
    }
}
