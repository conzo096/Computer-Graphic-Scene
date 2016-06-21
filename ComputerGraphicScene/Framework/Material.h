#pragma once
namespace BarnabusFramework
{
	class Material
	{
		// Material information for the model.
		glm::vec4 ambientColour; // Ambient colour of the lighting.
		glm::vec4 diffuseColour; // Diffuse colour of the lighting.
		glm::vec4 specularColour; // Specular colour of the lighting.
		float shininess; // How shiny the object is.
	public:
		Material();
		~Material();
		void SetAmbient(glm::vec4 amb) { ambientColour = amb; };
		void SetDiffuse(glm::vec4 diff) { diffuseColour = diff; };
		void SetSpecular(glm::vec4 spec) { specularColour = spec; };
		void SetShininess(float factor) { shininess = factor; };

		glm::vec4 GetAmbient() { return ambientColour; };
		glm::vec4 GetDiffuse() { return diffuseColour; };
		glm::vec4 GetSpecular() { return specularColour; };
		float GetShininess() { return shininess; };
	};
}
