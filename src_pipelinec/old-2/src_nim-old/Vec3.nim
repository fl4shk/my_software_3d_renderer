type
  Vec3*[T] {.bycopy,noinit.} = object
    x* {.noinit.}: T
    y* {.noinit.}: T
    z* {.noinit.}: T

proc `len`*[T](
  self: Vec3[T]
): uint = 3

#proc `operator +`(
#  left: Vec3I32,
#  right: Vec3I32,
#): Vec3I32 {.exportc,noconv.} = 
#  Vec3I32(x: left.x + right.x, y: left.y + right.y)

proc `setAt`*[T](
  self: Vec3[T],
  idx: uint,
  nElem: T,
): Vec3[T] = 
  result = self
  if idx == 0:
    result.x = nElem
  elif idx == 1:
    result.y = nElem
  else:
    result.z = nElem 

proc `getAt`*[T](
  self: Vec3[T],
  idx: Natural
): T =
  if idx == 0:
    result = self.x
  elif idx == 1:
    result = self.y
  else:
    result = self.z

proc `+`*[T](
  left: Vec3[T],
  right: Vec3[T],
): Vec3[T] {.noinit.} = 
  Vec3[T](
    x=left.x + right.x,
    y=left.y + right.y,
    z=left.z + right.z,
  )

proc `-`*[T](
  left: Vec3[T],
  right: Vec3[T],
): Vec3[T] {.noinit.} =
  Vec3[T](
    x=left.x - right.x,
    y=left.y - right.y,
    z=left.z - right.z,
  )

proc `*`*[T](
  left: Vec3[T],
  right: T,
): Vec3[T] {.noinit.} =
  Vec3[T](
    x=left.x * right,
    y=left.y * right,
    z=left.z * right,
  )

proc `/`*[T](
  left: Vec3[T],
  right: T,
): Vec3[T] {.noinit.} =
  #var temp {.noinit.}: Vec3[T] #{.static.}
  result = Vec3[T](
    x=T(left.x) div T(right),
    y=T(left.y) div T(right),
    z=T(left.z) div T(right)
  ) 
  #temp.x = left.x div right
  #temp.y = left.y div right
  #return temp

proc dot*[T](
  left: Vec3[T],
  right: Vec3[T],
): T {.noinit.} = 
  T(
    (
      left.x * right.x
    ) + (
      left.y * right.y 
    ) + (
      left.z * right.z
    )
  )


#var a = Vec3[int](
#  
#)
