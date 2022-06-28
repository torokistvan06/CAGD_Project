#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"

using namespace cagd;
using namespace std;

GLdouble spiral_on_cone::u_min = -TWO_PI;
GLdouble spiral_on_cone::u_max = +TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
}

GLdouble circular_helix::u_min = 0;
GLdouble circular_helix::u_max = 6 * PI;

DCoordinate3 circular_helix::d0(GLdouble u)
{
   GLdouble c = cos(u), s = sin(u);
   return DCoordinate3(c, s, u / 2);
}

DCoordinate3 circular_helix::d1(GLdouble u)
{
   GLdouble c = cos(u), s = sin(u);
   return DCoordinate3(-s, c, 1 / 2);
}

DCoordinate3 circular_helix::d2(GLdouble u)
{
   GLdouble c = cos(u), s = sin(u);
   return DCoordinate3(-c, -s, 0);
}

GLdouble rose::u_min = 0.0;
GLdouble rose::u_max = TWO_PI;
GLdouble rose::k = 5.0;

DCoordinate3 rose::d0(GLdouble u)
{
    GLdouble  c = cos(u), s = sin(u), ck = cos(k * u);
    return DCoordinate3(ck * c, ck * s, u);
}

DCoordinate3 rose::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u),  sk = sin(k * u), ck = cos(k * u);
    return DCoordinate3(-k * sk * c - ck * s, -k* sk *s + ck * c, 1.0);
}

DCoordinate3 rose::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), sk = sin(k * u), ck = cos(k * u);
    return DCoordinate3(-k * k * ck * c - k * sk * s - (-k * sk * s + ck * c),
                        -k * k * ck * s - k * sk * c - k * sk * c - ck * s,
                        0.0);
}

GLdouble torus_knot::u_min = 0.0;
GLdouble torus_knot::u_max = 6 * PI;

DCoordinate3 torus_knot::d0(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), c2 = cos(2.0 * u / 3.0), s2 = sin(2.0 * u / 3.0);
    return DCoordinate3((2.0 + c2) * c, (2.0 + c2) * s, s2);
}

DCoordinate3 torus_knot::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u) , c2 = cos(2.0*u/3.0), s2 = sin(2.0*u/3.0);
    return DCoordinate3((2.0 + c2) * (-s) - ((2.0 / 3.0) * s2) * c, (2.0 + c2) * c - (2.0 / 3.0 * s2) * s, (2.0 / 3.0) * c2);
}

DCoordinate3 torus_knot::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), c2 = cos(2.0*u/3.0), s2 = sin(2.0*u/3.0);
    return DCoordinate3((2.0 / 3.0 * s2) * s - (2.0 + c2) * c - (((4.0 / 9.0) * c2) * c - ((2.0 / 3.0) * s2) * s),
                        ((2.0 / 3.0 * s2) * (-c) - (2.0 + c2) * s) - ((4.0 / 9.0 * c2) * s + (2.0 / 3.0 * s2) * c),
                        -(4.0 / 9.0) * s2);
}

GLdouble cyclo::u_min = 0.0;
GLdouble cyclo::u_max = 6 * PI;

DCoordinate3 cyclo::d0(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(2.0 * (u - s), 2.0 * (1.0 - c), u);
}

DCoordinate3 cyclo::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(2.0 * (1.0 - c), 2.0 * s, 1.0);
}

DCoordinate3 cyclo::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(s, 2.0 * c, 0.0);
}

GLdouble spherical_sinusoid::u_min = 0.0;
GLdouble spherical_sinusoid::u_max = TWO_PI;
GLdouble spherical_sinusoid::k = 0.5;
GLdouble spherical_sinusoid::n = 10;

DCoordinate3 spherical_sinusoid::d0(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), cn = cos(n * u);
    return DCoordinate3(c / sqrt(1 + pow(k,2) + pow(cn,2)),
                        s / sqrt(1 + pow(k,2) + pow(cn,2)),
                        k * cn / sqrt(1 + pow(k,2) + pow(cn,2)));
}

