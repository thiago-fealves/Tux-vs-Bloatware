#pragma once
#include <vector>
#include "abstract_obstacle.hpp"
#include "bootstrap.hpp"
#include "polygon_obstacle.hpp"
#include "circle_obstacle.hpp"
#include "pipe.hpp"
#include <memory>

class ObstaclesList{

private:
  std::vector<AbstractObstacle*> _obstaclesList;

public:
    void setPolygonsObstaclesList(const std::vector<Vector>& verts, const char* path);
    void setCircleObstaclesList(const char* path);
    std::vector<AbstractObstacle*>& getList();
    void updateAll(std::vector<AbstractObstacle*> obstaclesList);
    void drawAll(std::vector<AbstractObstacle*> obstaclesList);
    ~ObstaclesList();
};

class PipeList {
private:
    std::vector<AbstractObstacle*> pipes;

public:
    PipeList() = default;
    ~PipeList();

    void generatePipes(const std::vector<Vector>& shapeLeft, 
        const std::vector<Vector>& shapeRight, const char* imagePathLeft, const char* imagePathRight);
    std::vector<AbstractObstacle*>& getList();
};