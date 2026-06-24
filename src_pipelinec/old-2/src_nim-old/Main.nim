import FixedPt
import PipelineCExtras
import NimToPipelineC

import Vec3
import Mat3x3
import MyMain
import std/macros

#iterator crange(a, b: int): int = 
#  var i = a
#  {.emit:["for (;", i, " < ", b, "; ++", i, ") {"].}
#  yield i
#  {.emit:"}".}

#proc main() = 
#  const Fw: uint = 32
#  let a = FixedPt[int64, Fw](data: 0x3000)
#  let b = FixedPt[int64, Fw](data: 0x1000)
#  let c = a * b
#  let d = a / b
#  let arr = [a, b, c, d]
#
#  for i in myRange(0, arr.len):
#    echo arr[i].data
#
#main()
  
#for i {.inject.} in 0 ..< arr.len:
#  echo arr[i].data

#for item in arr:
#  echo item
proc main() = 
  #mkNonPtr(left, Mat3x3[FixedPt[int64, 32]])
  #mkNonPtr(right, Mat3x3[FixedPt[int64, 32]])
  #mkNonPtr(output, Mat3x3[FixedPt[int64, 32]])
  #output = myMain(
  #  left=left,
  #  right=right
  #)
  #dumpTree(
  #block:
  #const
  #  left = Mat3x3[int]
  #  right = Mat3x3[int]
  #cexpr(left.m[0][0] == right.m[0][0])
  dumpTree:
    var left: Mat3x3[int]
    var right: Mat3x3[int]
    if left.m[0][0] == right.m[0][0]:
      discard
    elif left.m[1][0] == right.m[1][0]:
      left.m[0][0] = 3
    else:
        discard
    type Jkl[T] = object
      data*: T
    type Asdf[T] = object
      a*: Jkl[T]
  #celif 9 == 9:
  #  discard
  #celse:
  #  discard
  #)
    
#dumpTree:
#  type Jkl[T] = object
#    data*: T
#  type Asdf[T] = object
#    a*: Jkl[T]
#echo toPipelineC(main())
