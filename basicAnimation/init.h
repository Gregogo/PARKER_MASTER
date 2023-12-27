const float scale = 5;
const float speed = 150;

struct Keys
{
    bool w;
    bool a;
    bool s;
    bool d;
    bool shift;
    bool space;
};

struct StepSounds
{
    sf::Sound sound1;
    sf::Sound sound2;
    sf::Sound sound3;
    sf::Sound sound4;
};

struct movingVector
{
    float k;
    float b;
    float startingX;
    float endingX;
};

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;