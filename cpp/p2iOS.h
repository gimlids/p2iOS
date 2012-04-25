#ifndef P2IOS_H_
#define P2IOS_H_

#include <vector>

namespace p2iOS
{
   class p2iOSApp
   {
      
   };

   template <class T>
   class JavaArray
   {
   public:

      JavaArray(const int & size = 0) {
         shared_vector = new std::vector<T>(size);
         shared_reference_count = new int(1);
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

   private:
      // TODO put this stuff in a higher level automatic reference counting class
      std::vector<T> *shared_vector;
      unsigned int *shared_reference_count;
   };
}

#endif
