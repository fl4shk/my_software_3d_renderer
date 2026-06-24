#import std/macros
#
#macro genFixedPtType(
#  name: untyped,
#): untyped = 
#  result = nnkStmtList.newTree()
#  result.add newTree(nnkType)

type
  FixedPt*[IntT; Fw: static uint] {.bycopy,noinit.} = object
    data* {.noinit.}: IntT

proc fracWidth*[IntT; Fw: static uint](
  self: FixedPt[IntT, Fw]
): static uint {.noinit.} =
  Fw

proc `+`*(
  left: FixedPt,
  right: FixedPt,
): FixedPt =
  assert(left.Fw == right.Fw)
  result.data = left.data + right.data

proc `-`*(
  left: FixedPt,
  right: FixedPt,
): FixedPt =
  assert(left.Fw == right.Fw)
  result.data = left.data - right.data

proc `*`*(
  left: FixedPt,
  right: FixedPt,
): FixedPt =
  assert(left.Fw == right.Fw)
  #result.data = left.data - right.data
  result.data = (int64(left.data) * int64(right.data)) shr left.Fw

proc `/`*(
  left: FixedPt,
  right: FixedPt,
): FixedPt =
  assert(left.Fw == right.Fw)
  #result.data = left.data - right.data
  result.data = (int64(left.data) shl left.Fw) div int64(right.data)

#proc `fromInt`*[IntT; Fw: static uint](
#  toConv: IntT
#): FixedPt[IntT, Fw] {.noinit,used.} =
#  result.data = (toConv shl Fw)
#
#proc `toInt`*[IntT; Fw: static uint](
#  toConv: FixedPt[IntT, Fw]
#): IntT {.exportC,noinit,used.} =
#  result = toConv.data shr Fw