DCoordinate3 spherical_sinusoid::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), cn = cos(n * u), sn = sin(n * u);
    return DCoordinate3((n* c * cn * sn - s *(pow(cn,2) + pow(k,2) + 1))/pow((pow(cn,2) + pow(k,2) + 1),(3/2)),
                         (n * s * cn * sn + c * pow(cn,2) +(pow(k,2)+1) * c)/pow((pow(cn,2)+pow(k,2)+1),(3/2)),
                         -((pow(k,3)+k)*n*sn)/ pow((pow(cn,2) + pow(k,2) + 1),(3/2)));
}

DCoordinate3 spherical_sinusoid::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), cn = cos(n * u), sn = sin(n * u);
    return 0.02 * DCoordinate3(-(2 * n * s * cn *(pow(cn,2) + pow(k,2) +1)* sn +(pow(n,2) + 1) * c * pow(cn,4) - 2 * ((pow(k,2)+2) * pow(n,2) - pow(k,2) -1)*c * pow(cn,2) +(pow(k,2) + 1)*(pow(n,2) + pow(k,2) + 1)* c)/pow((pow(cn,2) + pow(k,2)+1),(5/2)),
                         (2 * n * c * cn * pow(cn,2) + pow(k,2) * sn -(pow(n,2) + 1) * s * pow(cn,4) + 2 * ((pow(k,2) + 2)* pow(n,2) - pow(k,2) - 1)*s * pow(cn,2) -(pow(k,2) + 1)*(pow(n,2) + pow(k,2) +1)* s)/pow((pow(cn,2) + pow(k,2)+1),(5/2)),
                          -(k*(pow(k,2) + 1) * pow(n,2) * cn *(3 * pow(sn,2) + pow(cn,2) + pow(k,2) + 1))/pow((pow(cn,2)+ pow(k,2) +1),(5/2)));
}

GLdouble clelia::u_min = 0.0;
GLdouble clelia::u_max = 6 * PI;
GLdouble clelia::R = 0.5;
GLdouble clelia::n = 5;

DCoordinate3 clelia::d0(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), cn = cos(n * u), sn = sin(n * u);
    return DCoordinate3(R * cn * c,
                        R * cn * s,
                        R * sn);
}

DCoordinate3 clelia::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), cn = cos(n * u), sn = sin(n * u);
    return DCoordinate3(-R * (n * c * sn + s * cn),
                        -R * (n * s * sn - c * cn),
                        R * n * cn);
}

DCoordinate3 clelia::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), cn = cos(n * u), sn = sin(n * u);
    return 0.1 * DCoordinate3(R * (2 * n * s * sn +(-pow(n,2) - 1) * c * cn),
                        -R * (2 * n * c * sn +(pow(n,2) + 1) * s * cn),
                        -R * pow(2,n) * sn);
}

GLdouble basin::u_min = 0.0;
GLdouble basin::u_max = PI;
GLdouble basin::n = 10;
GLdouble basin::a = 2;
GLdouble basin::b = 2;

DCoordinate3 basin::d0(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), cn = cos(n * u);
    return DCoordinate3(a * c * cn,
                        a * s * cn,
                        b * pow(cn,2));
}

DCoordinate3 basin::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), cn = cos(n * u), sn = sin(n * u);
    return DCoordinate3(-a * (n * c * sn + s * cn),
                        -a * (n * s * sn -  c * cn),
                        -2 * b * n * cn * sn);
}

DCoordinate3 basin::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u), cn = cos(n * u), sn = sin(n * u);
    return 0.1* DCoordinate3(a * (2 * n * s * sn +(-pow(n,2) - 1)* c * cn),
                        -a * (2 * n *  c * sn +(pow(n,2) + 1) * s * cn),
                        2 * b * pow(n,2) * (pow(sn,2) - pow(cn,2)));
}


// Surfaces

//Surface Torus
GLdouble surface_torus::u_min = 0;
GLdouble surface_torus::u_max = TWO_PI;
GLdouble surface_torus::v_min = 0;
GLdouble surface_torus::v_max = TWO_PI;
GLdouble surface_torus::r = 1;
GLdouble surface_torus::R = 2;

