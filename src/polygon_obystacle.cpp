#include "polygon_obstacle.hpp"
#include <iostream>

void PolygonObstacle::draw() {

    if (objectSprite) {
        float sprite_width = al_get_bitmap_width(objectSprite);
        float sprite_height = al_get_bitmap_height(objectSprite);
            Vector pos = get_position();
            al_draw_scaled_bitmap(objectSprite,
                0, 0, sprite_width, sprite_height,
                pos._x - (sprite_width * scale) / 2.0f,
                pos._y - (sprite_height * scale) / 2.0f,
                sprite_width * scale, sprite_height * scale,
                0
            );
    }
}

 void PolygonObstacle::update() {

        Vector pos = get_position();
        pos._y += 2;
        if (pos._y > 600 + 50) {
            pos._y = -50;
            pos._x = rand() % 800;
        }
        set_position(pos);
}

std::vector<Vector> PolygonObstacle::getVertices(){
    return this->vertices;
}

bool PolygonObstacle::checkCollisionWithPlayer(BrokenShip& player){
    
    for (size_t i = 0; i < this->vertices.size(); ++i) {
        
        Vector a = vertices[i] + this->get_position();
        Vector b = vertices[(i + 1) % vertices.size()] + this->get_position();

          al_draw_line(
            a._x, a._y,     
            b._x, b._y,      
            al_map_rgb(255, 255, 0),      
            1.0f);
            
        if (Vector::shortestDistancePointToSegment(player.get_position(), a, b) <= player.get_radius() * player.get_radius()) return true;
    }
    return false;
}
