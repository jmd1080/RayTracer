#include "Material.h"
// --------------------------------------------------------assignment operator

Material&
Material::operator= (const Material& rhs) {
	color = rhs.color;
	return (*this);
}
