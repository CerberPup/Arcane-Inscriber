#include <iostream>
#include <SFML\Graphics.hpp>
#include "Logger.cpp"
#include "Engine.h"
#include <Windows.h>
#include <map>
#include "Menu.h"


using namespace std;

void splash(Engine &e) {
	sf::Font font;
	if (!font.loadFromFile("Resources/arial.ttf")) {
		MessageBox(NULL, TEXT("Font not found!"), TEXT("ERROR"), NULL);
		return;
	}
	sf::Text title("Tytul", font, 80);
	title.setStyle(sf::Text::Bold);
	title.setPosition(e.width / 2 - title.getGlobalBounds().width / 2, e.height / 4);
	sf::Color c(255,255,255, 0);
	title.setFillColor(c);
	for (int i = 0; i < 46; i++)
	{
		e.window.clear(sf::Color(23, 23, 23, 255));
		e.window.draw(title);
		e.window.display();
		c.a += 3;
		Sleep(30);
		title.setFillColor(c);
	}
}

int main() {
	sf::VideoMode t = sf::VideoMode::getDesktopMode();
	LOG("Rozmiar ekranu", t.width, t.height);
	Engine e(t.width, t.height);

	map<string, sf::Texture> Texturki;

	while (e.window.isOpen()) {
		switch (Engine::state)
		{
		case Engine::State::SPLASH: {
			//animacja na starcie
			splash(e);
			Engine::state = Engine::State::MAINMENU;
			break;
		}
		case Engine::State::MAINMENU: {
			Menu().Run();
			//Menu. Po wcisnieciu start zmienia state na game
			
			break;
		}
		case Engine::State::GAME: {
			Engine::state = Engine::State::EXIT;
			//glowna petla gry. Osobne watki na przechwytywanie inputu, draw frame, kolizje, animacje
			break;
		}
		case Engine::State::EXIT: {
			Engine::window.close();
			break;
		}
		default:
			break;
		}
	}
}