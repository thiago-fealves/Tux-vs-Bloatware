#include "shots.hpp"
#include "windows_boss.hpp"
#include "bootstrap.hpp"
#include "collision.hpp"
//    --- BALL SHOT --- 
/**
 * @class Shot 
 * 
 * @brief represents a shot in a more abstract way, abstract class.
 */

// Initializes static members
std::list<Shot*> Shot::ShotsList; 
std::vector<Shot*> Shot::inactiveShotsList; 

/**
 * @brief Destroys all shots.
 */
void Shot::cleanShots() {
  // Delete the shots that are not nullptr and then clear the list, in both lists.

  for(Shot* &shot : ShotsList) {
    if(shot!=nullptr) {
      delete shot;
      shot=nullptr;
    }
  }
  ShotsList.clear();

  for(Shot* &shot : inactiveShotsList) {
    if(shot!=nullptr) {
      delete shot;
      shot=nullptr;
    }
  }
  inactiveShotsList.clear();
}

/**
 * @brief Build a standard shot.
 * 
 * @param position The initial position of the shot.
 * @param direction A vector in which the shot moves or points.
 * @param shotColor A shot color.
 */
Shot::Shot(Vector position, Vector direction, ALLEGRO_COLOR shotColor) : 
      GameObject(position), _direction(direction), _shotColor(shotColor) {}

/**
 * @brief Clears the list of shots to be removed. (deletes all of them).
 */
void Shot::removeInactiveShots() {
  for(Shot* &tiro : Shot::inactiveShotsList) {
    if(tiro != nullptr) {
      Shot::ShotsList.remove(tiro);
      delete tiro;
      tiro = nullptr;
    }
  }
  Shot::inactiveShotsList.clear();
}
  
/**
 * @brief For all shots, from the shot list, they are updated and then it is
 *  checked if the shot is active or if it collided with something (boss or the player)
 * 
 * @param player Player pointer.
 * @param boss Boss address(windows).
 * @param playing Address of the variable that indicates whether the game is still active.
 */
void Shot::updateShots(FixedShip* player, WindowsBoss& boss, bool &playing) {

  //atualiza a posição dos tiros e checa colisao
  for(Shot* shot : Shot::ShotsList) {

    if(shot==nullptr) continue;
  
    shot->update();

    if(!shot->isItActive()) {
      inactiveShotsList.push_back(shot);
    
    }else if(shot->shotCollidedWithPlayer(*player)) {
      player->takeDamage(playing);
      inactiveShotsList.push_back(shot);

    } else if(shot->shotCollidedWithBoss(boss)) {
      boss.takeDamage();
      inactiveShotsList.push_back(shot);
    }
    
  }

  // Removes the shots that are in the list of shots to remove.
  removeInactiveShots();

}

/**
 * @brief Calls the draw() function of all active shots.
 */
void Shot::drawShots() {
  for(auto shot : Shot::ShotsList) shot->draw();
}


//    --- BALL SHOT --- 
/**
 * @class Ball Shot
 * 
 * @brief represents a ball-shaped shot.
 */

/**
 * @brief Constructs a ball-shaped shot and inserts it into the shot list.
 * 
 * @param initialPosi The initial position of the shot.
 * @param direction A vector in which the shot moves.
 * @param radius Radius of the shot.
 * @param speed Speed of the shot.
 */
BallShot::BallShot(Vector initialPosi, Vector direction, float radius, float speed) : 
  Shot(initialPosi, direction, al_map_rgb(100, 150, 200)), _speed(speed), _radius(radius) {
    Shot::ShotsList.push_back(this);
  }
 
/**
 * @brief Draw a ball
 */
void BallShot::draw() {
  
  // ------------------------------------------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  float draw_x = _position._x - (_radius /2);  // centralizar no x
  float draw_y = _position._y - (_radius/2); // centralizar no y

  al_draw_scaled_bitmap(
      ballShotSprite,          // ALLEGRO_BITMAP* do sprite
      0, 0,             // origem na imagem (top-left)
      al_get_bitmap_width(ballShotSprite),   // largura original do sprite
      al_get_bitmap_height(ballShotSprite),  // altura original do sprite
      draw_x, draw_y,   // posição na tela (centralizado na posição da bola)
      _radius*3, _radius*3,  // nova largura e altura desejadas
      0                 // flags (normalmente 0)
  );
}

