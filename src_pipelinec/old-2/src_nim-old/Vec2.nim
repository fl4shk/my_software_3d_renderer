type
  Vec2*[T] {.bycopy,noinit.} = object
    x* {.noinit.}, y* {.noinit.}: T

#proc `operator +`(
#  left: Vec2I32,
#  right: Vec2I32,
#): Vec2I32 {.exportc,noconv.} = 
#  Vec2I32(x: left.x + right.x, y: left.y + right.y)


proc `+`*[T](
  left: Vec2[T],
  right: Vec2[T],
): Vec2[T] {.noinit.} = 
  Vec2[T](x: left.x + right.x, y: left.y + right.y)

proc `-`*[T](
  left: Vec2[T],
  right: Vec2[T],
): Vec2[T] {.noinit.} =
  Vec2[T](x: left.x - right.x, y: left.y - right.y)

proc `*`*[T](
  left: Vec2[T],
  right: T,
): Vec2[T] {.noinit.} =
  Vec2[T](x: left.x * right, y: left.y * right)

proc `/`*[T](
  left: Vec2[T],
  right: T,
): Vec2[T] {.noinit.} =
  var temp {.noinit.}: Vec2[T] #{.static.}
  temp = Vec2[T](
    x: T(left.x) div T(right),
    y: T(left.y) div T(right)
  ) 
  #temp.x = left.x div right
  #temp.y = left.y div right
  return temp

proc dot*[T](
  left: Vec2[T],
  right: Vec2[T],
): T {.noinit.} = 
  T(left.x * right.x + left.y * right.y)

