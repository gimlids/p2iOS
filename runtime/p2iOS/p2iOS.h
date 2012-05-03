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

#undef TWO_PI

namespace p2iOS_user {
    void p2iOS_init();
    void setup();
    void draw();
}

namespace p2iOS
{
    
    // constants
    float TWO_PI = 6.28318530717958647693;
    
    // drawing state
   int width;
   int height;

    // event state
    int mouseX;
    int mouseY;
    
    // modes
    bool noLoopWasCalled = false;
    bool userWantsDrawLoop = true;
    bool ranUserSetup = false;
    
   template <class T>
   class JavaArray
   {
   public:
       size_t length;
       
      JavaArray(const size_t & size = 0) {
          //NSLog(@"creating JavaArray with size %zu", size);
          shared_vector = new std::vector< std::tr1::shared_ptr< T > >(size);
          length = size;
         shared_reference_count = new size_t();
          *shared_reference_count = 1;
      };

      // does the default operator= call this?
      JavaArray(const JavaArray & other) {
          copy(other);
      }
       

       
       // http://stackoverflow.com/questions/2639017/calling-assignment-operator-in-copy-constructor
       JavaArray<T> & operator=(const JavaArray<T> & rhs)
       {
           copy(rhs);
           return *this;
       };

      ~JavaArray() {
          //NSLog(@"decrementing reference_count from %zu", *shared_reference_count);
         (*shared_reference_count)--;
         if(*shared_reference_count == 0)
         {
             //NSLog(@"   deleting a shared_vector with size %zu", shared_vector->size());
             delete(shared_reference_count);
            delete(shared_vector);
         }
          // FIXME need to implement this for better karma ...
      };


      T & operator[](const size_t & index) {
          //NSLog(@"enter operator[], index = %zu, vector size = %zu", index, shared_vector->size());
          std::tr1::shared_ptr<T> item_ptr = (*shared_vector)[index];
          if (item_ptr.get() == NULL) {
              (*shared_vector)[index] = std::tr1::shared_ptr<T>(new T());
          }
         return * (*shared_vector)[index];
      };

   private:
       void copy(const JavaArray<T> & other) {
           length = other.length;
           shared_vector = other.shared_vector;
           shared_reference_count = other.shared_reference_count;
           (*shared_reference_count)++;
           //NSLog(@"copied JavaArray of size %zu, reference count is %zu", length, *shared_reference_count);
       };
       
      // TODO put this stuff in a higher level automatic reference counting class
       std::vector< std::tr1::shared_ptr< T > > *shared_vector;
      size_t *shared_reference_count;
   };
    
   //==========================================
   // initialization functions
   //==========================================

   void size(int _width, int _height)
   {
       ofSetWindowShape(_width, _height);
       width = _width;
       height = _height;
   };

    void noLoop() { /*noLoopWasCalled = true;*/ NSLog(@"p2iOS warning: noLoop() is not implemented"); }
   
    //===========================================
   // math
   //===========================================

   float sqrt(float value) { return sqrtf(value); }
   float atan2(float y, float x) { return atan2f(y, x); }
   float cos(float angle) { return cosf(angle); }
   float sin(float angle) { return sinf(angle); }
   float random(float low, float high) { return low + (high - low) * (float)rand()/(float)RAND_MAX; }
   float random(float high) { return random(0, high); }
   float radians(float degrees) { return degrees * TWO_PI / 360.0; }
   float dist(float x1, float y1, float x2, float y2) { return sqrtf((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)); }
 
   //=========================================
   // drawing state functions
   //=========================================

    void background(unsigned char gray) { ofBackground(gray); }
    void frameRate(int fps) { ofSetFrameRate(fps); }
    
    void fill(unsigned char gray, unsigned char alpha) { ofSetColor(gray, gray, gray, alpha); } // TODO implement fill color state
    void fill(int gray) { ofSetColor(gray); }
    
    void stroke(int gray) { ofSetColor(gray); }
    void noStroke() { NSLog(@"p2ios warning: noStroke() is not implemented"); }
    void smooth() { ofEnableSmoothing(); }

   //==========================================
   // drawing functions
   //==========================================

   void line(float x1, float y1, float x2, float y2)
    {
        ofLine(x1, y1, x2, y2);
    }
    
    void rect(float x, float y, float width, float height)
    {
        ofRect(x, y, width, height);
    }
    
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
           
           //ofBackground(127,127,127);
           
           srand((unsigned)time(0));
           
           p2iOS_user::p2iOS_init();
                      
       };
       void update() {       };
       void draw() {
           
           // run user setup in draw because often processing sketches draw in setup() and have no draw()
           if(!ranUserSetup)
           {
               p2iOS_user::setup();
               ranUserSetup = true;
               // FIXME let user do only one draw loop and keep showing the result
           }
           
           if(userWantsDrawLoop)
           {
               p2iOS_user::draw();
               if(noLoopWasCalled)
                   userWantsDrawLoop = false;
           }
       };
       void exit() { };
      
      void touchDown(ofTouchEventArgs &touch) { 
          p2iOS::mouseX = touch.x; // does processing have a touch API?
          p2iOS::mouseY = touch.y;
      };
       void touchMoved(ofTouchEventArgs &touch) {  
           p2iOS::mouseX = touch.x; // does processing have a touch API?
           p2iOS::mouseY = touch.y;
       };
       void touchUp(ofTouchEventArgs &touch) {  
           p2iOS::mouseX = touch.x; // does processing have a touch API?
           p2iOS::mouseY = touch.y;
       };
      void touchDoubleTap(ofTouchEventArgs &touch) { };
      void touchCancelled(ofTouchEventArgs &touch) { };
      
      void lostFocus() { };
      void gotFocus() { };
      void gotMemoryWarning() { };
      void deviceOrientationChanged(int newOrientation) { };
    };
}

#endif
