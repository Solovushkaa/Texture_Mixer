#pragma once

#include <SFML/Graphics.hpp>

class SizeError { };

inline void MixLayers(sf::Texture& newTexture, sf::Texture& red, sf::Texture& green, sf::Texture& blue)
{
	if (red.getSize() == green.getSize() && red.getSize() == blue.getSize())
	{
		sf::Image red_image = red.copyToImage();
		sf::Image green_image = green.copyToImage();
		sf::Image blue_image = blue.copyToImage();

		unsigned int ImageSize = red_image.getSize().x * red_image.getSize().y * 4;
		sf::Uint8* Pixels_arr = new sf::Uint8[ImageSize];

		unsigned int x = red.getSize().x, y = red.getSize().y;

		unsigned int counter = 0;
		for (unsigned int y_i = 0; y_i < y; ++y_i)
		{
			for (unsigned int x_i = 0; x_i < x; ++x_i)
			{
				sf::Uint8 red = red_image.getPixel(x_i, y_i).r;
				sf::Uint8 green = green_image.getPixel(x_i, y_i).g;
				sf::Uint8 blue = blue_image.getPixel(x_i, y_i).b;
				Pixels_arr[counter] = red; Pixels_arr[counter + 1] = green; Pixels_arr[counter + 2] = blue; Pixels_arr[counter + 3] = 255;
				counter += 4;
			}
		}
		newTexture.update(Pixels_arr);
		delete[] Pixels_arr;
	}
	else { throw SizeError(); }
}