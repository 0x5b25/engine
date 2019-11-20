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
  V(ImageExt, DrawToCanvas)    \
  V(ImageExt, dispose)

FOR_EACH_BINDING(DART_NATIVE_CALLBACK)

void ImageExt::dispose() {
  ClearDartWrapper();
}

void ImageExt::DrawToCanvas(
	const Canvas* canvas,
	double src_left,
	double src_top,
	double src_right,
	double src_bottom,
	double dst_left,
	double dst_top,
	double dst_right,
	double dst_bottom,
	const Paint& paint,
	const PaintData& paint_data
) {
	if (!bmp)
		return;
	if (!canvas)
		Dart_ThrowException(
			tonic::ToDart("Draw bitmap onto null canvas."));
	SkRect src = SkRect::MakeLTRB(src_left, src_top, src_right, src_bottom);
	SkRect dst = SkRect::MakeLTRB(dst_left, dst_top, dst_right, dst_bottom);
	canvas->canvas()->drawBitmapRect(*bmp, src, dst, paint.paint(),
		SkCanvas::kFast_SrcRectConstraint);
}

static void InstantiateImageExt(Dart_NativeArguments args){
    fml::RefPtr<ImageExt> imgExt = fml::MakeRefCounted<ImageExt>();

	SkBitmap* bmp = new SkBitmap();
	SkImageInfo info = SkImageInfo::Make
		(64,64 , SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kUnpremul_SkAlphaType);

	uint8_t* pixels = new uint8_t[64 * 64 * 4];

	bmp->installPixels(info, pixels, 64 * 4);

	for (int y = 0; y < 64; y++) {
		for (int x = 0; x < 64; x++) {
			int index = (y * 64 + x) * 4;
			if (x == y || x == 63 - y) {
				pixels[index] = 200;//r
				pixels[index + 1] = 100;//g
				pixels[index + 2] = 30;//b
				pixels[index + 3] = 220;//a
			}
			else {
				pixels[index] = 40;//r
				pixels[index + 1] = 120;//g
				pixels[index + 2] = 210;//b
				pixels[index + 3] = 100;//a
			}
		}
	}

	imgExt->pixelData = pixels;
	imgExt->bmp = bmp;

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