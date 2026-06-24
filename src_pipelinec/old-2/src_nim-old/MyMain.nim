import FixedPt
import Vec3
import Mat3x3

#{.emit:["#pragma MAIN_MHZ myMain 200.0"].}
template `myMain`*(
  left {.bycopy.}: Mat3x3[FixedPt[int64, 32]],
  right {.bycopy.}: Mat3x3[FixedPt[int64, 32]],
): Mat3x3[FixedPt[int64, 32]] =
  #mkStaticNoinit(a, int)
  #staticVarNoinit a: Vec3[float]
  #var a: Vec3[FixedPt[int64, 32]]
  #for i in myRange(0, int(a.len)):
  #  a = a.setAt(i, FixedPt[int64, 32](data: int64(i)))
  #a.x = 3
  #a.y = 5
  #a.z = 9
  #echo a.len
  var ret: Mat3x3[FixedPt[int64, 32]]
  ret = left * right
  if ret.m[2][2].data == int64(3):
    ret.m[0][0].data = int64(7)
  ret
