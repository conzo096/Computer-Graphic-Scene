/* Lighting class done by Conner Weatherston. Last edited: 15/06/2016.
   This class contains the variables and methods required for simple, directional lighting. 
 * Also this class is designed to be a base class for the more complicated lighting structures.
 */

#pragma once
class Lighting
{
private:
	glm::vec3 direction; // The direction of the lighting.
	glm::vec4 colour; // Colour of the lighting.
	glm::vec4 intensity;// Intensity of the colour spectrum. What colour it leans more towards. Better name?
public:
	Lighting();
	~Lighting();
	void SetDirection(glm::vec3 dir) { direction = dir; };
	void SetColour(glm::vec4 col) { colour = col; };
	void SetIntensity(glm::vec4 bias) { intensity = bias; };
	glm::vec3 GetDirection() { return direction; };
	glm::vec4 GetColour() { return colour; };
	glm::vec4 GetIntensity() { return intensity; };
};

