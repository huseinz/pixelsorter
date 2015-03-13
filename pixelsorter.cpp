#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow window;
//(sf::VideoMode(500,500,32), "pixelsort", sf::Style::Default);

class pixelsort{
	
	sf::Image   image;
	sf::Texture texture;
	sf::Sprite  sprite;
	

	pixelsort(std::string filename){
		
		if(!image.loadFromFile(filename)){
			std::cerr << "Failed to load input image\n";
			
		}
			
	} 
	
};


int main(int argc, char* argv[]){

	if(argc != 3){
		std::cerr << "Usage : " << argv[0] << " infile.png outfile.png\n";
		return 0;
	}	

	while (window.isOpen())
        {
                sf::Event event;
                while (window.pollEvent(event))
                {
                        if (event.type == sf::Event::Closed)
                                window.close();
                        if (event.key.code == sf::Keyboard::Q)
                                window.close();
                }

                window.clear(sf::Color::Black);
                window.display();

        }


	return 0;
}
