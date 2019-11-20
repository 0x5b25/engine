part of dart.ui;


class ImageExt extends NativeFieldWrapperClass2{

  String SayHello() native "ImageExt_SayHello";

  void UpdatePreservedStr(String val) native "ImageExt_UpdatePreservedStr";

  String GetPreservedStr() native "ImageExt_GetPreservedStr";

  void dispose() native "ImageExt_dispose";
}

ImageExt instantiateImageExt(){
  ImageExt ext;
  _instantiateImageExt((ImageExt result){
    ext = result;
  });

  return ext;
}

String _instantiateImageExt(void Function(ImageExt result) callback) native "instantiateImageExt";

