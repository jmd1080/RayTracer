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

	protected:

		Material&
		operator= (const Material& rhs);

	private:
		RGBColor color;
};

#endif
