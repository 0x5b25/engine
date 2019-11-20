part of dart.ui;


class ImageExt extends NativeFieldWrapperClass2{

  String SayHello() native 'ImageExt_SayHello';

  void UpdatePreservedStr(String val) native 'ImageExt_UpdatePreservedStr';

  String GetPreservedStr() native 'ImageExt_GetPreservedStr';

  void dispose() native 'ImageExt_dispose';


  void DrawToCanvas(Canvas canvas, Rect src, Rect dst, Paint paint) {
    assert(canvas != null); // image is checked on the engine side
    assert(_rectIsValid(src));
    assert(_rectIsValid(dst));
    assert(paint != null);
    _DrawToCanvas(canvas,
                   src.left,
                   src.top,
                   src.right,
                   src.bottom,
                   dst.left,
                   dst.top,
                   dst.right,
                   dst.bottom,
                   paint._objects,
                   paint._data);
  }
  void _DrawToCanvas(Canvas canvas,
                      double srcLeft,
                      double srcTop,
                      double srcRight,
                      double srcBottom,
                      double dstLeft,
                      double dstTop,
                      double dstRight,
                      double dstBottom,
                      List<dynamic> paintObjects,
                      ByteData paintData) native 'ImageExt_DrawToCanvas';

}

ImageExt instantiateImageExt(){
  ImageExt ext;
  _instantiateImageExt((ImageExt result){
    ext = result;
  });

  return ext;
}

String _instantiateImageExt(void Function(ImageExt result) callback) native 'instantiateImageExt';

