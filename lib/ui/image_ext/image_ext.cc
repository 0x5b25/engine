#include "flutter/lib/ui/image_ext/image_ext.h"

#include "flutter/fml/memory/ref_ptr.h"
#include "third_party/tonic/dart_binding_macros.h"
#include "third_party/tonic/dart_library_natives.h"
#include "third_party/tonic/dart_state.h"
#include "third_party/tonic/logging/dart_invoke.h"
#include "third_party/tonic/typed_data/typed_list.h"

namespace flutter{


std::string ImageExt::SayHello(){
    return "Hello from image extension!";
}

void ImageExt::UpdatePreservedStr(const std::string& val) {
  preservedVal = val;
}

std::string ImageExt::GetPreservedStr() {
  return preservedVal;
}

IMPLEMENT_WRAPPERTYPEINFO(ui, ImageExt);

#define FOR_EACH_BINDING(V) \
  V(ImageExt, SayHello)    \
  V(ImageExt, UpdatePreservedStr)    \
  V(ImageExt, GetPreservedStr)    \
  V(ImageExt, dispose)

FOR_EACH_BINDING(DART_NATIVE_CALLBACK)

void ImageExt::dispose() {
  ClearDartWrapper();
}


static void InstantiateImageExt(Dart_NativeArguments args){
    fml::RefPtr<ImageExt> imgExt = fml::MakeRefCounted<ImageExt>();

	Dart_Handle callback_handle = Dart_GetNativeArgument(args, 0);

	if (!Dart_IsClosure(callback_handle)) {
        Dart_SetReturnValue(args, tonic::ToDart("Callback must be a function"));
        return;
    }

	tonic::DartInvoke(callback_handle, {tonic::ToDart(imgExt)});
	//Dart_SetReturnValue(args, tonic::ToDart(imgExt));
}


void ImageExt::RegisterNatives(tonic::DartLibraryNatives* natives) {
  natives->Register({
      {"instantiateImageExt", InstantiateImageExt, 1, true},
  });
  natives->Register({FOR_EACH_BINDING(DART_REGISTER_NATIVE)});
}

}