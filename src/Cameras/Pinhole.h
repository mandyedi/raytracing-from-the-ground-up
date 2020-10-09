#ifndef __PINHOLE__
#define __PINHOLE__


#include "Point2D.h"
#include "World.h"


class Pinhole: public Camera {
	public:
	
		Pinhole();   							

		Pinhole(const Pinhole& ph);	
		
		virtual Camera*						
		clone(void) const;			

		Pinhole& 							
		operator= (const Pinhole& rhs);	
		
		virtual
		~Pinhole();   						
			
		void
		set_view_distance(const float vpd);
		
		void
		set_zoom(const float zoom_factor);
		
		Vector3D								
		get_direction(const Point2D& p) const;
		
		virtual void 												
		render_scene(const World& w);
		
	private:
			
		float	d;		// view plane distance
		float	zoom;
		
};





inline void
Pinhole::set_view_distance(float _d) {
	d = _d;
}	
	



inline void
Pinhole::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}	

#endif