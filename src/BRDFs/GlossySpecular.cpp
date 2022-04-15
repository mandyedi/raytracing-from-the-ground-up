//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


#include "../BRDFs/GlossySpecular.h"
#include "../Samplers/MultiJittered.h"



GlossySpecular::~GlossySpecular(void) {
    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
}



GlossySpecular::GlossySpecular(const GlossySpecular& gs)
    :   BRDF(gs),
        ks(gs.ks),
        cs(gs.cs),
        exp(gs.exp)
{
    sampler_ptr = gs.sampler_ptr->clone();
}



GlossySpecular::GlossySpecular(GlossySpecular&& gs) noexcept
    :   BRDF(std::move(gs)),
        ks(std::exchange(gs.ks, 0.0f)),
        cs(std::move(gs.cs)),
        exp(std::exchange(gs.exp, 0.0f)),
        sampler_ptr(std::exchange(gs.sampler_ptr, nullptr))
{}



GlossySpecular&
GlossySpecular::operator= (const GlossySpecular& gs) {
    BRDF::operator= (gs);

    ks          = gs.ks;
    cs          = gs.cs;
    exp         = gs.exp;
    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
    }
    sampler_ptr = gs.sampler_ptr->clone();

    return *this;
}

GlossySpecular&
GlossySpecular::operator= (GlossySpecular&& gs) noexcept {
    BRDF::operator= (std::move(gs));

    ks  = std::exchange(gs.ks, 0.0f);
    cs  = std::move(gs.cs);
    exp = std::exchange(gs.exp, 0.0f);

    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
    }
    sampler_ptr = gs.sampler_ptr;
    gs.sampler_ptr = nullptr;

    return *this;
}



GlossySpecular*
GlossySpecular::clone (void) const {
    return (new GlossySpecular(*this));
}



void
GlossySpecular::set_sampler(Sampler* sp, const float exp) {
    sampler_ptr = sp;
    sampler_ptr->map_samples_to_hemisphere(exp);
}



void
GlossySpecular::set_samples(const int num_samples, const float exp) {
    sampler_ptr = new MultiJittered(num_samples);
    sampler_ptr->map_samples_to_hemisphere(exp);
}



// no sampling here: just use the Phong formula
// this is used for direct illumination only
RGBColor
GlossySpecular::f(const ShadeRec &sr, const Vector3D &wo, const Vector3D &wi) const {
    RGBColor    L;
    double      ndotwi = sr.normal * wi;
    Vector3D    r(-wi + 2.0 * sr.normal * ndotwi); // mirror reflection direction
    double      rdotwo = r * wo;

    if (rdotwo > 0.0) {
        L = ks * cs * pow(rdotwo, exp);
    }

    return (L);
}



// this is used for indirect illumination
RGBColor
GlossySpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {

    double ndotwo = sr.normal * wo;
    Vector3D r = -wo + 2.0 * sr.normal * ndotwo;     // direction of mirror reflection

    Vector3D w = r;
    Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
    u.normalize();
    Vector3D v = u ^ w;

    Point3D sp = sampler_ptr->sample_hemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w;            // reflected ray direction

    if (sr.normal * wi < 0.0) {                     // reflected ray is below tangent plane
        wi = -sp.x * u - sp.y * v + sp.z * w;
    }

    float phong_lobe = pow(r * wi, exp);
    pdf = phong_lobe * (sr.normal * wi);

    return (ks * cs * phong_lobe);
}



RGBColor
GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const {
    return (RGBColor::black);
}
