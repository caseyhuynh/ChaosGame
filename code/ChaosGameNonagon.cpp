// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	Text choosePoints;
	Font font;
	font.loadFromFile("Fonts/arial.ttf");
	choosePoints.setFont(font);
	choosePoints.setString("Choose Points");
	choosePoints.setCharacterSize(75);
	choosePoints.setFillColor(Color::White);
	FloatRect textRect = choosePoints.getLocalBounds();
	choosePoints.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	choosePoints.setPosition(1920 / 2.0f, 75);
	
	srand(time(NULL));
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{

			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 9)
			    {
					vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					if (vertices.size() == 9)
					{
						choosePoints.setString("Choose one more");
						FloatRect textRect = choosePoints.getLocalBounds();
						choosePoints.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
						choosePoints.setPosition(1920 / 2.0f, 75);
					}
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
				/// choosePoints.setString("Choose Points");
					points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
		    ///goal:generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			for (int i = 0; i < 10; i++)
			{
				int vertex = rand() % 9;
				float x = (vertices.at(vertex).x - points.back().x) * (0.742) + points.back().x;
				float y = (vertices.at(vertex).y- points.back().y) * (0.742) + points.back().y;
				points.push_back(Vector2f(x, y));
			}
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();

		if (vertices.size() < 9 || points.size() == 0) {
			window.draw(choosePoints);
		}

		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
			
		}


		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape rect(Vector2f(5, 5));
			rect.setPosition(Vector2f(points[i].x, points[i].y));
			rect.setFillColor(Color::Red);
			window.draw(rect);
		}
		window.display();
	}
}