/**
 * @brief Add to the position of the ball (shot), the direction
 *  vector multiplied by the velocity. (normally the direction vectors are unitary)
 */
void BallShot::update() {
  this->_position = this->_position + (this->_direction * this->_speed);
}

/**
 * @brief Checks if the ball (shot) positions are within the game region.
 * 
 * @return If the ball shot is still active.
 */
bool BallShot::isItActive() {
  return !(((_position._x + _radius) < 0 || (_position._x - _radius) > SCREEN_W) ||
          ((_position._y + _radius) < 0 || (_position._y - _radius) > SCREEN_H));
}

/**
 * @brief Checks if the ball (shot) collided with the boss. (Circle-square collision.)
 * 
 * @param boss Boss address(windows).
 * 
 * @return If the ball shot collided like the boss.
 */
bool BallShot::shotCollidedWithBoss(WindowsBoss& boss) {
  return circleSquareCollision(_position, _radius, boss.get_position(), boss.getHalfSide());
}

/**
 * @brief Check if the ball (shot) collided with the player. (Circle-to-circle collision.)
 * 
 * @param player Player address.
 * 
 * @return If the ball shot collided like the player.
 */
bool BallShot::shotCollidedWithPlayer(FixedShip& player) {
  return circleCircleCollision(_position, _radius, player.get_position(), player.get_radius());
}


// --- LINE SHOT --- 
/**
 * @class Line shot
 * 
 * @brief represents a line-shaped shot, like a laser.
 */

/**
 * @brief Build a shot in the form of a line, initializing the values, placing its address in
 *  the list of shots and making the variable _direction store the end point of the half-line.
 * 
 * @param initialPosi Starting point of the line segment.
 * @param direction Vector that indicates the direction of the line.
 * @param thickness line thickness. (Unit vector normally.)
 * @param length Length of the semi-straight.
 * @param activationTime Time for the shot to cause damage.
 */ 
LineShot::LineShot(Vector initialPosi, Vector direction, float thickness, float length, double activationTime) : 
      Shot(initialPosi, direction, al_map_rgb(10, 150, 150)), _thickness(thickness),
      _length(length), _activationTime(activationTime)
{
  _direction = (_direction*length)+_position;
  Shot::ShotsList.push_back(this);
}

/**
 * @brief Draw a line.
 */
void LineShot::draw() {
  al_draw_line(_position._x, _position._y, _direction._x, _direction._y, 
  _shotColor, _thickness);
}

/**
 * @brief Checks if line thickness is greater than 0.4.
 * 
 * @return If the ball shot is still active.
 */
bool LineShot::isItActive() {
  return (_thickness > 0.4);
}

/**
 * @brief It makes the line thinner over time,
 *  and when the activation time ends, the line turns red and starts to deal damage.
 */
void LineShot::update() {
  this->_thickness -= 0.1;
  
  //If the line is already 'activated' then
  // there is no need to check the activation time anymore.
  if(_activated==true) return;

  this->_activationTime -= 0.3;
  if(this->_activationTime<=0) {
    this->_shotColor = al_map_rgb(255, 0, 0);
    this->_activated=true;
    gunshot_sound4->play(0.5);
  }
}

/**
 * @brief Check if the ball (line) collided with the player. (Circle-to-line collision.)
 * 
 * @param player Player address.
 * 
 * @return If the line shot collided like the player.
 */
bool LineShot::shotCollidedWithPlayer(FixedShip& player) {
  if(this->_activated==false) return false;

  // Checks whether the distance between the center of the circle and the half-line,
  // measured under perpendicular projection, is less than the radius plus half the thickness.
  return (Vector::shortestDistancePointToSegment(player.get_position(), _position, _direction)
  <=(player.get_radius() + (_thickness/2.0f)));

}

/**
 * @brief We haven't implemented the line shot for the player,
 *  so it doesn't make sense to implement this function.
 * 
 * @param boss Boss address(windows).
 * 
 * @return If the line shot collided like the boss.
 */
bool LineShot::shotCollidedWithBoss(WindowsBoss& boss) {
  return false;
}

