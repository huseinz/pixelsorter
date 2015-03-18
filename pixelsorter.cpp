#include <SFML/Graphics.hpp>
#include <iostream>


struct IOError{};
sf::RenderWindow window;
sf::Image   image;
sf::Texture image_tx;
sf::Sprite  image_sprite;
std::string infile;
std::string outfile;

bool init(std::string in, std::string out){
	
	if(!image.loadFromFile(in)){
		std::cerr << "Failed to load input image\n";
		return false;
	}
	if(!image.saveToFile(out)){
		std::cerr << "Failed to write output image\n";
		return false;
	}

	window.create(	sf::VideoMode(image.getSize().x, image.getSize().y),
			"pixel sorter", sf::Style::Default);
	
	infile = in;
	outfile = out;
	return true;
} 

bool writeImage(){
	if(image.saveToFile(outfile))
		return true;
	std::cerr << "Failed to write output image\n";
	return false;
}


int main(int argc, char* argv[]){

	if(argc != 3){
		std::cerr << "Usage : " << argv[0] << " infile.png outfile.png\n";
		return 0;
	}	

	if(!init(argv[1], argv[2]))
		return 0;

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
