#include "obstacles_list.hpp"


std::vector<AbstractObstacle*>& ObstaclesList::getList()
{
    return _obstaclesList;
}

void ObstaclesList::updateAll(std::vector<AbstractObstacle *> obstaclesList)
{
    for (auto *obs : obstaclesList)
    {
        obs->update();
    }
}

void ObstaclesList::drawAll(std::vector<AbstractObstacle *> obstaclesList)
{
    for (auto *obs : obstaclesList)
    {
        obs->draw();
    }
}

ObstaclesList::~ObstaclesList()
{
    for (auto *obs : _obstaclesList)
    {
        delete obs;
    }
    _obstaclesList.clear();
}

void ObstaclesList::setPolygonsObstaclesList(const std::vector<Vector>& verts, const char* path){

    this->_obstaclesList.clear();

    for (int i = 0; i < OBSTACLES_LIST_NUM; ++i) {
        float x = rand() % SCREEN_W;
        float y = -(rand() % 100);
        Vector position(x, y);
        PolygonObstacle* polyObstacle = new PolygonObstacle(position, verts, path);
        AbstractObstacle* baseObstacle = polyObstacle;
        this->_obstaclesList.emplace_back(baseObstacle);
    }

}

void ObstaclesList::setCircleObstaclesList(const char* path){

    this->_obstaclesList.clear();

    for (int i = 0; i < OBSTACLES_LIST_NUM; ++i) {
        float x = rand() % SCREEN_W;
        float y = -(rand() % 100);
        Vector position(x, y);
        CircleObstacle* polyObstacle = new CircleObstacle(position, path);
        AbstractObstacle* baseObstacle = polyObstacle;
        this->_obstaclesList.emplace_back(baseObstacle);
    }

}
