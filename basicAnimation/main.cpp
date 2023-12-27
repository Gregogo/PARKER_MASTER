#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "CollisionableObject.h"
#include "MovingObject.h"
#include "Car.h"
#include "ParkingLot.h"
#include "updateState.h"
#include "keysHandler.h"

void pollEvents(sf::RenderWindow &window, Keys &keys)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                onKeyPress(event, keys);
                break;
            case sf::Event::KeyReleased:
                onKeyRelease(event, keys);
                break;
            default:
                break;
        }
    }
}

void moveByInertia(locationCollisionableObjects &objectsOfLocation, locationMovingObjects &movingObjects, locationCars &Cars, float deltaTime ,ParkingLot parkingLot) {
    for ( auto &obj : movingObjects.objects) {
        if((obj->moveSpeed.x != 0 || obj->moveSpeed.y != 0) && !obj->moved) {
            obj->move({obj->moveSpeed.x * deltaTime * 100, obj->moveSpeed.y * deltaTime * 100}, 0, objectsOfLocation, movingObjects, Cars, parkingLot);
        }
    }
    for ( auto &car : Cars.cars) {
        if((car->moveSpeed.x != 0 || car->moveSpeed.y != 0) && !car->moved) {
            float speed = sqrt(car->moveSpeed.y * car->moveSpeed.y + car->moveSpeed.x * car->moveSpeed.x);
            sf::Vector2f moveDelta = sf::Vector2f (speed * cos((car->body.angle + car->wheelDirection * car->rotateSpeed * car->moveDirection) * M_PI / 180) * car->moveDirection, (speed * sin((car->body.angle + car->wheelDirection * car->rotateSpeed) * M_PI / 180) * car->moveDirection));
            car->move(moveDelta, car->wheelDirection * car->rotateSpeed * car->moveDirection, objectsOfLocation, movingObjects, Cars, parkingLot);
        }
    }
}

void update(Car &car, float deltaTime, Keys &keys, locationCollisionableObjects &objectsOfLocation, locationMovingObjects &movingObjects, locationCars &cars, ParkingLot parkingLot)
{
    updateState(keys, car);
    if (car.isDriving) {
        car.go(car.moveDirection, deltaTime, objectsOfLocation, movingObjects, cars, car.carSpeed, parkingLot);
    }
}

void redrawFrame(sf::RenderWindow &window, locationCollisionableObjects &objects, sf::Text &text, ParkingLot &parkingLot)
{
    window.clear(sf::Color(30, 30, 30));
    window.draw(parkingLot.body);
    for (auto object : objects.objects) {
        window.draw(object.body);
    }
    window.draw(text);
    window.display();
}

