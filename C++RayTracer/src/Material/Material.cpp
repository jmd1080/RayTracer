#include "Material.h"
#include <math.h>
// --------------------------------------------------------assignment operator

Material::Material(void):
color(RGBColor(0)),
kl(0.7),
ks(0.000001),
opacity(1),
kr(0)
{}

Material::Material(const Material& material):
color(material.color),
kl(material.kl),
ks(material.ks),
opacity(material.opacity),
kr(kr)
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
Material::set_kr(float reflect)
{
	kr = reflect;
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

		//Is = RGBColor(0);
		//Il = RGBColor(0);

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

	if (kr > 0 && sr.depth < MAX_DEPTH)
	{
		Ray reflectRay;
		reflectRay.o = sr.local_hit_point;

		// R = E – 2.0 * (N.E) * N

		reflectRay.d = sr.ray.d - (2 * (sr.normal * sr.ray.d) * sr.normal);
		RGBColor reflect = sr.w.tracer_ptr->trace_ray(reflectRay,sr.depth+1);
		result += kr*reflect;
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
