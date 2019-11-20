#pragma once

#include <string>

#include "flutter/lib/ui/dart_wrapper.h"
#include "third_party/dart/runtime/include/dart_api.h"


using tonic::DartPersistentValue;

namespace tonic {
class DartLibraryNatives;
}  // namespace tonic


namespace flutter
{
    
    class ImageExt : public RefCountedDartWrappable<ImageExt> {
        DEFINE_WRAPPERTYPEINFO();
      std::string preservedVal = "Not changed";
    public:

        std::string SayHello();

		void UpdatePreservedStr(const std::string& val);

		std::string GetPreservedStr();


        void dispose();

        static void RegisterNatives(tonic::DartLibraryNatives* natives);

    };



} // namespace flutter
