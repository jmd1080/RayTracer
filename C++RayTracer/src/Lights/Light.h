#ifndef __LIGHT__
#define __LIGHT__

#include "../Utilities/ShadeRec.h"

class Light {
	public:

		Light(void);

		Light(const Light& light);

		// Set the intensity
	    void
		set_intensity(float In);

	    // Returns the intensity given a shader record
	    virtual float
	    get_intensity(ShadeRec& sr) const = 0;

	protected:

		Light&
		operator= (const Light& rhs);

	private:
		float Il;
};

#endif
