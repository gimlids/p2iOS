#ifndef P2IOS_H_
#define P2IOS_H_

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <boost/shared_ptr.hpp>

#define P2IOS_MAIN \
int main(int argc, char** argv) { \
   printf("p2iOS says hello world!\n"); \
   return 0; \
}

namespace p2iOS
{

   int width;
   int height;

   template <class T>
   class JavaArray
   {
   public:

      JavaArray(const size_t & size = 0) {
         shared_vector = new std::vector< boost::shared_ptr< T > >(size);
         shared_reference_count = new size_t(1);
      };

      // does the default operator= call this?
      JavaArray(const JavaArray & other) {
         shared_vector = other.shared_vector;
         (*shared_reference_count)++;
      };

      ~JavaArray() {
         (*shared_reference_count)--;
         if(*shared_reference_count == 0)
            delete(shared_vector);
      };


      T & operator[](const size_t & index) {
         return * (*shared_vector)[index];
      };

   private:
      // TODO put this stuff in a higher level automatic reference counting class
      std::vector< boost::shared_ptr< T > > *shared_vector;
      size_t *shared_reference_count;
   };


   //==========================================
   // initialization functions
   //==========================================

   /* TODO: http://processing.org/reference/size_.html
   size(width, height, MODE)
   */
   void size(int width, int height)
   {
#warning processing code uses size(width, height) but this is not yet implemented in p2iOS
   };

   //===========================================
   // math
   //===========================================

   float sqrt(float value)
   {
      return sqrtf(value);
   };

   float atan2(float y, float x)
   {
      return atan2(y, x);
   };

   float cos(float angle)
   {
      return cos(angle);
   };

   float sin(float angle)
   {
      return sin(angle);
   };

   float random(float low, float high)
   {
#warning processing code uses random() but this is not yet implemented in p2iOS
   };

   float random(float high)
   {
      return random(0, high);
   };

   // =======================================
   // functions that take colors
   // =======================================

   /* TODO http://processing.org/reference/fill_.html
   fill(gray)
   fill(value1, value2, value3)
   fill(value1, value2, value3, alpha)
   fill(color)
   fill(color, alpha)
   fill(hex)
   fill(hex, alpha)
   */
   void fill(unsigned char gray, unsigned char alpha)
   {
#warning processing code uses fill(gray, alpha) but this is not yet implemented in p2iOS
   };

   /* TODO http://processing.org/reference/background_.html
   background(gray, alpha)
   background(value1, value2, value3)
   background(value1, value2, value3, alpha)
   background(color)
   background(color, alpha)
   background(hex)
   background(hex, alpha)
   */
   void background(unsigned char gray)
   {
#warning processing code uses background(gray) but this is not yet implemented in p2iOS
   };

   //=========================================
   // drawing state functions
   //=========================================

   void noStroke()
   {
#warning processing code uses noStroke() but this is not yet implemented in p2iOS
   };

   // TODO http://processing.org/reference/smooth_.html
   void smooth()
   {
#warning processing code uses smooth() but this is not yet implemented in p2iOS
   };

   //==========================================
   // drawing functions
   //==========================================

   void ellipse(float x, float y, float width, float height)
   {
#warning processing code uses ellipse(x, y, width, height) but this is not yet implemented in p2iOS
   }



}

#endif