DCoordinate3 surface_torus::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(r*sin(v),  (R + r * cos(v)) * cos(u), (R + r * cos(v)) * sin(u));
}

DCoordinate3 surface_torus::d01(GLdouble u, GLdouble v)
{
     return DCoordinate3(0.0, (R + r * cos(v)) * sin(u), (R + r * cos(v)) * -cos(u));
}

DCoordinate3 surface_torus::d10(GLdouble u, GLdouble v)
{
     return DCoordinate3(r*cos(v), (0 - r * sin(v)) * cos(u), (0 - r * sin(v)) * sin(u));
}

GLdouble curve_on_surface_torus::u_min = 0;
GLdouble curve_on_surface_torus::u_max = TWO_PI;
GLdouble curve_on_surface_torus::r = 1;
GLdouble curve_on_surface_torus::R = 2;

DCoordinate3 curve_on_surface_torus::d0(GLdouble u)
{
    return DCoordinate3(r * sin(2 * u), (R + r * cos(2 * u)) * sin(u), (R + r * cos(2 * u)) * cos(u));
}

DCoordinate3 curve_on_surface_torus::d1(GLdouble u)
{
    return DCoordinate3(2 * r * cos(2 * u), cos(u)*(r*cos(2*u)+R)-2*r*sin(u)*sin(2*u), -2*r*cos(u)*sin(2*u)-sin(u)*(r*cos(2*u)+R));
}

DCoordinate3 curve_on_surface_torus::d2(GLdouble u)
{
    return DCoordinate3(-4*r*sin(2*u), -4*r*cos(u)*sin(2*u)-5*r*sin(u)*cos(2*u)-R*sin(u), 4*r*sin(u)*sin(2*u)-5*r*cos(u)*cos(2*u)-R*cos(u));
}

// Sphere


GLdouble surface_sphere::v_min = 0;
GLdouble surface_sphere::v_max = TWO_PI;
GLdouble surface_sphere::u_min = EPS;
GLdouble surface_sphere::u_max = PI-EPS;

DCoordinate3 surface_sphere::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(sin(u)*cos(v), sin(u) * sin(v), cos(u));
}
DCoordinate3 surface_sphere::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(u)*cos(v), cos(u) * sin(v), -sin(u));
}
DCoordinate3 surface_sphere::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-sin(u)*sin(v), sin(u) * cos(v), 0.0);
}

GLdouble curve_on_surface_sphere::u_min = 0;
GLdouble curve_on_surface_sphere::u_max = PI;

DCoordinate3 curve_on_surface_sphere::d0(GLdouble u)
{
    return DCoordinate3(sin(u) * cos(3 * u / 4), sin(u) * sin(3 * u / 4), cos(u));
}

DCoordinate3 curve_on_surface_sphere::d1(GLdouble u)
{
    return DCoordinate3(cos((3*u)/4)*cos(u)-(3*sin((3*u)/4)*sin(u))/4, (3*cos((3*u)/4)*sin(u))/4+sin((3*u)/4)*cos(u), -sin(u));
}

DCoordinate3 curve_on_surface_sphere::d2(GLdouble u)
{
    return DCoordinate3(-(25*cos((3*u)/4)*sin(u)+24*sin((3*u)/4)*cos(u))/16, -(25*sin((3*u)/4)*sin(u)-24*cos((3*u)/4)*cos(u))/16, -cos(u));
}
// Cylindre

GLdouble surface_cylindre::v_min = -PI;
GLdouble surface_cylindre::v_max = 3 * PI;
GLdouble surface_cylindre::u_min = EPS;
GLdouble surface_cylindre::u_max = 2 * TWO_PI-EPS;
GLdouble surface_cylindre::R = 1;

DCoordinate3 surface_cylindre::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(R * cos(u - v), R * sin(u - v), u + v);
}

DCoordinate3 surface_cylindre::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(-R * sin(u - v), R * cos(u - v), 1);
}

