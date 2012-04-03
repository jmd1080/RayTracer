#include "Material.h"
// --------------------------------------------------------assignment operator

Material::Material(void):
color(RGBColor(0))
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
	double ratio = sr.hit_point.z;
	RGBColor out = color * 1600/(ratio*ratio);
	return color;
}

Material&
Material::operator= (const Material& rhs) {
	color = rhs.color;
	return (*this);
}
