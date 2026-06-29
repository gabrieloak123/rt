#ifndef VISIBILITY_TESTER_HPP
#define VISIBILITY_TESTER_HPP

#include "common.hpp"
#include "surfel.hpp"

namespace rt{

    class Scene;
    
    class VisibilityTester {
        private:
            Surfel p0, p1;    //< Test visibility between p0 and p1.
            Vec3 direction;   //< Direction to test visibility from p0.
            bool is_infinity; //< Infinity flag
        public:
            VisibilityTester() = default;
            VisibilityTester( const Surfel&, const Surfel& );
            VisibilityTester( const Surfel&, const Vec3&); // For directional
            bool unoccluded( const Scene& scene );
        
        };

}


#endif //< VISIBILITY_TESTER_HPP