DCoordinate3 surface_cylindre::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-R * sin(v - u), -R * cos(v - u), 1);
}


GLdouble curve_on_surface_cylindre::u_min = 0;
GLdouble curve_on_surface_cylindre::u_max = 2 * TWO_PI;
GLdouble curve_on_surface_cylindre::R = 1;

DCoordinate3 curve_on_surface_cylindre::d0(GLdouble u)
{
    return DCoordinate3(R * cos(u - sin(u)), R * sin(u - sin(u)), u + sin(u));
}

DCoordinate3 curve_on_surface_cylindre::d1(GLdouble u)
{
    return DCoordinate3(-R*(cos(u)-1)*sin(sin(u)-u), -R*(cos(u)-1)*cos(sin(u)-u), cos(u)+1);
}

DCoordinate3 curve_on_surface_cylindre::d2(GLdouble u)
{
    return DCoordinate3(R*(sin(u)*sin(sin(u)-u)-pow((cos(u)-1),2) *cos(sin(u)-u)) , R*pow((cos(u)-1),2)*sin(sin(u)-u)+R*sin(u)*cos(sin(u)-u), -sin(u));
}

// Bohemian dome

GLdouble surface_bohemian_dome::v_min = 0;
GLdouble surface_bohemian_dome::v_max = TWO_PI;
GLdouble surface_bohemian_dome::u_min = 0;
GLdouble surface_bohemian_dome::u_max = TWO_PI;
GLdouble surface_bohemian_dome::a = 3;
GLdouble surface_bohemian_dome::b = 2;

DCoordinate3 surface_bohemian_dome::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(a * cos(u), b * cos(v), a * sin(u) + b * sin(v));
}

DCoordinate3 surface_bohemian_dome::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(-a * sin(u), 0, a * cos(u));
}

DCoordinate3 surface_bohemian_dome::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(0, -b * sin(v), b * cos(v));
}

// Cone sinusoid

GLdouble surface_cone_sinusoid::v_min = 0;
GLdouble surface_cone_sinusoid::v_max = TWO_PI;
GLdouble surface_cone_sinusoid::u_min = 0;
GLdouble surface_cone_sinusoid::u_max = TWO_PI;
GLdouble surface_cone_sinusoid::k = 1;
GLdouble surface_cone_sinusoid::n = 8;

DCoordinate3 surface_cone_sinusoid::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(u * cos(v), u * sin(v), k * u * cos(n * v));
}

DCoordinate3 surface_cone_sinusoid::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(v), sin(v), k * cos(n * v));
}

DCoordinate3 surface_cone_sinusoid::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-u * sin(v), u * cos(v), -k * n * u * sin(n * v));
}


// Helicoid

GLdouble surface_helicoid::u_min = 0;
GLdouble surface_helicoid::u_max = TWO_PI;
GLdouble surface_helicoid::v_min = 0;
GLdouble surface_helicoid::v_max = TWO_PI;

DCoordinate3 surface_helicoid::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(u*cos(v),u*u,u*sin(v));
}
DCoordinate3 surface_helicoid::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(v),2*u,sin(v));
}
DCoordinate3 surface_helicoid::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-u*sin(v),0,u*cos(v));
}

GLdouble curve_on_surface_helicoid::u_min = 0;
GLdouble curve_on_surface_helicoid::u_max = TWO_PI;

DCoordinate3 curve_on_surface_helicoid::d0(GLdouble u)
{
    return DCoordinate3(u * cos(2 * u), u * u, u * sin(2 * u) );
}

DCoordinate3 curve_on_surface_helicoid::d1(GLdouble u)
{
    return DCoordinate3(cos(2*u)-2*u*sin(2*u) , 2 * u, sin(2*u)+2*u*cos(2*u));
}

DCoordinate3 curve_on_surface_helicoid::d2(GLdouble u)
{
    return DCoordinate3(-4*(sin(2*u)+u*cos(2*u)) , 2, -4*(u*sin(2*u)-cos(2*u)));
}
