#ifndef __LIGHT__
#define __LIGHT__

#include "../Utilities/ShadeRec.h"

class Light {
	public:

		Light(void);

		Light(float in);

		Light(const Light& light);

		// Set the intensity
	    virtual void
		set_intensity(float In) = 0;

	    // Returns the intensity given a shader record
	    virtual float
	    get_intensity(ShadeRec& sr) const = 0;

		virtual float
		get_rv(ShadeRec& sr) = 0;

	protected:

		Light&
		operator= (const Light& rhs);

};

#endif
