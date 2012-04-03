#include "Material.h"
// --------------------------------------------------------assignment operator

Material::Material(void):
color(RGBColor(0))
{}

Material::Material(const Material& material):
				color(material.color)
{}

// Returns the colour of the object based on the shade record
RGBColor
Material::shade(ShadeRec& sr)
{
	return color;
}

Material&
Material::operator= (const Material& rhs) {
	color = rhs.color;
	return (*this);
}
