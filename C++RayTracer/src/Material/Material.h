#ifndef __MATERIAL__
#define __MATERIAL__

#include "../World/World.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"

class Material {
	public:

		Material(void);

		Material(const Material& material);

		// Returns the colour of the object based on the shade record
	    RGBColor
		shade(ShadeRec& sr);

	    void
	    set_ks(float spec);

	    void
	    set_kl(float lamb);

	    void
	    set_color(RGBColor color);

	    void
	    set_opacity(float op);


	protected:

		Material&
		operator= (const Material& rhs);

	private:
		RGBColor color;
		float kl; // lambertian reflection coefficient
		float ks; // specular reflection coefficient
		float opacity; // transparency coefficient
};

#endif
