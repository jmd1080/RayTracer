#include "Material.h"
#include <math.h>
// --------------------------------------------------------assignment operator

Material::Material(void):
color(RGBColor(0)),
kl(0.7),
ks(0.0000001),
opacity(1)
{}

Material::Material(const Material& material):
color(material.color),
kl(material.kl),
ks(material.ks),
opacity(material.opacity)
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

void
Material::set_opacity(float op)
{
	opacity = op;
	if (opacity > 1)
		opacity = 1;
}

// Returns the colour of the object based on the shade record
RGBColor
Material::shade(ShadeRec& sr)
{
	RGBColor I = sr.w.ambient*kl;
	// Get contribution from all lights
	int num_lights = sr.w.lights.size();

	for (int j = 0; j < num_lights; j++) {
		// Lambertian
		RGBColor Il = kl*sr.w.lights[j]->get_intensity(sr);

		// Specular
		RGBColor Is =  Il*ks*pow(sr.w.lights[j]->get_rv(sr),27);

		if (Il.r < 0 || Il.g < 0 || Il.b < 0)
			Il = RGBColor(0);
		if (Is.r < 0 || Is.g < 0 || Is.b < 0)
			Is = RGBColor(0);

		I += Il + Is;
	}

	RGBColor result = color*I;

	if (opacity != 1)
	{
		Ray transRay;
		transRay.o = sr.local_hit_point;
		transRay.d = -1*(sr.ray.o - sr.local_hit_point);
		RGBColor trans = sr.w.tracer_ptr->trace_ray(transRay); // TODO weird color rounding error, trans is wrong!
		result = opacity*result + (1-opacity)*trans;
	}

	result.cap();

	return result;
}

double
Material::get_opacity()
{
	return opacity;
}

Material&
Material::operator= (const Material& rhs) {
	color = rhs.color;
	ks = rhs.ks;
	kl = rhs.kl;
	return (*this);
}
