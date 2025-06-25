// Doctest
#include "doctest.h"
#define private public
#include "obstacles_list.hpp"
#include "polygon_obstacle.hpp"
#include "circle_obstacle.hpp"
#include "pipe.hpp"
#include <vector>

TEST_CASE("ObstaclesList basic operations") {
    ObstaclesList obstacles;
    CHECK(obstacles._obstaclesList.empty());

    SUBCASE("setPolygonsObstaclesList populates list") {
        std::vector<Vector> verts = {Vector(0,0), Vector(1,0), Vector(1,1), Vector(0,1)};
        obstacles.setPolygonsObstaclesList(verts, "./assets/asteroid.png");
        CHECK(obstacles._obstaclesList.size() == OBSTACLES_LIST_NUM);
        for (auto* o : obstacles._obstaclesList) {
            CHECK(o != nullptr);
        }
    }

    SUBCASE("setCircleObstaclesList populates list") {
        obstacles.setCircleObstaclesList("./assets/asteroid.png");
        CHECK(obstacles._obstaclesList.size() == OBSTACLES_LIST_NUM);
        for (auto* o : obstacles._obstaclesList) {
            CHECK(o != nullptr);
        }
    }

    SUBCASE("clear properly empties and deletes") {
        obstacles.setCircleObstaclesList("./assets/asteroid.png");
        obstacles.clear();
        CHECK(obstacles._obstaclesList.empty());
    }
}

TEST_CASE("PipeList basic operations") {
    PipeList pipes;
    CHECK(pipes.pipes.empty());

    SUBCASE("generatePipes adds two pipes") {
        std::vector<Vector> shapeL = {Vector(0,0), Vector(1,0)};
        std::vector<Vector> shapeR = {Vector(0,1), Vector(1,1)};
        pipes.generatePipes(shapeL, shapeR, "./assets/asteroid.png", "./assets/asteroid2.png");
        CHECK(pipes.pipes.size() == 2);
        for (auto* p : pipes.pipes) {
            CHECK(p != nullptr);
        }
    }

    SUBCASE("clear empties pipes") {
        std::vector<Vector> shapeL = {Vector(0,0), Vector(1,0)};
        std::vector<Vector> shapeR = {Vector(0,1), Vector(1,1)};
        pipes.generatePipes(shapeL, shapeR, "./assets/asteroid.png", "./assets/asteroid2.png");
        pipes.clear();
        CHECK(pipes.pipes.empty());
    }
}

TEST_CASE("ObstaclesList updateAll and drawAll do not crash") {
    ObstaclesList obstacles;
    std::vector<Vector> verts = {Vector(0,0), Vector(1,0), Vector(1,1), Vector(0,1)};
    obstacles.setPolygonsObstaclesList(verts, "./assets/asteroid.png");
    // We just want to make sure updateAll/drawAll don't crash
    obstacles.updateAll(obstacles._obstaclesList);
    obstacles.drawAll(obstacles._obstaclesList);
    CHECK(true);
}
