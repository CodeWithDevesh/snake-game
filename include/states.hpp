#if !defined(STATES_HPP)
#define STATES_HPP

enum State
{
    SNAKE,
    HEAD,
    EMPTY,
    TAIL,
    FOOD
};

enum Direction
{
    UP = 1,
    DOWN = -1,
    LEFT = -2,
    RIGHT = 2,
    NONE
};

#endif // STATES_HPP
