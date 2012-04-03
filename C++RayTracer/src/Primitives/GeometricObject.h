#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

//class Material;
	
#include "../Utilities/Point3D.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"


//----------------------------------------------------------------------------------------------------- Class GeometricObject

class GeometricObject {	
	
	public:	

		GeometricObject(void);									// default constructor
		
		GeometricObject(const GeometricObject& object);			// copy constructor
	
		virtual GeometricObject*								// virtual copy constructor
		clone(void) const = 0;

		virtual 												// destructor
		~GeometricObject (void);	
			
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
				
		int
		get_material(void) const;

		Material*
		get_material_ptr(void) const;

		void
		set_material(int);

		void
		set_material_ptr(Material*);

	
	protected:
	
		mutable Material*   material_ptr;   	// mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const
	
		int material;

		GeometricObject&						// assignment operator
		operator= (const GeometricObject& rhs);
};


// ------------------------------------------------------------------------- get_material

inline int
GeometricObject::get_material(void) const {
	return (material);
}


inline Material* 
GeometricObject::get_material_ptr(void) const {
	return (material_ptr);
}

#endif
