#ifndef __LIGHT__
#define __LIGHT__

#include "../Utilities/ShadeRec.h"


class Light {
	public:

		Light(void);

		Light(const Light& light);

		// Set the intensity
	    virtual void
		set_intensity(RGBColor In) = 0;

	    // Returns the intensity given a shader record
	    virtual RGBColor
	    get_intensity(ShadeRec& sr) const = 0;

		virtual float
		get_rv(ShadeRec& sr) = 0;

	protected:

		Light&
		operator= (const Light& rhs);

};

#endif
