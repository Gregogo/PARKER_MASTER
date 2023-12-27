void onKeyPress(sf::Event event, Keys &keys)
{
    if (event.key.code == 32)
    {
        keys.space = true;
    }
    if (event.key.code == 38)
    {
        keys.shift = true;
    }
    if (event.key.code == 22)
    {
        keys.w = true;
    }
    if (event.key.code == 0)
    {
        keys.a = true;
    }
    if (event.key.code == 18)
    {
        keys.s = true;
    }
    if (event.key.code == 3)
    {
        keys.d = true;
    }
}

void onKeyRelease(sf::Event event, Keys &keys)
{
    if (event.key.code == 32)
    {
        keys.space = false;
    }
    if (event.key.code == 38)
    {
        keys.shift = false;
    }
    if (event.key.code == 22)
    {
        keys.w = false;
    }
    if (event.key.code == 0)
    {
        keys.a = false;
    }
    if (event.key.code == 18)
    {
        keys.s = false;
    }
    if (event.key.code == 3)
    {
        keys.d = false;
    }
}