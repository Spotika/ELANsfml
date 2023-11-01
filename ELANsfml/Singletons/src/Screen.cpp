#include "ELANsfml/Singletons/Screen.h"
#include "ELANsfml/Helpers/Config.h"

void Screen::Init() {
  render_window = new sf::RenderWindow(
      sf::VideoMode(config::window::width, config::window::height),
      config::window::title);
  if (render_window == nullptr) {
    throw;
  }
  render_window->setFramerateLimit(config::window::FPS);

  font = new sf::Font;

  font->loadFromFile(
      R"(/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Medium.ttf)");
}

sf::RenderWindow *Screen::GetRenderWindow() { return render_window; }

sf::Font *Screen::GetFont() { return font; }

void Screen::SetView(sf::Vector2f size, sf::Vector2f center) {
  sf::View view;
  view.setSize(size);
  view.setCenter(center);

  render_window->setView(view);
}

void Screen::SetResizable(bool is_resizable) { is_resizable_ = is_resizable; }

bool Screen::IsResizable() const { return is_resizable_; }