int main()
{
    auto cementSquare1 = CollisionableObject(
            false,
            0,
            sf::Vector2f(1200, 0),
            0.001,
            {
                    sf::Vector2f(0, 0),
                    sf::Vector2f(750, 0),
                    sf::Vector2f(750, 300),
                    sf::Vector2f(0, 300),
            },
            "../cement.jpg",
            sf::Vector2f(0, 0),
            sf::Vector2f(100, 67),
            1
    );
    auto firstWall = CollisionableObject(
            false,
            1,
            sf::Vector2f(-200, 0),
            0.01,
            {
                    sf::Vector2f(0, 0),
                    sf::Vector2f(200, 0),
                    sf::Vector2f(200, WINDOW_HEIGHT),
                    sf::Vector2f(0, WINDOW_HEIGHT)
            },
            "../black.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(10, 10),
            1
    );
    auto secondWall = CollisionableObject(
            false,
            2,
            sf::Vector2f(-200, -200),
            0.01,
            {
                    sf::Vector2f(0, 0),
                    sf::Vector2f(WINDOW_WIDTH + 400, 0),
                    sf::Vector2f(WINDOW_WIDTH + 400, 200),
                    sf::Vector2f(0, 200)
            },
            "../black.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(10, 10),
            1
    );
    auto thirdWall = CollisionableObject(
            false,
            3,
            sf::Vector2f(WINDOW_WIDTH, 0),
            0.01,
            {
                    sf::Vector2f(0, 0),
                    sf::Vector2f(200, 0),
                    sf::Vector2f(200, WINDOW_HEIGHT),
                    sf::Vector2f(0, WINDOW_HEIGHT)
            },
            "../black.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(10, 10),
            1
    );
    auto forthWall = CollisionableObject(
            false,
            4,
            sf::Vector2f(-200, WINDOW_HEIGHT),
            0.01,
            {
                    sf::Vector2f(0, 0),
                    sf::Vector2f(WINDOW_WIDTH + 400, 0),
                    sf::Vector2f(WINDOW_WIDTH + 400, 200),
                    sf::Vector2f(0, 200)
            },
            "../black.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(10, 10),
            1
    );
    auto npcCar1 = CollisionableObject(
            false,
            5,
            sf::Vector2f(430, 130),
            90.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/BlueKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto npcCar2 = CollisionableObject(
            false,
            6,
            sf::Vector2f(650, 130),
            90.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/RedKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto npcCar3 = CollisionableObject(
            false,
            7,
            sf::Vector2f(745, 130),
            90.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/BlueKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto collisionableFigure = CollisionableObject(
            false,
            8,
            sf::Vector2f(450, 650),
            -5,
            {
                    sf::Vector2f(0, 0),
                    sf::Vector2f(200, 0),
                    sf::Vector2f(500, 100),
                    sf::Vector2f(200, 200),
                    sf::Vector2f(0, 200)
            },
            "../box.jpg",
            sf::Vector2f(0, 0),
            sf::Vector2f(40, 40),
            1
    );
    auto collisionableCar = CollisionableObject(
            true,
            9,
            sf::Vector2f(1600, 700),
            180.01,
            {
//                    sf::Vector2f(0, 0),
//                    sf::Vector2f(25, 0),
//                    sf::Vector2f(25, 17),
//                    sf::Vector2f(0, 17),
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/BlueKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    std::vector <sf::Vector2f> ballPoints;
    int pointNumber = 20;
    float R = 50;
    for (int i = 0; i < pointNumber; i++) {
        float angle = M_PI * 2 / pointNumber * i;
        ballPoints.push_back({R * cos(angle), R * sin(angle)});
    }
    auto ballFigure = CollisionableObject(
            false,
            10,
            sf::Vector2f(700, 950),
            0.1,
            ballPoints,
            "../ball.jpg",
            sf::Vector2f(0, 0),
            sf::Vector2f(40, 40),
            1
    );
    auto cementSquare2 = CollisionableObject(
            false,
            11,
            sf::Vector2f(0, 0),
            0.001,
            {
                    sf::Vector2f(0, 0),
                    sf::Vector2f(1200, 0),
                    sf::Vector2f(1200, 100),
                    sf::Vector2f(0, 100),
            },
            "../cement.jpg",
            sf::Vector2f(0, 0),
            sf::Vector2f(100, 67),
            1
    );
    auto cementSquare3 = CollisionableObject(
            false,
            12,
            sf::Vector2f(0, 100),
            0.001,
            {
                    sf::Vector2f(0, 0),
                    sf::Vector2f(300, 0),
                    sf::Vector2f(300, 980),
                    sf::Vector2f(0, 980),
            },
            "../cement.jpg",
            sf::Vector2f(0, 0),
            sf::Vector2f(100, 67),
            1
    );
    auto npcCar4 = CollisionableObject(
            false,
            13,
            sf::Vector2f(845, 130),
            90.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/BlueKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto npcCar5 = CollisionableObject(
            false,
            14,
            sf::Vector2f(945, 140),
            93.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/RedKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto npcCar6 = CollisionableObject(
            false,
            15,
            sf::Vector2f(1040, 140),
            85.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/RedKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto npcCar7 = CollisionableObject(
            false,
            16,
            sf::Vector2f(1150, 130),
            95.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/BlueKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto npcCar8 = CollisionableObject(
            false,
            17,
            sf::Vector2f(1240, 398),
            180.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/BlueKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto npcCar9 = CollisionableObject(
            false,
            18,
            sf::Vector2f(1245, 500),
            180.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/BlueKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto npcCar10 = CollisionableObject(
            false,
            19,
            sf::Vector2f(1260, 605),
            183.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/RedKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto npcCar11 = CollisionableObject(
            false,
            20,
            sf::Vector2f(1245, 700),
            176.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/RedKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    auto npcCar12 = CollisionableObject(
            false,
            21,
            sf::Vector2f(430, 510),
            100.01,
            {
                    sf::Vector2f(3, 0),
                    sf::Vector2f(21, 0),
                    sf::Vector2f(25, 4),
                    sf::Vector2f(25, 13),
                    sf::Vector2f(21, 17),
                    sf::Vector2f(3, 17),
                    sf::Vector2f(0, 14),
                    sf::Vector2f(0, 3),
            },
            "../cars/kalina/BlueKalina.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(25, 17),
            5
    );
    std::vector <sf::Vector2f> ballPoints2;
    int pointNumber2 = 20;
    float R2 = 75;
    for (int i = 0; i < pointNumber2; i++) {
        float angle = M_PI * 2 / pointNumber2 * i;
        ballPoints2.push_back({R2 * cos(angle), R2 * sin(angle)});
    }
    auto clumba = CollisionableObject(
            false,
            22,
            sf::Vector2f(540, 470),
            -80.01,
            ballPoints2,
            "../Clumba.png",
            sf::Vector2f(0, 0),
            sf::Vector2f(50, 50),
            1
    );
    std::vector <locationCollisionableObjects> collisionableObjectsOfLocations = {
            {
                    {
                            cementSquare1,
                            firstWall,
                            secondWall,
                            thirdWall,
                            forthWall,
                            npcCar1,
                            npcCar2,
                            npcCar3,
                            collisionableFigure,
                            collisionableCar,
                            ballFigure,
                            cementSquare2,
                            cementSquare3,
                            npcCar4,
                            npcCar5,
                            npcCar6,
                            npcCar7,
                            npcCar8,
                            npcCar9,
                            npcCar10,
                            npcCar11,
                            npcCar12,
                            clumba,
                    },
            },
    };

    auto movableNpcCar1 = MovingObject(collisionableObjectsOfLocations[0].objects[5], 0.1, 20);
    auto movableNpcCar2 = MovingObject(collisionableObjectsOfLocations[0].objects[6], 0.1, 60);
    auto movableNpcCar3 = MovingObject(collisionableObjectsOfLocations[0].objects[7], 0.1, 60);
    auto figure = MovingObject(collisionableObjectsOfLocations[0].objects[8], 0.1, 60);
    auto ball = MovingObject(collisionableObjectsOfLocations[0].objects[10], 0.6, 20);
    auto movableNpcCar4 = MovingObject(collisionableObjectsOfLocations[0].objects[13], 0.1, 60);
    auto movableNpcCar5 = MovingObject(collisionableObjectsOfLocations[0].objects[14], 0.1, 60);
    auto movableNpcCar6 = MovingObject(collisionableObjectsOfLocations[0].objects[15], 0.1, 60);
    auto movableNpcCar7 = MovingObject(collisionableObjectsOfLocations[0].objects[16], 0.1, 60);
    auto movableNpcCar8 = MovingObject(collisionableObjectsOfLocations[0].objects[17], 0.1, 60);
    auto movableNpcCar9 = MovingObject(collisionableObjectsOfLocations[0].objects[18], 0.1, 60);
    auto movableNpcCar10 = MovingObject(collisionableObjectsOfLocations[0].objects[19], 0.1, 60);
    auto movableNpcCar11 = MovingObject(collisionableObjectsOfLocations[0].objects[20], 0.1, 60);
    auto movableNpcCar12 = MovingObject(collisionableObjectsOfLocations[0].objects[21], 0.1, 60);

    std::vector <locationMovingObjects> movingObjectsOfLocations = {
            {
                    {
                            &movableNpcCar1,
                            &movableNpcCar2,
                            &movableNpcCar3,
                            &figure,
                            &ball,
                            &movableNpcCar4,
                            &movableNpcCar5,
                            &movableNpcCar6,
                            &movableNpcCar7,
                            &movableNpcCar8,
                            &movableNpcCar9,
                            &movableNpcCar10,
                            &movableNpcCar11,
                            &movableNpcCar12,
                    },
            },
    };

    auto car = Car(collisionableObjectsOfLocations[0].objects[9], 1.2, 6);

    std::vector <locationCars> CarsOfLocations = {
            {
                    {
                            &car,
                    },
            },
    };
    auto parkingLot = ParkingLot{
            sf::Vector2f(550, 110),
            90.01,
            {
                    sf::Vector2f(0, 0),
                    sf::Vector2f(30 * 5, 0),
                    sf::Vector2f(30 * 5, 20 * 5),
                    sf::Vector2f(0, 20 * 5),
            },
    };
    std::cout << "main" << std::endl;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
            "Back Home", sf::Style::Fullscreen, settings);

    Keys keys;
    keys = {
            w : false,
            a : false,
            s : false,
            d : false,
            shift : false,
    };
    sf::Clock animationClock;
    sf::Clock movementClock;

    sf::Font font;
    font.loadFromFile("../ArialRegular.ttf");
    sf::Text frameCounter;

    frameCounter.setFont(font); // font is a sf::Font
    frameCounter.setString("");
    frameCounter.setFillColor(sf::Color::Red);
    frameCounter.setCharacterSize(170); // in pixels, not points!

    while (window.isOpen())
    {
        if (car.won) {
            frameCounter.setString("YOU HAVE WON!!!!");
        }
        if (car.lost) {
            frameCounter.setString("YOU HAVE LOST, loser");
        }
        for (auto obj : movingObjectsOfLocations[0].objects) {
            obj->moved = false;
        }
        for (auto car : CarsOfLocations[0].cars) {
            car->moved = false;
        }
        pollEvents(window, keys);
        const float time = animationClock.getElapsedTime().asSeconds();
        const float deltaTime = movementClock.restart().asSeconds();
        update(car, deltaTime, keys, collisionableObjectsOfLocations[0], movingObjectsOfLocations[0], CarsOfLocations[0], parkingLot);
        moveByInertia(collisionableObjectsOfLocations[0], movingObjectsOfLocations[0], CarsOfLocations[0], deltaTime, parkingLot);
        redrawFrame(window, collisionableObjectsOfLocations[0], frameCounter, parkingLot);
    }
}