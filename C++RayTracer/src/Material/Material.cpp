#include "Material.h"
// --------------------------------------------------------assignment operator

Material::Material(void):
color(RGBColor(0)),
ka(1)
{}

Material::Material(const Material& material):
color(material.color)
{}

void
Material::set_color(RGBColor inColor)
{
	color = inColor;
}

// Returns the colour of the object based on the shade record
RGBColor
Material::shade(ShadeRec& sr)
{
	float I = sr.w.ambient*ka;
	return color*I;
}

Material&
Material::operator= (const Material& rhs) {
	color = rhs.color;
	ka = rhs.ka;
	return (*this);
}
