#ifndef __MATERIAL__
#define __MATERIAL__

#include "../World/World.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"

const double	DEFAULT_KR	=	0.0;
const double	DEFAULT_KS	=	0.0000003;
const double	DEFAULT_KL	=	0.7;



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
	    set_kr(float reflect);

	    void
	    set_color(RGBColor color);

	    void
	    set_opacity(float op);

	    double
	    get_opacity();


	protected:

		Material&
		operator= (const Material& rhs);

	private:
		RGBColor color;
		float kl; // lambertian reflection coefficient
		float ks; // specular reflection coefficient
		float opacity; // transparency coefficient
		float kr; // reflection coefficient
};

#endif
