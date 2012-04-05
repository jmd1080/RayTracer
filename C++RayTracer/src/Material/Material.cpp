#include "Material.h"
#include <math.h>
// --------------------------------------------------------assignment operator

Material::Material(void):
color(RGBColor(0)),
kl(0.7),
ks(0.0000001)
{}

Material::Material(const Material& material):
color(material.color)
{}

void
Material::set_color(RGBColor inColor)
{
	color = inColor;
}

void
Material::set_kl(float lamb)
{
	kl = lamb;
}

void
Material::set_ks(float spec)
{
	ks = spec;
}

// Returns the colour of the object based on the shade record
RGBColor
Material::shade(ShadeRec& sr)
{
	double I = sr.w.ambient*kl;
	// Get contribution from all lights
	int num_lights = sr.w.lights.size();

	for (int j = 0; j < num_lights; j++) {
		// Lambertian
		float Il = kl*sr.w.lights[j]->get_intensity(sr);

		// Specular
		double Is =  - Il*ks*pow(sr.w.lights[j]->get_rv(sr),27);

		I += Il + Is;
	}

	RGBColor result = color*I;

	result.cap();

	return result;
}

Material&
Material::operator= (const Material& rhs) {
	color = rhs.color;
	ks = rhs.ks;
	kl = rhs.kl;
	return (*this);
}
