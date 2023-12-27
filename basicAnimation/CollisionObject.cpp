#include "CollisionableObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>
#include <string>


CollisionableObject::CollisionableObject (bool isCar, int index, sf::Vector2f position, float angle, std::vector <sf::Vector2f> points, const std::string& texturePath, sf::Vector2f texturePoint1, sf::Vector2f texturePoint2, float scale) {
    {
        this->scale = scale;
        this->index = index;
        this->position = position;
        this->angle = angle;
        this->points = points;
        this->texturePoint1 = texturePoint1;
        this->texturePoint2 = texturePoint2;
        body.setOrigin(0, 0);
        texture.loadFromFile(texturePath);
        body.setPointCount(points.size());
        for(int i = 0; i <= points.size() - 1; i++) {
            body.setPoint(i, points[i]);
        }
        body.setScale(scale, scale);
        body.setPosition(position);
        body.setTexture(&texture);
        body.setTextureRect(sf::IntRect (texturePoint1.x, texturePoint1.y, texturePoint2.x, texturePoint2.y));
        body.setRotation(angle);

        originalPoints.clear();
        for( auto &point: this->points) {
            point.x = point.x * scale;
            point.y = point.y * scale;
            originalPoints.emplace_back(point.x, point.y - (isCar ? 8.5 * scale : 0));
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

void CollisionableObject::generatePossiblePoints (sf::Vector2f delta, float rotation) {
    possiblePoints.clear();
    for(int i = 0; i <= points.size() - 1; i++) {
        possiblePoints.emplace_back(points[i].x * cos(rotation) - points[i].y * sin(rotation) + delta.x, points[i].x * sin(rotation) + points[i].y * cos(rotation) + delta.y);
    }
}

void CollisionableObject::generatePoints (sf::Vector2f delta, float rotation) {
    for(int i = 0; i <= points.size() - 1; i++) {
        points[i] = (sf::Vector2f (points[i].x * cos(rotation) - points[i].y * sin(rotation) + delta.x, points[i].x * sin(rotation) + points[i].y * cos(rotation) + delta.y));
    }
}
