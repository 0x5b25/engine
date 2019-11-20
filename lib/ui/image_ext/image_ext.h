#pragma once

#include <string>
#include <stdint.h>

#include "flutter/lib/ui/dart_wrapper.h"
#include "flutter/lib/ui/dart_wrapper.h"
#include "flutter/lib/ui/painting/canvas.h"

#include "third_party/dart/runtime/include/dart_api.h"

#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkRefCnt.h"
#include "third_party/skia/include/utils/SkShadowUtils.h"


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
		SkBitmap* bmp;
		uint8_t* pixelData = nullptr;

		~ImageExt() { delete pixelData; delete bmp; }

        std::string SayHello();

		void UpdatePreservedStr(const std::string& val);

		std::string GetPreservedStr();

		void DrawToCanvas(
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
		);

        void dispose();

        static void RegisterNatives(tonic::DartLibraryNatives* natives);

    };



} // namespace flutter
