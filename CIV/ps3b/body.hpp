#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Constants for the window size.
const int window_height = 500;
const int window_side = 500;

// Physics Constants
const double gravity = 667000000000;

class body: public sf::Drawable
{
public:

  // Constructors
  body();
  body(double pos_x, double pos_y, double vel_x, double vel_y,
       double obj_mass, double radius, std::string file_name);

  // Set radius / image position
  void set_radius(float radius);
  void set_position();              // Sets the planets positions

  // Finds the force between two body objects, adds to force vector
  // (sums all the forces together essentially)
  void find_force(body &Body1, body &Body2);

  // Time step
  void step(double time_t);

  // Overridden operator >> for inputing from a file
  friend std::istream& operator>> (std::istream &input, body &cBody);

  // Overriddden operator << for debugging
  friend std::ostream& operator<< (std::ostream &output, body &cBody);

private:

  // Draw method
  void virtual draw(sf::RenderTarget& target, sf::RenderStates states) const;

  // Member variables
  double _acc_x, _acc_y;
  double _for_x, _for_y;
  double _pos_x, _pos_y;
  double _vel_x, _vel_y;
  double _mass, _radius;
  std::string _filename;

  // Image related objects
  sf::Image _image;
  sf::Sprite _sprite;
  sf::Texture _texture;
};
