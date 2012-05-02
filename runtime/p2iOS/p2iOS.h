#ifndef P2IOS_H_
#define P2IOS_H_

#include <vector>
#include <math.h>

#include <tr1/memory>

#include <ofMain.h>
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

#define P2IOS_MAIN \
int main(int argc, char** argv) { \
   printf("p2iOS says hello world!\n"); \
   ofSetupOpenGL(1024,768, OF_FULLSCREEN); \
   ofRunApp(new p2iOS::p2iOSApp()); \
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
       ofSetWindowShape(width, height);
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
       return low + (high - low) * (float)rand()/(float)RAND_MAX;
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
       ofStyle currentStyle = ofGetStyle();
       currentStyle.bFill = true;
       currentStyle.bgColor.setHsb(0, 0, float(gray) / 255.0, float(alpha) / 255.0);
       ofSetStyle(currentStyle);
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
       ofBackground(gray);
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
       ofEllipse(x, y, width, height);
   };


   class p2iOSApp : public ofxiPhoneApp {
   public:
       void setup(){	
           // register touch events
           ofRegisterTouchEvents(this);
           
           // initialize the accelerometer
           ofxAccelerometer.setup();
           
           //iPhoneAlerts will be sent to this.
           ofxiPhoneAlerts.addListener(this);
           
           //If you want a landscape oreintation 
           //iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
           
           ofBackground(127,127,127);
           
           srand((unsigned)time(0));
       };
       void update() { };
       void draw() {
          
       };
       void exit() { };
      
      void touchDown(ofTouchEventArgs &touch) { };
      void touchMoved(ofTouchEventArgs &touch) { };
      void touchUp(ofTouchEventArgs &touch) { };
      void touchDoubleTap(ofTouchEventArgs &touch) { };
      void touchCancelled(ofTouchEventArgs &touch) { };
      
      void lostFocus() { };
      void gotFocus() { };
      void gotMemoryWarning() { };
      void deviceOrientationChanged(int newOrientation) { };
    };
}

#endif
