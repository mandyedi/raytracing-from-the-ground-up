### Dev Guide

The following description is based on some suggestion from the book. Follow them please, even if there is a better solution.

* Floats or Doubles

    Use doubles for all ray-object intersection calculations.
    List of classes that use double:
    
    `GeometricObject` and all descendant. `Matrix, Normal, Point3D, Vector3D, ShadeRec`

    Use floats for shading calculation.
    List of classes that use float:
    
    `BRDF, Camera, Light, Material, Point2D, RGBColor, ViewPlane` 

### Styleguide

Style guide is based on chapter 1.10 Coding Style. Any other guide that is listed below is based on the already implemented source code. For readability and consistency follow the suggested coding style please.

* Identifiers

    * Class names start with uppercase and subsequent words start with uppercase.
    ```cpp
    class Sphere;
    class GeometricObject;
    ```
    * Member function name and data members are lower case and subsequent words are separated by underscore.
    ```cpp
    RGBColor	
    trace_ray(const Ray& ray) const;

    class Sphere: public GeometricObject {
        private:
            Point3D center;
    };
    ```
    * Pointer names end with `_ptr`
    ```cpp
    Sphere* sphere_prt = new Sphere;
    ```
    * Setter functions and function that modify data members contain the data member name after an underscore
    ```cpp
    inline void
    Matte::set_cd(const RGBColor c) {
        ambient_brdf->set_cd(c);
        diffuse_brdf->set_cd(c);
    }

    void
    Camera::compute_uvw(void) {
        // implementation
    }
    ```

* Data Types

    In the original source code every classes implements their own copy constructor, assignment operator, and destructor even if they don't allocate memory dynamically. In the book it is a recommendation but not a necessity (chapter 1.10.2).
    Follow this for consistency please.
    ```cpp
    Ray::Ray (const Ray& ray)
	: 	o(ray.o), 
		d(ray.d) 
    {}

    Ray& 
    Ray::operator= (const Ray& rhs) {
        
        if (this == &rhs)
            return (*this);
            
        o = rhs.o; 
        d = rhs.d; 

        return (*this);	
    }

    Ray::~Ray (void) {}
    ```

* Encapsulation
    
    As the book specifies "Class members are generally private or protected, but there are exceptions based on their frequency of access."
    
    The following classes' data members are public: `BBox, Matrix, Normal, Point3D, Ray, RGBColor, ShadeRec, Vector3D, ViewPlane, World`

* Function Signatures
    
    The author suggest that we should avoid temporarily constructed parameters like the example below.
    ```cpp
    void
    Matter::set_cd(const RGBColor& c);

    matter_ptr->set_cd(RGBColor(r, g, b));
    ```
    Instead we should use a less object-oriented signature:
    ```cpp
    void
    Matte::set_cd(float r, float g, float b);

    matte_ptr->set_cd(r, g, b);
    ```

* Pure Virtual and Virtual Functions
    
    Declare a function pure virtual in the base class if it has to be defined for every derived class.
    Otherwise declare a function as virtual in the base class and also define it here. It can do nothing or return a default value.

* File Structure

    Put each class declaration in a header file (`Sphere.h`) and put the class definition in a separate file (`Sphere.cpp`).
    To prevent it being included more than once use include guard.
    ```cpp
    #ifndef __SPHERE__
    #define __SPHERE__
    #include "GeometricObject.h"
    class Sphere: public GeometricObject {
        // data member and member function declarations...
    };
    #endif
    ``` 

