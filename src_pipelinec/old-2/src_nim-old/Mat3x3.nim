import PipelineCExtras
import Vec3

type
  Mat3x3*[T] {.bycopy,noinit.} = object
    m* {.noinit.}: array[3, array[3, T]]

proc `len2dX`*[T](
  self: Mat3x3[T],
): uint =
  uint(self.m[0].len)
proc `len2dY`*[T](
  self: Mat3x3[T],
): uint =
  uint(self.m.len)


template `+`*[T](
  left: Mat3x3[T],
  right: Mat3x3[T],
): Mat3x3[T] = 
  var ret {.noinit.}: Mat3x3[T]
  for j in myRange(0u, left.len2dY):
    for i in myRange(0u, left.len2dx):
      ret.m[j][i] = (
        left.m[j][i] + right.m[j][i]
      )
  ret

template `-`*[T](
  left: Mat3x3[T],
  right: Mat3x3[T],
): Mat3x3[T] = 
  var ret {.noinit.}: Mat3x3[T]

  for j in myRange(0u, left.len2dY):
    for i in myRange(0u, left.len2dx):
      ret.left.m[j][i] = (
        left.m[j][i] - right.m[j][i]
      )
  ret
template `*`*[T](
  left: Mat3x3[T],
  right: T,
): Mat3x3[T] = 
  var ret {.noinit.}: Mat3x3[T]
  for j in myRange(0u, left.len2dY):
    for i in myRange(0u, left.len2dx):
      ret.m[j][i] = (
        left.m[j][i] * right
      )
  ret

template `*`*[T](
  left: Mat3x3[T],
  right: Mat3x3[T],
): Mat3x3[T] =
  var ret {.noinit.}: Mat3x3[T]
  for j in myRange(0u, left.len2dY):
    for i in myRange(0u, left.len2dx):
      var sum: T
      for k in myRange(0u, left.len2dx):
        let temp_sum: T = left.m[j][k] * right.m[k][i]
        sum = sum + temp_sum;
      ret.m[j][i] = sum
  ret

