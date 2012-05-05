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

#undef HALF_PI
#undef TWO_PI
#undef PI

#define null NULL

typedef bool boolean;

namespace p2iOS_user {
    void p2iOS_init();
    void setup();
    void draw();
}

namespace p2iOS
{
    
    ////////////////////////////////////////////////
    // Processing Symbols
    ////////////////////////////////////////////////
    
    // constants
    double TWO_PI = 6.28318530717958647693;
    double PI = 3.14159265358979323846;
    double HALF_PI = 1.57079632679489661923;
    
    // drawing state
   int width;
   int height;

    // event state
    int mouseX;
    int mouseY;
    
    
    ////////////////////////////////////////////////
    // Processing State 
    ////////////////////////////////////////////////
    
    // modes
    enum ColorSpace { RGB };
    class ColorMode {
    public:
        ColorSpace space;
        float range1;
        float range2;
        float range3;
        float range4;
    };
    ColorMode _colorMode;
    
    enum EllipseMode { CENTER };
    EllipseMode _ellipseMode;
    
    bool noLoopWasCalled = false;
    bool userWantsDrawLoop = true;
    bool ranUserSetup = false;
    
    ////////////////////////////////////////////////
    // Java implementations
    ////////////////////////////////////////////////
    
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
   // Processing APIs
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
 
    template <class T>
    T min(T a, T b) { return std::min(a, b); }
    
    float constrain(float value, float min, float max) {
        return std::min(max, std::max(min, value));
    }
    
    float map(float value, float low_in, float high_in, float low_out, float high_out) { return low_out + (high_out - low_out) * ((value - low_in) / (high_in - low_in)); }
    float norm(float value, float low, float high) { return map(value, low, high, 0., 1.); }
    
    /////////////////////////////////////////
    // Time
    /////////////////////////////////////////
    
    int second() { return ofGetSeconds(); }
    int minute() { return ofGetMinutes(); }
    int hour() { return ofGetHours(); }
    
   //=========================================
   // drawing state functions
   //=========================================

    void ellipseMode(EllipseMode mode) {
        _ellipseMode = mode;
    }
    
    // TODO does this apply only to 4 param color commands?
    void colorMode(ColorSpace space, float range1, float range2, float range3, float range4) {
        _colorMode.space = space;
        _colorMode.range1 = range1;
        _colorMode.range2 = range2;
        _colorMode.range3 = range3;
        _colorMode.range4 = range4;
    }
    
    void background(unsigned char gray) { ofBackground(gray); }
    void frameRate(int fps) { ofSetFrameRate(fps); }
    
    void fill(unsigned char gray, unsigned char alpha) {
        // TODO implement fill color state
        ofSetColor(gray, gray, gray, (alpha / _colorMode.range4) * 255);
    } 
    void fill(int gray) { ofSetColor(gray); }
    void noFill() { NSLog(@"p2iOS warning: noFill() is not implemented"); }
    
    void strokeWeight(float width) { NSLog(@"p2iOS warning: strokeWeight() is not implemented"); }
    
    void stroke(int gray, int alpha) { ofSetColor(gray, gray, gray, alpha); }
    void stroke(int gray) { ofSetColor(gray); }
    void noStroke() { NSLog(@"p2iOS warning: noStroke() is not implemented"); }
    
    void smooth() { ofEnableSmoothing(); }

    void pushMatrix() { ofPushMatrix(); }
    void popMatrix() { ofPopMatrix(); }
    void translate(float x, float y) { ofTranslate(x, y); }
    void rotate(float angle) { ofRotate(angle * 360.0 / TWO_PI); }
    
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
       switch(_ellipseMode) {
           case CENTER:
               ofEllipse(x - width/2., y - height/2., width, height);
               break;
       }
       
   };
    
    void bezier(float anchor1x, float anchor1y,
                float control1x, float control1y,
                float control2x, float control2y,
                float anchor2x, float anchor2y) {
        ofBezier(anchor1x, anchor1y, control1x, control1y, control2x, control2y, anchor2x, anchor2y);
    }

   class p2iOSApp : public ofxiPhoneApp {       
   public:
       void setup(){	
           ofRegisterTouchEvents(this);
           //ofxAccelerometer.setup();
           ofxiPhoneAlerts.addListener(this);
           
           //If you want a landscape oreintation 
           //iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
           
           // Processing default background is "light gray" http://processing.org/reference/background_.html
           ofBackground(192, 192, 192);
           
           // processing state init
           srand((unsigned)time(0));
           
           _ellipseMode = CENTER;
           
           _colorMode.space = RGB;
           _colorMode.range1 = 255;
           _colorMode.range2 = 255;
           _colorMode.range3 = 255;
           _colorMode.range4 = 255;
           
                      
       };
       void update() {       };
       void draw() {
           
           // run user setup in draw because often processing sketches draw in setup() and have no draw()
           if(!ranUserSetup)
           {
               
               p2iOS_user::p2iOS_init();
               
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
