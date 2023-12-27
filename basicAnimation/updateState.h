void updateState(Keys keys, Car &car)
{
    if (keys.a && car.wheelDirection != -1)
    {
        car.rotateWheelsLeft();
    }
    if (keys.d && car.wheelDirection != 1)
    {
        car.rotateWheelsRight();
    }
    if (!keys.d && !keys.a && car.wheelDirection != 0) {
        car.rotateWheelsStraight();
    }
    if (keys.w && car.moveDirection != 1)
    {
        car.moveDirection = 1;
    }
    if (keys.s && car.moveDirection != -1)
    {
        car.moveDirection = -1;
    }
    if (!keys.s && !keys.w && car.isDriving)
    {
        car.isDriving = false;
    }
    if ((keys.s || keys.w) && !car.isDriving)
    {
        car.isDriving = true;
    }
    if (keys.shift)
    {
        car.moveSpeed = {0 , 0};
    }
}