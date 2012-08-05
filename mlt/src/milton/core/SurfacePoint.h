/**<!-------------------------------------------------------------------->
   @class  SurfacePoint
   @author Travis Fischer (fisch0920@gmail.com)
   @date   Fall 2008
   
   @brief
      Core class representing a single point on the surface of a Shape, 
   which was likely generated by either an intersection with a Ray or random 
   sampling on the surface of the shape.  SurfacePoint encapsulates all of the 
   different information about a surface point and is used for shading 
   evaluation (BSDF), emittance evaluation (Emitter), and so-called importance 
   evaluation (Sensor).
   
      Milton supports the useful distinction between geometric and shading 
   normals defined at a point, where the geometric normal 
   (SurfacePoint::normalG) is the actual normal of the underlying surface at a 
   point, and the shading normal (SurfacePoint::normalS) is a (possibly) 
   perturbed version of the geometric normal.  Shading normals attempt to 
   simulate more complex underlying geometry by varying the apparent normal 
   across the surface of a simpler surface such as a plane. It is important to 
   note that shading normals have no physical basic whatsoever -- they are 
   merely a useful (and very common) method for faking higher resolution (ie. 
   more expensive) geometry. See the bump mapping implementation in Material 
   for an example use of shading normals.
   
   @note
      When finding the closest intersection point between a Ray and a set of 
   objects in the scene, SurfacePoint is used to hold the 'current' closest 
   object and any metadata that shape may need to <b>lazily</b> fill in the 
   rest of the SurfacePoint structure later on (see Shape::initSurfacePoint).
   <!-------------------------------------------------------------------->**/

#ifndef SURFACE_POINT_H_
#define SURFACE_POINT_H_

#include <shapes/Triangle.h>
#include <materials/IndexOfRefraction.h>

#include <boost/shared_ptr.hpp>
#include <ostream>

namespace milton {

class  BSDF;
class  Emitter;
class  Sensor;
class  Shape;
struct Ray;

struct MILTON_DLL_EXPORT SurfacePoint : public SSEAligned {
   ///@name Surface data lazily filled in by Shape::initSurfacePoint
   //@{-----------------------------------------------------------------
   
   /// intersected shape
   Shape   *shape;
   
   /// world-space position
   Point3   position;
   
   /// geometric normal
   Vector3  normalG;
   
   /// shading normal (possibly a perturbed version of the geometric normal, 
   /// normalG)
   Vector3  normalS;
   
   /// UV coordinates
   UV       uv;
   
   
   //@}-----------------------------------------------------------------
   ///@name Material data evaluated lazily by Material::initSurfacePoint
   //@{-----------------------------------------------------------------
   
   /// reflectance
   BSDF    *bsdf;
   
   /// emittance
   Emitter *emitter;
   
   /// importance aka sensor response (for cameras)
   Sensor  *sensor;
   
   /// incident index of refraction
   real_t   ior1;
   
   /// exitent  index of refraction
   real_t   ior2;
   
   unsigned iorIndex;
   
   
   //@}-----------------------------------------------------------------
   ///@name Shape-specific, lazy-helper data
   //@{-----------------------------------------------------------------
   
   unsigned index;
   unsigned normalCase;
   
   
   //@}-----------------------------------------------------------------
   ///@name Constructors
   //@{-----------------------------------------------------------------
   
   inline SurfacePoint() 
      : shape(NULL), bsdf(NULL), emitter(NULL), sensor(NULL), 
        ior1(IndexOfRefraction::AIR), ior2(IndexOfRefraction::AIR), 
        iorIndex(0), normal(normalS)
   { }
   
   inline SurfacePoint(Shape *shape_, const Point3 &p0, const Point3 &p1)
      : shape(shape_), position(p1), normalG((p0 - p1).getNormalized()), 
        bsdf(NULL), emitter(NULL), sensor(NULL), 
        ior1(IndexOfRefraction::AIR), ior2(IndexOfRefraction::AIR), 
        iorIndex(0), normal(normalS)
   { }
   
   ~SurfacePoint();
   
   
   //@}-----------------------------------------------------------------
   ///@name Utility normal accessor
   //@{-----------------------------------------------------------------
   
   /**
    * @brief
    *    Convenience stand-in normal which plays nicely with shapes that 
    * don't support the concept of a normal (ex. point lights)
    */
   struct SurfacePointNormal {
      inline SurfacePointNormal(const Vector3 &normal)
         : hasNormal(true), m_normal(normal)
      { }
      
      /**
       * @brief
       *    If the associated SurfacePoint is defined at a point with a normal, 
       * will return the standard dot product of the given Vector3 @p v with 
       * its shading normal, normalS.  If the point does not have a normal 
       * (ex. point lights), this function will return 1.
       */
      inline real_t dot(const Vector3 &v) const {
         return (hasNormal ? m_normal.dot(v) : 1);
      }
      
      /// whether or not the underlying SurfacePoint has a surface normal
      bool hasNormal;
      
      private:
         const Vector3 &m_normal;
   } normal;
   
   
   //@}-----------------------------------------------------------------
   ///@name Initialization
   //@{-----------------------------------------------------------------
   
   /**
    * @brief 
    *    Initializes this point, assuming shape has already been 
    * filled in, in addition to any optional shape or material-specific 
    * utility data (index, normalCase)
    * 
    * @returns false if this point is invalid and can't be initialized
    *    (in the case of an invalid t-value)
    */
   bool init(const Ray &ray, real_t t);
   
   /**
    * @brief 
    *    Initializes this point, assuming shape/position have already been 
    * filled in, in addition to any optional shape or material-specific 
    * utility data (UV, index, normalCase)
    */
   void init();
   
   
   //@}-----------------------------------------------------------------
};

typedef boost::shared_ptr<SurfacePoint> SurfacePointPtr;

/// Prints a SurfacePoint to an output stream for debugging purposes
MILTON_DLL_EXPORT std::ostream &operator<<(std::ostream &os, const SurfacePoint &pt);

}

#endif // SURFACE_POINT_H_

